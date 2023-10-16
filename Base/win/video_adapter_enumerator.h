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

#ifndef BASE_WIN_VIDEO_ADAPTER_ENUMERATOR_H
#define BASE_WIN_VIDEO_ADAPTER_ENUMERATOR_H

#include "Base/win/device_enumerator.h"
#include "Base/base_export.h"

namespace base {
	namespace win {

        class BASE_EXPORT VideoAdapterEnumarator : public DeviceEnumerator
		{
		public:
			VideoAdapterEnumarator();

			std::string adapterString() const;
			std::string biosString() const;
			std::string chipString() const;
			std::string dacType() const;
			uint64_t memorySize() const;

		private:
			DISALLOW_COPY_AND_ASSIGN(VideoAdapterEnumarator);
		};

	}
} // namespace base::win

#endif // BASE_WIN_VIDEO_ADAPTER_ENUMERATOR_H
