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

#ifndef CLIENT_CONFIG_FACTORY_H
#define CLIENT_CONFIG_FACTORY_H

#include "Base/macros_magic.h"
#include "proto/desktop.pb.h"

namespace client {

class ConfigFactory
{
public:
    static proto::DesktopConfig defaultDesktopManageConfig();
    static proto::DesktopConfig defaultDesktopViewConfig();

    static void setDefaultDesktopManageConfig(proto::DesktopConfig* config);
    static void setDefaultDesktopViewConfig(proto::DesktopConfig* config);

    // Corrects invalid values in the configuration if they are.
    static void fixupDesktopConfig(proto::DesktopConfig* config);

private:
    DISALLOW_COPY_AND_ASSIGN(ConfigFactory);
};

} // namespace client

#endif // CLIENT_CONFIG_FACTORY_H
