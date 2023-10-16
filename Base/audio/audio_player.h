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

#ifndef BASE_AUDIO_AUDIO_PLAYER_H
#define BASE_AUDIO_AUDIO_PLAYER_H

#include "Base/macros_magic.h"
#include "Base/base_export.h"

#include <memory>
#include <mutex>
#include <queue>

namespace proto {
class AudioPacket;
} // namespace proto

namespace base {

class AudioOutput;

class BASE_EXPORT AudioPlayer
{
public:
    ~AudioPlayer();

    static std::unique_ptr<AudioPlayer> create();
    void addPacket(std::unique_ptr<proto::AudioPacket> packet);

private:
    AudioPlayer();
    bool init();
    size_t onMoreDataRequired(void* data, size_t size);

    std::unique_ptr<AudioOutput> output_;

    std::queue<std::unique_ptr<proto::AudioPacket>> incoming_queue_;
    std::mutex incoming_queue_lock_;

    std::queue<std::unique_ptr<proto::AudioPacket>> work_queue_;
    size_t source_pos_ = 0;

    DISALLOW_COPY_AND_ASSIGN(AudioPlayer);
};

} // namespace base

#endif // BASE_AUDIO_AUDIO_PLAYER_H
