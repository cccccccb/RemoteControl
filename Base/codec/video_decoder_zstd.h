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

#ifndef BASE_CODEC_VIDEO_DECODER_ZSTD_H
#define BASE_CODEC_VIDEO_DECODER_ZSTD_H

#include "Base/macros_magic.h"
#include "Base/codec/scoped_zstd_stream.h"
#include "Base/codec/video_decoder.h"

namespace base {

class PixelTranslator;

class VideoDecoderZstd : public VideoDecoder
{
public:
    ~VideoDecoderZstd() override;

    static std::unique_ptr<VideoDecoderZstd> create();

    bool decode(const proto::VideoPacket& packet, Frame* target_frame) override;

private:
    VideoDecoderZstd();

    ScopedZstdDStream stream_;
    std::unique_ptr<PixelTranslator> translator_;
    std::unique_ptr<Frame> source_frame_;

    DISALLOW_COPY_AND_ASSIGN(VideoDecoderZstd);
};

} // namespace base

#endif // BASE_CODEC_VIDEO_DECODER_ZSTD_H
