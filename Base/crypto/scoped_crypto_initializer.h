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

#ifndef BASE_CRYPTO_SCOPED_CRYPTO_INITIALIZER_H
#define BASE_CRYPTO_SCOPED_CRYPTO_INITIALIZER_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

namespace base {

class BASE_EXPORT ScopedCryptoInitializer
{
public:
    ScopedCryptoInitializer();
    ~ScopedCryptoInitializer();

    bool isSucceeded() const { return initialized_; }

private:
    bool initialized_ = false;
    DISALLOW_COPY_AND_ASSIGN(ScopedCryptoInitializer);
};

} // namespace base

#endif // BASE_CRYPTO_SCOPED_CRYPTO_INITIALIZER_H
