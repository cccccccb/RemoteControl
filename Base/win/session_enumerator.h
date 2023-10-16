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

#ifndef BASE_WIN_SESSION_ENUMERATOR_H
#define BASE_WIN_SESSION_ENUMERATOR_H

#include "Base/macros_magic.h"
#include "Base/session_id.h"
#include "Base/win/scoped_wts_memory.h"
#include "Base/base_export.h"

#include <string>

namespace base {
	namespace win {

        class BASE_EXPORT SessionEnumerator
		{
		public:
			SessionEnumerator();
			~SessionEnumerator();

			void advance();
			bool isAtEnd() const;

			static const char* stateToString(WTS_CONNECTSTATE_CLASS state);

			WTS_CONNECTSTATE_CLASS state() const;
			SessionId sessionId() const;

			// A string that contains the name of this session. For example, "services", "console",
			// or "RDP-Tcp#0".
			std::string sessionName() const;
			std::u16string sessionName16() const;

			// A string that contains the name of the computer that the session is running on.
			std::string hostName() const;
			std::u16string hostName16() const;

			// A string that contains the name of the user who is logged on to the session.
			// If no user is logged on to the session, the string is empty.
			std::string userName() const;
			std::u16string userName16() const;

			// A string that contains the domain name of the user who is logged on to the session.
			// If no user is logged on to the session, the string is empty.
			std::string domainName() const;
			std::u16string domainName16() const;

			// A string that contains the name of the farm that the virtual machine is joined to.
			// If the session is not running on a virtual machine that is joined to a farm, the string
			// is empty.
			std::string farmName() const;
			std::u16string farmName16() const;

			bool isUserLocked() const;

		private:
			base::win::ScopedWtsMemory<WTS_SESSION_INFO_1W> info_;
			DWORD count_ = 0;
			DWORD current_ = 0;

			DISALLOW_COPY_AND_ASSIGN(SessionEnumerator);
		};

	}
} // namespace base::win

#endif // BASE_WIN_SESSION_ENUMERATOR_H
