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

#include "Base/desktop/win/mirror_helper.h"

#include "Base/logging.h"
#include "Base/strings/string_util.h"
#include "Base/win/registry.h"

namespace base {

//--------------------------------------------------------------------------------------------------
// static
bool MirrorHelper::findDisplayDevice(std::wstring device_string,
                                     std::wstring* device_name,
                                     std::wstring* device_key)
{
    DCHECK(device_name);
    DCHECK(device_key);

    DISPLAY_DEVICEW device_info;

    memset(&device_info, 0, sizeof(device_info));
    device_info.cb = sizeof(device_info);

    DWORD device_number = 0;

    while (EnumDisplayDevicesW(nullptr, device_number, &device_info, 0))
    {
        if (device_string == device_info.DeviceString)
        {
            std::wstring device_key_view(device_info.DeviceKey);
            std::wstring prefix(L"\\Registry\\Machine\\");

            if (base::startsWith(device_key_view, prefix))
            {
                device_key_view = device_key_view.substr(prefix.size() - 1, device_key_view.length() - prefix.size());
                device_key->assign(device_key_view);
            }

            device_name->assign(device_info.DeviceName);
            return true;
        }

        ++device_number;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------
// static
bool MirrorHelper::attachToDesktop(std::wstring key_path, bool attach)
{
    base::win::RegistryKey device_key;

    LONG status = device_key.open(HKEY_LOCAL_MACHINE,
                                  key_path.data(),
                                  KEY_ALL_ACCESS | KEY_WOW64_64KEY);
    if (status != ERROR_SUCCESS)
    {
        LOG(LS_WARNING) << "Unable to open registry key for device: "
                        << base::SystemError::toString(static_cast<DWORD>(status));
        return false;
    }

    static const wchar_t kAttachToDesktop[] = L"Attach.ToDesktop";

    if (attach)
    {
        DWORD attached;

        status = device_key.readValueDW(kAttachToDesktop, &attached);
        if (status == ERROR_SUCCESS)
        {
            if (attached != 0)
            {
                LOG(LS_WARNING) << "Mirror driver is already attached by another application";
            }
        }
    }

    status = device_key.writeValue(kAttachToDesktop, static_cast<DWORD>(!!attach));
    if (status != ERROR_SUCCESS)
    {
        LOG(LS_WARNING) << "Unable to set value for registry key: "
                        << base::SystemError::toString(static_cast<DWORD>(status));
        return false;
    }

    return true;
}

} // namespace base
