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

#ifndef COMMON_UI_UPDATE_DIALOG_H
#define COMMON_UI_UPDATE_DIALOG_H

#include "Base/macros_magic.h"
#include "Common/update_checker.h"
#include "Common/update_info.h"
#include "Common/common_export.h"

#include <QDialog>

namespace Ui {
class UpdateDialog;
} // namespace Ui

namespace common {

class COMMON_EXPORT UpdateDialog
    : public QDialog,
      public common::UpdateChecker::Delegate
{
    Q_OBJECT

public:
    UpdateDialog(std::string update_server,
                 std::string package_name,
                 QWidget* parent = nullptr);
    UpdateDialog(const UpdateInfo& update_info, QWidget* parent = nullptr);
    ~UpdateDialog() override;

protected:
    // QDialog implementation.
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    // common::UpdateChecker::Delegate implementation.
    void onUpdateCheckedFinished(const base::ByteArray& result) override;

private slots:
    void onUpdateNow();

private:
    void initialize();

    std::unique_ptr<Ui::UpdateDialog> ui;
    UpdateInfo update_info_;

    std::unique_ptr<UpdateChecker> checker_;
    bool checker_finished_ = true;

    DISALLOW_COPY_AND_ASSIGN(UpdateDialog);
};

} // namespace common

#endif // COMMON_UI_UPDATE_DIALOG_H
