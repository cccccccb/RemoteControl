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

#ifndef BASE_DESKTOP_FRAME_H
#define BASE_DESKTOP_FRAME_H

#include "Base/macros_magic.h"
#include "Base/desktop/pixel_format.h"
#include "Base/desktop/region.h"
#include "Base/base_export.h"

namespace base {

class SharedMemoryBase;

class BASE_EXPORT Frame
{
public:
    virtual ~Frame() = default;

    SharedMemoryBase* sharedMemory() const { return shared_memory_; }

    uint8_t* frameDataAtPos(const Point& pos) const;
    uint8_t* frameDataAtPos(int x, int y) const;
    uint8_t* frameData() const { return data_; }
    const Size& size() const { return size_; }
    const PixelFormat& format() const { return format_; }
    int stride() const { return stride_; }
    bool contains(int x, int y) const;

    void copyPixelsFrom(const uint8_t* src_buffer, int src_stride, const Rect& dest_rect);
    void copyPixelsFrom(const Frame& src_frame, const Point& src_pos, const Rect& dest_rect);

    const Region& constUpdatedRegion() const { return updated_region_; }
    Region* updatedRegion() { return &updated_region_; }

    void setTopLeft(const Point& top_left) { top_left_ = top_left; }
    const Point& topLeft() const { return top_left_; }

    void setCapturerType(uint32_t capturer_type) { capturer_type_ = capturer_type; }
    uint32_t capturerType() const { return capturer_type_; }

    // Copies various information from |other|. Anything initialized in constructor are not copied.
    // This function is usually used when sharing a source Frame with several clients: the original
    // Frame should be kept unchanged. For example and SharedFrame::share().
    void copyFrameInfoFrom(const Frame& other);

protected:
    Frame(const Size& size,
          const PixelFormat& format,
          int stride,
          uint8_t* data,
          SharedMemoryBase* shared_memory);

    static size_t calcMemorySize(const Size& size, int bytes_per_pixel);

    // Ownership of the buffers is defined by the classes that inherit from this class. They must
    // guarantee that the buffer is not deleted before the frame is deleted.
    uint8_t* const data_;
    SharedMemoryBase* const shared_memory_;

private:
    const Size size_;
    const PixelFormat format_;
    const int stride_;

    Region updated_region_;
    Point top_left_;
    Point dpi_;
    uint32_t capturer_type_ = 0;

    DISALLOW_COPY_AND_ASSIGN(Frame);
};

} // namespace base

#endif // BASE_DESKTOP_FRAME_H
