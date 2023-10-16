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

#ifndef BASE_CODEC_AUDIO_DECODER_H
#define BASE_CODEC_AUDIO_DECODER_H

#include "proto/desktop.pb.h"
#include "Base/base_export.h"

#include <memory>

namespace proto {
class AudioPacket;
} // namespace proto

namespace base {

class BASE_EXPORT AudioDecoder
{
public:
    static std::unique_ptr<AudioDecoder> create(proto::AudioEncoding encoding);

    virtual ~AudioDecoder() = default;

    // Returns the decoded packet. If the packet is invalid, then a NULL
    // std::unique_ptr is returned.
    virtual std::unique_ptr<proto::AudioPacket> decode(const proto::AudioPacket& packet) = 0;
};

} // namespace base

#endif // BASE_CODEC_AUDIO_DECODER_H
