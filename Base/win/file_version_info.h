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

#ifndef BASE_WIN_FILE_VERSION_INFO_H
#define BASE_WIN_FILE_VERSION_INFO_H

#include "Base/macros_magic.h"
#include "Base/filesystem.hpp"

#include <string>
#include <vector>

#include <Windows.h>

struct tagVS_FIXEDFILEINFO;
typedef tagVS_FIXEDFILEINFO VS_FIXEDFILEINFO;

namespace base {
	namespace win {

		class FileVersionInfo
		{
		public:
			~FileVersionInfo();

			// Creates a FileVersionInfo for the specified path. Returns NULL if something
			// goes wrong (typically the file does not exit or cannot be opened). The
			// returned object should be deleted when you are done with it.
			static std::unique_ptr<FileVersionInfo> createFileVersionInfo(
				const ghc::filesystem::path& file_path);

			// Creates a FileVersionInfo for the specified module. Returns NULL in case of error.
			// The returned object should be deleted when you are done with it.
			static std::unique_ptr<FileVersionInfo> createFileVersionInfoForModule(HMODULE module);

			// Accessors to the different version properties.
			// Returns an empty string if the property is not found.
			std::wstring companyName();
			std::wstring companyShortName();
			std::wstring productName();
			std::wstring productShortName();
			std::wstring internalName();
			std::wstring productVersion();
			std::wstring privateBuild();
			std::wstring specialBuild();
			std::wstring comments();
			std::wstring originalFilename();
			std::wstring fileDescription();
			std::wstring fileVersion();
			std::wstring legalCopyright();
			std::wstring legalTrademarks();
			std::wstring lastChange();
			bool isOfficialBuild();

			// Lets you access other properties not covered above.
			bool value(const wchar_t* name, std::wstring* value);

			// Similar to GetValue but returns a wstring (empty string if the property
			// does not exist).
			std::wstring stringValue(const wchar_t* name);

			// Get the fixed file info if it exists. Otherwise NULL
			const VS_FIXEDFILEINFO* fixed_file_info() const { return fixed_file_info_; }

		private:
			// |data| is a VS_VERSION_INFO resource. |language| and |code_page| are
			// extracted from the \VarFileInfo\Translation value of |data|.
			FileVersionInfo(std::vector<uint8_t>&& data, WORD language, WORD code_page);
			FileVersionInfo(void* data, WORD language, WORD code_page);

			const std::vector<uint8_t> owned_data_;
			const void* const data_;
			const WORD language_;
			const WORD code_page_;

			// This is a pointer into |data_| if it exists. Otherwise nullptr.
			const VS_FIXEDFILEINFO* const fixed_file_info_;

			DISALLOW_COPY_AND_ASSIGN(FileVersionInfo);
		};

	}
} // namespace base::win

#endif // BASE_WIN_FILE_VERSION_INFO_H
