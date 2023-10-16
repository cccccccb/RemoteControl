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

#include "Host/Core/integrity_check.h"

#include "Base/logging.h"
#include "Base/files/base_paths.h"
#include "Base/strings/unicode.h"
#include "Base/filesystem.hpp"

namespace host {

//--------------------------------------------------------------------------------------------------
bool integrityCheck()
{
#if defined(OS_WIN)
    static const char16_t* kFiles[] =
    {
        u"RemoteControlHost.exe",
        u"RemoteControlDesktopAgent.exe",
        u"RemoteControlService.exe"
    };
    static const size_t kMinFileSize = 5 * 1024; // 5 kB.

    ghc::filesystem::path current_dir;
    if (!base::BasePaths::currentExecDir(&current_dir))
    {
        LOG(LS_ERROR) << "Failed to get the directory of the current executable file";
        return false;
    }

    ghc::filesystem::path current_file;
    if (!base::BasePaths::currentExecFile(&current_file))
    {
        LOG(LS_ERROR) << "Failed to get the path to the current executable file";
        return false;
    }

    bool current_file_found = false;

    for (size_t i = 0; i < std::size(kFiles); ++i)
    {
        ghc::filesystem::path file_path(current_dir);
        file_path.append(kFiles[i]);

        if (file_path == current_file)
            current_file_found = true;

        std::error_code error_code;
        ghc::filesystem::file_status status = ghc::filesystem::status(file_path, error_code);
        if (error_code)
        {
            LOG(LS_ERROR) << "Failed to get file status '" << file_path << "': "
                          << base::utf16FromLocal8Bit(error_code.message());
            return false;
        }

        if (!ghc::filesystem::exists(status))
        {
            LOG(LS_ERROR) << "File '" << file_path << "' does not exist";
            return false;
        }

        if (!ghc::filesystem::is_regular_file(status))
        {
            LOG(LS_ERROR) << "File '" << file_path << "' is not a file";
            return false;
        }

        uintmax_t file_size = ghc::filesystem::file_size(file_path, error_code);
        if (file_size < kMinFileSize)
        {
            LOG(LS_ERROR) << "File '" << file_path << "' is not the correct size: " << file_size;
            return false;
        }
    }

    if (!current_file_found)
    {
        LOG(LS_ERROR) << "Current executable file was not found in the list of components";
        return false;
    }
#endif // defined(OS_WIN)

    return true;
}

} // namespace host
