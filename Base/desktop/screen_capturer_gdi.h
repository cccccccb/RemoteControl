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

#ifndef BASE_DESKTOP_SCREEN_CAPTURER_GDI_H
#define BASE_DESKTOP_SCREEN_CAPTURER_GDI_H

#include "Base/desktop/screen_capturer.h"
#include "Base/desktop/shared_frame.h"
#include "Base/win/scoped_hdc.h"

namespace base {

class Differ;
class SharedMemoryFactory;

class ScreenCapturerGdi : public ScreenCapturer
{
public:
    ScreenCapturerGdi();
    ~ScreenCapturerGdi() override;

    // ScreenCapturer implementation.
    int screenCount() override;
    bool screenList(ScreenList* screens) override;
    bool selectScreen(ScreenId screen_id) override;
    ScreenId currentScreen() const override;
    const Frame* captureFrame(Error* error) override;
    const MouseCursor* captureCursor() override;
    Point cursorPosition() override;

protected:
    // ScreenCapturer implementation.
    void reset() override;

private:
    const Frame* captureImage();
    bool prepareCaptureResources();

    typedef HRESULT(STDAPICALLTYPE* DwmEnableCompositionFunc) (UINT uCompositionAction);
    typedef HRESULT(STDAPICALLTYPE* DwmIsCompositionEnabledFunc) (BOOL* pfEnabled);

    HMODULE dwmapi_dll_ = nullptr;
    DwmEnableCompositionFunc dwm_enable_composition_func_ = nullptr;
    DwmIsCompositionEnabledFunc dwm_is_composition_enabled_func_ = nullptr;

    bool composition_changed_ = false;

    ScreenId current_screen_id_ = kFullDesktopScreenId;
    std::wstring current_device_key_;

    Rect desktop_dc_rect_;
    Rect screen_rect_;

    std::unique_ptr<Differ> differ_;
    win::ScopedGetDC desktop_dc_;
    win::ScopedCreateDC memory_dc_;

    FrameQueue<Frame> queue_;

    std::unique_ptr<MouseCursor> mouse_cursor_;
    CURSORINFO curr_cursor_info_;
    CURSORINFO prev_cursor_info_;

    DISALLOW_COPY_AND_ASSIGN(ScreenCapturerGdi);
};

} // namespace base

#endif // BASE_DESKTOP_SCREEN_CAPTURER_GDI_H
