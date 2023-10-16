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

#ifndef BASE_DESKTOP_WIN_DXGI_OUTPUT_DUPLICATOR_H
#define BASE_DESKTOP_WIN_DXGI_OUTPUT_DUPLICATOR_H

#include "Base/desktop/frame_rotation.h"
#include "Base/desktop/shared_frame.h"
#include "Base/desktop/win/d3d_device.h"
#include "Base/desktop/win/dxgi_context.h"
#include "Base/desktop/win/dxgi_cursor.h"
#include "Base/desktop/win/dxgi_texture.h"
#include "Base/memory/byte_array.h"
#include "Base/win/desktop.h"

#include <dxgi.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

#include <string>
#include <vector>

namespace base {

// Duplicates the content on one IDXGIOutput, i.e. one monitor attached to one video card. None of
// functions in this class is thread-safe.
class DxgiOutputDuplicator
{
public:
    using Context = DxgiOutputContext;

    // Creates an instance of DxgiOutputDuplicator from a D3dDevice and one of its IDXGIOutput1.
    // Caller must maintain the lifetime of device, to make sure it outlives this instance. Only
    // DxgiAdapterDuplicator can create an instance.
    DxgiOutputDuplicator(const D3dDevice& device,
                         const Microsoft::WRL::ComPtr<IDXGIOutput1>& output,
                         const DXGI_OUTPUT_DESC& desc);

    // To allow this class to work with vector.
    DxgiOutputDuplicator(DxgiOutputDuplicator&& other);

    // Destructs this instance. We need to make sure texture_ has been released before duplication_.
    ~DxgiOutputDuplicator();

    // Initializes duplication object.
    bool initialize();

    // Copies the content of current IDXGIOutput to the |target|. To improve the performance, this
    // function copies only regions merged from |context|->updated_region and detectUpdatedRegion().
    // The |offset| decides the offset in the |target| where the content should be copied to. i.e.
    // this function copies the content to the rectangle of (offset.x(), offset.y()) to
    // (offset.x() + desktop_rect_.width(), offset.y() + desktop_rect_.height()).
    // Returns false in case of a failure.
    bool duplicate(
        Context* context, const Point& offset, SharedFrame* target_frame, DxgiCursor* cursor);

    // Returns the desktop rect covered by this DxgiOutputDuplicator.
    const Rect& desktopRect() const { return desktop_rect_; }

    // Returns the device name from DXGI_OUTPUT_DESC.
    const std::wstring& deviceName() const { return device_name_; }

    void setup(Context* context);

    void unregister(const Context* const context);

    // How many frames have been captured by this DxigOutputDuplicator.
    int64_t numFramesCaptured() const;

    // Moves |desktop_rect_|. See DxgiDuplicatorController::translateRect().
    void translateRect(const Point& position);

private:
    // Calls doDetectUpdatedRegion(). If it fails, this function sets the |updated_region| as
    // entire untranslatedDesktopRect().
    void detectUpdatedRegion(const DXGI_OUTDUPL_FRAME_INFO& frame_info, Region* updated_region);

    // Returns untranslated updated region, which are directly returned by Windows APIs. Returns
    // false in case of a failure.
    bool doDetectUpdatedRegion(const DXGI_OUTDUPL_FRAME_INFO& frame_info, Region* updated_region);

    bool releaseFrame();

    // Initializes duplication_ instance. Expects duplication_ is in empty status.
    // Returns false if system does not support IDXGIOutputDuplication.
    bool duplicateOutput();

    // Returns a Rect with the same size of desktopSize(), but translated by offset.
    Rect translatedDesktopRect(const Point& offset) const;

    // Returns a Rect with the same size of desktopSize(), but starts from (0, 0).
    Rect untranslatedDesktopRect() const;

    // Spreads changes from |context| to other registered Context(s) in contexts_.
    void spreadContextChange(const Context* const context);

    // Returns the size of desktop rectangle current instance representing.
    Size desktopSize() const;

    const D3dDevice device_;
    const Microsoft::WRL::ComPtr<IDXGIOutput1> output_;
    const std::wstring device_name_;
    const Rect initial_desktop_rect_;
    Rect desktop_rect_;
    Microsoft::WRL::ComPtr<IDXGIOutputDuplication> duplication_;
    DXGI_OUTDUPL_DESC desc_;
    std::vector<uint8_t> metadata_;
    std::unique_ptr<DxgiTexture> texture_;
    Rotation rotation_ = Rotation::CLOCK_WISE_0;
    Size unrotated_size_;

    // After each AcquireNextFrame() function call, updated_region_(s) of all active Context(s)
    // need to be updated. Since they have missed the change this time. And during next duplicate()
    // function call, their updated_region_ will be merged and copied.
    std::vector<Context*> contexts_;

    // The last full frame of this output and its offset. If on AcquireNextFrame() failed because
    // of timeout, i.e. no update, we can copy content from |last_frame_|.
    std::unique_ptr<SharedFrame> last_frame_;
    Point last_frame_offset_;

    int64_t num_frames_captured_ = 0;
    Desktop desktop_;
};

} // namespace base

#endif // BASE_DESKTOP_WIN_DXGI_OUTPUT_DUPLICATOR_H
