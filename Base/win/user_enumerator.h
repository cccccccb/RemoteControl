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

#ifndef BASE_WIN_USER_ENUMERATOR_H
#define BASE_WIN_USER_ENUMERATOR_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

#include <cstdint>
#include <string>
#include <vector>

struct _USER_INFO_3;

namespace base {
	namespace win {

        class BASE_EXPORT UserEnumerator
		{
		public:
			UserEnumerator();
			~UserEnumerator();

			void advance();
			bool isAtEnd() const;

			std::string name() const;
			std::string fullName() const;
			std::string comment() const;
			std::string homeDir() const;
			std::vector<std::pair<std::string, std::string>> groups() const;
			bool isDisabled() const;
			bool isPasswordCantChange() const;
			bool isPasswordExpired() const;
			bool isDontExpirePassword() const;
			bool isLockout() const;
			uint32_t numberLogons() const;
			uint32_t badPasswordCount() const;
			uint64_t lastLogonTime() const;

		private:
			_USER_INFO_3* user_info_ = nullptr;
			unsigned long total_entries_ = 0;
			unsigned long current_entry_ = 0;

			DISALLOW_COPY_AND_ASSIGN(UserEnumerator);
		};

	}
} // base::win

#endif // BASE_WIN_USER_ENUMERATOR_H
