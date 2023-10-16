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

#ifndef HOST_SERVER_H
#define HOST_SERVER_H

#include "BuildConfig/build_config.h"
#include "Base/filesystem.hpp"
#include "Base/net/tcp_server.h"
#include "Base/peer/server_authenticator_manager.h"
#include "Common/http_file_downloader.h"
#include "Common/update_checker.h"
#include "Host/Core/router_controller.h"
#include "Host/Core/user_session_manager.h"
#include "Host/Core/system_settings.h"

namespace base {
class FilePathWatcher;
class TaskRunner;
class WaitableTimer;
} // namespace base

namespace host {

class Server
    : public base::TcpServer::Delegate,
      public RouterController::Delegate,
      public base::ServerAuthenticatorManager::Delegate,
      public UserSessionManager::Delegate,
      public common::UpdateChecker::Delegate,
      public common::HttpFileDownloader::Delegate
{
public:
    explicit Server(std::shared_ptr<base::TaskRunner> task_runner);
    ~Server() override;

    void start();
    void setSessionEvent(base::win::SessionStatus status, base::SessionId session_id);
    void setPowerEvent(uint32_t power_event);

protected:
    // net::TcpServer::Delegate implementation.
    void onNewConnection(std::unique_ptr<base::TcpChannel> channel) override;

    // RouterController::Delegate implementation.
    void onRouterStateChanged(const proto::internal::RouterState& router_state) override;
    void onHostIdAssigned(const std::string& session_name, base::HostId host_id) override;
    void onClientConnected(std::unique_ptr<base::TcpChannel> channel) override;

    // base::AuthenticatorManager::Delegate implementation.
    void onNewSession(base::ServerAuthenticatorManager::SessionInfo&& session_info) override;

    // UserSessionManager::Delegate implementation.
    void onHostIdRequest(const std::string& session_name) override;
    void onResetHostId(base::HostId host_id) override;
    void onUserListChanged() override;

    // common::UpdateChecker::Delegate implementation.
    void onUpdateCheckedFinished(const base::ByteArray& result) override;

    // common::HttpFileDownloader::Delegate implementation.
    void onFileDownloaderError(int error_code) override;
    void onFileDownloaderCompleted() override;
    void onFileDownloaderProgress(int percentage) override;

private:
    void startAuthentication(std::unique_ptr<base::TcpChannel> channel);
    void addFirewallRules();
    void deleteFirewallRules();
    void updateConfiguration(const ghc::filesystem::path& path, bool error);
    void reloadUserList();
    void connectToRouter();
    void disconnectFromRouter();
    void checkForUpdates();

    std::shared_ptr<base::TaskRunner> task_runner_;
    std::unique_ptr<base::WaitableTimer> update_timer_;

    std::unique_ptr<base::FilePathWatcher> settings_watcher_;
    SystemSettings settings_;

    // Accepts incoming network connections.
    std::unique_ptr<base::TcpServer> server_;
    std::unique_ptr<RouterController> router_controller_;
    std::unique_ptr<base::ServerAuthenticatorManager> authenticator_manager_;
    std::unique_ptr<UserSessionManager> user_session_manager_;

    std::unique_ptr<common::UpdateChecker> update_checker_;
    std::unique_ptr<common::HttpFileDownloader> update_downloader_;

    DISALLOW_COPY_AND_ASSIGN(Server);
};

} // namespace host

#endif // HOST_SERVER_H
