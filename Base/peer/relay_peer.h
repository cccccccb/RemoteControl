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

#ifndef BASE_PEER_RELAY_PEER_H
#define BASE_PEER_RELAY_PEER_H

#include "Base/macros_magic.h"
#include "Base/optional.hpp"
#include "Base/peer/host_id.h"
#include "Base/memory/byte_array.h"
#include "proto/router_common.pb.h"
#include "proto/router_peer.pb.h"
#include "Base/base_export.h"

#include <asio/ip/tcp.hpp>

namespace base {

class TcpChannel;
class Location;

class BASE_EXPORT RelayPeer
{
public:
    RelayPeer();
    ~RelayPeer();

    class Delegate
    {
    public:
        virtual ~Delegate() = default;

        virtual void onRelayConnectionReady(std::unique_ptr<TcpChannel> channel) = 0;
        virtual void onRelayConnectionError() = 0;
    };

    void start(const proto::ConnectionOffer& offer, Delegate* delegate);
    bool isFinished() const { return is_finished_; }
    const proto::ConnectionOffer& connectionOffer() const { return connection_offer_; }

private:
    void onConnected();
    void onErrorOccurred(const Location& location, const std::error_code& error_code);

    static ByteArray authenticationMessage(const proto::RelayKey& key, const std::string& secret);

    Delegate* delegate_ = nullptr;
    proto::ConnectionOffer connection_offer_;
    bool is_finished_ = false;

    uint32_t message_size_ = 0;
    ByteArray message_;

    asio::io_context& io_context_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::resolver resolver_;

    DISALLOW_COPY_AND_ASSIGN(RelayPeer);
};

} // namespace base

#endif // BASE_PEER_RELAY_PEER_H
