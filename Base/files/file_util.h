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

#ifndef BASE_FILES_FILE_UTIL_H
#define BASE_FILES_FILE_UTIL_H

#include "Base/memory/byte_array.h"
#include "Base/filesystem.hpp"
#include "Base/base_export.h"

namespace base {

BASE_EXPORT bool writeFile(const ghc::filesystem::path& filename, const void* data, size_t size);
BASE_EXPORT bool writeFile(const ghc::filesystem::path& filename, const ByteArray& buffer);
BASE_EXPORT bool writeFile(const ghc::filesystem::path& filename, std::string buffer);

BASE_EXPORT bool readFile(const ghc::filesystem::path& filename, ByteArray* buffer);
BASE_EXPORT bool readFile(const ghc::filesystem::path& filename, std::string* buffer);

} // namespace base

#endif // BASE_FILES_FILE_UTIL_H
