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

#ifndef HOST_UI_USER_DIALOG_H
#define HOST_UI_USER_DIALOG_H

#include "Base/macros_magic.h"
#include "Base/peer/user.h"
#include "ui_user_dialog.h"

namespace host {

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    UserDialog(const base::User& user, const QStringList& exist_names, QWidget* parent);
    ~UserDialog() override;

    base::User user() { return user_; }

protected:
    // QDialog implementation.
    bool eventFilter(QObject* object, QEvent* event) override;

private slots:
    void onCheckAllButtonPressed();
    void onCheckNoneButtonPressed();
    void onButtonBoxClicked(QAbstractButton* button);

private:
    void setAccountChanged(bool changed);

    Ui::UserDialog ui;

    QStringList exist_names_;
    base::User user_;
    bool account_changed_ = true;

    DISALLOW_COPY_AND_ASSIGN(UserDialog);
};

} // namespace host

#endif // HOST_UI_USER_DIALOG_H
