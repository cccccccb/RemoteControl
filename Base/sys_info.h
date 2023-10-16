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

#ifndef BASE_SYS_INFO_H
#define BASE_SYS_INFO_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

#include <cstdint>
#include <string>

namespace base {

class BASE_EXPORT SysInfo
{
public:
    static std::string operatingSystemName();
    static std::string operatingSystemVersion();
    static std::string operatingSystemArchitecture();
    static std::string operatingSystemDir();
    static std::string operatingSystemKey();
    static int64_t operatingSystemInstallDate();

    static uint64_t uptime();

    static std::string computerName();
    static std::string computerDomain();
    static std::string computerWorkgroup();

    static std::string processorName();
    static std::string processorVendor();
    static int processorPackages();
    static int processorCores();
    static int processorThreads();

private:
    DISALLOW_COPY_AND_ASSIGN(SysInfo);
};

} // namespace base

#endif // BASE_SYS_INFO_H
