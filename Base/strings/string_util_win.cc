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

#include "Base/logging.h"

#include <Windows.h>

namespace base {

//--------------------------------------------------------------------------------------------------
int compareCaseInsensitive(std::u16string first, std::u16string second)
{
    int ret = CompareStringW(LOCALE_INVARIANT,
                             NORM_IGNORECASE,
                             reinterpret_cast<const wchar_t*>(first.data()),
                             static_cast<int>(first.size()),
                             reinterpret_cast<const wchar_t*>(second.data()),
                             static_cast<int>(second.size()));
    CHECK_NE(ret, 0);

    // To maintain the C runtime convention of comparing strings, the value 2 can be subtracted
    // from a nonzero return value. Then, the meaning of <0, ==0, and >0 is consistent with the C
    // runtime.
    return ret - 2;
}

//--------------------------------------------------------------------------------------------------
std::u16string toUpper(std::u16string in)
{
    if (in.empty())
        return std::u16string();

    std::u16string out;
    out.resize(in.size());

    if (!LCMapStringW(LOCALE_INVARIANT,
                      LCMAP_UPPERCASE,
                      reinterpret_cast<const wchar_t*>(in.data()), static_cast<int>(in.size()),
                      const_cast<wchar_t*>(reinterpret_cast<const wchar_t*>(out.data())), static_cast<int>(out.size())))
    {
        return std::u16string();
    }

    return out;
}

//--------------------------------------------------------------------------------------------------
std::u16string toLower(std::u16string in)
{
    if (in.empty())
        return std::u16string();

    std::u16string out;
    out.resize(in.size());

    if (!LCMapStringW(LOCALE_INVARIANT,
                      LCMAP_LOWERCASE,
                      reinterpret_cast<const wchar_t*>(in.data()), static_cast<int>(in.size()),
					  const_cast<wchar_t*>(reinterpret_cast<const wchar_t*>(out.data())), static_cast<int>(out.size())))
    {
        return std::u16string();
    }

    return out;
}

} // namespace base
