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

#ifndef BASE_PEER_USER_H
#define BASE_PEER_USER_H

#include "Base/memory/byte_array.h"
#include "proto/router_admin.pb.h"
#include "Base/base_export.h"

namespace base {

class BASE_EXPORT User
{
public:
    User() = default;
    ~User() = default;

    User(const User& other) = default;
    User& operator=(const User& other) = default;

    User(User&& other) noexcept = default;
    User& operator=(User&& other) noexcept = default;

    enum Flags { ENABLED = 1 };

    static const size_t kMaxUserNameLength = 64;
    static const size_t kMinPasswordLength = 1;
    static const size_t kMaxPasswordLength = 64;
    static const size_t kSafePasswordLength = 8;

    static bool isValidUserName(std::u16string username);
    static bool isValidPassword(std::u16string password);
    static bool isSafePassword(std::u16string password);

    static User create(std::u16string name, std::u16string password);
    bool isValid() const;

    static User parseFrom(const proto::User& serialized_user);
    proto::User serialize() const;

    static const User kInvalidUser;

    int64_t entry_id = 0;
    std::u16string name;
    std::string group;
    ByteArray salt;
    ByteArray verifier;
    uint32_t sessions = 0;
    uint32_t flags = 0;
};

} // namespace base

#endif // BASE_PEER_USER_H
