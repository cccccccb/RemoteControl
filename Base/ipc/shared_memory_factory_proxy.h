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

#ifndef BASE_IPC_SHARED_MEMORY_FACTORY_PROXY_H
#define BASE_IPC_SHARED_MEMORY_FACTORY_PROXY_H

#include "Base/macros_magic.h"

namespace base {

class SharedMemoryFactory;

class SharedMemoryFactoryProxy
{
public:
    explicit SharedMemoryFactoryProxy(SharedMemoryFactory* factory);
    ~SharedMemoryFactoryProxy();

    void dettach();

    void onSharedMemoryCreate(int id);
    void onSharedMemoryDestroy(int id);

private:
    SharedMemoryFactory* factory_;

    DISALLOW_COPY_AND_ASSIGN(SharedMemoryFactoryProxy);
};

} // namespace base

#endif // BASE_IPC_SHARED_MEMORY_FACTORY_PROXY_H
