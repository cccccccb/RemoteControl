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

#ifndef HOST_UI_CONFIG_DIALOG_H
#define HOST_UI_CONFIG_DIALOG_H

#include "BuildConfig/build_config.h"
#include "Base/peer/user_list.h"
#include "QtBase/locale_loader.h"
#include "ui_config_dialog.h"

namespace host {

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget* parent = nullptr);
    ~ConfigDialog() override;

private slots:
    void onOneTimeStateChanged(int state);
    void onConnConfirmStateChanged(int state);
    void onUserContextMenu(const QPoint& point);
    void onCurrentUserChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void onAddUser();
    void onModifyUser();
    void onDeleteUser();
    void onServiceInstallRemove();
    void onServiceStartStop();
    void onPassProtectClicked();
    void onChangePassClicked();
    void onImport();
    void onExport();
    void onConfigChanged() { setConfigChanged(true); }
    void onButtonBoxClicked(QAbstractButton* button);

private:
    void setConfigChanged(bool changed);
    bool isConfigChanged() const;
    void reloadAll();
    void reloadUserList(const base::UserList& user_list);
    void reloadServiceStatus();
    bool isServiceStarted();
    bool installService();
    bool removeService();
    bool startService();
    bool stopService();
    bool restartService();

    Ui::ConfigDialog ui;

    enum class ServiceState { NOT_INSTALLED, ACCESS_DENIED, NOT_STARTED, STARTED };
    ServiceState service_state_;

    DISALLOW_COPY_AND_ASSIGN(ConfigDialog);
};

} // namespace host

#endif // HOST_UI_CONFIG_DIALOG_H
