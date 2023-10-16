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

#ifndef BASE_DESKTOP_SHARED_FRAME_H
#define BASE_DESKTOP_SHARED_FRAME_H

#include "Base/desktop/frame.h"
#include "Base/memory/local_memory.h"
#include "Base/base_export.h"

#include <memory>

namespace base {

// SharedFrame is a Frame that may have multiple instances all sharing the same buffer.
class BASE_EXPORT SharedFrame : public Frame
{
public:
    ~SharedFrame() override;

    static std::unique_ptr<SharedFrame> wrap(std::unique_ptr<Frame> desktop_frame);

    // Returns whether |this| and |other| share the underlying Frame.
    bool shareFrameWith(const SharedFrame& other) const;

    // Creates a clone of this object.
    std::unique_ptr<SharedFrame> share();

    // Checks if the frame is currently shared. If it returns false it's guaranteed that there are
    // no clones of the object.
    bool isShared();

    Frame* underlyingFrame();

private:
    explicit SharedFrame(base::local_shared_ptr<Frame>& frame);

    base::local_shared_ptr<Frame> frame_;

    DISALLOW_COPY_AND_ASSIGN(SharedFrame);
};

} // namespace base

#endif // BASE_DESKTOP_SHARED_FRAME_H
