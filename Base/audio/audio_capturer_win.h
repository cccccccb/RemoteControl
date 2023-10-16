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

#ifndef BASE_AUDIO_AUDIO_CAPTURER_WIN_H
#define BASE_AUDIO_AUDIO_CAPTURER_WIN_H

#include "Base/macros_magic.h"
#include "Base/threading/thread_checker.h"
#include "Base/win/scoped_co_mem.h"
#include "Base/audio/audio_capturer.h"
#include "Base/audio/audio_volume_filter_win.h"

#include <asio/high_resolution_timer.hpp>

#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <wrl/client.h>

namespace base {

class DefaultAudioDeviceChangeDetector;

// An AudioCapturer implementation for Windows by using Windows Audio Session API, a.k.a. WASAPI.
// It supports up to 8 channels, but treats all layouts as a most commonly used one. E.g. 3.1 and
// surround layouts will both be marked as surround layout.
class AudioCapturerWin : public AudioCapturer
{
public:
    AudioCapturerWin();
    ~AudioCapturerWin() override;

    // AudioCapturer interface.
    bool start(const PacketCapturedCallback& callback) override;

private:
    // Executes deinitialize() and initialize(). If initialize() function call returns false,
    // deinitialize() will be called again to ensure we will initialize COM components again.
    bool resetAndInitialize();

    // Resets all COM components to nullptr, so isInitialized() will return false.
    void deinitialize();

    // Initializes default audio device related components. These components must be recreated once
    // the default audio device changed. Returns false if initialization failed.
    bool initialize();

    // Whether all components are correctly initialized. If last initialize() function call failed,
    // this function will return false. Otherwise this function will return true.
    bool isInitialized() const;

    // Receives all packets from the audio capture endpoint buffer and pushes them to the network.
    void doCapture();

    void onCaptureTimeout(const std::error_code& error_code);

    PacketCapturedCallback callback_;

    proto::AudioPacket::SamplingRate sampling_rate_;
    asio::high_resolution_timer capture_timer_;
    std::chrono::milliseconds audio_device_period_;
    AudioVolumeFilterWin volume_filter_;

    base::win::ScopedCoMem<WAVEFORMATEX> wave_format_ex_;
    Microsoft::WRL::ComPtr<IAudioCaptureClient> audio_capture_client_;
    Microsoft::WRL::ComPtr<IAudioClient> audio_client_;
    Microsoft::WRL::ComPtr<IMMDevice> mm_device_;

    std::unique_ptr<DefaultAudioDeviceChangeDetector> default_device_detector_;
    HRESULT last_capture_error_;
    base::ThreadChecker thread_checker_;

    DISALLOW_COPY_AND_ASSIGN(AudioCapturerWin);
};

} // namespace base

#endif // BASE_AUDIO_AUDIO_CAPTURER_WIN_H
