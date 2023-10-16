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

#include "Base/system_error.h"

#if defined(OS_WIN)
#include "Base/strings/string_printf.h"
#include "Base/strings/string_util.h"
#include "Base/strings/unicode.h"
#endif // defined(OS_WIN)

#if defined(OS_WIN)
#include <Windows.h>
#elif defined(OS_POSIX)
#include <cstring>
#include <cerrno>
#endif // defined(OS_WIN)

namespace base {

//--------------------------------------------------------------------------------------------------
SystemError::SystemError(Code code)
    : code_(code)
{
    // Nothing
}

//--------------------------------------------------------------------------------------------------
// static
SystemError SystemError::last()
{
#if defined(OS_WIN)
    return SystemError(GetLastError());
#elif defined(OS_POSIX)
    return SystemError(errno);
#else
#error Platform support not implemented
#endif
}

//--------------------------------------------------------------------------------------------------
SystemError::Code SystemError::code() const
{
    return code_;
}

//--------------------------------------------------------------------------------------------------
std::string SystemError::toString()
{
    return toString(code_);
}

//--------------------------------------------------------------------------------------------------
// static
std::string SystemError::toString(Code code)
{
#if defined(OS_WIN)
    constexpr int kErrorMessageBufferSize = 256;
    wchar_t msgbuf[kErrorMessageBufferSize];

    DWORD len = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               nullptr, code, 0, msgbuf, std::size(msgbuf), nullptr);
    if (len)
    {
        std::wstring msg = collapseWhitespace(msgbuf, true) + stringPrintf(L" (0x%lX)", code);
        return utf8FromWide(msg);
    }

    return stringPrintf("Error (0x%lX) while retrieving error. (0x%lX)",
                        GetLastError(),
                        code);
#elif defined(OS_POSIX)
    return std::strerror(code);
#else
#error Platform support not implemented
#endif
}

} // namespace base
