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

#ifndef BASE_DESKTOP_SHARED_MEMORY_FRAME_H
#define BASE_DESKTOP_SHARED_MEMORY_FRAME_H

#include "Base/desktop/frame.h"
#include "Base/base_export.h"

#include <memory>

namespace base {

class SharedMemoryFactory;

class BASE_EXPORT SharedMemoryFrame : public Frame
{
public:
    ~SharedMemoryFrame() override;

    static std::unique_ptr<Frame> create(
        const Size& size, const PixelFormat& format, SharedMemoryFactory* shared_memory_factory);

    static std::unique_ptr<Frame> open(
        const Size& size, const PixelFormat& format, int id, SharedMemoryFactory* shared_memory_factory);

    static std::unique_ptr<Frame> attach(
        const Size& size, const PixelFormat& format, std::unique_ptr<SharedMemoryBase> shared_memory);

private:
    SharedMemoryFrame(const Size& size, const PixelFormat& format, SharedMemoryBase* shared_memory);

    DISALLOW_COPY_AND_ASSIGN(SharedMemoryFrame);
};

} // namespace base

#endif // BASE_DESKTOP_SHARED_MEMORY_FRAME_H
