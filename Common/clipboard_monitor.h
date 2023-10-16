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

#ifndef COMMON_CLIPBOARD_MONITOR_H
#define COMMON_CLIPBOARD_MONITOR_H

#include "Base/threading/thread.h"
#include "Common/clipboard.h"
#include "Common/common_export.h"

namespace common {

class COMMON_EXPORT ClipboardMonitor
    : public base::Thread::Delegate,
      public common::Clipboard::Delegate
{
public:
    ClipboardMonitor();
    ~ClipboardMonitor() override;

    void start(std::shared_ptr<base::TaskRunner> caller_task_runner,
               common::Clipboard::Delegate* delegate);

    void injectClipboardEvent(const proto::ClipboardEvent& event);
    void clearClipboard();

protected:
    // base::Thread::Delegate implementation.
    void onBeforeThreadRunning() override;
    void onAfterThreadRunning() override;

    // common::Clipboard::Delegate implementation.
    void onClipboardEvent(const proto::ClipboardEvent& event) override;

private:
    common::Clipboard::Delegate* delegate_ = nullptr;

    std::unique_ptr<base::Thread> thread_;
    std::shared_ptr<base::TaskRunner> caller_task_runner_;
    std::shared_ptr<base::TaskRunner> self_task_runner_;
    std::unique_ptr<common::Clipboard> clipboard_;

    DISALLOW_COPY_AND_ASSIGN(ClipboardMonitor);
};

} // namespace common

#endif // COMMON_CLIPBOARD_MONITOR_H
