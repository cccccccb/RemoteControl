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

#ifndef COMMON_UI_STATUS_DIALOG_H
#define COMMON_UI_STATUS_DIALOG_H

#include "Base/macros_magic.h"
#include "Common/common_export.h"

#include <QDialog>

namespace Ui {
class StatusDialog;
} // namespace Ui

namespace common {

class COMMON_EXPORT StatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatusDialog(QWidget* parent = nullptr);
    ~StatusDialog() override;

    void addMessage(const QString& message);
    void addMessageAndActivate(const QString& message);
    void retranslateUi();

private:
    std::unique_ptr<Ui::StatusDialog> ui;

    DISALLOW_COPY_AND_ASSIGN(StatusDialog);
};

} // namespace common

#endif // COMMON_UI_STATUS_DIALOG_H
