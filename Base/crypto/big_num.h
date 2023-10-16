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

#ifndef BASE_CRYPTO_BIG_NUM_H
#define BASE_CRYPTO_BIG_NUM_H

#include "Base/macros_magic.h"
#include "Base/crypto/openssl_util.h"
#include "Base/memory/byte_array.h"

#include <memory>

namespace base {

class BigNum
{
public:
    BigNum() = default;

    BigNum(BigNum&& other) noexcept;
    BigNum& operator=(BigNum&& other) noexcept;

    ~BigNum();

    bool isValid() const { return num_ != nullptr; }

    void reset(bignum_st* num = nullptr);
    bignum_st* release();

    bignum_st* get() { return num_.get(); }
    const bignum_st* get() const { return num_.get(); }

    std::string toStdString() const;
    ByteArray toByteArray() const;

    static BigNum create();
    static BigNum fromStdString(std::string string);
    static BigNum fromByteArray(const ByteArray& array);

    operator bignum_st*() const { return num_.get(); }

    class Context
    {
    public:
        Context(Context&& other) noexcept;
        Context& operator=(Context&& other) noexcept;

        ~Context();

        static Context create();

        bool isValid() const { return ctx_ != nullptr; }

        void reset(bignum_ctx* ctx = nullptr);
        bignum_ctx* release();

        bignum_ctx* get() { return ctx_.get(); }
        const bignum_ctx* get() const { return ctx_.get(); }

        operator bignum_ctx*() const { return ctx_.get(); }

    private:
        Context(bignum_ctx* ctx)
            : ctx_(ctx)
        {
            // Nothing
        }

        BIGNUM_CTX_ptr ctx_;
        DISALLOW_COPY_AND_ASSIGN(Context);
    };

private:
    explicit BigNum(bignum_st* num)
        : num_(num)
    {
        // Nothing
    }

    BigNum(const uint8_t* buffer, size_t buffer_size);

    BIGNUM_ptr num_;

    DISALLOW_COPY_AND_ASSIGN(BigNum);
};

} // namespace base

#endif // BASE_CRYPTO_BIG_NUM_H
