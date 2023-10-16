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

#ifndef BASE_CODEC_CURSOR_DECODER_H
#define BASE_CODEC_CURSOR_DECODER_H

#include "Base/base_export.h"

#include "Base/macros_magic.h"
#include "Base/codec/scoped_zstd_stream.h"
#include "Base/memory/byte_array.h"
#include "Base/optional.hpp"

namespace proto {
class CursorShape;
} // namespace proto

namespace base {

class MouseCursor;

class BASE_EXPORT CursorDecoder
{
public:
    CursorDecoder();
    ~CursorDecoder();

    std::shared_ptr<MouseCursor> decode(const proto::CursorShape& cursor_shape);

    int cachedCursors() const;
    int takenCursorsFromCache() const;

private:
    ByteArray decompressCursor(const proto::CursorShape& cursor_shape) const;

    std::vector<std::shared_ptr<MouseCursor>> cache_;
    tl::optional<size_t> cache_size_;
    ScopedZstdDStream stream_;
    int taken_from_cache_ = 0;

    DISALLOW_COPY_AND_ASSIGN(CursorDecoder);
};

} // namespace base

#endif // BASE_CODEC_CURSOR_DECODER_H
