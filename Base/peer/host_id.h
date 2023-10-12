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

#ifndef BASE_PEER_HOST_ID_H
#define BASE_PEER_HOST_ID_H

#include "Base/base_export.h"

#include <string>

namespace base {

using HostId = unsigned long long;

BASE_EXPORT extern const HostId kInvalidHostId;

// Checks if a string is a host ID.
BASE_EXPORT bool isHostId(std::u16string str);
BASE_EXPORT bool isHostId(std::string str);

// Converts a string to a host ID.
// If the string is empty or the conversion failed, then |kInvalidHostId| is returned.
BASE_EXPORT HostId stringToHostId(std::u16string str);
BASE_EXPORT HostId stringToHostId(std::string str);

// Converts a host ID to a string.
// If the host ID is |kInvalidHostId|, an empty string is returned.
BASE_EXPORT std::u16string hostIdToString16(HostId host_id);
BASE_EXPORT std::string hostIdToString(HostId host_id);

} // namespace base

#endif // BASE_PEER_HOST_ID_H
