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

#ifndef CLIENT_UI_DESKTOP_STATISTICS_DIALOG_H
#define CLIENT_UI_DESKTOP_STATISTICS_DIALOG_H

#include "Base/macros_magic.h"
#include "Client/Core/desktop_window.h"
#include "ui_statistics_dialog.h"

#include <QTime>

namespace client {

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget* parent = nullptr);
    ~StatisticsDialog() override;

    void setMetrics(const DesktopWindow::Metrics& metrics);

signals:
    void sig_metricsRequired();

private:
    static QString sizeToString(int64_t size);
    static QString speedToString(int64_t speed);

    Ui::StatisticsDialog ui;
    QTimer* update_timer_ = nullptr;
    QTime duration_;

    DISALLOW_COPY_AND_ASSIGN(StatisticsDialog);
};

} // namespace client

#endif // CLIENT_UI_DESKTOP_STATISTICS_DIALOG_H
