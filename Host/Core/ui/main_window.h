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

#ifndef HOST_UI_MAIN_WINDOW_H
#define HOST_UI_MAIN_WINDOW_H

#include "BuildConfig/build_config.h"
#include "Host/Core/user_session_window.h"
#include "ui_main_window.h"

#include <QMainWindow>
#include <QPointer>
#include <QSystemTrayIcon>

namespace common {
class StatusDialog;
} // namespace common

namespace host {

class NotifierWindow;
class UserSessionAgentProxy;

class MainWindow
    : public QMainWindow,
      public UserSessionWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    void connectToService();
    void activateHost();
    void hideToTray();

protected:
    // QMainWindow implementation.
    void closeEvent(QCloseEvent* event) override;

    // UserSessionWindow implementation.
    void onStatusChanged(UserSessionAgent::Status status) override;
    void onClientListChanged(const UserSessionAgent::ClientList& clients) override;
    void onCredentialsChanged(const proto::internal::Credentials& credentials) override;
    void onRouterStateChanged(const proto::internal::RouterState& state) override;
    void onConnectConfirmationRequest(
        const proto::internal::ConnectConfirmationRequest& request) override;
    void onVideoRecordingStateChanged(
        const std::string& computer_name, const std::string& user_name, bool started) override;

private slots:
    void realClose();
    void onLanguageChanged(QAction* action);
    void onSettings();
    void onShowHide();
    void onHelp();
    void onAbout();
    void onExit();
    void onSettingsChanged();
    void onKillSession(uint32_t session_id);

private:
    void createLanguageMenu(const QString& current_locale);
    void updateStatusBar();
    void updateTrayIconTooltip();

    Ui::MainWindow ui;

    bool should_be_quit_ = false;

    QSystemTrayIcon tray_icon_;
    QMenu tray_menu_;
    QPointer<NotifierWindow> notifier_;

    common::StatusDialog* status_dialog_ = nullptr;
    proto::internal::RouterState::State last_state_ = proto::internal::RouterState::DISABLED;

    std::unique_ptr<UserSessionAgentProxy> agent_proxy_;
    std::shared_ptr<UserSessionWindowProxy> window_proxy_;

    DISALLOW_COPY_AND_ASSIGN(MainWindow);
};

} // namespace host

#endif // HOST_UI_MAIN_WINDOW_H
