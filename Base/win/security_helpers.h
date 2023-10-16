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

#ifndef BASE_WIN_SECURITY_HELPERS_H
#define BASE_WIN_SECURITY_HELPERS_H

#include "Base/memory/typed_buffer.h"

#include <string>

#include <Windows.h>

namespace base {
	namespace win {

		using ScopedAcl = TypedBuffer<ACL>;
		using ScopedSd = TypedBuffer<SECURITY_DESCRIPTOR>;
		using ScopedSid = TypedBuffer<SID>;

		// Initializes COM security of the process applying the passed security
		// descriptor.  The function configures the following settings:
		//  - Server authenticates that all data received is from the expected client.
		//  - Server can impersonate clients to check their identity but cannot act on
		//    their behalf.
		//  - Caller's identity is verified on every call (Dynamic cloaking).
		//  - Unless |activate_as_activator| is true, activations where the server
		//    would run under this process's identity are prohibited.
		bool initializeComSecurity(const wchar_t* security_descriptor,
			const wchar_t* mandatory_label,
			bool activate_as_activator);

		bool userSidString(std::wstring* user_sid);

		ScopedSd convertSddlToSd(const std::wstring& sddl);

	}
} // namespace base::win

#endif // BASE_WIN_SECURITY_HELPERS_H
