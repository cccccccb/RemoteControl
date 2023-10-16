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

#include "Base/desktop/win/screen_capture_utils.h"

#include "Base/logging.h"
#include "Base/desktop/win/bitmap_info.h"
#include "Base/strings/unicode.h"
#include "Base/win/scoped_gdi_object.h"

#include <VersionHelpers.h>

namespace base {

namespace {

//--------------------------------------------------------------------------------------------------
Point dpiByRect(const Rect& rect)
{
    Point result(96, 96);

    if (!IsWindows8Point1OrGreater())
    {
        // We can get DPI for a specific monitor starting with Windows 8.1.
        return result;
    }

    RECT native_rect;
    native_rect.left = rect.left();
    native_rect.top = rect.top();
    native_rect.right = rect.right();
    native_rect.bottom = rect.bottom();

    HMONITOR monitor = MonitorFromRect(&native_rect, MONITOR_DEFAULTTONEAREST);
    if (!monitor)
    {
        PLOG(LS_WARNING) << "MonitorFromRect failed";
        return result;
    }

    HMODULE module = LoadLibraryW(L"shcore.dll");
    if (module)
    {
        enum MONITOR_DPI_TYPE_WIN81
        {
            MDT_EFFECTIVE_DPI_WIN81,
            MDT_ANGULAR_DPI_WIN81,
            MDT_RAW_DPI_WIN81,
            MDT_DEFAULT_WIN81
        };

        typedef HRESULT(WINAPI* GetDpiForMonitorFunc)
            (HMONITOR, MONITOR_DPI_TYPE_WIN81, UINT*, UINT*);

        GetDpiForMonitorFunc getDpiForMonitorFunc =
            reinterpret_cast<GetDpiForMonitorFunc>(GetProcAddress(module, "GetDpiForMonitor"));
        if (getDpiForMonitorFunc)
        {
            UINT dpi_x = 0;
            UINT dpi_y = 0;

            HRESULT hr = getDpiForMonitorFunc(monitor, MDT_EFFECTIVE_DPI_WIN81, &dpi_x, &dpi_y);
            if (FAILED(hr))
            {
                LOG(LS_WARNING) << "GetDpiForMonitor failed: "
                                << SystemError(static_cast<DWORD>(hr)).toString();
            }
            else
            {
                result.setX(static_cast<int32_t>(dpi_x));
                result.setY(static_cast<int32_t>(dpi_y));
            }
        }
        else
        {
            PLOG(LS_WARNING) << "GetProcAddress failed";
        }

        FreeLibrary(module);
    }
    else
    {
        PLOG(LS_WARNING) << "LoadLibraryW failed";
    }

    return result;
}

} // namespace

//--------------------------------------------------------------------------------------------------
// static
bool ScreenCaptureUtils::screenList(ScreenCapturer::ScreenList* screen_list)
{
    DCHECK_EQ(screen_list->screens.size(), 0U);

    for (int device_index = 0;; ++device_index)
    {
        DISPLAY_DEVICEW device;
        memset(&device, 0, sizeof(device));
        device.cb = sizeof(device);

        // |enum_result| is 0 if we have enumerated all devices.
        if (!EnumDisplayDevicesW(nullptr, static_cast<DWORD>(device_index), &device, 0))
            break;

        // We only care about active displays.
        if (!(device.StateFlags & DISPLAY_DEVICE_ACTIVE) ||
            (device.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
        {
            continue;
        }

        DEVMODEW device_mode;
        memset(&device_mode, 0, sizeof(device_mode));
        device_mode.dmSize = sizeof(device_mode);

        if (!EnumDisplaySettingsExW(device.DeviceName, ENUM_CURRENT_SETTINGS, &device_mode, 0))
        {
            PLOG(LS_WARNING) << "EnumDisplaySettingsExW failed";
            return false;
        }

        std::string device_name = utf8FromWide(device.DeviceName);
        bool is_primary = (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);
        Rect rect = Rect::makeXYWH(device_mode.dmPosition.x, device_mode.dmPosition.y,
            static_cast<int32_t>(device_mode.dmPelsWidth),
            static_cast<int32_t>(device_mode.dmPelsHeight));
        Point dpi = dpiByRect(rect);

        ScreenCapturer::Screen screen;
        screen.id = device_index;
        screen.title = device_name;
        screen.position = rect.topLeft();
        screen.resolution = rect.size();
        screen.dpi = dpi;
        screen.is_primary = is_primary;

        screen_list->screens.push_back(screen);
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
// static
bool ScreenCaptureUtils::isScreenValid(ScreenCapturer::ScreenId screen, std::wstring* device_key)
{
    if (screen == ScreenCapturer::kFullDesktopScreenId)
    {
        device_key->clear();
        return true;
    }

    DISPLAY_DEVICEW device;
    device.cb = sizeof(device);

    if (!EnumDisplayDevicesW(nullptr, static_cast<DWORD>(screen), &device, 0))
    {
        PLOG(LS_WARNING) << "EnumDisplayDevicesW failed";
        return false;
    }

    *device_key = device.DeviceKey;
    return true;
}

//--------------------------------------------------------------------------------------------------
// static
Rect ScreenCaptureUtils::fullScreenRect()
{
    return Rect::makeXYWH(GetSystemMetrics(SM_XVIRTUALSCREEN),
                          GetSystemMetrics(SM_YVIRTUALSCREEN),
                          GetSystemMetrics(SM_CXVIRTUALSCREEN),
                          GetSystemMetrics(SM_CYVIRTUALSCREEN));
}

//--------------------------------------------------------------------------------------------------
// static
Rect ScreenCaptureUtils::screenRect(ScreenCapturer::ScreenId screen,
                                    const std::wstring& device_key)
{
    if (screen == ScreenCapturer::kFullDesktopScreenId)
        return fullScreenRect();

    DISPLAY_DEVICEW device;
    device.cb = sizeof(device);
    if (!EnumDisplayDevicesW(nullptr, static_cast<DWORD>(screen), &device, 0))
    {
        PLOG(LS_WARNING) << "EnumDisplayDevicesW failed";
        return Rect();
    }

    // Verifies the device index still maps to the same display device, to make sure we are
    // capturing the same device when devices are added or removed. DeviceKey is documented as
    // reserved, but it actually contains the registry key for the device and is unique for each
    // monitor, while DeviceID is not.
    if (device.DeviceKey != device_key)
    {
        LOG(LS_WARNING) << "Invalid device key";
        return Rect();
    }

    DEVMODEW device_mode;
    device_mode.dmSize = sizeof(device_mode);
    device_mode.dmDriverExtra = 0;

    if (!EnumDisplaySettingsExW(device.DeviceName, ENUM_CURRENT_SETTINGS, &device_mode, 0))
    {
        PLOG(LS_WARNING) << "EnumDisplaySettingsExW failed";
        return Rect();
    }

    return Rect::makeXYWH(device_mode.dmPosition.x,
                          device_mode.dmPosition.y,
                          static_cast<int32_t>(device_mode.dmPelsWidth),
                          static_cast<int32_t>(device_mode.dmPelsHeight));
}

//--------------------------------------------------------------------------------------------------
// static
int ScreenCaptureUtils::screenCount()
{
    return GetSystemMetrics(SM_CMONITORS);
}

} // namespace base
