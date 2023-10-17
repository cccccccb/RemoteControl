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

#include "Client/Core/client.h"

#include "Base/logging.h"
#include "Base/task_runner.h"
#include "Base/strings/strcat.h"
#include "Base/strings/string_number_conversions.h"
#include "Client/Core/status_window_proxy.h"

#if defined(OS_MAC)
#include "Base/mac/app_nap_blocker.h"
#endif // defined(OS_MAC)

namespace client {

//--------------------------------------------------------------------------------------------------
Client::Client(std::shared_ptr<base::TaskRunner> io_task_runner)
    : io_task_runner_(std::move(io_task_runner))
{
    qInfo() << "Ctor";
    DCHECK(io_task_runner_);

#if defined(OS_MAC)
    base::addAppNapBlock();
#endif // defined(OS_MAC)
}

//--------------------------------------------------------------------------------------------------
Client::~Client()
{
    qInfo() << "Dtor";
    DCHECK(io_task_runner_->belongsToCurrentThread());
    stop();

#if defined(OS_MAC)
    base::releaseAppNapBlock();
#endif // defined(OS_MAC)
}

//--------------------------------------------------------------------------------------------------
void Client::start(const Config& config)
{
    DCHECK(io_task_runner_->belongsToCurrentThread());
    DCHECK(status_window_proxy_);

    if (state_ != State::CREATED)
    {
        qWarning() << "Client already started before";
        return;
    }

    config_ = config;
    state_ = State::STARTED;

    if (base::isHostId(config_.address_or_id))
    {
        qInfo() << "Starting RELAY connection";

        // Show the status window.
        status_window_proxy_->onStarted(config_.address_or_id);
    }
    else
    {
        qInfo() << "Starting DIRECT connection";

        // Show the status window.
        status_window_proxy_->onStarted(
            base::strCat({ config_.address_or_id, u":", base::numberToString16(config_.port) }));

        // Create a network channel for messaging.
        channel_ = std::make_unique<base::TcpChannel>();

        // Set the listener for the network channel.
        channel_->setListener(this);

        // Now connect to the host.
        channel_->connect(config_.address_or_id, config_.port);
    }
}

//--------------------------------------------------------------------------------------------------
void Client::stop()
{
    DCHECK(io_task_runner_->belongsToCurrentThread());

    if (state_ != State::STOPPPED)
    {
        qInfo() << "Stopping client...";
        state_ = State::STOPPPED;

        authenticator_.reset();
        channel_.reset();

        status_window_proxy_->onStopped();

        qInfo() << "Client stopped";
    }
    else
    {
        qWarning() << "Client already stopped";
    }
}

//--------------------------------------------------------------------------------------------------
void Client::setStatusWindow(std::shared_ptr<StatusWindowProxy> status_window_proxy)
{
    status_window_proxy_ = std::move(status_window_proxy);
}

//--------------------------------------------------------------------------------------------------
// static
base::Version Client::version()
{
    return base::Version(REMOTECONTROL_VERSION_MAJOR, REMOTECONTROL_VERSION_MINOR, REMOTECONTROL_VERSION_PATCH);
}

//--------------------------------------------------------------------------------------------------
std::u16string Client::computerName() const
{
    return config_.computer_name;
}

//--------------------------------------------------------------------------------------------------
proto::SessionType Client::sessionType() const
{
    return config_.session_type;
}

//--------------------------------------------------------------------------------------------------
void Client::sendMessage(uint8_t channel_id, const google::protobuf::MessageLite& message)
{
    if (!channel_)
    {
        qWarning() << "sendMessage called but channel not initialized";
        return;
    }

    channel_->send(channel_id, base::serialize(message));
}

//--------------------------------------------------------------------------------------------------
int64_t Client::totalRx() const
{
    if (!channel_)
    {
        qWarning() << "totalRx called but channel not initialized";
        return 0;
    }

    return channel_->totalRx();
}

//--------------------------------------------------------------------------------------------------
int64_t Client::totalTx() const
{
    if (!channel_)
    {
        qWarning() << "totalTx called but channel not initialized";
        return 0;
    }

    return channel_->totalTx();
}

//--------------------------------------------------------------------------------------------------
int Client::speedRx()
{
    if (!channel_)
    {
        qWarning() << "speedRx called but channel not initialized";
        return 0;
    }

    return channel_->speedRx();
}

//--------------------------------------------------------------------------------------------------
int Client::speedTx()
{
    if (!channel_)
    {
        qWarning() << "speedTx called but channel not initialized";
        return 0;
    }

    return channel_->speedTx();
}

//--------------------------------------------------------------------------------------------------
void Client::onTcpConnected()
{
    qInfo() << "Connection established";
    startAuthentication();
}

//--------------------------------------------------------------------------------------------------
void Client::onTcpDisconnected(base::NetworkChannel::ErrorCode error_code)
{
    qInfo() << "Connection terminated: " << base::NetworkChannel::errorToString(error_code).c_str();

    // Show an error to the user.
    status_window_proxy_->onDisconnected(error_code);
}

//--------------------------------------------------------------------------------------------------
void Client::onTcpMessageReceived(uint8_t channel_id, const base::ByteArray& buffer)
{
    if (channel_id == proto::HOST_CHANNEL_ID_SESSION)
    {
        onSessionMessageReceived(channel_id, buffer);
    }
    else if (channel_id == proto::HOST_CHANNEL_ID_SERVICE)
    {
        // TODO
    }
    else
    {
        qWarning() << "Unhandled incoming message from channel: " << channel_id;
    }
}

//--------------------------------------------------------------------------------------------------
void Client::onTcpMessageWritten(uint8_t channel_id, size_t pending)
{
    if (channel_id == proto::HOST_CHANNEL_ID_SESSION)
    {
        onSessionMessageWritten(channel_id, pending);
    }
    else if (channel_id == proto::HOST_CHANNEL_ID_SERVICE)
    {
        // TODO
    }
    else
    {
        qWarning() << "Unhandled outgoing message from channel: " << channel_id;
    }
}

//--------------------------------------------------------------------------------------------------
void Client::startAuthentication()
{
    qInfo() << "Start authentication for '" << config_.username << "' - '" << config_.password << "'";

    static const size_t kReadBufferSize = 2 * 1024 * 1024; // 2 Mb.

    channel_->setReadBufferSize(kReadBufferSize);
    channel_->setNoDelay(true);
    channel_->setKeepAlive(true);

    authenticator_ = std::make_unique<base::ClientAuthenticator>(io_task_runner_);

    authenticator_->setIdentify(proto::IDENTIFY_SRP);
    authenticator_->setUserName(config_.username);
    authenticator_->setPassword(config_.password);
    authenticator_->setSessionType(static_cast<uint32_t>(config_.session_type));

    authenticator_->start(std::move(channel_),
                          [this](base::ClientAuthenticator::ErrorCode error_code)
    {
        if (error_code == base::ClientAuthenticator::ErrorCode::SUCCESS)
        {
            qInfo() << "Successful authentication";

            // The authenticator takes the listener on itself, we return the receipt of
            // notifications.
            channel_ = authenticator_->takeChannel();
            channel_->setListener(this);

            const base::Version& host_version = authenticator_->peerVersion();
            if (host_version >= base::Version(2, 6, 0))
            {
                qInfo() << "Using channel id support";
                channel_->setChannelIdSupport(true);
            }

            base::Version client_version(REMOTECONTROL_VERSION_MAJOR, REMOTECONTROL_VERSION_MINOR,
                                         REMOTECONTROL_VERSION_PATCH, GIT_COMMIT_COUNT);
            if (host_version > client_version)
            {
                qWarning() << "Version mismatch (host: " << host_version.toString().c_str()
                                << " client: " << client_version.toString().c_str();
                status_window_proxy_->onVersionMismatch(host_version, client_version);
            }
            else
            {
                status_window_proxy_->onConnected();

                // Signal that everything is ready to start the session (connection established,
                // authentication passed).
                onSessionStarted(host_version);

                // Now the session will receive incoming messages.
                channel_->resume();
            }
        }
        else
        {
            qInfo() << "Failed authentication: "
                         << base::ClientAuthenticator::errorToString(error_code);
            status_window_proxy_->onAccessDenied(error_code);
        }

        // Authenticator is no longer needed.
        io_task_runner_->deleteSoon(std::move(authenticator_));
    });
}

} // namespace client
