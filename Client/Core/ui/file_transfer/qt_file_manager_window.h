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

#ifndef CLIENT_UI_FILE_TRANSFER_QT_FILE_MANAGER_WINDOW_H
#define CLIENT_UI_FILE_TRANSFER_QT_FILE_MANAGER_WINDOW_H

#include "Client/Core/file_manager_window.h"
#include "Client/Core/file_remover.h"
#include "Client/Core/file_transfer.h"
#include "Client/Core/ui/session_window.h"

#include <QPointer>

namespace Ui {
class FileManagerWindow;
} // namespace Ui

namespace client {

class FileManagerWindowProxy;
class FilePanel;
class FileRemoveDialog;
class FileTransferDialog;

class QtFileManagerWindow
    : public SessionWindow,
      public FileManagerWindow
{
    Q_OBJECT

public:
    explicit QtFileManagerWindow(QWidget* parent = nullptr);
    ~QtFileManagerWindow() override;

    // SessionWindow implementation.
    std::unique_ptr<Client> createClient() override;

    // FileManagerWindow implementation.
    void start(std::shared_ptr<FileControlProxy> file_control_proxy) override;
    void onErrorOccurred(proto::FileError error_code) override;
    void onDriveList(common::FileTask::Target target,
                     proto::FileError error_code,
                     const proto::DriveList& drive_list) override;
    void onFileList(common::FileTask::Target target,
                    proto::FileError error_code,
                    const proto::FileList& file_list) override;
    void onCreateDirectory(common::FileTask::Target target, proto::FileError error_code) override;
    void onRename(common::FileTask::Target target, proto::FileError error_code) override;

    QByteArray saveState() const;
    void restoreState(const QByteArray& state);

public slots:
    void refresh();

protected:
    // QWidget implementation.
    void closeEvent(QCloseEvent* event) override;

private slots:
    void removeItems(FilePanel* sender, const FileRemover::TaskList& items);
    void sendItems(FilePanel* sender, const std::vector<FileTransfer::Item>& items);
    void receiveItems(FilePanel* sender,
                      const QString& target_folder,
                      const std::vector<FileTransfer::Item>& items);
    void onPathChanged(FilePanel* sender, const QString& path);

private:
    void transferItems(FileTransfer::Type type,
                       const QString& source_path,
                       const QString& target_path,
                       const std::vector<FileTransfer::Item>& items);

    void initPanel(common::FileTask::Target target,
                   const QString& title,
                   const QString& mime_type,
                   FilePanel* panel);

    std::unique_ptr<Ui::FileManagerWindow> ui;
    std::shared_ptr<FileManagerWindowProxy> file_manager_window_proxy_;
    std::shared_ptr<FileControlProxy> file_control_proxy_;

    QPointer<FileRemoveDialog> remove_dialog_;
    QPointer<FileTransferDialog> transfer_dialog_;

    DISALLOW_COPY_AND_ASSIGN(QtFileManagerWindow);
};

} // namespace client

#endif // CLIENT_UI_FILE_TRANSFER_QT_FILE_MANAGER_WINDOW_H
