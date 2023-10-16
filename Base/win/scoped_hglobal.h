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

#ifndef BASE_WIN_SCOPED_HGLOBAL_H
#define BASE_WIN_SCOPED_HGLOBAL_H

#include "Base/macros_magic.h"

#include <Windows.h>

namespace base {
	namespace win {

		template<class T>
		class ScopedHGLOBAL
		{
		public:
			explicit ScopedHGLOBAL(HGLOBAL glob) : glob_(glob)
			{
				data_ = static_cast<T*>(GlobalLock(glob_));
			}

			~ScopedHGLOBAL()
			{
				GlobalUnlock(glob_);
			}

			T* get()
			{
				return data_;
			}

			size_t size() const
			{
				return GlobalSize(glob_);
			}

			T* operator->() const
			{
				assert(data_ != 0);
				return data_;
			}

			T* release()
			{
				T* data = data_;
				data_ = nullptr;
				return data;
			}

		private:
			HGLOBAL glob_;
			T* data_;

			DISALLOW_COPY_AND_ASSIGN(ScopedHGLOBAL);
		};

	}
} // namespace base::win

#endif // BASE_WIN_SCOPED_HGLOBAL_H
