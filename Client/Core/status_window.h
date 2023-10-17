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

#ifndef CLIENT_STATUS_WINDOW_H
#define CLIENT_STATUS_WINDOW_H

#include "Base/peer/client_authenticator.h"

namespace client {

class StatusWindow
{
public:
    virtual ~StatusWindow() = default;

    virtual void onStarted(const std::u16string& address_or_id) = 0;
    virtual void onStopped() = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnected(base::TcpChannel::ErrorCode error_code) = 0;
    virtual void onVersionMismatch(const base::Version& host, const base::Version& client) = 0;
    virtual void onAccessDenied(base::ClientAuthenticator::ErrorCode error_code) = 0;
};

} // namespace client

#endif // CLIENT_STATUS_WINDOW_H
