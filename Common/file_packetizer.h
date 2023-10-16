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

#ifndef COMMON_FILE_PACKETIZER_H
#define COMMON_FILE_PACKETIZER_H

#include "Base/filesystem.hpp"
#include "Base/macros_magic.h"
#include "proto/file_transfer.pb.h"

#include <fstream>
#include <memory>

namespace common {

class FilePacketizer
{
public:
    ~FilePacketizer() = default;

    // Creates an instance of the class.
    // Parameter |file_path| contains the full path to the file.
    // If the specified file can not be opened for reading, then returns nullptr.
    static std::unique_ptr<FilePacketizer> create(const ghc::filesystem::path& file_path);

    // Creates a packet for transferring.
    std::unique_ptr<proto::FilePacket> readNextPacket(const proto::FilePacketRequest& request);

private:
    explicit FilePacketizer(std::ifstream&& file_stream);

    std::ifstream file_stream_;

    uint64_t file_size_ = 0;
    uint64_t left_size_ = 0;

    DISALLOW_COPY_AND_ASSIGN(FilePacketizer);
};

} // namespace common

#endif // COMMON_FILE_PACKETIZER_H
