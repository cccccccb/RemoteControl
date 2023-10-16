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

#ifndef BASE_CRYPTO_DATA_CRYPTOR_FAKE_H
#define BASE_CRYPTO_DATA_CRYPTOR_FAKE_H

#include "Base/macros_magic.h"
#include "Base/crypto/data_cryptor.h"

namespace base {

class DataCryptorFake : public DataCryptor
{
public:
    DataCryptorFake() = default;
    ~DataCryptorFake() override = default;

    bool encrypt(std::string in, std::string* out) override;
    bool decrypt(std::string in, std::string* out) override;

private:
    DISALLOW_COPY_AND_ASSIGN(DataCryptorFake);
};

} // namespace base

#endif // BASE_CRYPTO_DATA_CRYPTOR_FAKE_H
