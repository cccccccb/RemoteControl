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

#ifndef BASE_STRINGS_STRING_PRINTF_H
#define BASE_STRINGS_STRING_PRINTF_H

#include "BuildConfig/build_config.h"
#include "Base/base_export.h"

#include <string>

namespace base {

// Return a C++ string given vprintf-like input.
BASE_EXPORT std::string stringPrintfV(const char* format, va_list args);

// Return a C++ string given printf-like input.
BASE_EXPORT std::string stringPrintf(const char* format, ...);

// Store result into a supplied string and return it.
BASE_EXPORT const std::string& sStringPrintf(std::string* dst, const char* format, ...);

#if defined(OS_WIN)
BASE_EXPORT std::wstring stringPrintfV(const wchar_t* format, va_list args);
BASE_EXPORT std::wstring stringPrintf(const wchar_t* format, ...);
BASE_EXPORT const std::wstring& sStringPrintf(std::wstring* dst, const wchar_t* format, ...);
#endif // defined(OS_WIN)

} // namespace base

#endif // BASE_STRINGS_STRING_PRINTF_H
