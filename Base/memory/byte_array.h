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

#ifndef BASE_MEMORY_BYTE_ARRAY_H
#define BASE_MEMORY_BYTE_ARRAY_H

#include "Base/base_export.h"

#include <cstdint>
#include <string>
#include <vector>

#include <google/protobuf/message_lite.h>

namespace base {

using ByteArray = std::vector<uint8_t>;

BASE_EXPORT ByteArray fromData(const void* data, size_t size);

BASE_EXPORT ByteArray fromStdString(std::string in);
BASE_EXPORT std::string toStdString(const ByteArray& in);

BASE_EXPORT ByteArray fromHex(std::string in);
BASE_EXPORT std::string toHex(const ByteArray& in);

BASE_EXPORT void append(ByteArray* in, const void* data, size_t size);

BASE_EXPORT base::ByteArray serialize(const google::protobuf::MessageLite& message);

template <class T>
bool parse(const base::ByteArray& buffer, T* message)
{
    return message->ParseFromArray(buffer.data(), static_cast<int>(buffer.size()));
}

BASE_EXPORT int compare(const base::ByteArray& first, const base::ByteArray& second);

inline bool equals(const base::ByteArray& first, const base::ByteArray& second)
{
    return compare(first, second) == 0;
}

BASE_EXPORT std::ostream& operator<<(std::ostream& out, const ByteArray& bytearray);

} // namespace base

#endif // BASE_MEMORY_BYTE_ARRAY_H
