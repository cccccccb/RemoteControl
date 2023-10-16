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

#include "Base/strings/unicode.h"

#include "Base/logging.h"

#if defined(OS_WIN)
#include <Windows.h>
#endif // defined(OS_WIN)

#if defined(OS_LINUX) || defined(OS_MAC)
#include <unicode/utypes.h>
#include <unicode/ustring.h>
#endif // OS_POSIX || OS_MAC

namespace base {

namespace {

#if defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
template <class InputType>
bool wideToLocalImpl(InputType in, std::string* out)
{
    out->clear();

    const size_t in_len = in.length();
    if (!in_len)
        return true;

    const int out_len = WideCharToMultiByte(CP_ACP, 0,
                                            reinterpret_cast<const wchar_t*>(in.data()),
                                            static_cast<int>(in_len),
                                            nullptr, 0, nullptr, nullptr);
    if (out_len <= 0)
        return false;

    out->resize(static_cast<size_t>(out_len));

    if (WideCharToMultiByte(CP_ACP, 0,
                            reinterpret_cast<const wchar_t*>(in.data()),
                            static_cast<int>(in_len),
                            (LPSTR)out->data(), out_len, nullptr, nullptr) != out_len)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class OutputType>
bool localToWideImpl(const std::string &in, OutputType* out)
{
    out->clear();

    const size_t in_len = in.length();
    if (!in_len)
        return true;

    const int out_len =
        MultiByteToWideChar(CP_ACP, 0, in.data(), static_cast<int>(in_len), nullptr, 0);
    if (out_len <= 0)
        return false;

    out->resize(static_cast<size_t>(out_len));

    if (MultiByteToWideChar(CP_ACP, 0, in.data(), static_cast<int>(in_len),
                            const_cast<wchar_t*>(reinterpret_cast<const wchar_t*>(out->data())), out_len) != out_len)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class InputType>
bool wideToUtf8Impl(InputType in, std::string* out)
{
    out->clear();

    const size_t in_len = in.length();
    if (!in_len)
        return true;

    const int out_len = WideCharToMultiByte(CP_UTF8, 0,
                                            reinterpret_cast<const wchar_t*>(in.data()),
                                            static_cast<int>(in_len),
                                            nullptr, 0, nullptr, nullptr);
    if (out_len <= 0)
        return false;

    out->resize(static_cast<size_t>(out_len));

    if (WideCharToMultiByte(CP_UTF8, 0,
                            reinterpret_cast<const wchar_t*>(in.data()),
                            static_cast<int>(in_len),
                            LPSTR(out->data()), out_len, nullptr, nullptr) != out_len)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class OutputType>
bool utf8ToWideImpl(const std::string &in, OutputType* out)
{
    out->clear();

    const size_t in_len = in.length();
    if (!in_len)
        return true;

    const int out_len =
        MultiByteToWideChar(CP_UTF8, 0, in.data(), static_cast<int>(in_len), nullptr, 0);
    if (out_len <= 0)
        return false;

    out->resize(static_cast<size_t>(out_len));

    if (MultiByteToWideChar(CP_UTF8, 0, in.data(), static_cast<int>(in_len),
                            const_cast<wchar_t*>(reinterpret_cast<const wchar_t*>(out->data())), out_len) != out_len)
    {
        return false;
    }

    return true;
}

#else

//--------------------------------------------------------------------------------------------------
bool utf16ToUtf8Impl(std::u16string in, std::string* out)
{
    out->clear();

    if (!in.length())
        return true;

    UErrorCode error_code = U_ZERO_ERROR;
    int32_t out_len = 0;
    u_strToUTF8(nullptr, 0, &out_len, in.data(), in.length(), &error_code);
    if (error_code != U_BUFFER_OVERFLOW_ERROR || out_len <= 0)
        return false;

    error_code = U_ZERO_ERROR;
    out->resize(out_len);

    u_strToUTF8(out->data(), out->length(), &out_len, in.data(), in.length(), &error_code);
    if (!U_SUCCESS(error_code) || out_len <= 0)
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
bool utf8ToUtf16Impl(std::string in, std::u16string* out)
{
    out->clear();

    if (!in.length())
        return true;

    UErrorCode error_code = U_ZERO_ERROR;
    int32_t out_len = 0;
    u_strFromUTF8(nullptr, 0, &out_len, in.data(), in.length(), &error_code);
    if (error_code != U_BUFFER_OVERFLOW_ERROR || out_len <= 0)
        return false;

    error_code = U_ZERO_ERROR;
    out->resize(out_len);

    u_strFromUTF8(out->data(), out->length(), &out_len, in.data(), in.length(), &error_code);
    if (!U_SUCCESS(error_code) || out_len <= 0)
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
bool utf16ToLocalImpl(std::u16string in, std::string* out)
{
    return utf16ToUtf8Impl(in, out);
}

//--------------------------------------------------------------------------------------------------
bool localToUtf16Impl(std::string in, std::u16string* out)
{
    return utf8ToUtf16Impl(in, out);
}

#endif

//--------------------------------------------------------------------------------------------------
template <class InputString, class OutputString>
OutputString asciiConverter(InputString in)
{
    OutputString out;
    out.resize(in.size());

    for (size_t i = 0; i < out.size(); ++i)
        out[i] = static_cast<typename OutputString::value_type>(in[i]);

    return out;
}

} // namespace

//--------------------------------------------------------------------------------------------------
bool utf16ToUtf8(const std::u16string &in, std::string* out)
{
#if defined(WCHAR_T_IS_UTF16)
    return wideToUtf8Impl(in, out);
#else
    return utf16ToUtf8Impl(in, out);
#endif
}

//--------------------------------------------------------------------------------------------------
bool utf8ToUtf16(const std::string &in, std::u16string* out)
{
#if defined(WCHAR_T_IS_UTF16)
    return utf8ToWideImpl(in, out);
#else
    return utf8ToUtf16Impl(in, out);
#endif
}

//--------------------------------------------------------------------------------------------------
std::u16string utf16FromUtf8(const std::string &in)
{
    std::u16string out;
    utf8ToUtf16(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
std::string utf8FromUtf16(const std::u16string &in)
{
    std::string out;
    utf16ToUtf8(in, &out);
    return out;
}

#if defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
bool wideToUtf8(const std::wstring &in, std::string* out)
{
    return wideToUtf8Impl(in, out);
}

//--------------------------------------------------------------------------------------------------
bool utf8ToWide(const std::string &in, std::wstring* out)
{
    return utf8ToWideImpl(in, out);
}

//--------------------------------------------------------------------------------------------------
std::wstring wideFromUtf8(const std::string &in)
{
    std::wstring out;
    utf8ToWide(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
std::string utf8FromWide(const std::wstring &in)
{
    std::string out;
    wideToUtf8(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
bool wideToUtf16(const std::wstring &in, std::u16string* out)
{
#if defined(WCHAR_T_IS_UTF16)
    out->assign(reinterpret_cast<const char16_t*>(in.data()), in.size());
    return true;
#else
#error Implement me!
#endif
}

//--------------------------------------------------------------------------------------------------
bool utf16ToWide(const std::u16string &in, std::wstring* out)
{
#if defined(WCHAR_T_IS_UTF16)
    out->assign(reinterpret_cast<const wchar_t*>(in.data()), in.size());
    return true;
#else
#error Implement me!
#endif
}

//--------------------------------------------------------------------------------------------------
std::wstring wideFromUtf16(const std::u16string &in)
{
    std::wstring out;
    utf16ToWide(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
std::u16string utf16FromWide(const std::wstring &in)
{
    std::u16string out;
    wideToUtf16(in, &out);
    return out;
}

#endif // defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
std::string asciiFromUtf16(const std::u16string &in)
{
    return asciiConverter<std::u16string, std::string>(in);
}

//--------------------------------------------------------------------------------------------------
std::u16string utf16FromAscii(const std::string &in)
{
    return asciiConverter<std::string, std::u16string>(in);
}

#if defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
std::string asciiFromWide(const std::wstring &in)
{
    return asciiConverter<std::wstring, std::string>(in);
}

//--------------------------------------------------------------------------------------------------
std::wstring wideFromAscii(const std::string &in)
{
    return asciiConverter<std::string, std::wstring>(in);
}

#endif // defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
bool utf16ToLocal8Bit(const std::u16string &in, std::string* out)
{
#if defined(WCHAR_T_IS_UTF16)
    return wideToLocalImpl(in, out);
#else
    return utf16ToLocalImpl(in, out);
#endif
}

//--------------------------------------------------------------------------------------------------
bool local8BitToUtf16(const std::string &in, std::u16string* out)
{
#if defined(WCHAR_T_IS_UTF16)
    return localToWideImpl(in, out);
#else
    return localToUtf16Impl(in, out);
#endif
}

//--------------------------------------------------------------------------------------------------
std::u16string utf16FromLocal8Bit(const std::string &in)
{
    std::u16string out;
    local8BitToUtf16(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
std::string local8BitFromUtf16(const std::u16string &in)
{
    std::string out;
    utf16ToLocal8Bit(in, &out);
    return out;
}

#if defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
bool wideToLocal8Bit(const std::wstring &in, std::string* out)
{
    return wideToLocalImpl(in, out);
}

//--------------------------------------------------------------------------------------------------
bool local8BitToWide(const std::string &in, std::wstring* out)
{
    return localToWideImpl(in, out);
}

//--------------------------------------------------------------------------------------------------
std::wstring wideFromLocal8Bit(const std::string &in)
{
    std::wstring out;
    local8BitToWide(in, &out);
    return out;
}

//--------------------------------------------------------------------------------------------------
std::string local8BitFromWide(const std::wstring &in)
{
    std::string out;
    wideToLocal8Bit(in, &out);
    return out;
}

#endif // defined(OS_WIN)

} // namespace base
