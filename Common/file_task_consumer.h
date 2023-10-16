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

#ifndef COMMON_FILE_TASK_CONSUMER_H
#define COMMON_FILE_TASK_CONSUMER_H

#include <memory>
#include "Common/common_export.h"

namespace common {

class FileTask;

class COMMON_EXPORT FileTaskConsumer
{
public:
    virtual ~FileTaskConsumer() = default;

    virtual void doTask(std::shared_ptr<FileTask> task) = 0;
};

} // namespace common

#endif // COMMON_FILE_TASK_CONSUMER_H
