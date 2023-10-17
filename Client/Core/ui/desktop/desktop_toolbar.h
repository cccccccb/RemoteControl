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

#ifndef CLIENT_UI_DESKTOP_DESKTOP_TOOLBAR_H
#define CLIENT_UI_DESKTOP_DESKTOP_TOOLBAR_H

#include "Base/macros_magic.h"
#include "Client/Core/ui/desktop/desktop_settings.h"
#include "proto/common.pb.h"
#include "proto/desktop_extensions.pb.h"
#include "ui_desktop_toolbar.h"

namespace client {

class DesktopToolBar : public QFrame
{
    Q_OBJECT

public:
    DesktopToolBar(proto::SessionType session_type, QWidget* parent);
    ~DesktopToolBar() override;

    void enableScreenSelect(bool enable);
    void enablePowerControl(bool enable);
    void enableRemoteUpdate(bool enable);
    void enableTaskManager(bool enable);
    void enableVideoPauseFeature(bool enable);
    void enableAudioPauseFeature(bool enable);
    void enableCtrlAltDelFeature(bool enable);
    void enablePasteAsKeystrokesFeature(bool enable);

    void setScreenList(const proto::ScreenList& screen_list);
    void startRecording(bool enable);

    int scale() const { return scale_; }
    bool autoScrolling() const;
    bool sendKeyCombinations() const;
    bool isPanelHidden() const;
    bool isPanelPinned() const;
    bool isVideoPauseEnabled() const;
    bool isAudioPauseEnabled() const;

signals:
    void sig_pasteAsKeystrokes();
    void sig_keyCombination(int key_secuence);
    void sig_switchToFullscreen(bool fullscreen);
    void sig_switchToAutosize();
    void sig_settingsButton();
    void sig_screenSelected(const proto::Screen& screen);
    void sig_scaleChanged();
    void sig_autoScrollChanged(bool enabled);
    void sig_keyCombinationsChanged(bool enabled);
    void sig_takeScreenshot();
    void sig_startSession(proto::SessionType session_type);
    void sig_powerControl(proto::PowerControl::Action action);
    void sig_startRemoteUpdate();
    void sig_startTaskManager();
    void sig_startStatistics();
    void sig_minimizeSession();
    void sig_closeSession();
    void sig_showHidePanel();
    void sig_recordingStateChanged(bool enable);
    void sig_videoPauseChanged(bool enable);
    void sig_audioPauseChanged(bool enable);

protected:
    // QFrame implementation.
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEvent* event) override;
#else
    void enterEvent(QEnterEvent* event) override;
#endif
    void leaveEvent(QEvent* event) override;

private slots:
    void onHideTimer();
    void onFullscreenButton(bool checked);
    void onAutosizeButton();
    void onCtrlAltDel();
    void onPowerControl(QAction* action);
    void onChangeResolutionAction(QAction* action);
    void onChangeScreenAction(QAction* action);
    void onMenuShow();
    void onMenuHide();
    void onShowRecordSettings();

private:
    void createAdditionalMenu(proto::SessionType session_type);
    void showFullScreenButtons(bool show);
    void updateScaleMenu();
    void updateSize();
    void delayedHide();

    Ui::DesktopToolBar ui;

    const proto::SessionType session_type_;
    bool is_recording_started_ = false;

    QSize current_resolution_;
    int64_t current_screen_id_ = -1;
    int screen_count_ = 0;

    std::unique_ptr<QMenu> power_menu_;
    QMenu* additional_menu_ = nullptr;

    QList<QAction*> screen_actions_;

    QMenu* resolutions_menu_ = nullptr;
    QActionGroup* resolutions_group_ = nullptr;

    QMenu* scale_menu_ = nullptr;
    QActionGroup* scale_group_ = nullptr;

    QTimer* hide_timer_ = nullptr;

    bool allow_hide_ = true;
    bool leaved_ = true;

    int scale_ = 100;

    DISALLOW_COPY_AND_ASSIGN(DesktopToolBar);
};

} // namespace client

#endif // CLIENT_UI_DESKTOP_DESKTOP_TOOLBAR_H
