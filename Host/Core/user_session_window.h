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

#ifndef HOST_USER_SESSION_WINDOW_H
#define HOST_USER_SESSION_WINDOW_H

#include "Host/Core/user_session_agent.h"

namespace host {

class UserSessionWindow
{
public:
    virtual ~UserSessionWindow() = default;

    virtual void onStatusChanged(UserSessionAgent::Status status) = 0;
    virtual void onClientListChanged(const UserSessionAgent::ClientList& clients) = 0;
    virtual void onCredentialsChanged(const proto::internal::Credentials& credentials) = 0;
    virtual void onRouterStateChanged(const proto::internal::RouterState& state) = 0;
    virtual void onConnectConfirmationRequest(
        const proto::internal::ConnectConfirmationRequest& request) = 0;
    virtual void onVideoRecordingStateChanged(
        const std::string& computer_name, const std::string& user_name, bool started) = 0;
};

} // namespace host

#endif // HOST_USER_SESSION_WINDOW_H
