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

#ifndef COMMON_SYSTEM_INFO_CONSTANTS_H
#define COMMON_SYSTEM_INFO_CONSTANTS_H

#include "Common/common_export.h"

namespace common {

COMMON_EXPORT extern const char kSystemInfo_Summary[];
COMMON_EXPORT extern const char kSystemInfo_Devices[];
COMMON_EXPORT extern const char kSystemInfo_VideoAdapters[];
COMMON_EXPORT extern const char kSystemInfo_Monitors[];
COMMON_EXPORT extern const char kSystemInfo_Printers[];
COMMON_EXPORT extern const char kSystemInfo_PowerOptions[];
COMMON_EXPORT extern const char kSystemInfo_Drivers[];
COMMON_EXPORT extern const char kSystemInfo_Services[];
COMMON_EXPORT extern const char kSystemInfo_EnvironmentVariables[];
COMMON_EXPORT extern const char kSystemInfo_EventLogs[];
COMMON_EXPORT extern const char kSystemInfo_NetworkAdapters[];
COMMON_EXPORT extern const char kSystemInfo_Routes[];
COMMON_EXPORT extern const char kSystemInfo_Connections[];
COMMON_EXPORT extern const char kSystemInfo_NetworkShares[];
COMMON_EXPORT extern const char kSystemInfo_Licenses[];
COMMON_EXPORT extern const char kSystemInfo_Applications[];
COMMON_EXPORT extern const char kSystemInfo_OpenFiles[];
COMMON_EXPORT extern const char kSystemInfo_LocalUsers[];
COMMON_EXPORT extern const char kSystemInfo_LocalUserGroups[];
COMMON_EXPORT extern const char kSystemInfo_Processes[];

} // namespace common

#endif // COMMON_SYSTEM_INFO_CONSTANTS_H
