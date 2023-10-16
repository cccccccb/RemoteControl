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

#ifndef BASE_NET_IP_UTIL_H
#define BASE_NET_IP_UTIL_H

#include <string>

namespace base {

bool isValidIpV4Address(std::u16string address);
bool isValidIpV6Address(std::u16string address);

bool isIpInRange(std::u16string ip, std::u16string network, std::u16string mask);

} // namespace base

#endif // BASE_NET_IP_UTIL_H
