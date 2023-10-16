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

#ifndef BASE_DESKTOP_WIN_BITMAP_INFO_H
#define BASE_DESKTOP_WIN_BITMAP_INFO_H

#include <cstdint>

#include <Windows.h>

namespace base {

struct BitmapInfo
{
    BITMAPINFOHEADER header;
    union
    {
        struct
        {
            uint32_t red;
            uint32_t green;
            uint32_t blue;
        } mask;
        RGBQUAD color[256];
    } u;
};

} // namespace base

#endif // BASE_DESKTOP_WIN_BITMAP_INFO_H
