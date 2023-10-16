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

#ifndef HOST_INPUT_INJECTOR_H
#define HOST_INPUT_INJECTOR_H

#include "Base/macros_magic.h"
#include "Base/desktop/geometry.h"
#include "proto/desktop.pb.h"

namespace host {

class InputInjector
{
public:
    virtual ~InputInjector() = default;

    virtual void setScreenOffset(const base::Point& offset) = 0;
    virtual void setBlockInput(bool enable) = 0;
    virtual void injectKeyEvent(const proto::KeyEvent& event) = 0;
    virtual void injectTextEvent(const proto::TextEvent& event) = 0;
    virtual void injectMouseEvent(const proto::MouseEvent& event) = 0;
};

} // namespace host

#endif // HOST_INPUT_INJECTOR_H
