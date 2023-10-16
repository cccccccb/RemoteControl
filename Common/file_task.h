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

#ifndef COMMON_FILE_TASK_H
#define COMMON_FILE_TASK_H

#include "Base/macros_magic.h"
#include "Common/common_export.h"

#include <memory>

namespace proto {
class FileRequest;
class FileReply;
} // namespace proto

namespace common {

class FileTaskFactory;
class FileTaskProducerProxy;

class COMMON_EXPORT FileTask : public std::enable_shared_from_this<FileTask>
{
public:
    enum class Target
    {
        LOCAL, // Local task.
        REMOTE // Remote task.
    };

    FileTask(std::shared_ptr<FileTaskProducerProxy> producer_proxy,
             std::unique_ptr<proto::FileRequest> request,
             Target target);
    virtual ~FileTask();

    // Returns the target of the current request. It can be a local computer or a remote computer.
    Target target() const { return target_; }

    // Returns the data of the current request.
    const proto::FileRequest& request() const;

    // Returns reply data for the current request.
    // If method setReply has not been called and data has not been set, an empty reply will be
    // returned.
    const proto::FileReply& reply() const;

    // Sets the reply to the current request. The sender will be notified of this reply.
    void setReply(std::unique_ptr<proto::FileReply> reply);

private:
    std::shared_ptr<FileTaskProducerProxy> producer_proxy_;
    const Target target_;

    std::unique_ptr<proto::FileRequest> request_;
    std::unique_ptr<proto::FileReply> reply_;

    DISALLOW_COPY_AND_ASSIGN(FileTask);
};

} // namespace common

#endif // COMMON_FILE_TASK_H
