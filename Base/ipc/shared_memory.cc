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

#include "Base/ipc/shared_memory.h"

#include "Base/ipc/shared_memory_factory_proxy.h"
#include "Base/strings/string_number_conversions.h"
#include "Base/strings/string_util.h"
#include "Base/strings/unicode.h"

#if defined(USE_PCG_GENERATOR)
#include "Others/pcg-cpp/pcg_random.hpp"
#endif // defined(USE_PCG_GENERATOR)

#include <atomic>
#include <random>

#if defined(OS_WIN)
#include <AclAPI.h>
#endif // defined(OS_WIN)

#if defined(OS_LINUX)
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif // defined(OS_LINUX)

namespace base {

namespace {

//--------------------------------------------------------------------------------------------------
int randomInt()
{
#if defined(USE_PCG_GENERATOR)
    pcg_extras::seed_seq_from<std::random_device> device;
    pcg32_fast engine(device);
#else // defined(USE_PCG_GENERATOR)
    std::random_device device;
    std::mt19937 engine(device());
#endif

    std::uniform_int_distribution<> distance(0, std::numeric_limits<int>::max());
    return distance(engine);
}

//--------------------------------------------------------------------------------------------------
int createUniqueId()
{
    static std::atomic_int last_id = randomInt();
    return last_id++;
}

//--------------------------------------------------------------------------------------------------
std::u16string createFilePath(int id)
{
#if defined(OS_WIN)
    static const char16_t kPrefix[] = u"Global\\aspia_";
#else
    static const char16_t kPrefix[] = u"/aspia_shm_";
#endif
    return kPrefix + numberToString16(id);
}

#if defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
bool modeToDesiredAccess(SharedMemory::Mode mode, DWORD* desired_access)
{
    switch (mode)
    {
        case SharedMemory::Mode::READ_ONLY:
            *desired_access = FILE_MAP_READ;
            return true;

        case SharedMemory::Mode::READ_WRITE:
            *desired_access = FILE_MAP_WRITE;
            return true;

        default:
            NOTREACHED();
            return false;
    }
}

//--------------------------------------------------------------------------------------------------
bool createFileMapping(SharedMemory::Mode mode, int id, size_t size, win::ScopedHandle* out)
{
    DWORD protect;

    switch (mode)
    {
        case SharedMemory::Mode::READ_ONLY:
            protect = PAGE_READONLY;
            break;

        case SharedMemory::Mode::READ_WRITE:
            protect = PAGE_READWRITE;
            break;

        default:
            NOTREACHED();
            return false;
    }

    const DWORD low = size & 0xFFFFFFFF;
    const DWORD high = static_cast<DWORD64>(size) >> 32 & 0xFFFFFFFF;

    std::u16string path = createFilePath(id);

    win::ScopedHandle file(CreateFileMappingW(
        INVALID_HANDLE_VALUE, nullptr, protect, high, low, asWide(path)));
    if (!file.isValid())
    {
        PLOG(LS_WARNING) << "CreateFileMappingW failed";
        return false;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        LOG(LS_WARNING) << "Already exists shared memory: " << path;
        return false;
    }

    DWORD error_code = SetSecurityInfo(
        file, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, nullptr, nullptr);
    if (error_code != ERROR_SUCCESS)
    {
        LOG(LS_WARNING) << "SetSecurityInfo failed: " << SystemError::toString(error_code);
        return false;
    }

    out->swap(file);
    return true;
}

//--------------------------------------------------------------------------------------------------
bool openFileMapping(SharedMemory::Mode mode, int id, win::ScopedHandle* out)
{
    DWORD desired_access;
    if (!modeToDesiredAccess(mode, &desired_access))
        return false;

    win::ScopedHandle file(OpenFileMappingW(desired_access, FALSE, asWide(createFilePath(id))));
    if (!file.isValid())
    {
        PLOG(LS_WARNING) << "OpenFileMappingW failed";
        return false;
    }

    out->swap(file);
    return true;
}

//--------------------------------------------------------------------------------------------------
bool mapViewOfFile(SharedMemory::Mode mode, HANDLE file, void** memory)
{
    DWORD desired_access;
    if (!modeToDesiredAccess(mode, &desired_access))
        return false;

    *memory = MapViewOfFile(file, desired_access, 0, 0, 0);
    if (!*memory)
    {
        PLOG(LS_WARNING) << "MapViewOfFile failed";
        return false;
    }

    return true;
}

#endif // defined(OS_WIN)

} // namespace

#if defined(OS_WIN)
const SharedMemory::PlatformHandle kInvalidHandle = nullptr;
#else
const SharedMemory::PlatformHandle kInvalidHandle = -1;
#endif

//--------------------------------------------------------------------------------------------------
SharedMemory::SharedMemory(int id,
                           ScopedPlatformHandle&& handle,
                           void* data,
                           base::local_shared_ptr<SharedMemoryFactoryProxy> factory_proxy)
    : factory_proxy_(std::move(factory_proxy)),
      handle_(std::move(handle)),
      data_(data),
      id_(id)
{
    if (factory_proxy_)
        factory_proxy_->onSharedMemoryCreate(id_);
}

//--------------------------------------------------------------------------------------------------
SharedMemory::~SharedMemory()
{
    if (factory_proxy_)
        factory_proxy_->onSharedMemoryDestroy(id_);

#if defined(OS_WIN)
    UnmapViewOfFile(data_);
#endif // defined(OS_WIN)

#if defined(OS_LINUX)
    struct stat info;
    if (fstat(handle_.get(), &info) != 0)
    {
        PLOG(LS_WARNING) << "fstat failed";
    }
    else
    {
        munmap(data_, info.st_size);
    }

    std::string name = base::local8BitFromUtf16(createFilePath(id_));
    if (shm_unlink(name.c_str()) == -1)
    {
        PLOG(LS_WARNING) << "shm_unlink failed";
    }
#endif // defined(OS_LINUX)
}

//--------------------------------------------------------------------------------------------------
// static
std::unique_ptr<SharedMemory> SharedMemory::create(
    Mode mode, size_t size, base::local_shared_ptr<SharedMemoryFactoryProxy> factory_proxy)
{
    static const int kRetryCount = 10;

#if defined(OS_WIN)
    ScopedPlatformHandle file;
    int id = -1;

    for (int i = 0; i < kRetryCount; ++i)
    {
        id = createUniqueId();
        if (createFileMapping(mode, id, size, &file))
            break;
    }

    if (!file.isValid())
        return nullptr;

    void* memory = nullptr;
    if (!mapViewOfFile(mode, file, &memory))
        return nullptr;

    memset(memory, 0, size);

    return std::unique_ptr<SharedMemory>(
        new SharedMemory(id, std::move(file), memory, std::move(factory_proxy)));
#elif defined(OS_LINUX)
    int id = -1;
    int fd = -1;

    for (int i = 0; i < kRetryCount; ++i)
    {
        id = createUniqueId();

        std::string name = base::local8BitFromUtf16(createFilePath(id));
        int open_flags = O_CREAT;

        if (mode == Mode::READ_ONLY)
        {
            open_flags |= O_RDONLY;
        }
        else
        {
            DCHECK_EQ(mode, Mode::READ_WRITE);
            open_flags |= O_RDWR;
        }

        fd = shm_open(name.c_str(), open_flags, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            PLOG(LS_WARNING) << "shm_open failed";
            continue;
        }

        break;
    }

    if (fd == -1)
    {
        LOG(LS_WARNING) << "Unable to create shared memory";
        return nullptr;
    }

    if (ftruncate(fd, size) == -1)
    {
        PLOG(LS_WARNING) << "ftruncate failed";
        return nullptr;
    }

    int protection = PROT_READ;
    if (mode == Mode::READ_WRITE)
        protection |= PROT_WRITE;

    void* memory = mmap(nullptr, size, protection, MAP_SHARED, fd, 0);
    if (!memory)
    {
        PLOG(LS_WARNING) << "mmap failed";
        return nullptr;
    }

    memset(memory, 0, size);

    return std::unique_ptr<SharedMemory>(
        new SharedMemory(id, ScopedPlatformHandle(fd), memory, std::move(factory_proxy)));
#else
    NOTIMPLEMENTED();
    return nullptr;
#endif
}

//--------------------------------------------------------------------------------------------------
// static
std::unique_ptr<SharedMemory> SharedMemory::open(
    Mode mode, int id, base::local_shared_ptr<SharedMemoryFactoryProxy> factory_proxy)
{
#if defined(OS_WIN)
    ScopedPlatformHandle file;
    if (!openFileMapping(mode, id, &file))
        return nullptr;

    void* memory = nullptr;
    if (!mapViewOfFile(mode, file, &memory))
        return nullptr;

    return std::unique_ptr<SharedMemory>(
        new SharedMemory(id, std::move(file), memory, std::move(factory_proxy)));
#elif defined(OS_LINUX)
    std::string name = base::local8BitFromUtf16(createFilePath(id));
    int open_flags = 0;

    if (mode == Mode::READ_ONLY)
    {
        open_flags |= O_RDONLY;
    }
    else
    {
        DCHECK_EQ(mode, Mode::READ_WRITE);
        open_flags |= O_RDWR;
    }

    int fd = shm_open(name.c_str(), open_flags, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        PLOG(LS_WARNING) << "shm_open failed";
        return nullptr;
    }

    struct stat info;
    if (fstat(fd, &info) != 0)
    {
        PLOG(LS_WARNING) << "Unable to get shared memory size";
        return nullptr;
    }

    int protection = PROT_READ;
    if (mode == Mode::READ_WRITE)
        protection |= PROT_WRITE;

    void* memory = mmap(nullptr, info.st_size, protection, MAP_SHARED, fd, 0);
    if (!memory)
    {
        PLOG(LS_WARNING) << "mmap failed";
        return nullptr;
    }

    return std::unique_ptr<SharedMemory>(
        new SharedMemory(id, ScopedPlatformHandle(fd), memory, std::move(factory_proxy)));
#else
    NOTIMPLEMENTED();
    return nullptr;
#endif
}

} // namespace base
