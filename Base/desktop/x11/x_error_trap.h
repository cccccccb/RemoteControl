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

#ifndef BASE_DESKTOP_X11_X_ERROR_TRAP_H
#define BASE_DESKTOP_X11_X_ERROR_TRAP_H

#include "Base/macros_magic.h"

#include <X11/Xlib.h>

namespace base {

// Helper class that registers X Window error handler. Caller can use
// GetLastErrorAndDisable() to get the last error that was caught, if any.
class XErrorTrap
{
public:
    explicit XErrorTrap(Display* display);
    ~XErrorTrap();

    // Returns last error and removes unregisters the error handler.
    int lastErrorAndDisable();

private:
    XErrorHandler original_error_handler_;
    bool enabled_;

    DISALLOW_COPY_AND_ASSIGN(XErrorTrap);
};

} // namespace base

#endif // BASE_DESKTOP_X11_X_ERROR_TRAP_H
