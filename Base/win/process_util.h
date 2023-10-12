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

#ifndef BASE_WIN_PROCESS_UTIL_H
#define BASE_WIN_PROCESS_UTIL_H

#include "Base/command_line.h"
#include "Base/win/scoped_object.h"
#include "Base/filesystem.hpp"

namespace base {
	namespace win {

        BASE_EXPORT bool isProcessElevated();

		enum class ProcessExecuteMode
		{
			NORMAL, ELEVATE
		};

        BASE_EXPORT bool createProcess(
			const CommandLine& command_line,
			ProcessExecuteMode mode = ProcessExecuteMode::NORMAL);

        BASE_EXPORT bool createProcess(
			const ghc::filesystem::path& program,
			std::u16string arguments,
			ProcessExecuteMode mode = ProcessExecuteMode::NORMAL);

        BASE_EXPORT bool copyProcessToken(DWORD desired_access, ScopedHandle* token_out);

		// Creates a copy of the current process with SE_TCB_NAME privilege enabled.
        BASE_EXPORT bool createPrivilegedToken(ScopedHandle* token_out);

        BASE_EXPORT bool isProcessStartedFromService();

	}
} // namespace base::win

#endif // BASE_WIN_PROCESS_UTIL_H
