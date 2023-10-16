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

#ifndef BASE_CRYPTO_SRP_CONSTANTS_H
#define BASE_CRYPTO_SRP_CONSTANTS_H

#include "Base/optional.hpp"

#include <cstdint>
#include <string>

namespace base {

using SrpNgPair = std::pair<std::string, std::string>;

extern const SrpNgPair kSrpNgPair_1024;
extern const SrpNgPair kSrpNgPair_1536;
extern const SrpNgPair kSrpNgPair_2048;
extern const SrpNgPair kSrpNgPair_3072;
extern const SrpNgPair kSrpNgPair_4096;
extern const SrpNgPair kSrpNgPair_6144;
extern const SrpNgPair kSrpNgPair_8192;

tl::optional<SrpNgPair> pairByGroup(std::string group);

} // namespace base

#endif // BASE_CRYPTO_SRP_CONSTANTS_H
