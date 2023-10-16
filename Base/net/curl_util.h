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

#ifndef BASE_NET_CURL_UTIL_H
#define BASE_NET_CURL_UTIL_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

#include <curl/curl.h>

namespace base {

class BASE_EXPORT ScopedCURL
{
public:
    ScopedCURL();
    ~ScopedCURL();

    CURL* get() { return curl_; }

private:
    CURL* curl_;
    DISALLOW_COPY_AND_ASSIGN(ScopedCURL);
};

class BASE_EXPORT ScopedCURLM
{
public:
    ScopedCURLM();
    ~ScopedCURLM();

    CURLM* get() { return curlm_; }

private:
    CURLM* curlm_;
    DISALLOW_COPY_AND_ASSIGN(ScopedCURLM);
};

} // namespace base

#endif // BASE_NET_CURL_UTIL_H
