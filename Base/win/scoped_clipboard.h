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

#ifndef BASE_WIN_SCOPED_CLIPBOARD_H
#define BASE_WIN_SCOPED_CLIPBOARD_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

#include <Windows.h>

namespace base {
	namespace win {

        class BASE_EXPORT ScopedClipboard
		{
		public:
			ScopedClipboard() = default;
			~ScopedClipboard();

			bool init(HWND owner);
			BOOL empty();
			void setData(UINT format, HANDLE mem);

			//
			// The caller must not free the handle. The caller should lock the handle,
			// copy the clipboard data, and unlock the handle. All this must be done
			// before this ScopedClipboard is destroyed.
			//
			HANDLE data(UINT format) const;

		private:
			bool opened_ = false;

			DISALLOW_COPY_AND_ASSIGN(ScopedClipboard);
		};

	}
} // namespace base::win

#endif // BASE_WIN_SCOPED_CLIPBOARD_H
