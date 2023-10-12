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

#include "Client/Core/online_checker/online_checker_direct.h"

#include "Base/location.h"
#include "Base/logging.h"
#include "Base/waitable_timer.h"
#include "Base/net/tcp_channel.h"
#include "proto/key_exchange.pb.h"

#include <QDebug>

namespace client {

namespace {

const size_t kNumberOfParallelTasks = 30;
const std::chrono::seconds kTimeout { 15 };

} // namespace

class OnlineCheckerDirect::Instance : public base::TcpChannel::Listener
{
public:
    Instance(int computer_id, const std::u16string& address, uint16_t port,
             std::shared_ptr<base::TaskRunner> task_runner);
    ~Instance() override;

    using FinishCallback = std::function<void(int computer_id, bool online)>;

    void start(FinishCallback finish_callback);
    int computerId() const { return computer_id_; }

protected:
    // base::TcpChannel::Listener implementation.
    void onTcpConnected() override;
    void onTcpDisconnected(base::NetworkChannel::ErrorCode error_code) override;
    void onTcpMessageReceived(uint8_t channel_id, const base::ByteArray& buffer) override;
    void onTcpMessageWritten(uint8_t channel_id, size_t pending) override;

private:
    void onFinished(bool online);

    const int computer_id_;
    const std::u16string address_;
    const uint16_t port_;

    FinishCallback finish_callback_;
    std::unique_ptr<base::TcpChannel> channel_;
    base::WaitableTimer timer_;
};

//--------------------------------------------------------------------------------------------------
OnlineCheckerDirect::Instance::Instance(
    int computer_id, const std::u16string& address, uint16_t port,
    std::shared_ptr<base::TaskRunner> task_runner)
    : computer_id_(computer_id),
      address_(address),
      port_(port),
      timer_(base::WaitableTimer::Type::SINGLE_SHOT, std::move(task_runner))
{
    timer_.start(kTimeout, [this]()
    {
        qInfo() << "Timeout for computer: " << computer_id_;
        onFinished(false);
    });
}

//--------------------------------------------------------------------------------------------------
OnlineCheckerDirect::Instance::~Instance()
{
    finish_callback_ = nullptr;
    channel_->setListener(nullptr);
    channel_.reset();
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::start(FinishCallback finish_callback)
{
    finish_callback_ = std::move(finish_callback);
    DCHECK(finish_callback_);

    qInfo() << "Starting connection to " << address_ << ":" << port_
                 << " (computer: " << computer_id_ << ")";

    channel_ = std::make_unique<base::TcpChannel>();
    channel_->setListener(this);
    channel_->connect(address_, port_);
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::onTcpConnected()
{
    qInfo() << "Connection to " << address_ << ":" << port_
                 << " established (computer: " << computer_id_ << ")";

    proto::ClientHello message;

    message.set_encryption(proto::ENCRYPTION_CHACHA20_POLY1305);
    message.set_identify(proto::IDENTIFY_SRP);

    channel_->setNoDelay(true);
    channel_->resume();
    channel_->send(proto::HOST_CHANNEL_ID_SESSION, base::serialize(message));
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::onTcpDisconnected(
    base::NetworkChannel::ErrorCode /* error_code */)
{
    qInfo() << "Connection aborted for computer: " << computer_id_;
    onFinished(false);
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::onTcpMessageReceived(
    uint8_t /* channel_id */, const base::ByteArray& buffer)
{
    proto::ServerHello message;

    if (!base::parse(buffer, &message))
    {
        qWarning() << "Invalid message received";
        return;
    }

    switch (message.encryption())
    {
        case proto::ENCRYPTION_CHACHA20_POLY1305:
        {
            qInfo() << "Message received for computer: " << computer_id_;
            onFinished(true);
        }
        break;

        default:
        {
            qWarning() << "Invalid encryption method: " << message.encryption();
        }
        return;
    }
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::onTcpMessageWritten(
    uint8_t /* channel_id */, size_t /* pending */)
{
    // Nothing
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::Instance::onFinished(bool online)
{
    if (finish_callback_)
    {
        finish_callback_(computer_id_, online);
        finish_callback_ = nullptr;
    }
    else
    {
        qWarning() << "Invalid callback";
    }
}

//--------------------------------------------------------------------------------------------------
OnlineCheckerDirect::OnlineCheckerDirect(std::shared_ptr<base::TaskRunner> task_runner)
    : task_runner_(std::move(task_runner))
{
    qInfo() << "Ctor";
    DCHECK(task_runner_);
}

//--------------------------------------------------------------------------------------------------
OnlineCheckerDirect::~OnlineCheckerDirect()
{
    qInfo() << "Dtor";

    delegate_ = nullptr;
    pending_queue_.clear();
    work_queue_.clear();
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::start(const ComputerList& computers, Delegate* delegate)
{
    pending_queue_ = computers;
    delegate_ = delegate;
    DCHECK(delegate_);

    if (pending_queue_.empty())
    {
        qInfo() << "No computers in list";
        onFinished(FROM_HERE);
        return;
    }

    size_t count = std::min(pending_queue_.size(), kNumberOfParallelTasks);
    while (count != 0)
    {
        const Computer& computer = pending_queue_.front();
        std::unique_ptr<Instance> instance = std::make_unique<Instance>(
            computer.computer_id, computer.address, computer.port, task_runner_);

        qInfo() << "Instance for '" << computer.computer_id << "' is created (address: "
                     << computer.address << " port: " << computer.port << ")";
        work_queue_.emplace_back(std::move(instance));
        pending_queue_.pop_front();

        --count;
    }

    for (const auto& task : work_queue_)
    {
        task->start(std::bind(&OnlineCheckerDirect::onChecked, this,
                              std::placeholders::_1, std::placeholders::_2));
    }
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::onChecked(int computer_id, bool online)
{
    if (delegate_)
    {
        delegate_->onDirectCheckerResult(computer_id, online);
    }
    else
    {
        qWarning() << "Invalid delegate";
        return;
    }

    if (!pending_queue_.empty())
    {
        const Computer& computer = pending_queue_.front();
        std::unique_ptr<Instance> instance = std::make_unique<Instance>(
            computer.computer_id, computer.address, computer.port, task_runner_);

        qInfo() << "Instance for '" << computer.computer_id << "' is created (address: "
                     << computer.address << " port: " << computer.port << ")";

        work_queue_.emplace_back(std::move(instance));
        work_queue_.back()->start(std::bind(&OnlineCheckerDirect::onChecked, this,
                                            std::placeholders::_1, std::placeholders::_2));
        pending_queue_.pop_front();
    }
    else
    {
        for (auto it = work_queue_.begin(); it != work_queue_.end(); ++it)
        {
            if (it->get()->computerId() == computer_id)
            {
                work_queue_.erase(it);
                break;
            }
        }

        if (work_queue_.empty())
        {
            qInfo() << "No more items in queue";
            onFinished(FROM_HERE);
            return;
        }
    }
}

//--------------------------------------------------------------------------------------------------
void OnlineCheckerDirect::onFinished(const base::Location& location)
{
    qInfo() << "Finished (from: " << location.toString().c_str() << ")";
    if (delegate_)
    {
        delegate_->onDirectCheckerFinished();
    }
    else
    {
        qWarning() << "Invalid delegate";
    }
}

} // namespace client