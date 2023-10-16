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

#ifndef BASE_NET_CONNECT_ENUMERATOR_H
#define BASE_NET_CONNECT_ENUMERATOR_H

#include "Base/macros_magic.h"
#include "Base/win/scoped_object.h"
#include "Base/base_export.h"

#include <cstdint>
#include <memory>
#include <string>

namespace base {

class BASE_EXPORT ConnectEnumerator
{
public:
    enum class Mode { TCP, UDP };

    explicit ConnectEnumerator(Mode mode);
    ~ConnectEnumerator();

    bool isAtEnd() const;
    void advance();

    std::string protocol() const;
    std::string processName() const;
    std::string localAddress() const;
    std::string remoteAddress() const;
    uint16_t localPort() const;
    uint16_t remotePort() const;
    std::string state() const;

private:
    const Mode mode_;
    base::win::ScopedHandle snapshot_;
    std::unique_ptr<uint8_t[]> table_buffer_;

    uint32_t num_entries_ = 0;
    uint32_t pos_ = 0;

    DISALLOW_COPY_AND_ASSIGN(ConnectEnumerator);
};

} // namespace base

#endif // BASE_NET_CONNECT_ENUMERATOR_H
