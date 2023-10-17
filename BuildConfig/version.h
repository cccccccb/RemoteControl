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

#ifndef REMOTECONTROL_VERSION_H
#define REMOTECONTROL_VERSION_H

#define STR_HELPER_INTERNAL(x) #x
#define STR_INTERNAL(x) STR_HELPER_INTERNAL(x)

#define REMOTECONTROL_VERSION_STRING                 \
    STR_INTERNAL(REMOTECONTROL_VERSION_MAJOR) "."    \
    STR_INTERNAL(REMOTECONTROL_VERSION_MINOR) "."    \
    STR_INTERNAL(REMOTECONTROL_VERSION_PATCH) "."    \
    STR_INTERNAL(GIT_COMMIT_COUNT)

#define REMOTECONTROL_VERSION                        \
    REMOTECONTROL_VERSION_MAJOR,REMOTECONTROL_VERSION_MINOR, \
    REMOTECONTROL_VERSION_PATCH,GIT_COMMIT_COUNT

#endif // REMOTECONTROL_VERSION_H
