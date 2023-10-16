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

#include "Base/strings/string_util.h"

#include "Base/strings/string_util_constants.h"
#include "Base/strings/unicode.h"

#include <cstdint>

namespace base {

namespace {

const std::string kEmptyString;
const std::wstring kEmptyStringWide;

// Assuming that a pointer is the size of a "machine word", then
// uintptr_t is an integer type that is also a machine word.
using MachineWord = uintptr_t;

//--------------------------------------------------------------------------------------------------
bool isMachineWordAligned(const void* pointer)
{
    return !(reinterpret_cast<MachineWord>(pointer) & (sizeof(MachineWord) - 1));
}

template <typename CharacterType>
struct NonASCIIMask;

template <>
struct NonASCIIMask<char>
{
    static constexpr MachineWord value()
    {
        return static_cast<MachineWord>(0x8080808080808080ULL);
    }
};

template <>
struct NonASCIIMask<char16_t>
{
    static constexpr MachineWord value()
    {
        return static_cast<MachineWord>(0xFF80FF80FF80FF80ULL);
    }
};

template <>
struct NonASCIIMask<wchar_t>
{
    static constexpr MachineWord value()
    {
        return static_cast<MachineWord>(0xFFFFFF80FFFFFF80ULL);
    }
};

//--------------------------------------------------------------------------------------------------
template <class Char>
bool doIsStringASCII(const Char* characters, size_t length)
{
    if (!length)
        return true;

    constexpr MachineWord non_ascii_bit_mask = NonASCIIMask<Char>::value();
    MachineWord all_char_bits = 0;
    const Char* end = characters + length;

    // Prologue: align the input.
    while (!isMachineWordAligned(characters) && characters < end)
        all_char_bits |= *characters++;
    if (all_char_bits & non_ascii_bit_mask)
        return false;

    // Compare the values of CPU word size.
    constexpr size_t chars_per_word = sizeof(MachineWord) / sizeof(Char);
    constexpr int batch_count = 16;
    while (characters <= end - batch_count * chars_per_word)
    {
        all_char_bits = 0;
        for (int i = 0; i < batch_count; ++i)
        {
            all_char_bits |= *(reinterpret_cast<const MachineWord*>(characters));
            characters += chars_per_word;
        }
        if (all_char_bits & non_ascii_bit_mask)
            return false;
    }

    // Process the remaining words.
    all_char_bits = 0;
    while (characters <= end - chars_per_word)
    {
        all_char_bits |= *(reinterpret_cast<const MachineWord*>(characters));
        characters += chars_per_word;
    }

    // Process the remaining bytes.
    while (characters < end)
        all_char_bits |= *characters++;

    return !(all_char_bits & non_ascii_bit_mask);
}

//--------------------------------------------------------------------------------------------------
bool isUnicodeWhitespace(char16_t c)
{
    // kWhitespaceWide is a NULL-terminated string
    for (const char16_t* cur = kWhitespaceUtf16; *cur; ++cur)
    {
        if (*cur == c)
            return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template<typename CharType>
std::basic_string<CharType> collapseWhitespaceT(
    std::basic_string<CharType> text, bool trim_sequences_with_line_breaks)
{
    std::basic_string<CharType> result;
    result.resize(text.size());

    // Set flags to pretend we're already in a trimmed whitespace sequence, so we
    // will trim any leading whitespace.
    bool in_whitespace = true;
    bool already_trimmed = true;

    int chars_written = 0;
    for (typename std::basic_string<CharType>::const_iterator i(text.begin());
         i != text.end(); ++i)
    {
        if (isUnicodeWhitespace(static_cast<char16_t>(*i)))
        {
            if (!in_whitespace)
            {
                // Reduce all whitespace sequences to a single space.
                in_whitespace = true;
                result[static_cast<size_t>(chars_written++)] = u' ';
            }
            if (trim_sequences_with_line_breaks && !already_trimmed &&
                ((*i == '\n') || (*i == '\r')))
            {
                // Whitespace sequences containing CR or LF are eliminated entirely.
                already_trimmed = true;
                --chars_written;
            }
        }
        else
        {
            // Non-whitespace chracters are copied straight across.
            in_whitespace = false;
            already_trimmed = false;
            result[static_cast<size_t>(chars_written++)] = *i;
        }
    }

    if (in_whitespace && !already_trimmed)
    {
        // Any trailing whitespace is eliminated.
        --chars_written;
    }

    result.resize(static_cast<size_t>(chars_written));
    return result;
}

//--------------------------------------------------------------------------------------------------
template<typename StringType>
void removeCharsT(StringType* str, std::basic_string<typename StringType::value_type> substr)
{
    size_t pos;

    while ((pos = str->find(substr)) != StringType::npos)
        str->erase(pos, substr.length());
}

} // namespace

//--------------------------------------------------------------------------------------------------
std::string replaceLfByCrLf(const std::string& in)
{
    if (in.empty())
        return std::string();

    std::string out;
    out.resize(2 * in.size());

    char* out_p_begin = &out[0];
    char* out_p = out_p_begin;
    const char* in_p_begin = &in[0];
    const char* in_p_end = &in[in.size()];

    for (const char* in_p = in_p_begin; in_p < in_p_end; ++in_p)
    {
        char c = *in_p;

        if (c == '\n')
            *out_p++ = '\r';

        *out_p++ = c;
    }

    out.resize(static_cast<size_t>(out_p - out_p_begin));
    return out;
}

//--------------------------------------------------------------------------------------------------
std::string replaceCrLfByLf(const std::string& in)
{
    if (in.empty())
        return std::string();

    std::string out;
    out.resize(in.size());

    char* out_p_begin = &out[0];
    char* out_p = out_p_begin;
    const char* in_p_begin = &in[0];
    const char* in_p_end = &in[in.size()];

    for (const char* in_p = in_p_begin; in_p < in_p_end; ++in_p)
    {
        char c = *in_p;

        if ((c == '\r') && (in_p + 1 < in_p_end) && (*(in_p + 1) == '\n'))
        {
            *out_p++ = '\n';
            ++in_p;
        }
        else
        {
            *out_p++ = c;
        }
    }

    out.resize(static_cast<size_t>(out_p - out_p_begin));
    return out;
}

//--------------------------------------------------------------------------------------------------
bool isStringUTF8(std::string str)
{
    const char* ptr = str.data();
    const char* ptr_end = str.data() + str.length();

    while (ptr != ptr_end)
    {
        if ((*ptr & 0x80) == 0)
        {
            // Single-byte symbol.
            ++ptr;
        }
        else if ((*ptr & 0xc0) == 0x80 || (*ptr & 0xfe) == 0xfe)
        {
            // Invalid first byte.
            return false;
        }
        else
        {
            // First byte of a multi-byte symbol. The bits from 2 to 6 are the count
            // of continuation bytes (up to 5 of them).
            for (char first = *ptr << 1; first & 0x80; first <<= 1)
            {
                ++ptr;

                // Missing continuation byte.
                if (ptr == ptr_end)
                    return false;

                // Invalid continuation byte.
                if ((*ptr & 0xc0) != 0x80)
                    return false;
            }

            ++ptr;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
bool isStringASCII(std::string string)
{
    return doIsStringASCII(string.data(), string.length());
}

//--------------------------------------------------------------------------------------------------
bool isStringASCII(std::u16string string)
{
    return doIsStringASCII(string.data(), string.length());
}

//--------------------------------------------------------------------------------------------------
std::u16string collapseWhitespace(std::u16string text, bool trim_sequences_with_line_breaks)
{
    return collapseWhitespaceT<char16_t>(text, trim_sequences_with_line_breaks);
}

#if defined(OS_WIN)
//--------------------------------------------------------------------------------------------------
std::wstring collapseWhitespace(std::wstring text, bool trim_sequences_with_line_breaks)
{
    return collapseWhitespaceT<wchar_t>(text, trim_sequences_with_line_breaks);
}
#endif // defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
std::string collapseWhitespaceASCII(std::string text, bool trim_sequences_with_line_breaks)
{
    return collapseWhitespaceT<char>(text, trim_sequences_with_line_breaks);
}

namespace {

//--------------------------------------------------------------------------------------------------
template <class CharType>
int compareCaseInsensitiveASCIIT(std::basic_string<CharType> a,
                                 std::basic_string<CharType> b)
{
    // Find the first characters that aren't equal and compare them.  If the end of one of the
    // strings is found before a nonequal character, the lengths of the strings are compared.
    size_t i = 0;

    while (i < a.length() && i < b.length())
    {
        CharType lower_a = toLowerASCII(a[i]);
        CharType lower_b = toLowerASCII(b[i]);

        if (lower_a < lower_b)
            return -1;
        if (lower_a > lower_b)
            return 1;
        ++i;
    }

    // End of one string hit before finding a different character. Expect the
    // common case to be "strings equal" at this point so check that first.
    if (a.length() == b.length())
        return 0;

    if (a.length() < b.length())
        return -1;

    return 1;
}

} // namespace

//--------------------------------------------------------------------------------------------------
int compareCaseInsensitiveASCII(std::string first, std::string second)
{
    return compareCaseInsensitiveASCIIT<char>(first, second);
}

//--------------------------------------------------------------------------------------------------
int compareCaseInsensitiveASCII(std::u16string first, std::u16string second)
{
    return compareCaseInsensitiveASCIIT<char16_t>(first, second);
}

//--------------------------------------------------------------------------------------------------
template<typename CharType>
bool startsWithT(std::basic_string<CharType> str, std::basic_string<CharType> search_for)
{
    if (search_for.size() > str.size())
        return false;

    return str.substr(0, search_for.size()) == search_for;
}

//--------------------------------------------------------------------------------------------------
bool startsWith(std::string str, std::string search_for)
{
    return startsWithT<char>(str, search_for);
}

//--------------------------------------------------------------------------------------------------
bool startsWith(std::u16string str, std::u16string search_for)
{
    return startsWithT<char16_t>(str, search_for);
}

#if defined(OS_WIN)
//--------------------------------------------------------------------------------------------------
bool startsWith(std::wstring str, std::wstring search_for)
{
    return startsWithT<wchar_t>(str, search_for);
}
#endif // defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
template <typename CharType>
bool endsWithT(std::basic_string<CharType> str, std::basic_string<CharType> search_for)
{
    if (search_for.size() > str.size())
        return false;

    std::basic_string<CharType> source =
        str.substr(str.size() - search_for.size(), search_for.size());

    return source == search_for;
}

//--------------------------------------------------------------------------------------------------
bool endsWith(std::string str, std::string search_for)
{
    return endsWithT<char>(str, search_for);
}

//--------------------------------------------------------------------------------------------------
bool endsWith(std::u16string str, std::u16string search_for)
{
    return endsWithT<char16_t>(str, search_for);
}

#if defined(OS_WIN)
//--------------------------------------------------------------------------------------------------
bool endsWith(std::wstring str, std::wstring search_for)
{
    return endsWithT<wchar_t>(str, search_for);
}
#endif // defined(OS_WIN)

namespace {

//--------------------------------------------------------------------------------------------------
template <typename CharType>
TrimPositions trimStringT(std::basic_string<CharType> input,
                          std::basic_string<CharType> trim_chars,
                          TrimPositions positions,
                          std::basic_string<CharType>* output)
{
    // Find the edges of leading/trailing whitespace as desired. Need to use
    // a StringPiece version of input to be able to call find* on it with the
    // StringPiece version of trim_chars (normally the trim_chars will be a
    // constant so avoid making a copy).
    const size_t last_char = input.length() - 1;
    const size_t first_good_char = (positions & TRIM_LEADING) ?
        input.find_first_not_of(trim_chars) : 0;
    const size_t last_good_char = (positions & TRIM_TRAILING) ?
        input.find_last_not_of(trim_chars) : last_char;

    // When the string was all trimmed, report that we stripped off characters
    // from whichever position the caller was interested in. For empty input, we
    // stripped no characters, but we still need to clear |output|.
    if (input.empty() ||
        first_good_char == std::basic_string<CharType>::npos ||
        last_good_char == std::basic_string<CharType>::npos)
    {
        bool input_was_empty = input.empty();  // in case output == &input
        output->clear();
        return input_was_empty ? TRIM_NONE : positions;
    }

    // Trim.
    output->assign(input.data() + first_good_char, last_good_char - first_good_char + 1);

    // Return where we trimmed from.
    return static_cast<TrimPositions>(
        (first_good_char == 0 ? TRIM_NONE : TRIM_LEADING) |
        (last_good_char == last_char ? TRIM_NONE : TRIM_TRAILING));
}

//--------------------------------------------------------------------------------------------------
template <typename StringType>
StringType trimStringViewT(StringType input, StringType trim_chars, TrimPositions positions)
{
    size_t begin = (positions & TRIM_LEADING) ? input.find_first_not_of(trim_chars) : 0;
    size_t end = (positions & TRIM_TRAILING) ? input.find_last_not_of(trim_chars) + 1 : input.size();

    if (begin > input.size())
        begin = input.size();

    if (end > input.size())
        end = input.size();

    return input.substr(begin, end - begin);
}

} // namespace

//--------------------------------------------------------------------------------------------------
bool trimString(std::string input, std::string trim_chars, std::string* output)
{
    return trimStringT(input, trim_chars, TRIM_ALL, output) != TRIM_NONE;
}

//--------------------------------------------------------------------------------------------------
bool trimString(std::u16string input, std::u16string trim_chars, std::u16string* output)
{
    return trimStringT(input, trim_chars, TRIM_ALL, output) != TRIM_NONE;
}

//--------------------------------------------------------------------------------------------------
std::u16string trimString(std::u16string input,
                               std::u16string trim_chars,
                               TrimPositions positions)
{
    return trimStringViewT(input, trim_chars, positions);
}

//--------------------------------------------------------------------------------------------------
std::string trimString(std::string input,
                            std::string trim_chars,
                            TrimPositions positions)
{
    return trimStringViewT(input, trim_chars, positions);
}

//--------------------------------------------------------------------------------------------------
TrimPositions trimWhitespace(std::u16string input,
                             TrimPositions positions,
                             std::u16string* output)
{
    return trimStringT(input, std::u16string(kWhitespaceUtf16), positions, output);
}

//--------------------------------------------------------------------------------------------------
std::u16string trimWhitespace(std::u16string input, TrimPositions positions)
{
    return trimStringViewT(input, std::u16string(kWhitespaceUtf16), positions);
}

//--------------------------------------------------------------------------------------------------
TrimPositions trimWhitespaceASCII(std::string input,
                                  TrimPositions positions,
                                  std::string* output)
{
    return trimStringT(input, std::string(kWhitespaceASCII), positions, output);
}

//--------------------------------------------------------------------------------------------------
std::string trimWhitespaceASCII(std::string input, TrimPositions positions)
{
    return trimStringViewT(input, std::string(kWhitespaceASCII), positions);
}

//--------------------------------------------------------------------------------------------------
void removeChars(std::string* str, std::string substr)
{
    removeCharsT(str, substr);
}

//--------------------------------------------------------------------------------------------------
void removeChars(std::wstring* str, std::wstring substr)
{
    removeCharsT(str, substr);
}

namespace {

//--------------------------------------------------------------------------------------------------
template <typename CharType>
std::basic_string<CharType> toLowerASCIIT(std::basic_string<CharType> str)
{
    std::basic_string<CharType> ret;
    ret.reserve(str.size());

    for (size_t i = 0; i < str.size(); ++i)
        ret.push_back(toLowerASCII(str[i]));

    return ret;
}

//--------------------------------------------------------------------------------------------------
template <typename CharType>
std::basic_string<CharType> toUpperASCIIT(std::basic_string<CharType> str)
{
    std::basic_string<CharType> ret;
    ret.reserve(str.size());

    for (size_t i = 0; i < str.size(); ++i)
        ret.push_back(toUpperASCII(str[i]));

    return ret;
}

}  // namespace

//--------------------------------------------------------------------------------------------------
std::u16string toUpperASCII(std::u16string in)
{
    return toUpperASCIIT<char16_t>(in);
}

//--------------------------------------------------------------------------------------------------
std::u16string toLowerASCII(std::u16string in)
{
    return toLowerASCIIT<char16_t>(in);
}

//--------------------------------------------------------------------------------------------------
std::string toUpperASCII(std::string in)
{
    return toUpperASCIIT<char>(in);
}

//--------------------------------------------------------------------------------------------------
std::string toLowerASCII(std::string in)
{
    return toLowerASCIIT<char>(in);
}

//--------------------------------------------------------------------------------------------------
const std::string& emptyString()
{
    return kEmptyString;
}

//--------------------------------------------------------------------------------------------------
const std::wstring& emptyStringW()
{
    return kEmptyStringWide;
}

} // namespace base
