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

#ifndef CLIENT_UI_CLIENT_WINDOW_H
#define CLIENT_UI_CLIENT_WINDOW_H

#include "Base/macros_magic.h"
#include "Base/memory/byte_array.h"
#include "Client/Core/client_config.h"
#include "Common/update_checker.h"
#include "proto/desktop.pb.h"
#include "ui_client_window.h"

#include <QMainWindow>

namespace client {

class ClientWindow
    : public QMainWindow,
      public common::UpdateChecker::Delegate
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget* parent = nullptr);
    ~ClientWindow() override;

protected:
    // QMainWindow implementation.
    void closeEvent(QCloseEvent* event) override;

    // common::UpdateChecker::Delegate implementation.
    void onUpdateCheckedFinished(const base::ByteArray& result) override;

private slots:
    void onLanguageChanged(QAction* action);
    void onSettings();
    void onHelp();
    void onAbout();
    void sessionTypeChanged(int item_index);
    void sessionConfigButtonPressed();
    void connectToHost();
    void onCheckUpdates();

private:
    void createLanguageMenu(const QString& current_locale);
    void reloadSessionTypes();

    Ui::ClientWindow ui;
    std::unique_ptr<common::UpdateChecker> update_checker_;

    DISALLOW_COPY_AND_ASSIGN(ClientWindow);
};

} // namespace client

#endif // CLIENT_UI_CLIENT_WINDOW_H
