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

#ifndef BASE_DESKTOP_WIN_DXGI_FRAME_H
#define BASE_DESKTOP_WIN_DXGI_FRAME_H

#include "Base/optional.hpp"
#include "Base/desktop/screen_capturer.h"
#include "Base/desktop/shared_frame.h"
#include "Base/desktop/win/dxgi_context.h"

#include <memory>
#include <vector>

namespace base {

class DxgiDuplicatorController;
class SharedMemoryFactory;

// A pair of a SharedFrame and a DxgiDuplicatorController::Context for the client of
// DxgiDuplicatorController.
class DxgiFrame final
{
public:
    using Context = DxgiFrameContext;

    explicit DxgiFrame(base::local_shared_ptr<DxgiDuplicatorController> controller,
                       SharedMemoryFactory* shared_memory_factory);
    ~DxgiFrame();

    // Should not be called if prepare() is not executed or returns false.
    SharedFrame* frame() const;

private:
    // Allows DxgiDuplicatorController to access prepare() and context() function as well as
    // Context class.
    friend class DxgiDuplicatorController;

    // Prepares current instance with desktop size and source id.
    bool prepare(const Size& size, ScreenCapturer::ScreenId source_id);

    // Should not be called if prepare() is not executed or returns false.
    Context* context();

    SharedMemoryFactory* const shared_memory_factory_;
    tl::optional<Size> last_frame_size_;
    ScreenCapturer::ScreenId source_id_ = ScreenCapturer::kFullDesktopScreenId;
    std::unique_ptr<SharedFrame> frame_;
    Context context_;
};

} // namespace base

#endif // BASE_DESKTOP_WIN_DXGI_FRAME_H
