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

#ifndef BASE_WIN_EVENT_ENUMERATOR_H
#define BASE_WIN_EVENT_ENUMERATOR_H

#include "Base/memory/byte_array.h"
#include "Base/win/scoped_object.h"
#include "Base/base_export.h"

#include <cstdint>
#include <memory>
#include <string>

namespace base {
	namespace win {

        class BASE_EXPORT EventEnumerator
		{
		public:
			EventEnumerator(std::wstring log_name, uint32_t start, uint32_t count);
			~EventEnumerator();

			uint32_t count() const;
			bool isAtEnd() const;
			void advance();

			enum class Type { UNKNOWN, ERR, WARN, INFO, AUDIT_SUCCESS, AUDIT_FAILURE, SUCCESS };

			Type type() const;
			int64_t time() const;
			std::string category() const;
			uint32_t eventId() const;
			std::string source() const;
			std::string description() const;

		private:
			EVENTLOGRECORD* record() const;

			std::wstring log_name_;
			ScopedEventLog event_log_;
			uint32_t records_count_ = 0;
			int end_record_ = 0;

			mutable int current_pos_ = 0;
			mutable ByteArray record_buffer_;

			DISALLOW_COPY_AND_ASSIGN(EventEnumerator);
		};

	}
} // namespace base::win

#endif // BASE_WIN_EVENT_ENUMERATOR_H
