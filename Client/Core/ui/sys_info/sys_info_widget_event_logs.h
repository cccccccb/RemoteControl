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

#ifndef CLIENT_UI_SYS_INFO_SYS_INFO_EVENT_LOGS_H
#define CLIENT_UI_SYS_INFO_SYS_INFO_EVENT_LOGS_H

#include "Client/Core/ui/sys_info/sys_info_widget.h"
#include "ui_sys_info_widget_event_logs.h"

namespace client {

class SysInfoWidgetEventLogs : public SysInfoWidget
{
    Q_OBJECT

public:
    explicit SysInfoWidgetEventLogs(QWidget* parent = nullptr);
    ~SysInfoWidgetEventLogs() override;

    // SysInfo implementation.
    std::string category() const override;
    proto::system_info::SystemInfoRequest request() const override;
    void setSystemInfo(const proto::system_info::SystemInfo& system_info) override;
    QTreeWidget* treeWidget() override;

private slots:
    void onContextMenu(const QPoint& point);
    void onPageActivated(int index);

private:
    proto::system_info::SystemInfoRequest createRequest(
        proto::system_info::EventLogs::Event::Type type, uint32_t start) const;
    static QString levelToString(proto::system_info::EventLogs::Event::Level value);

    Ui::SysInfoEventLogs ui;
    int current_column_ = 0;

    static const uint32_t kRecordsPerPage = 1000;

    proto::system_info::EventLogs::Event::Type current_type_ =
        proto::system_info::EventLogs::Event::TYPE_SYSTEM;
    uint32_t total_records_ = 0;
    uint32_t start_record_ = 0;
};

} // namespace client

#endif // CLIENT_UI_SYS_INFO_SYS_INFO_EVENT_LOGS_H
