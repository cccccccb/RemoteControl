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

#ifndef CLIENT_DESKTOP_CONTROL_PROXY_H
#define CLIENT_DESKTOP_CONTROL_PROXY_H

#include "Base/macros_magic.h"
#include "Base/filesystem.hpp"

#include "proto/desktop.pb.h"
#include "proto/desktop_extensions.pb.h"
#include "proto/system_info.pb.h"
#include "proto/task_manager.pb.h"


namespace base {
class TaskRunner;
} // namespace base

namespace client {

class DesktopControl;

class DesktopControlProxy : public std::enable_shared_from_this<DesktopControlProxy>
{
public:
    DesktopControlProxy(std::shared_ptr<base::TaskRunner> io_task_runner,
                        DesktopControl* desktop_control);
    ~DesktopControlProxy();

    void dettach();

    void setDesktopConfig(const proto::DesktopConfig& desktop_config);
    void setCurrentScreen(const proto::Screen& screen);
    void setPreferredSize(int width, int height);
    void setVideoPause(bool enable);
    void setAudioPause(bool enable);
    void setVideoRecording(bool enable, const ghc::filesystem::path& file_path);
    void onKeyEvent(const proto::KeyEvent& event);
    void onTextEvent(const proto::TextEvent& event);
    void onMouseEvent(const proto::MouseEvent& event);
    void onPowerControl(proto::PowerControl::Action action);
    void onRemoteUpdate();
    void onSystemInfoRequest(const proto::system_info::SystemInfoRequest& request);
    void onTaskManager(const proto::task_manager::ClientToHost& message);
    void onMetricsRequest();

private:
    std::shared_ptr<base::TaskRunner> io_task_runner_;
    DesktopControl* desktop_control_;

    DISALLOW_COPY_AND_ASSIGN(DesktopControlProxy);
};

} // namespace client

#endif // CLIENT_DESKTOP_CONTROL_PROXY_H
