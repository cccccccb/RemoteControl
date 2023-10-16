//
// Aspia Project
// Copyright (C) 2016-2023 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "Host/Core/server.h"

#include "Base/filesystem.hpp"
#include "Base/logging.h"
#include "Base/task_runner.h"
#include "Base/waitable_timer.h"
#include "Base/crypto/random.h"
#include "Base/files/base_paths.h"
#include "Base/files/file_path_watcher.h"
#include "Base/net/tcp_channel.h"
#include "Common/update_info.h"
#include "Host/Core/client_session.h"
#include "Host/Core/win/updater_launcher.h"

#if defined(OS_WIN)
#include "Base/files/file_util.h"
#include "Base/net/firewall_manager.h"
#include "Base/win/process_util.h"
#endif // defined(OS_WIN)

namespace host {

namespace {

const wchar_t kFirewallRuleName[] = L"Aspia Host Service";
const wchar_t kFirewallRuleDecription[] = L"Allow incoming TCP connections";

} // namespace

//--------------------------------------------------------------------------------------------------
Server::Server(std::shared_ptr<base::TaskRunner> task_runner)
    : task_runner_(std::move(task_runner))
{
    LOG(LS_INFO) << "Ctor";
    DCHECK(task_runner_);
}

//--------------------------------------------------------------------------------------------------
Server::~Server()
{
    LOG(LS_INFO) << "Dtor";
    LOG(LS_INFO) << "Stopping the server...";

    settings_watcher_.reset();
    authenticator_manager_.reset();
    user_session_manager_.reset();
    server_.reset();

    deleteFirewallRules();

    LOG(LS_INFO) << "Server is stopped";
}

//--------------------------------------------------------------------------------------------------
void Server::start()
{
    if (server_)
    {
        DLOG(LS_WARNING) << "An attempt was start an already running server";
        return;
    }

    LOG(LS_INFO) << "Starting the host server";

    ghc::filesystem::path settings_file = settings_.filePath();
    LOG(LS_INFO) << "Configuration file path: " << settings_file;

    std::error_code ignored_code;
    if (!ghc::filesystem::exists(settings_file, ignored_code))
    {
        LOG(LS_WARNING) << "Configuration file does not exist";
    }

    update_timer_ = std::make_unique<base::WaitableTimer>(
        base::WaitableTimer::Type::REPEATED, task_runner_);
    update_timer_->start(std::chrono::minutes(5), std::bind(&Server::checkForUpdates, this));

    settings_watcher_ = std::make_unique<base::FilePathWatcher>(task_runner_);
    settings_watcher_->watch(settings_file, false,
        std::bind(&Server::updateConfiguration, this, std::placeholders::_1, std::placeholders::_2));

    authenticator_manager_ = std::make_unique<base::ServerAuthenticatorManager>(task_runner_, this);

    user_session_manager_ = std::make_unique<UserSessionManager>(task_runner_);
    user_session_manager_->start(this);

    reloadUserList();
    addFirewallRules();

    server_ = std::make_unique<base::TcpServer>();
    server_->start(u"0.0.0.0", settings_.tcpPort(), this);

    if (settings_.isRouterEnabled())
    {
        LOG(LS_INFO) << "Router enabled";
        connectToRouter();
    }

    LOG(LS_INFO) << "Host server is started successfully";
}

//--------------------------------------------------------------------------------------------------
void Server::setSessionEvent(base::win::SessionStatus status, base::SessionId session_id)
{
    LOG(LS_INFO) << "Session event (status: " << static_cast<int>(status)
                 << " session_id: " << session_id << ")";

    if (user_session_manager_)
    {
        user_session_manager_->onUserSessionEvent(status, session_id);
    }
    else
    {
        LOG(LS_WARNING) << "Invalid user session manager";
    }
}

//--------------------------------------------------------------------------------------------------
void Server::setPowerEvent(uint32_t power_event)
{
#if defined(OS_WIN)
    LOG(LS_INFO) << "Power event: " << power_event;

    switch (power_event)
    {
        case PBT_APMSUSPEND:
        {
            disconnectFromRouter();
        }
        break;

        case PBT_APMRESUMEAUTOMATIC:
        {
            if (settings_.isRouterEnabled())
            {
                LOG(LS_INFO) << "Router enabled";
                connectToRouter();
            }
        }
        break;

        default:
            // Ignore other events.
            break;
    }
#endif // defined(OS_WIN)
}

//--------------------------------------------------------------------------------------------------
void Server::onNewConnection(std::unique_ptr<base::TcpChannel> channel)
{
    LOG(LS_INFO) << "New DIRECT connection";
    startAuthentication(std::move(channel));
}

//--------------------------------------------------------------------------------------------------
void Server::onRouterStateChanged(const proto::internal::RouterState& router_state)
{
    LOG(LS_INFO) << "Router state changed";
    user_session_manager_->onRouterStateChanged(router_state);
}

//--------------------------------------------------------------------------------------------------
void Server::onHostIdAssigned(const std::string& session_name, base::HostId host_id)
{
    LOG(LS_INFO) << "New host ID assigned: " << host_id << " ('" << session_name << "')";
    user_session_manager_->onHostIdChanged(session_name, host_id);
}

//--------------------------------------------------------------------------------------------------
void Server::onClientConnected(std::unique_ptr<base::TcpChannel> channel)
{
    LOG(LS_INFO) << "New RELAY connection";
    startAuthentication(std::move(channel));
}

//--------------------------------------------------------------------------------------------------
void Server::onNewSession(base::ServerAuthenticatorManager::SessionInfo&& session_info)
{
    LOG(LS_INFO) << "New client session";

    if (session_info.version >= base::Version(2, 6, 0))
    {
        LOG(LS_INFO) << "Using channel id support";
        session_info.channel->setChannelIdSupport(true);
    }

    base::Version host_version(REMOTECONTROL_VERSION_MAJOR, REMOTECONTROL_VERSION_MINOR,
                               REMOTECONTROL_VERSION_PATCH, GIT_COMMIT_COUNT);
    if (host_version > session_info.version)
    {
        LOG(LS_WARNING) << "Version mismatch (host: " << host_version.toString()
                        << " client: " << session_info.version.toString();
    }

    std::unique_ptr<ClientSession> session = ClientSession::create(
        static_cast<proto::SessionType>(session_info.session_type),
        std::move(session_info.channel),
        task_runner_);

    if (session)
    {
        session->setVersion(session_info.version);
        session->setComputerName(session_info.computer_name);
        session->setUserName(session_info.user_name);
    }
    else
    {
        LOG(LS_WARNING) << "Invalid client session";
        return;
    }

    if (user_session_manager_)
    {
        user_session_manager_->onClientSession(std::move(session));
    }
    else
    {
        LOG(LS_WARNING) << "Invalid user session manager";
    }
}

//--------------------------------------------------------------------------------------------------
void Server::onHostIdRequest(const std::string& session_name)
{
    if (!router_controller_)
    {
        LOG(LS_WARNING) << "No router controller";
        return;
    }

    LOG(LS_INFO) << "New host ID request for session name: '" << session_name << "'";
    router_controller_->hostIdRequest(session_name);
}

//--------------------------------------------------------------------------------------------------
void Server::onResetHostId(base::HostId host_id)
{
    if (!router_controller_)
    {
        LOG(LS_WARNING) << "No router controller";
        return;
    }

    LOG(LS_INFO) << "Reset host ID for: " << host_id;
    router_controller_->resetHostId(host_id);
}

//--------------------------------------------------------------------------------------------------
void Server::onUserListChanged()
{
    LOG(LS_INFO) << "User list changed";
    reloadUserList();
}

//--------------------------------------------------------------------------------------------------
void Server::onUpdateCheckedFinished(const base::ByteArray& result)
{
    common::UpdateInfo update_info = common::UpdateInfo::fromXml(result);
    if (!update_info.isValid())
    {
        LOG(LS_INFO) << "No valid update info";
    }
    else
    {
        base::Version current_version(
            REMOTECONTROL_VERSION_MAJOR, REMOTECONTROL_VERSION_MINOR, REMOTECONTROL_VERSION_PATCH);
        base::Version new_version = update_info.version();

        if (new_version > current_version)
        {
            update_downloader_ = std::make_unique<common::HttpFileDownloader>();
            update_downloader_->start(update_info.url(), task_runner_, this);
        }
        else
        {
            LOG(LS_INFO) << "No available updates";
        }
    }

    task_runner_->deleteSoon(std::move(update_checker_));
}

//--------------------------------------------------------------------------------------------------
void Server::onFileDownloaderError(int error_code)
{
    LOG(LS_WARNING) << "Unable to download update: " << error_code;
    task_runner_->deleteSoon(std::move(update_downloader_));
}

//--------------------------------------------------------------------------------------------------
void Server::onFileDownloaderCompleted()
{
    //! @todo remove it~
#if defined(OS_WIN)
    std::error_code error_code;
    ghc::filesystem::path file_path = ghc::filesystem::temp_directory_path(error_code);
    if (error_code)
    {
        LOG(LS_WARNING) << "Unable to get temp directory: "
                        << base::utf16FromLocal8Bit(error_code.message());
    }
    else
    {
        file_path.append("aspia_host_" + base::toHex(base::Random::byteArray(16)) + ".msi");

        if (!base::writeFile(file_path, update_downloader_->data()))
        {
            LOG(LS_WARNING) << "Unable to write file '" << file_path << "'";
        }
        else
        {
            std::u16string arguments;

            arguments += u"/i "; // Normal install.
            arguments += file_path.u16string(); // MSI package file.
            arguments += u" /qn"; // No UI during the installation process.

            if (base::win::createProcess(u"msiexec",
                                         arguments,
                                         base::win::ProcessExecuteMode::ELEVATE))
            {
                LOG(LS_INFO) << "Update process started (cmd: " << arguments << ")";
            }
            else
            {
                LOG(LS_WARNING) << "Unable to create update process (cmd: " << arguments << ")";

                // If the update fails, delete the temporary file.
                if (!ghc::filesystem::remove(file_path, error_code))
                {
                    LOG(LS_WARNING) << "Unable to remove installer file: "
                                    << base::utf16FromLocal8Bit(error_code.message());
                }
            }
        }
    }
#endif // defined(OS_WIN)

    task_runner_->deleteSoon(std::move(update_downloader_));
}

//--------------------------------------------------------------------------------------------------
void Server::onFileDownloaderProgress(int percentage)
{
    LOG(LS_INFO) << "Update downloading progress: " << percentage << "%";
}

//--------------------------------------------------------------------------------------------------
void Server::startAuthentication(std::unique_ptr<base::TcpChannel> channel)
{
    LOG(LS_INFO) << "Start authentication";

    static const size_t kReadBufferSize = 1 * 1024 * 1024; // 1 Mb.

    channel->setReadBufferSize(kReadBufferSize);
    channel->setNoDelay(true);

    if (authenticator_manager_)
    {
        authenticator_manager_->addNewChannel(std::move(channel));
    }
    else
    {
        LOG(LS_WARNING) << "Invalid authenticator manager";
    }
}

//--------------------------------------------------------------------------------------------------
void Server::addFirewallRules()
{
#if defined(OS_WIN)
    ghc::filesystem::path file_path;
    if (!base::BasePaths::currentExecFile(&file_path))
    {
        LOG(LS_WARNING) << "currentExecFile failed";
        return;
    }

    base::FirewallManager firewall(file_path);
    if (!firewall.isValid())
    {
        LOG(LS_WARNING) << "Invalid firewall manager";
        return;
    }

    uint16_t tcp_port = settings_.tcpPort();

    if (!firewall.addTcpRule(kFirewallRuleName, kFirewallRuleDecription, tcp_port))
    {
        LOG(LS_WARNING) << "Unable to add firewall rule";
        return;
    }

    LOG(LS_INFO) << "Rule is added to the firewall (TCP " << tcp_port << ")";
#endif // defined(OS_WIN)
}

//--------------------------------------------------------------------------------------------------
void Server::deleteFirewallRules()
{
#if defined(OS_WIN)
    ghc::filesystem::path file_path;
    if (!base::BasePaths::currentExecFile(&file_path))
    {
        LOG(LS_WARNING) << "currentExecFile failed";
        return;
    }

    base::FirewallManager firewall(file_path);
    if (!firewall.isValid())
    {
        LOG(LS_WARNING) << "Invalid firewall manager";
        return;
    }

    LOG(LS_INFO) << "Delete firewall rule";
    firewall.deleteRuleByName(kFirewallRuleName);
#endif // defined(OS_WIN)
}

//--------------------------------------------------------------------------------------------------
void Server::updateConfiguration(const ghc::filesystem::path& path, bool error)
{
    LOG(LS_INFO) << "Configuration file change detected";

    if (!error)
    {
        ghc::filesystem::path settings_file_path = settings_.filePath();
        std::error_code ignored_error;

        // While writing the configuration, the file may be empty for a short time. The
        // configuration monitor has time to detect this, but we must not load an empty
        // configuration.
        if (ghc::filesystem::file_size(settings_file_path, ignored_error) <= 0)
        {
            LOG(LS_INFO) << "Configuration file is empty. Configuration update skipped";
            return;
        }

        DCHECK_EQ(path, settings_file_path);

        // Synchronize the parameters from the file.
        settings_.sync();

        // Apply settings for user sessions BEFORE reloading the user list.
        user_session_manager_->onSettingsChanged();

        // Reload user lists.
        reloadUserList();

        // If a controller instance already exists.
        if (router_controller_)
        {
            LOG(LS_INFO) << "Has router controller";

            if (settings_.isRouterEnabled())
            {
                LOG(LS_INFO) << "Router enabled";

                // Check if the connection parameters have changed.
                if (router_controller_->address() != settings_.routerAddress() ||
                    router_controller_->port() != settings_.routerPort() ||
                    router_controller_->publicKey() != settings_.routerPublicKey())
                {
                    // Reconnect to the router with new parameters.
                    LOG(LS_INFO) << "Router parameters have changed";
                    connectToRouter();
                }
                else
                {
                    LOG(LS_INFO) << "Router parameters without changes";
                }
            }
            else
            {
                // Destroy the controller.
                LOG(LS_INFO) << "The router is now disabled";
                router_controller_.reset();

                proto::internal::RouterState router_state;
                router_state.set_state(proto::internal::RouterState::DISABLED);
                user_session_manager_->onRouterStateChanged(router_state);
            }
        }
        else
        {
            LOG(LS_INFO) << "No router controller";

            if (settings_.isRouterEnabled())
            {
                LOG(LS_INFO) << "Router enabled";
                connectToRouter();
            }
        }
    }
    else
    {
        LOG(LS_WARNING) << "Error detected";
    }
}

//--------------------------------------------------------------------------------------------------
void Server::reloadUserList()
{
    LOG(LS_INFO) << "Reloading user list";

    // Read the list of regular users.
    std::unique_ptr<base::UserList> user_list(settings_.userList().release());

    // Add a list of one-time users to the list of regular users.
    user_list->merge(*user_session_manager_->userList());

    // Updating the list of users.
    authenticator_manager_->setUserList(std::move(user_list));
}

//--------------------------------------------------------------------------------------------------
void Server::connectToRouter()
{
    LOG(LS_INFO) << "Connecting to router...";

    // Destroy the previous instance.
    router_controller_.reset();

    // Fill the connection parameters.
    RouterController::RouterInfo router_info;
    router_info.address = settings_.routerAddress();
    router_info.port = settings_.routerPort();
    router_info.public_key = settings_.routerPublicKey();

    // Connect to the router.
    router_controller_ = std::make_unique<RouterController>(task_runner_);
    router_controller_->start(router_info, this);
}

//--------------------------------------------------------------------------------------------------
void Server::disconnectFromRouter()
{
    LOG(LS_INFO) << "Disconnect from router";

    if (router_controller_)
    {
        router_controller_.reset();
        LOG(LS_INFO) << "Disconnected from router";
    }
    else
    {
        LOG(LS_INFO) << "No router controller";
    }
}

//--------------------------------------------------------------------------------------------------
void Server::checkForUpdates()
{
#if defined(OS_WIN)
    int64_t last_timepoint = settings_.lastUpdateCheck();
    auto now = std::chrono::system_clock::now();
    auto current_timepoint = std::chrono::system_clock::to_time_t(now);

    LOG(LS_INFO) << "Last timepoint: " << last_timepoint << ", current: " << current_timepoint;

    int64_t time_diff = current_timepoint - last_timepoint;
    if (time_diff <= 0)
    {
        settings_.setLastUpdateCheck(current_timepoint);
        return;
    }

    static const int64_t kSecondsPerMinute = 60;
    static const int64_t kMinutesPerHour = 60;
    static const int64_t kHoursPerDay = 24;

    int64_t days = time_diff / kSecondsPerMinute / kMinutesPerHour / kHoursPerDay;
    if (days < 1)
        return;

    if (days < settings_.updateCheckFrequency())
    {
        LOG(LS_INFO) << "Not enough time has elapsed since the previous check for updates";
        return;
    }

    settings_.setLastUpdateCheck(current_timepoint);

    LOG(LS_INFO) << "Start checking for updates";

    update_checker_ = std::make_unique<common::UpdateChecker>();

    update_checker_->setUpdateServer(settings_.updateServer());
    update_checker_->setPackageName("host");

    update_checker_->start(task_runner_, this);
#endif // defined(OS_WIN)
}

} // namespace host
