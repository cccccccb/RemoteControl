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

#ifndef BASE_CRYPTO_SECURE_MEMORY_H
#define BASE_CRYPTO_SECURE_MEMORY_H

#include "Base/memory/byte_array.h"
#include "Base/base_export.h"

namespace base {

void BASE_EXPORT memZero(void* data, size_t data_size);
void BASE_EXPORT memZero(std::string* str);
void BASE_EXPORT memZero(std::u16string* str);
void BASE_EXPORT memZero(ByteArray* str);

} // namespace base

#endif // BASE_CRYPTO_SECURE_MEMORY_H
