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

#ifndef CLIENT_UI_ROUTER_MANAGER_ROUTER_STATUS_DIALOG_H
#define CLIENT_UI_ROUTER_MANAGER_ROUTER_STATUS_DIALOG_H

#include "Base/macros_magic.h"
#include "ui_router_status_dialog.h"

namespace client {

class RouterStatusDialog : public QDialog
{
    Q_OBJECT

public:
    RouterStatusDialog(QWidget* parent);
    ~RouterStatusDialog() override;

    void setStatus(const QString& message);

signals:
    void sig_canceled();

private:
    Ui::RouterStatusDialog ui;

    DISALLOW_COPY_AND_ASSIGN(RouterStatusDialog);
};

} // namespace client

#endif // CLIENT_UI_ROUTER_MANAGER_ROUTER_STATUS_DIALOG_H
