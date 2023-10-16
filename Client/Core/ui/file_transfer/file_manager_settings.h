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

#ifndef CLIENT_UI_FILE_TRANSFER_FILE_MANAGER_SETTINGS_H
#define CLIENT_UI_FILE_TRANSFER_FILE_MANAGER_SETTINGS_H

#include "Base/macros_magic.h"

#include <QSettings>

namespace client {

class FileManagerSettings
{
public:
    FileManagerSettings();
    ~FileManagerSettings() = default;

    QByteArray windowGeometry() const;
    void setWindowGeometry(const QByteArray& geometry);

    QByteArray windowState() const;
    void setWindowState(const QByteArray& state);

private:
    QSettings settings_;

    DISALLOW_COPY_AND_ASSIGN(FileManagerSettings);
};

} // namespace client

#endif // CLIENT_UI_FILE_TRANSFER_FILE_MANAGER_SETTINGS_H
