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

#ifndef BASE_NET_TCP_CHANNEL_H
#define BASE_NET_TCP_CHANNEL_H

#include "Base/memory/byte_array.h"
#include "Base/net/network_channel.h"
#include "Base/net/variable_size.h"
#include "Base/net/write_task.h"
#include "Base/peer/host_id.h"
#include "Base/base_export.h"

#include <asio/ip/tcp.hpp>
#include <asio/high_resolution_timer.hpp>

#include <queue>

namespace base {

class TcpChannelProxy;
class Location;
class MessageEncryptor;
class MessageDecryptor;
class TcpServer;

class BASE_EXPORT TcpChannel : public NetworkChannel
{
public:
    // Constructor available for client.
    TcpChannel();
    ~TcpChannel() override;

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void onTcpConnected() = 0;
        virtual void onTcpDisconnected(ErrorCode error_code) = 0;
        virtual void onTcpMessageReceived(uint8_t channel_id, const ByteArray& buffer) = 0;
        virtual void onTcpMessageWritten(uint8_t channel_id, size_t pending) = 0;
    };

    std::shared_ptr<TcpChannelProxy> channelProxy();

    // Sets an instance of the class to receive connection status notifications or new messages.
    // You can change this in the process.
    void setListener(Listener* listener);

    // Sets an instance of a class to encrypt and decrypt messages.
    // By default, a fake cryptographer is created that only copies the original message.
    // You must explicitly establish a cryptographer before or after establishing a connection.
    void setEncryptor(std::unique_ptr<MessageEncryptor> encryptor);
    void setDecryptor(std::unique_ptr<MessageDecryptor> decryptor);

    // Gets the address of the remote host as a string.
    std::u16string peerAddress() const;

    // Connects to a host at the specified address and port.
    void connect(std::u16string address, uint16_t port);

    // Returns true if the channel is connected and false if not connected.
    bool isConnected() const;

    // Returns true if the channel is paused and false if not. If the channel is not connected,
    // then the return value is undefined.
    bool isPaused() const;

    // Pauses the channel. After calling the method, new messages will not be read from the socket.
    // If at the time the method was called, the message was read, then notification of this
    // message will be received only after calling method resume().
    void pause();

    // After calling the method, reading new messages will continue.
    void resume();

    // Sending a message. The method call is thread safe. After the call, the message will be added
    // to the queue to be sent.
    void send(uint8_t channel_id, ByteArray&& buffer);

    // Disable or enable the algorithm of Nagle.
    bool setNoDelay(bool enable);

    // Enables or disables sending keep alive packets.
    bool setKeepAlive(bool enable,
                      const Seconds& interval = Seconds(45),
                      const Seconds& timeout = Seconds(15));

    void setChannelIdSupport(bool enable);
    bool hasChannelIdSupport() const;

    bool setReadBufferSize(size_t size);
    bool setWriteBufferSize(size_t size);

    size_t pendingMessages() const { return write_queue_.size(); }

    base::HostId hostId() const { return host_id_; }
    void setHostId(base::HostId host_id) { host_id_ = host_id; }

protected:
    friend class TcpServer;
    friend class RelayPeer;

    // Constructor available for server. An already connected socket is being moved.
    explicit TcpChannel(asio::ip::tcp::socket&& socket);

    // Disconnects to remote host. The method is not available for an external call.
    // To disconnect, you must destroy the channel by calling the destructor.
    void disconnect();

private:
    friend class TcpChannelProxy;

    enum class ReadState
    {
        IDLE,                // No reads are in progress right now.
        READ_SIZE,           // Reading the message size.
        READ_SERVICE_HEADER, // Reading the contents of the service header.
        READ_SERVICE_DATA,   // Reading the contents of the service data.
        READ_USER_DATA,      // Reading the contents of the user data.
        PENDING              // There is a message about which we did not notify.
    };

    struct UserDataHeader
    {
        uint8_t channel_id;
        uint8_t reserved;
    };

    enum ServiceMessageType
    {
        KEEP_ALIVE = 1
    };

    enum KeepAliveFlags
    {
        KEEP_ALIVE_PONG = 0,
        KEEP_ALIVE_PING = 1
    };

    struct ServiceHeader
    {
        uint8_t type;      // Type of service packet (see ServiceDataType).
        uint8_t flags;     // Flags bitmask (depends on the type).
        uint8_t reserved1; // Reserved.
        uint8_t reserved2; // Reserved.
        uint32_t length;   // Additional data size.
    };

    void onErrorOccurred(const Location& location, const std::error_code& error_code);
    void onErrorOccurred(const Location& location, ErrorCode error_code);
    void onMessageWritten(uint8_t channel_id);
    void onMessageReceived();

    void addWriteTask(WriteTask::Type type, uint8_t channel_id, ByteArray&& data);

    void doWrite();
    void onWrite(const std::error_code& error_code, size_t bytes_transferred);

    void doReadSize();
    void onReadSize(const std::error_code& error_code, size_t bytes_transferred);

    void doReadUserData(size_t length);
    void onReadUserData(const std::error_code& error_code, size_t bytes_transferred);

    void doReadServiceHeader();
    void onReadServiceHeader(const std::error_code& error_code, size_t bytes_transferred);

    void doReadServiceData(size_t length);
    void onReadServiceData(const std::error_code& error_code, size_t bytes_transferred);

    void onKeepAliveInterval(const std::error_code& error_code);
    void onKeepAliveTimeout(const std::error_code& error_code);
    void sendKeepAlive(uint8_t flags, const void* data, size_t size);

    std::shared_ptr<TcpChannelProxy> proxy_;
    asio::io_context& io_context_;
    asio::ip::tcp::socket socket_;
    std::unique_ptr<asio::ip::tcp::resolver> resolver_;

    std::unique_ptr<asio::high_resolution_timer> keep_alive_timer_;
    Seconds keep_alive_interval_;
    Seconds keep_alive_timeout_;
    ByteArray keep_alive_counter_;
    TimePoint keep_alive_timestamp_;

    Listener* listener_ = nullptr;
    bool connected_ = false;
    bool paused_ = true;

    std::unique_ptr<MessageEncryptor> encryptor_;
    std::unique_ptr<MessageDecryptor> decryptor_;

    std::queue<WriteTask> write_queue_;
    VariableSizeWriter variable_size_writer_;
    ByteArray write_buffer_;

    ReadState state_ = ReadState::IDLE;
    VariableSizeReader variable_size_reader_;
    ByteArray read_buffer_;
    ByteArray decrypt_buffer_;

    base::HostId host_id_ = base::kInvalidHostId;
    bool is_channel_id_supported_ = false;

    DISALLOW_COPY_AND_ASSIGN(TcpChannel);
};

} // namespace base

#endif // BASE_NET_TCP_CHANNEL_H
