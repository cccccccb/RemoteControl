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

#ifndef COMMON_DESKTOP_SESSION_CONSTANTS_H
#define COMMON_DESKTOP_SESSION_CONSTANTS_H

#include "BuildConfig/build_config.h"
#include "Common/common_export.h"

#include <cstdint>

namespace common {

COMMON_EXPORT extern const char kSelectScreenExtension[];
COMMON_EXPORT extern const char kPreferredSizeExtension[];
COMMON_EXPORT extern const char kVideoRecordingExtension[];
COMMON_EXPORT extern const char kPowerControlExtension[];
COMMON_EXPORT extern const char kRemoteUpdateExtension[];
COMMON_EXPORT extern const char kSystemInfoExtension[];
COMMON_EXPORT extern const char kTaskManagerExtension[];
COMMON_EXPORT extern const char kVideoPauseExtension[];
COMMON_EXPORT extern const char kAudioPauseExtension[];

COMMON_EXPORT extern const char kSupportedExtensionsForManage[];
COMMON_EXPORT extern const char kSupportedExtensionsForView[];

COMMON_EXPORT extern const uint32_t kSupportedVideoEncodings;
COMMON_EXPORT extern const uint32_t kSupportedAudioEncodings;

COMMON_EXPORT extern const char kFlagDisablePasteAsKeystrokes[];
COMMON_EXPORT extern const char kFlagDisableAudio[];
COMMON_EXPORT extern const char kFlagDisableClipboard[];
COMMON_EXPORT extern const char kFlagDisableCursorShape[];
COMMON_EXPORT extern const char kFlagDisableCursorPosition[];
COMMON_EXPORT extern const char kFlagDisableDesktopEffects[];
COMMON_EXPORT extern const char kFlagDisableDesktopWallpaper[];
COMMON_EXPORT extern const char kFlagDisableFontSmoothing[];
COMMON_EXPORT extern const char kFlagDisableClearClipboard[];
COMMON_EXPORT extern const char kFlagDisableLockAtDisconnect[];
COMMON_EXPORT extern const char kFlagDisableBlockInput[];

} // namespace common

#endif // COMMON_DESKTOP_SESSION_CONSTANTS_H
