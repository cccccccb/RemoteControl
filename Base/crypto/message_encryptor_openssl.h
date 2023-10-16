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

#ifndef BASE_CRYPTO_MESSAGE_ENCRYPTOR_OPENSSL_H
#define BASE_CRYPTO_MESSAGE_ENCRYPTOR_OPENSSL_H

#include "Base/macros_magic.h"
#include "Base/crypto/message_encryptor.h"
#include "Base/crypto/openssl_util.h"
#include "Base/memory/byte_array.h"

namespace base {

class MessageEncryptorOpenssl : public MessageEncryptor
{
public:
    ~MessageEncryptorOpenssl() override;

    static std::unique_ptr<MessageEncryptor> createForAes256Gcm(
        const ByteArray& key, const ByteArray& iv);

    static std::unique_ptr<MessageEncryptor> createForChaCha20Poly1305(
        const ByteArray& key, const ByteArray& iv);

    // MessageEncryptor implementation.
    size_t encryptedDataSize(size_t in_size) override;
    bool encrypt(const void* in, size_t in_size, void* out) override;

private:
    MessageEncryptorOpenssl(EVP_CIPHER_CTX_ptr ctx, const ByteArray& iv);

    EVP_CIPHER_CTX_ptr ctx_;
    ByteArray iv_;

    DISALLOW_COPY_AND_ASSIGN(MessageEncryptorOpenssl);
};

} // namespace base

#endif // BASE_CRYPTO_MESSAGE_ENCRYPTOR_OPENSSL_H
