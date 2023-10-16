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

#ifndef BASE_WIN_DEVICE_H
#define BASE_WIN_DEVICE_H

#include "Base/win/scoped_object.h"
#include "Base/filesystem.hpp"

namespace base {
	namespace win {

		class Device
		{
		public:
			Device() = default;
			virtual ~Device();

			bool open(const ghc::filesystem::path& device_path,
				DWORD desired_access,
				DWORD share_mode);
			bool open(const ghc::filesystem::path& device_path);
			void close();
			bool ioControl(DWORD io_control_code,
				LPVOID input_buffer,
				DWORD input_buffer_size,
				LPVOID output_buffer,
				DWORD output_buffer_size,
				LPDWORD bytes_returned);

		private:
			ScopedHandle device_;

			DISALLOW_COPY_AND_ASSIGN(Device);
		};

	}
} // namespace base::win

#endif // BASE_WIN_DEVICE_H
