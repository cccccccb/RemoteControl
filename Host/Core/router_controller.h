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

#ifndef HOST_ROUTER_CONTROLLER_H
#define HOST_ROUTER_CONTROLLER_H

#include "Base/waitable_timer.h"
#include "Base/net/tcp_channel.h"
#include "Base/peer/host_id.h"
#include "Base/peer/relay_peer_manager.h"
#include "proto/host_internal.pb.h"

#include <queue>

namespace base {
class ClientAuthenticator;
} // namespace base

namespace host {

class RouterController
    : public base::TcpChannel::Listener,
      public base::RelayPeerManager::Delegate
{
public:
    explicit RouterController(std::shared_ptr<base::TaskRunner> task_runner);
    ~RouterController() override;

    struct RouterInfo
    {
        std::u16string address;
        uint16_t port = 0;
        base::ByteArray public_key;
    };

    class Delegate
    {
    public:
        virtual ~Delegate() = default;

        virtual void onRouterStateChanged(const proto::internal::RouterState& router_state) = 0;
        virtual void onHostIdAssigned(const std::string& username, base::HostId host_id) = 0;
        virtual void onClientConnected(std::unique_ptr<base::TcpChannel> channel) = 0;
    };

    void start(const RouterInfo& router_info, Delegate* delegate);

    void hostIdRequest(const std::string& session_name);
    void resetHostId(base::HostId host_id);

    const std::u16string& address() const { return router_info_.address; }
    uint16_t port() const { return router_info_.port; }
    const base::ByteArray& publicKey() const { return router_info_.public_key; }

protected:
    // base::TcpChannel::Listener implementation.
    void onTcpConnected() override;
    void onTcpDisconnected(base::NetworkChannel::ErrorCode error_code) override;
    void onTcpMessageReceived(uint8_t channel_id, const base::ByteArray& buffer) override;
    void onTcpMessageWritten(uint8_t channel_id, size_t pending) override;

    // base::RelayPeerManager::Delegate implementation.
    void onNewPeerConnected(std::unique_ptr<base::TcpChannel> channel) override;

private:
    void connectToRouter();
    void delayedConnectToRouter();
    void routerStateChanged(proto::internal::RouterState::State state);
    static const char* routerStateToString(proto::internal::RouterState::State state);

    Delegate* delegate_ = nullptr;

    std::shared_ptr<base::TaskRunner> task_runner_;
    std::unique_ptr<base::TcpChannel> channel_;
    std::unique_ptr<base::ClientAuthenticator> authenticator_;
    std::unique_ptr<base::RelayPeerManager> peer_manager_;
    base::WaitableTimer reconnect_timer_;
    RouterInfo router_info_;

    std::queue<std::string> pending_id_requests_;

    DISALLOW_COPY_AND_ASSIGN(RouterController);
};

} // namespace host

#endif // HOST_ROUTER_CONTROLLER_H
