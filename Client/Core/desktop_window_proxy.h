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

#ifndef CLIENT_DESKTOP_WINDOW_PROXY_H
#define CLIENT_DESKTOP_WINDOW_PROXY_H

#include "Base/macros_magic.h"
#include "Client/Core/desktop_window.h"

#include <string>

namespace base {
class TaskRunner;
} // namespace base

namespace client {

class DesktopControlProxy;

class DesktopWindowProxy : public std::enable_shared_from_this<DesktopWindowProxy>
{
public:
    DesktopWindowProxy(std::shared_ptr<base::TaskRunner> ui_task_runner,
                       DesktopWindow* desktop_window);
    ~DesktopWindowProxy();

    void dettach();

    void showWindow(std::shared_ptr<DesktopControlProxy> desktop_control_proxy,
                    const base::Version& peer_version);

    void configRequired();

    void setCapabilities(const proto::DesktopCapabilities& capabilities);
    void setScreenList(const proto::ScreenList& screen_list);
    void setCursorPosition(const proto::CursorPosition& cursor_position);
    void setSystemInfo(const proto::system_info::SystemInfo& system_info);
    void setTaskManager(const proto::task_manager::HostToClient& message);
    void setMetrics(const DesktopWindow::Metrics& metrics);

    std::shared_ptr<base::Frame> allocateFrame(const base::Size& size);
    void setFrameError(proto::VideoErrorCode error_code);
    void setFrame(const base::Size& screen_size, std::shared_ptr<base::Frame> frame);
    void drawFrame();
    void setMouseCursor(std::shared_ptr<base::MouseCursor> mouse_cursor);

private:
    std::shared_ptr<base::TaskRunner> ui_task_runner_;
    std::unique_ptr<FrameFactory> frame_factory_;
    DesktopWindow* desktop_window_;

    DISALLOW_COPY_AND_ASSIGN(DesktopWindowProxy);
};

} // namespace client

#endif // CLIENT_DESKTOP_WINDOW_PROXY_H
