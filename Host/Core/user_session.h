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

#ifndef HOST_USER_SESSION_H
#define HOST_USER_SESSION_H

#include "BuildConfig/build_config.h"
#include "Base/optional.hpp"
#include "Base/session_id.h"
#include "Base/waitable_timer.h"
#include "Base/ipc/ipc_channel.h"
#include "Base/peer/host_id.h"
#include "Base/peer/user_list.h"
#include "Base/win/session_status.h"
#include "Host/Core/client_session.h"
#include "Host/Core/desktop_session_manager.h"
#include "Host/Core/system_settings.h"
#include "Host/Core/unconfirmed_client_session.h"
#include "proto/host_internal.pb.h"

namespace base {
class ScopedTaskRunner;
} // namespace base

namespace host {

class UserSession
    : public base::IpcChannel::Listener,
      public DesktopSession::Delegate,
      public UnconfirmedClientSession::Delegate,
      public ClientSession::Delegate
{
public:
    enum class Type
    {
        CONSOLE = 0,
        RDP = 1
    };

    enum class State
    {
        STARTED = 0,
        DETTACHED = 1,
        FINISHED = 2
    };

    class Delegate
    {
    public:
        virtual ~Delegate() = default;

        virtual void onUserSessionHostIdRequest(const std::string& session_name) = 0;
        virtual void onUserSessionCredentialsChanged() = 0;
        virtual void onUserSessionDettached() = 0;
        virtual void onUserSessionFinished() = 0;
    };

    UserSession(std::shared_ptr<base::TaskRunner> task_runner,
                base::SessionId session_id,
                std::unique_ptr<base::IpcChannel> channel,
                Delegate* delegate);
    ~UserSession() override;

    static const char* typeToString(Type type);
    static const char* stateToString(State state);

    void start(const proto::internal::RouterState& router_state);
    void restart(std::unique_ptr<base::IpcChannel> channel);

    Type type() const { return type_; }
    State state() const { return state_; }
    base::SessionId sessionId() const { return session_id_; }
    base::HostId hostId() const { return host_id_; }
    tl::optional<std::string> sessionName() const;
    base::User user() const;
    size_t clientsCount() const;
    bool isConnectedToUi() const { return channel_ != nullptr; }

    void onClientSession(std::unique_ptr<ClientSession> client_session);
    void onUserSessionEvent(base::win::SessionStatus status, base::SessionId session_id);
    void onHostIdChanged(base::HostId host_id);
    void onSettingsChanged();

protected:
    // base::IpcChannel::Listener implementation.
    void onIpcDisconnected() override;
    void onIpcMessageReceived(const base::ByteArray& buffer) override;

    // DesktopSession::Delegate implementation.
    void onDesktopSessionStarted() override;
    void onDesktopSessionStopped() override;
    void onScreenCaptured(const base::Frame* frame, const base::MouseCursor* cursor) override;
    void onScreenCaptureError(proto::VideoErrorCode error_code) override;
    void onAudioCaptured(const proto::AudioPacket& audio_packet) override;
    void onCursorPositionChanged(const proto::CursorPosition& cursor_position) override;
    void onScreenListChanged(const proto::ScreenList& list) override;
    void onClipboardEvent(const proto::ClipboardEvent& event) override;

    // UnconfirmedClientSession::Delegate implementation.
    void onUnconfirmedSessionAccept(uint32_t id) override;
    void onUnconfirmedSessionReject(uint32_t id) override;

    // ClientSession::Delegate implementation.
    void onClientSessionConfigured() override;
    void onClientSessionFinished() override;
    void onClientSessionVideoRecording(
        const std::string& computer_name, const std::string& user_name, bool started) override;

private:
    void onSessionDettached(const base::Location& location);
    void sendConnectEvent(const ClientSession& client_session);
    void sendDisconnectEvent(uint32_t session_id);
    void updateCredentials(const base::Location& location);
    void sendCredentials(const base::Location& location);
    void killClientSession(uint32_t id);
    void sendHostIdRequest(const base::Location& location);
    void addNewClientSession(std::unique_ptr<ClientSession> client_session);
    void setState(const base::Location& location, State state);
    void mergeAndSendConfiguration();

    std::shared_ptr<base::TaskRunner> task_runner_;
    std::unique_ptr<base::ScopedTaskRunner> scoped_task_runner_;
    std::unique_ptr<base::IpcChannel> channel_;

    Type type_;
    State state_ = State::DETTACHED;
    base::WaitableTimer ui_attach_timer_;
    base::WaitableTimer desktop_dettach_timer_;

    base::SessionId session_id_;
    proto::internal::RouterState router_state_;
    base::HostId host_id_ = base::kInvalidHostId;

    bool password_enabled_ = false;
    uint32_t password_characters_ = 0;
    int password_length_ = 0;
    std::chrono::milliseconds password_expire_interval_ { 0 };
    base::WaitableTimer password_expire_timer_;
    std::string password_;

    bool connection_confirmation_ = false;
    SystemSettings::NoUserAction no_user_action_ = SystemSettings::NoUserAction::ACCEPT;
    std::chrono::milliseconds auto_confirmation_interval_ { 0 };

    using ClientSessionPtr = std::unique_ptr<ClientSession>;
    using ClientSessionList = std::vector<ClientSessionPtr>;
    using UnconfirmedClientSessionPtr = std::unique_ptr<UnconfirmedClientSession>;
    using UnconfirmedClientSessionList = std::vector<UnconfirmedClientSessionPtr>;

    UnconfirmedClientSessionList pending_clients_;
    ClientSessionList desktop_clients_;

    std::unique_ptr<DesktopSessionManager> desktop_session_;
    base::local_shared_ptr<DesktopSessionProxy> desktop_session_proxy_;

    Delegate* delegate_ = nullptr;

    proto::internal::UiToService incoming_message_;
    proto::internal::ServiceToUi outgoing_message_;

    DISALLOW_COPY_AND_ASSIGN(UserSession);
};

} // namespace host

#endif // HOST_USER_SESSION_H
