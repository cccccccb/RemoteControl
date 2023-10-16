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

#ifndef HOST_CLIENT_SESSION_DESKTOP_H
#define HOST_CLIENT_SESSION_DESKTOP_H

#include "BuildConfig/build_config.h"
#include "Base/macros_magic.h"
#include "Base/desktop/geometry.h"
#include "Base/memory/local_memory.h"
#include "Base/waitable_timer.h"
#include "Host/Core/client_session.h"
#include "Host/Core/desktop_session.h"

#if defined(OS_WIN)
#include "Host/Core/task_manager.h"
#endif // defined(OS_WIN)

namespace base {
class AudioEncoder;
class CursorEncoder;
class Frame;
class MouseCursor;
class ScaleReducer;
class VideoEncoder;
} // namespace base

namespace host {

class DesktopSessionProxy;

class ClientSessionDesktop
    : public ClientSession
#if defined(OS_WIN)
      , public TaskManager::Delegate
#endif // defined(OS_WIN)
{
public:
    ClientSessionDesktop(proto::SessionType session_type,
                         std::unique_ptr<base::TcpChannel> channel,
                         std::shared_ptr<base::TaskRunner> task_runner);
    ~ClientSessionDesktop() override;

    void setDesktopSessionProxy(base::local_shared_ptr<DesktopSessionProxy> desktop_session_proxy);

    void encodeScreen(const base::Frame* frame, const base::MouseCursor* cursor);
    void encodeAudio(const proto::AudioPacket& audio_packet);
    void setVideoErrorCode(proto::VideoErrorCode error_code);
    void setCursorPosition(const proto::CursorPosition& cursor_position);
    void setScreenList(const proto::ScreenList& list);
    void injectClipboardEvent(const proto::ClipboardEvent& event);

    const DesktopSession::Config& desktopSessionConfig() const { return desktop_session_config_; }

protected:
    // ClientSession implementation.
    void onStarted() override;
    void onReceived(uint8_t channel_id, const base::ByteArray& buffer) override;
    void onWritten(uint8_t channel_id, size_t pending) override;

#if defined(OS_WIN)
    // TaskManager::Delegate implementation.
    void onTaskManagerMessage(const proto::task_manager::HostToClient& message) override;
#endif // defined(OS_WIN)

private:
    void readExtension(const proto::DesktopExtension& extension);
    void readConfig(const proto::DesktopConfig& config);
    void readSelectScreenExtension(const std::string& data);
    void readPreferredSizeExtension(const std::string& data);
    void readVideoPauseExtension(const std::string& data);
    void readAudioPauseExtension(const std::string& data);
    void readPowerControlExtension(const std::string& data);
    void readRemoteUpdateExtension(const std::string& data);
    void readSystemInfoExtension(const std::string& data);
    void readVideoRecordingExtension(const std::string& data);
    void readTaskManagerExtension(const std::string& data);
    void onOverflowDetectionTimer();
    void downStepOverflow();
    void upStepOverflow();

    base::local_shared_ptr<DesktopSessionProxy> desktop_session_proxy_;
    std::unique_ptr<base::ScaleReducer> scale_reducer_;
    std::unique_ptr<base::VideoEncoder> video_encoder_;
    std::unique_ptr<base::CursorEncoder> cursor_encoder_;
    std::unique_ptr<base::AudioEncoder> audio_encoder_;
    DesktopSession::Config desktop_session_config_;
    base::Size source_size_;
    base::Size preferred_size_;
    base::Size forced_size_;
    bool is_video_paused_ = false;
    bool is_audio_paused_ = false;

    base::WaitableTimer overflow_detection_timer_;
    size_t write_overflow_count_ = 0;
    size_t write_normal_count_ = 1;
    size_t last_pending_count_ = 0;
    bool critical_overflow_ = false;
    int max_fps_ = 0;

#if defined(OS_WIN)
    std::unique_ptr<TaskManager> task_manager_;
#endif // defined(OS_WIN)

    std::unique_ptr<proto::ClientToHost> incoming_message_;
    std::unique_ptr<proto::HostToClient> outgoing_message_;

    DISALLOW_COPY_AND_ASSIGN(ClientSessionDesktop);
};

} // namespace host

#endif // HOST_CLIENT_SESSION_DESKTOP_H
