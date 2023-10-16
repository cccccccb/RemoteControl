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

#ifndef BASE_CODEC_WEBM_VIDEO_ENCODER_H
#define BASE_CODEC_WEBM_VIDEO_ENCODER_H

#include "Base/macros_magic.h"
#include "Base/codec/scoped_vpx_codec.h"
#include "Base/desktop/geometry.h"
#include "Base/memory/byte_array.h"
#include "Base/base_export.h"

#define VPX_CODEC_DISABLE_COMPAT 1
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

namespace proto {
class VideoPacket;
} // namespace proto

namespace base {

class Frame;

class BASE_EXPORT WebmVideoEncoder
{
public:
    WebmVideoEncoder();
    ~WebmVideoEncoder();

    bool encode(const Frame& frame, proto::VideoPacket* packet);

private:
    void createImage();
    bool createCodec();

    Size last_frame_size_;

    // VPX image and buffer to hold the actual YUV planes.
    std::unique_ptr<vpx_image_t> image_;
    ByteArray image_buffer_;

    vpx_codec_enc_cfg_t config_;
    ScopedVpxCodec codec_;
};

} // namespace base

#endif // BASE_CODEC_WEBM_VIDEO_ENCODER_H
