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

#ifndef BASE_STRINGS_UNICODE_H
#define BASE_STRINGS_UNICODE_H

#include "BuildConfig/build_config.h"
#include "Base/base_export.h"

#include <string>

namespace base {

//
// UTF-16 <-> UTF-8.
//

BASE_EXPORT bool utf16ToUtf8(const std::u16string &in, std::string* out);
BASE_EXPORT bool utf8ToUtf16(const std::string &in, std::u16string* out);

BASE_EXPORT std::u16string utf16FromUtf8(const std::string &in);
BASE_EXPORT std::string utf8FromUtf16(const std::u16string &in);

#if defined(OS_WIN)

//
// Wide <-> UTF-8.
//

BASE_EXPORT bool wideToUtf8(const std::wstring &in, std::string* out);
BASE_EXPORT bool utf8ToWide(const std::string &in, std::wstring* out);

BASE_EXPORT std::wstring wideFromUtf8(const std::string &in);
BASE_EXPORT std::string utf8FromWide(const std::wstring &in);

//
// Wide <-> UTF-16.
//

BASE_EXPORT bool wideToUtf16(const std::wstring &in, std::u16string* out);
BASE_EXPORT bool utf16ToWide(const std::u16string &in, std::wstring* out);

BASE_EXPORT std::wstring wideFromUtf16(const std::u16string &in);
BASE_EXPORT std::u16string utf16FromWide(const std::wstring &in);

#endif // #if defined(OS_WIN)

//
// ASCII <-> UTF-16.
//

BASE_EXPORT std::string asciiFromUtf16(const std::u16string &in);
BASE_EXPORT std::u16string utf16FromAscii(const std::string &in);

#if defined(OS_WIN)

//
// ASCII <-> Wide.
//

BASE_EXPORT std::string asciiFromWide(const std::wstring &in);
BASE_EXPORT std::wstring wideFromAscii(const std::string &in);

#endif // defined(OS_WIN)

//
// Local 8 bit <-> UTF-16.
//

BASE_EXPORT bool utf16ToLocal8Bit(const std::u16string &in, std::string* out);
BASE_EXPORT bool local8BitToUtf16(const std::string &in, std::u16string* out);

BASE_EXPORT std::u16string utf16FromLocal8Bit(const std::string &in);
BASE_EXPORT std::string local8BitFromUtf16(const std::u16string &in);

#if defined(OS_WIN)

//
// Local 8 bit <-> Wide.
//

BASE_EXPORT bool wideToLocal8Bit(const std::wstring &in, std::string* out);
BASE_EXPORT bool local8BitToWide(const std::string &in, std::wstring* out);

BASE_EXPORT std::wstring wideFromLocal8Bit(const std::string &in);
BASE_EXPORT std::string local8BitFromWide(const std::wstring &in);

#endif // defined(OS_WIN)

} // namespace base

#endif // BASE_STRINGS_UNICODE_H
