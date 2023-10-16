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

#ifndef BASE_MESSAGE_LOOP_MESSAGE_PUMP_DEFAULT_H
#define BASE_MESSAGE_LOOP_MESSAGE_PUMP_DEFAULT_H

#include "Base/macros_magic.h"
#include "Base/message_loop/message_pump.h"

#include <condition_variable>
#include <mutex>

namespace base {

class MessagePumpDefault : public MessagePump
{
public:
    MessagePumpDefault() = default;
    ~MessagePumpDefault() override = default;

    // MessagePump methods:
    void run(Delegate* delegate) override;
    void quit() override;
    void scheduleWork() override;
    void scheduleDelayedWork(const TimePoint& delayed_work_time) override;

private:
    // This flag is set to false when run() should return.
    bool keep_running_ = true;

    // Used to sleep until there is more work to do.
    std::condition_variable event_;

    bool have_work_ = false;
    std::mutex have_work_lock_;

    // The time at which we should call doDelayedWork.
    TimePoint delayed_work_time_;

    DISALLOW_COPY_AND_ASSIGN(MessagePumpDefault);
};

} // namespace base

#endif // BASE_MESSAGE_LOOP_MESSAGE_PUMP_DEFAULT_H
