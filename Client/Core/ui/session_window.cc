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

#include "Client/Core/ui/session_window.h"

#include "Base/logging.h"
#include "Client/Core/client.h"
#include "Client/Core/client_proxy.h"
#include "Client/Core/status_window_proxy.h"
#include "Client/Core/ui/authorization_dialog.h"
#include "Common/ui/status_dialog.h"
#include "QtBase/application.h"

namespace client {

//--------------------------------------------------------------------------------------------------
SessionWindow::SessionWindow(QWidget* parent)
    : QWidget(parent),
      status_window_proxy_(
          std::make_shared<StatusWindowProxy>(qt_base::Application::uiTaskRunner(), this))
{
    qInfo() << "Ctor";
}

//--------------------------------------------------------------------------------------------------
SessionWindow::~SessionWindow()
{
    qInfo() << "Dtor";
    status_window_proxy_->dettach();
}

//--------------------------------------------------------------------------------------------------
bool SessionWindow::connectToHost(Config config)
{
    qInfo() << "Connecting to host";

    if (client_proxy_)
    {
        qWarning() << "Attempt to start an already running client";
        return false;
    }

    // Set the window title.
    setClientTitle(config);

    if (config.username.empty() || config.password.empty())
    {
        qInfo() << "Empty user name or password";

        AuthorizationDialog auth_dialog(this);

		auth_dialog.setUserName(QString::fromStdU16String(config.username));
        auth_dialog.setPassword(QString::fromStdU16String(config.password));

        if (auth_dialog.exec() == AuthorizationDialog::Rejected)
        {
            qInfo() << "Authorization rejected by user";
            return false;
        }

		const QString &dialogUserName = auth_dialog.userName();
		const QString &dialogPassword = auth_dialog.password();
		std::u16string userName(reinterpret_cast<const char16_t*>(dialogUserName.utf16()));
		std::u16string password(reinterpret_cast<const char16_t*>(dialogPassword.utf16()));

		config.username = userName;
        config.password = password;
    }

    // When connecting with a one-time password, the username must be in the following format:
    // #host_id.
    if (config.username.empty())
    {
        qInfo() << "User name is empty. Connection by ID";
        config.username = u"#" + config.address_or_id;
    }

    // Create a client instance.
    std::unique_ptr<Client> client = createClient();

    // Set the window that will receive notifications.
    client->setStatusWindow(status_window_proxy_);

    client_proxy_ = std::make_unique<ClientProxy>(
        qt_base::Application::ioTaskRunner(), std::move(client), config);

    qInfo() << "Start client proxy";
    client_proxy_->start();
    return true;
}

//--------------------------------------------------------------------------------------------------
Config SessionWindow::config() const
{
    return client_proxy_->config();
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::closeEvent(QCloseEvent* /* event */)
{
    qInfo() << "Close event";

    if (client_proxy_)
    {
        qInfo() << "Stopping client proxy";
        client_proxy_->stop();
        client_proxy_.reset();
    }
    else
    {
        qInfo() << "No client proxy";
    }
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onStarted(const std::u16string& address_or_id)
{
    qInfo() << "Attempt to establish a connection";

    // Create a dialog to display the connection status.
    status_dialog_ = new common::StatusDialog(this);

    // After closing the status dialog, close the session window.
    connect(status_dialog_, &common::StatusDialog::finished, this, &SessionWindow::close);

    status_dialog_->setWindowFlag(Qt::WindowStaysOnTopHint);
    status_dialog_->addMessageAndActivate(tr("Attempt to connect to %1.").arg(address_or_id));
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onStopped()
{
    qInfo() << "Connection stopped";
    status_dialog_->close();
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onConnected()
{
    qInfo() << "Connection established";

    status_dialog_->addMessageAndActivate(tr("Connection established."));
    status_dialog_->hide();
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onDisconnected(base::TcpChannel::ErrorCode error_code)
{
    qInfo() << "Network error";
    onErrorOccurred(netErrorToString(error_code));
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onVersionMismatch(const base::Version& host, const base::Version& client)
{
    QString host_version = QString::fromStdString(host.toString());
    QString client_version = QString::fromStdString(client.toString());

    onErrorOccurred(
        tr("The Host version is newer than the Client version (%1 > %2). "
           "Please update the application.")
           .arg(host_version).arg(client_version));
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onAccessDenied(base::ClientAuthenticator::ErrorCode error_code)
{
    qInfo() << "Authentication error";
    onErrorOccurred(authErrorToString(error_code));
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::setClientTitle(const Config& config)
{
    QString session_name;

    switch (config.session_type)
    {
        case proto::SESSION_TYPE_DESKTOP_MANAGE:
            session_name = tr("Desktop Manage");
            break;

        case proto::SESSION_TYPE_DESKTOP_VIEW:
            session_name = tr("Desktop View");
            break;

    case proto::SESSION_TYPE_DESKTOP_CONTROL:
        session_name = tr("Desktop Control");
        break;

        default:
            NOTREACHED();
            break;
    }

    QString computer_name = QString::fromStdU16String(config.computer_name);
    if (computer_name.isEmpty())
    {
        computer_name = QString("%1:%2").arg(config.address_or_id).arg(config.port);
    }

    setWindowTitle(QString("%1 - %2").arg(computer_name).arg(session_name));
}

//--------------------------------------------------------------------------------------------------
void SessionWindow::onErrorOccurred(const QString& message)
{
    hide();

    for (const auto& object : children())
    {
        QWidget* widget = dynamic_cast<QWidget*>(object);
        if (widget)
            widget->hide();
    }

    status_dialog_->addMessageAndActivate(message);
}

//--------------------------------------------------------------------------------------------------
// static
QString SessionWindow::netErrorToString(base::TcpChannel::ErrorCode error_code)
{
    const char* message;

    switch (error_code)
    {
        case base::TcpChannel::ErrorCode::INVALID_PROTOCOL:
            message = QT_TR_NOOP("Violation of the communication protocol.");
            break;

        case base::TcpChannel::ErrorCode::ACCESS_DENIED:
            message = QT_TR_NOOP("Cryptography error (message encryption or decryption failed).");
            break;

        case base::TcpChannel::ErrorCode::NETWORK_ERROR:
            message = QT_TR_NOOP("An error occurred with the network (e.g., the network cable was accidentally plugged out).");
            break;

        case base::TcpChannel::ErrorCode::CONNECTION_REFUSED:
            message = QT_TR_NOOP("Connection was refused by the peer (or timed out).");
            break;

        case base::TcpChannel::ErrorCode::REMOTE_HOST_CLOSED:
            message = QT_TR_NOOP("Remote host closed the connection.");
            break;

        case base::TcpChannel::ErrorCode::SPECIFIED_HOST_NOT_FOUND:
            message = QT_TR_NOOP("Host address was not found.");
            break;

        case base::TcpChannel::ErrorCode::SOCKET_TIMEOUT:
            message = QT_TR_NOOP("Socket operation timed out.");
            break;

        case base::TcpChannel::ErrorCode::ADDRESS_IN_USE:
            message = QT_TR_NOOP("Address specified is already in use and was set to be exclusive.");
            break;

        case base::TcpChannel::ErrorCode::ADDRESS_NOT_AVAILABLE:
            message = QT_TR_NOOP("Address specified does not belong to the host.");
            break;

        default:
        {
            if (error_code != base::TcpChannel::ErrorCode::UNKNOWN)
            {
                qWarning() << "Unknown error code: " << static_cast<int>(error_code);
            }

            message = QT_TR_NOOP("An unknown error occurred.");
        }
        break;
    }

    return tr(message);
}

//--------------------------------------------------------------------------------------------------
// static
QString SessionWindow::authErrorToString(base::ClientAuthenticator::ErrorCode error_code)
{
    const char* message;

    switch (error_code)
    {
        case base::ClientAuthenticator::ErrorCode::SUCCESS:
            message = QT_TR_NOOP("Authentication successfully completed.");
            break;

        case base::ClientAuthenticator::ErrorCode::NETWORK_ERROR:
            message = QT_TR_NOOP("Network authentication error.");
            break;

        case base::ClientAuthenticator::ErrorCode::PROTOCOL_ERROR:
            message = QT_TR_NOOP("Violation of the data exchange protocol.");
            break;

        case base::ClientAuthenticator::ErrorCode::ACCESS_DENIED:
            message = QT_TR_NOOP("Wrong user name or password.");
            break;

        case base::ClientAuthenticator::ErrorCode::SESSION_DENIED:
            message = QT_TR_NOOP("Specified session type is not allowed for the user.");
            break;

        default:
            message = QT_TR_NOOP("An unknown error occurred.");
            break;
    }

    return tr(message);
}

} // namespace client
