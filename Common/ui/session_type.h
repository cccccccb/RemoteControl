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

#ifndef COMMON_UI_SESSION_TYPE_H
#define COMMON_UI_SESSION_TYPE_H

#include "proto/common.pb.h"
#include "Common/common_export.h"

#include <QString>

namespace common {

COMMON_EXPORT const char* sessionTypeToString(proto::SessionType session_type);

COMMON_EXPORT QString sessionTypeToLocalizedString(proto::SessionType session_type);

} // namespace common

#endif // COMMON_UI_SESSION_TYPE_H
