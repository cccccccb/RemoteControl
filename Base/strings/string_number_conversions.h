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

#ifndef BASE_STRINGS_STRING_NUMBER_CONVERSIONS_H
#define BASE_STRINGS_STRING_NUMBER_CONVERSIONS_H

#include <cstdint>
#include <string>
#include "Base/base_export.h"

// DO NOT use these functions in any UI unless it's NOT localized on purpose.
// Using these functions in the UI would lead numbers to be formatted in a non-native way.

namespace base {

// Functions to convert a string to a number.
// The string must contain only a number, no other characters are allowed.
// Positive numbers should not have the '+' symbol.
// The value |output| changes only when the conversion is successful. |output| cannot be equal to
// nullptr.
// If it was possible to convert the string to a number, then true is returned, otherwise false.

BASE_EXPORT bool stringToInt(std::string input, int* output);
BASE_EXPORT bool stringToInt(std::u16string input, int* output);

BASE_EXPORT bool stringToUint(std::string input, unsigned int* output);
BASE_EXPORT bool stringToUint(std::u16string input, unsigned int* output);

BASE_EXPORT bool stringToChar(std::string input, signed char* output);
BASE_EXPORT bool stringToChar(std::u16string input, signed char* output);

BASE_EXPORT bool stringToShort(std::string input, short* output);
BASE_EXPORT bool stringToShort(std::u16string input, short* output);

BASE_EXPORT bool stringToUChar(std::string input, unsigned char* output);
BASE_EXPORT bool stringToUChar(std::u16string input, unsigned char* output);

BASE_EXPORT bool stringToUShort(std::string input, unsigned short* output);
BASE_EXPORT bool stringToUShort(std::u16string input, unsigned short* output);

BASE_EXPORT bool stringToULong(std::string input, unsigned long* output);
BASE_EXPORT bool stringToULong(std::u16string input, unsigned long* output);

BASE_EXPORT bool stringToInt64(std::string input, int64_t* output);
BASE_EXPORT bool stringToInt64(std::u16string input, int64_t* output);

BASE_EXPORT bool stringToUint64(std::string input, unsigned long int* output);
BASE_EXPORT bool stringToUint64(std::u16string input, unsigned long int* output);

BASE_EXPORT bool stringToULong64(std::string input, unsigned long long* output);
BASE_EXPORT bool stringToULong64(std::u16string input, unsigned long long* output);

// Functions to convert a number to a string.

BASE_EXPORT std::string numberToString(int value);
BASE_EXPORT std::u16string numberToString16(int value);

BASE_EXPORT std::string numberToString(unsigned int value);
BASE_EXPORT std::u16string numberToString16(unsigned int value);

BASE_EXPORT std::string numberToString(long value);
BASE_EXPORT std::u16string numberToString16(long value);

BASE_EXPORT std::string numberToString(signed char value);
BASE_EXPORT std::u16string numberToString16(signed char value);

BASE_EXPORT std::string numberToString(short value);
BASE_EXPORT std::u16string numberToString16(short value);

BASE_EXPORT std::string numberToString(unsigned char value);
BASE_EXPORT std::u16string numberToString16(unsigned char value);

BASE_EXPORT std::string numberToString(unsigned short value);
BASE_EXPORT std::u16string numberToString16(unsigned short value);

BASE_EXPORT std::string numberToString(unsigned long value);
BASE_EXPORT std::u16string numberToString16(unsigned long value);

BASE_EXPORT std::string numberToString(long long value);
BASE_EXPORT std::u16string numberToString16(long long value);

BASE_EXPORT std::string numberToString(unsigned long long value);
BASE_EXPORT std::u16string numberToString16(unsigned long long value);

} // namespace base

#endif // BASE_STRINGS_STRING_NUMBER_CONVERSIONS_H
