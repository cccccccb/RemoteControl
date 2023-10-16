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

#ifndef HOST_DESKTOP_SESSION_H
#define HOST_DESKTOP_SESSION_H

#include "proto/desktop_internal.pb.h"

namespace base {
class Frame;
class MouseCursor;
} // namespace base

namespace host {

class DesktopSession
{
public:
    virtual ~DesktopSession() = default;

    class Delegate
    {
    public:
        virtual ~Delegate() = default;

        virtual void onDesktopSessionStarted() = 0;
        virtual void onDesktopSessionStopped() = 0;
        virtual void onScreenCaptured(const base::Frame* frame, const base::MouseCursor* cursor) = 0;
        virtual void onScreenCaptureError(proto::VideoErrorCode error_code) = 0;
        virtual void onAudioCaptured(const proto::AudioPacket& audio_packet) = 0;
        virtual void onCursorPositionChanged(const proto::CursorPosition& cursor_position) = 0;
        virtual void onScreenListChanged(const proto::ScreenList& list) = 0;
        virtual void onClipboardEvent(const proto::ClipboardEvent& event) = 0;
    };

    struct Config
    {
        bool disable_font_smoothing = true;
        bool disable_wallpaper = true;
        bool disable_effects = true;
        bool block_input = false;
        bool lock_at_disconnect = false;
        bool clear_clipboard = true;
        bool cursor_position = false;

        bool equals(const Config& other) const
        {
            return (disable_font_smoothing == other.disable_font_smoothing) &&
                   (disable_wallpaper == other.disable_wallpaper) &&
                   (disable_effects == other.disable_effects) &&
                   (block_input == other.block_input) &&
                   (lock_at_disconnect == other.lock_at_disconnect) &&
                   (clear_clipboard == other.clear_clipboard) &&
                   (cursor_position == other.cursor_position);
        }
    };

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void control(proto::internal::DesktopControl::Action action) = 0;
    virtual void configure(const Config& config) = 0;
    virtual void selectScreen(const proto::Screen& screen) = 0;
    virtual void captureScreen() = 0;

    virtual void setScreenCaptureFps(int fps) = 0;

    virtual void injectKeyEvent(const proto::KeyEvent& event) = 0;
    virtual void injectTextEvent(const proto::TextEvent& event) = 0;
    virtual void injectMouseEvent(const proto::MouseEvent& event) = 0;
    virtual void injectClipboardEvent(const proto::ClipboardEvent& event) = 0;

    static const char* controlActionToString(proto::internal::DesktopControl::Action action);
};

} // namespace host

#endif // HOST_DESKTOP_SESSION_H
