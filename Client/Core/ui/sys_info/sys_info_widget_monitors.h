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

#ifndef CLIENT_UI_SYS_INFO_SYS_INFO_MONITORS_H
#define CLIENT_UI_SYS_INFO_SYS_INFO_MONITORS_H

#include "Client/Core/ui/sys_info/sys_info_widget.h"
#include "ui_sys_info_widget_monitors.h"

namespace client {

class SysInfoWidgetMonitors : public SysInfoWidget
{
    Q_OBJECT

public:
    explicit SysInfoWidgetMonitors(QWidget* parent = nullptr);
    ~SysInfoWidgetMonitors() override;

    // SysInfo implementation.
    std::string category() const override;
    void setSystemInfo(const proto::system_info::SystemInfo& system_info) override;
    QTreeWidget* treeWidget() override;

private slots:
    void onContextMenu(const QPoint& point);

private:
    static QString inputSignalTypeToString(
        proto::system_info::Monitors::Monitor::InputSignalType value);

    Ui::SysInfoMonitors ui;
};

} // namespace client

#endif // CLIENT_UI_SYS_INFO_SYS_INFO_MONITORS_H
