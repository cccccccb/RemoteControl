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

#include "Client/Core/ui/desktop/qt_desktop_window.h"

#include "Base/filesystem.hpp"
#include "Base/logging.h"
#include "Base/stl_util.h"
#include "Base/desktop/mouse_cursor.h"
#include "Base/strings/string_split.h"
#include "Client/Core/client_desktop.h"
#include "Client/Core/desktop_control_proxy.h"
#include "Client/Core/desktop_window_proxy.h"
#include "Client/Core/ui/desktop/desktop_config_dialog.h"
#include "Client/Core/ui/desktop/desktop_toolbar.h"
#include "Client/Core/ui/desktop/frame_factory_qimage.h"
#include "Client/Core/ui/desktop/frame_qimage.h"
#include "Client/Core/ui/desktop/statistics_dialog.h"
#include "Client/Core/ui/desktop/task_manager_window.h"
#include "Common/desktop_session_constants.h"
#include "QtBase/application.h"

#include <QApplication>
#include <QBrush>
#include <QClipboard>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QWindow>
#include <QDebug>

namespace client {

namespace {

//--------------------------------------------------------------------------------------------------
QSize scaledSize(const QSize& source_size, int scale)
{
    if (scale == -1)
        return source_size;

    int width = static_cast<int>(static_cast<double>(source_size.width() * scale) / 100.0);
    int height = static_cast<int>(static_cast<double>(source_size.height() * scale) / 100.0);

    return QSize(width, height);
}

} // namespace

//--------------------------------------------------------------------------------------------------
QtDesktopWindow::QtDesktopWindow(proto::SessionType session_type,
                                 const proto::DesktopConfig& desktop_config,
                                 QWidget* parent)
    : SessionWindow(parent),
      session_type_(session_type),
      desktop_config_(desktop_config),
      desktop_window_proxy_(std::make_shared<DesktopWindowProxy>(
          qt_base::Application::uiTaskRunner(), this))
{
    setMinimumSize(400, 300);

    desktop_ = new DesktopWidget(this);

    scroll_area_ = new QScrollArea(this);
    scroll_area_->setAlignment(Qt::AlignCenter);
    scroll_area_->setFrameShape(QFrame::NoFrame);
    scroll_area_->setWidget(desktop_);

    QPalette palette(scroll_area_->palette());
    palette.setBrush(QPalette::Window, QBrush(QColor(25, 25, 25)));
    scroll_area_->viewport()->setPalette(palette);

    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->addWidget(scroll_area_);

    toolbar_ = new DesktopToolBar(session_type_, scroll_area_);
    toolbar_->installEventFilter(this);

    resize_timer_ = new QTimer(this);
    connect(resize_timer_, &QTimer::timeout, this, &QtDesktopWindow::onResizeTimer);

    scroll_timer_ = new QTimer(this);
    connect(scroll_timer_, &QTimer::timeout, this, &QtDesktopWindow::onScrollTimer);

    desktop_->enableKeyCombinations(toolbar_->sendKeyCombinations());
    desktop_->enableRemoteCursorPosition(desktop_config_.flags() & proto::CURSOR_POSITION);

    connect(toolbar_, &DesktopToolBar::sig_keyCombination, desktop_, &DesktopWidget::executeKeyCombination);
    connect(toolbar_, &DesktopToolBar::sig_settingsButton, this, &QtDesktopWindow::changeSettings);
    connect(toolbar_, &DesktopToolBar::sig_switchToAutosize, this, &QtDesktopWindow::autosizeWindow);
    connect(toolbar_, &DesktopToolBar::sig_takeScreenshot, this, &QtDesktopWindow::takeScreenshot);
    connect(toolbar_, &DesktopToolBar::sig_scaleChanged, this, &QtDesktopWindow::scaleDesktop);
    connect(toolbar_, &DesktopToolBar::sig_minimizeSession, this, [this]()
    {
        is_minimized_from_full_screen_ = true;
        showMinimized();
    });
    connect(toolbar_, &DesktopToolBar::sig_closeSession, this, &QtDesktopWindow::close);
    connect(toolbar_, &DesktopToolBar::sig_showHidePanel, this, &QtDesktopWindow::onShowHidePanel);

    enable_video_pause_ = toolbar_->isVideoPauseEnabled();
    connect(toolbar_, &DesktopToolBar::sig_videoPauseChanged, this, [this](bool enable)
    {
        enable_video_pause_ = enable;
    });

    enable_audio_pause_ = toolbar_->isAudioPauseEnabled();
    connect(toolbar_, &DesktopToolBar::sig_audioPauseChanged, this, [this](bool enable)
    {
        enable_audio_pause_ = enable;
    });

    connect(toolbar_, &DesktopToolBar::sig_screenSelected, this, [this](const proto::Screen& screen)
    {
        desktop_control_proxy_->setCurrentScreen(screen);
    });

    connect(toolbar_, &DesktopToolBar::sig_powerControl, this, [this](proto::PowerControl::Action action)
    {
        desktop_control_proxy_->onPowerControl(action);
    });

    connect(toolbar_, &DesktopToolBar::sig_startRemoteUpdate, this, [this]()
    {
        desktop_control_proxy_->onRemoteUpdate();
    });

    connect(toolbar_, &DesktopToolBar::sig_startTaskManager, this, [this]()
    {
        if (!task_manager_)
        {
            task_manager_ = new TaskManagerWindow();
            task_manager_->setAttribute(Qt::WA_DeleteOnClose);

            connect(task_manager_, &TaskManagerWindow::sig_sendMessage,
                    this, [this](const proto::task_manager::ClientToHost& message)
            {
                desktop_control_proxy_->onTaskManager(message);
            });
        }

        task_manager_->show();
        task_manager_->activateWindow();
    });

    connect(toolbar_, &DesktopToolBar::sig_startStatistics, this, [this]()
    {
        desktop_control_proxy_->onMetricsRequest();
    });

    connect(toolbar_, &DesktopToolBar::sig_pasteAsKeystrokes, this, &QtDesktopWindow::onPasteKeystrokes);
    connect(toolbar_, &DesktopToolBar::sig_switchToFullscreen, this, [this](bool fullscreen)
    {
        if (fullscreen)
        {
            is_maximized_ = isMaximized();
            showFullScreen();
        }
        else
        {
            if (is_maximized_)
                showMaximized();
            else
                showNormal();
        }
    });

    connect(toolbar_, &DesktopToolBar::sig_keyCombinationsChanged,
            desktop_, &DesktopWidget::enableKeyCombinations);

    desktop_->installEventFilter(this);
    scroll_area_->viewport()->installEventFilter(this);

    connect(toolbar_, &DesktopToolBar::sig_startSession, this, [this](proto::SessionType session_type)
    {
        client::Config session_config = config();
        session_config.session_type = session_type;
    });

    connect(toolbar_, &DesktopToolBar::sig_recordingStateChanged, this, [this](bool enable)
    {
        ghc::filesystem::path file_path;

        if (enable)
        {
            DesktopSettings settings;
            file_path = settings.recordingPath().toStdU16String();
        }

        desktop_control_proxy_->setVideoRecording(enable, file_path);
    });

    connect(desktop_, &DesktopWidget::sig_mouseEvent, this, &QtDesktopWindow::onMouseEvent);
    connect(desktop_, &DesktopWidget::sig_keyEvent, this, &QtDesktopWindow::onKeyEvent);

    desktop_->setFocus();
}

//--------------------------------------------------------------------------------------------------
QtDesktopWindow::~QtDesktopWindow()
{
    desktop_window_proxy_->dettach();
}

//--------------------------------------------------------------------------------------------------
std::unique_ptr<Client> QtDesktopWindow::createClient()
{
    std::unique_ptr<ClientDesktop> client = std::make_unique<ClientDesktop>(
        qt_base::Application::ioTaskRunner());

    client->setDesktopConfig(desktop_config_);
    client->setDesktopWindow(desktop_window_proxy_);

    return std::move(client);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::showWindow(
    std::shared_ptr<DesktopControlProxy> desktop_control_proxy, const base::Version& peer_version)
{
    desktop_control_proxy_ = std::move(desktop_control_proxy);
    peer_version_ = peer_version;

    show();
    activateWindow();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::configRequired()
{
    if (!(video_encodings_ & common::kSupportedVideoEncodings))
    {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("There are no supported video encodings."),
                             QMessageBox::Ok);
        close();
    }
    else
    {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("The current video encoding is not supported by the host. "
                                "Please specify a different video encoding."),
                             QMessageBox::Ok);

        DesktopConfigDialog* dialog = new DesktopConfigDialog(
            session_type_, desktop_config_, video_encodings_, this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);

        connect(dialog, &DesktopConfigDialog::sig_configChanged, this, &QtDesktopWindow::onConfigChanged);
        connect(dialog, &DesktopConfigDialog::rejected, this, &QtDesktopWindow::close);

        dialog->show();
        dialog->activateWindow();
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setCapabilities(const proto::DesktopCapabilities& capabilities)
{
    video_encodings_ = capabilities.video_encodings();

    // The list of extensions is passed as a string. Extensions are separated by a semicolon.
    std::vector<std::string> extensions_list = base::splitStringView(
        capabilities.extensions(), ";", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

    // By default, remote update is disabled.
    toolbar_->enableRemoteUpdate(false);

    if (base::contains(extensions_list, common::kRemoteUpdateExtension))
    {
        if (Client::version() > peer_version_)
            toolbar_->enableRemoteUpdate(true);
    }

    toolbar_->enablePowerControl(base::contains(extensions_list, common::kPowerControlExtension));
    toolbar_->enableScreenSelect(base::contains(extensions_list, common::kSelectScreenExtension));
    toolbar_->enableTaskManager(base::contains(extensions_list, common::kTaskManagerExtension));
    toolbar_->enableVideoPauseFeature(base::contains(extensions_list, common::kVideoPauseExtension));
    toolbar_->enableAudioPauseFeature(base::contains(extensions_list, common::kAudioPauseExtension));
    toolbar_->enableCtrlAltDelFeature(capabilities.os_type() == proto::DesktopCapabilities::OS_TYPE_WINDOWS);

    for (int i = 0; i < capabilities.flag_size(); ++i)
    {
        const proto::DesktopCapabilities::Flag& flag = capabilities.flag(i);
        const std::string& name = flag.name();
        bool value = flag.value();

        if (name == common::kFlagDisablePasteAsKeystrokes)
        {
            toolbar_->enablePasteAsKeystrokesFeature(!value);
        }
        else if (name == common::kFlagDisableAudio)
        {
            disable_feature_audio_ = value;
        }
        else if (name == common::kFlagDisableClipboard)
        {
            disable_feature_clipboard_ = value;
        }
        else if (name == common::kFlagDisableCursorShape)
        {
            disable_feature_cursor_shape_ = value;
        }
        else if (name == common::kFlagDisableCursorPosition)
        {
            disable_feature_cursor_position_ = value;
        }
        else if (name == common::kFlagDisableDesktopEffects)
        {
            disable_feature_desktop_effects_ = value;
        }
        else if (name == common::kFlagDisableDesktopWallpaper)
        {
            disable_feature_desktop_wallpaper_ = value;
        }
        else if (name == common::kFlagDisableFontSmoothing)
        {
            disable_feature_font_smoothing_ = value;
        }
        else if (name == common::kFlagDisableClearClipboard)
        {
            disable_feature_clear_clipboard_ = value;
        }
        else if (name == common::kFlagDisableLockAtDisconnect)
        {
            disable_feature_lock_at_disconnect_ = value;
        }
        else if (name == common::kFlagDisableBlockInput)
        {
            disable_feature_block_input_ = value;
        }
        else
        {
            qWarning() << "Unknown flag '" << name.c_str() << "' with value: " << value;
        }
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setScreenList(const proto::ScreenList& screen_list)
{
    toolbar_->setScreenList(screen_list);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setCursorPosition(const proto::CursorPosition& cursor_position)
{
    base::Frame* frame = desktop_->desktopFrame();
    if (!frame)
        return;

    const base::Size& frame_size = frame->size();

    int pos_x = static_cast<int>(
        static_cast<double>(desktop_->width() * cursor_position.x()) /
        static_cast<double>(frame_size.width()));
    int pos_y = static_cast<int>(
        static_cast<double>(desktop_->height() * cursor_position.y()) /
        static_cast<double>(frame_size.height()));

    desktop_->setCursorPosition(QPoint(pos_x, pos_y));
    desktop_->update();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setTaskManager(const proto::task_manager::HostToClient& message)
{
    if (task_manager_)
        task_manager_->readMessage(message);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setMetrics(const DesktopWindow::Metrics& metrics)
{
    if (!statistics_dialog_)
    {
        statistics_dialog_ = new StatisticsDialog(this);
        statistics_dialog_->setAttribute(Qt::WA_DeleteOnClose);

        connect(statistics_dialog_, &StatisticsDialog::sig_metricsRequired, this, [this]()
        {
            desktop_control_proxy_->onMetricsRequest();
        });

        statistics_dialog_->show();
        statistics_dialog_->activateWindow();
    }

    statistics_dialog_->setMetrics(metrics);
}

//--------------------------------------------------------------------------------------------------
std::unique_ptr<FrameFactory> QtDesktopWindow::frameFactory()
{
    return std::make_unique<FrameFactoryQImage>();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setFrameError(proto::VideoErrorCode error_code)
{
    desktop_->setDesktopFrameError(error_code);
    desktop_->update();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setFrame(
    const base::Size& screen_size, std::shared_ptr<base::Frame> frame)
{
    screen_size_ = QSize(screen_size.width(), screen_size.height());

    bool has_old_frame = desktop_->desktopFrame() != nullptr;

    desktop_->setDesktopFrame(frame);
    scaleDesktop();

    if (!has_old_frame)
    {
        qInfo() << "Resize window (first frame)";
        autosizeWindow();

        // If the parameters indicate that it is necessary to record the connection session, then we
        // start recording.
        DesktopSettings settings;
        if (settings.recordSessions())
            toolbar_->startRecording(true);
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::drawFrame()
{
    desktop_->drawDesktopFrame();
    toolbar_->update();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::setMouseCursor(std::shared_ptr<base::MouseCursor> mouse_cursor)
{
    base::Point local_dpi(base::MouseCursor::kDefaultDpiX, base::MouseCursor::kDefaultDpiY);
    base::Point remote_dpi = mouse_cursor->constDpi();

    QWidget* current_window = window();
    if (current_window)
    {
        if (QWindow *currentWindowHandle = current_window->windowHandle())
        {
            QScreen* current_screen = currentWindowHandle->screen();
            if (current_screen)
            {
                local_dpi.setX(static_cast<int32_t>(current_screen->logicalDotsPerInchX()));
                local_dpi.setY(static_cast<int32_t>(current_screen->logicalDotsPerInchY()));
            }
        }
    }

    int width = mouse_cursor->width();
    int height = mouse_cursor->height();
    int hotspot_x = mouse_cursor->hotSpotX();
    int hotspot_y = mouse_cursor->hotSpotY();

    QImage image(mouse_cursor->constImage().data(), width, height, mouse_cursor->stride(),
                 QImage::Format::Format_ARGB32);

    if (local_dpi != remote_dpi)
    {
        double scale_factor_x =
            static_cast<double>(local_dpi.x()) / static_cast<double>(remote_dpi.x());
        double scale_factor_y =
            static_cast<double>(local_dpi.y()) / static_cast<double>(remote_dpi.y());

        width = std::max(static_cast<int>(static_cast<double>(width) * scale_factor_x), 1);
        height = std::max(static_cast<int>(static_cast<double>(height) * scale_factor_y), 1);
        hotspot_x = static_cast<int>(static_cast<double>(hotspot_x) * scale_factor_x);
        hotspot_y = static_cast<int>(static_cast<double>(hotspot_y) * scale_factor_y);

        QImage scaled_image =
            image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        desktop_->setCursorShape(QPixmap::fromImage(std::move(scaled_image)),
                                 QPoint(hotspot_x, hotspot_y));
    }
    else
    {
        desktop_->setCursorShape(QPixmap::fromImage(std::move(image)),
                                 QPoint(hotspot_x, hotspot_y));
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::resizeEvent(QResizeEvent* event)
{
    int panel_width = toolbar_->width();
    int window_width = width();

    QPoint new_pos;
    new_pos.setX(((window_width * panel_pos_x_) / 100) - (panel_width / 2));
    new_pos.setY(0);

    if (new_pos.x() < 0)
        new_pos.setX(0);
    else if (new_pos.x() > (window_width - panel_width))
        new_pos.setX(window_width - panel_width);

    toolbar_->move(new_pos);
    scaleDesktop();

    QWidget::resizeEvent(event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::leaveEvent(QEvent* event)
{
    if (scroll_timer_->isActive())
        scroll_timer_->stop();

    QWidget::leaveEvent(event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        bool is_minimized = isMinimized();

        qInfo() << "Window minimized: " << is_minimized;

        if (is_minimized)
        {
            if (enable_video_pause_)
            {
                desktop_control_proxy_->setVideoPause(true);
                video_pause_last_ = true;
            }

            if (enable_audio_pause_)
            {
                desktop_control_proxy_->setAudioPause(true);
                audio_pause_last_ = true;
            }

            desktop_->userLeftFromWindow();
        }
        else
        {
            if (enable_video_pause_ || video_pause_last_)
            {
                if (video_pause_last_)
                {
                    desktop_control_proxy_->setVideoPause(false);
                    video_pause_last_ = false;
                }
            }

            if (enable_audio_pause_ || audio_pause_last_)
            {
                if (audio_pause_last_)
                {
                    desktop_control_proxy_->setAudioPause(false);
                    audio_pause_last_ = false;
                }
            }
        }
    }

    QWidget::changeEvent(event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::showEvent(QShowEvent *event)
{
    if (is_minimized_from_full_screen_)
    {
        is_minimized_from_full_screen_ = false;
        showFullScreen();
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::focusOutEvent(QFocusEvent* event)
{
    desktop_->userLeftFromWindow();
    QWidget::focusOutEvent(event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::closeEvent(QCloseEvent* /* event */)
{
    if (task_manager_)
        task_manager_->close();
}

//--------------------------------------------------------------------------------------------------
bool QtDesktopWindow::eventFilter(QObject* object, QEvent* event)
{
    if (object == desktop_)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
            if (key_event->key() == Qt::Key_Tab)
            {
                desktop_->doKeyEvent(key_event);
                return true;
            }
        }

        return false;
    }
    else if (object == scroll_area_->viewport())
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
            QPoint pos = desktop_->mapFromGlobal(wheel_event->globalPos());

            desktop_->doMouseEvent(wheel_event->type(),
                                   wheel_event->buttons(),
                                   pos,
                                   wheel_event->angleDelta());
            return true;
        }
    }
    else if (object == toolbar_)
    {
        if (event->type() == QEvent::Resize)
        {
            int panel_width = toolbar_->width();
            int window_width = width();

            QPoint new_pos;
            new_pos.setX(((window_width * panel_pos_x_) / 100) - (panel_width / 2));
            new_pos.setY(0);

            if (new_pos.x() < 0)
                new_pos.setX(0);
            else if (new_pos.x() > (window_width - panel_width))
                new_pos.setX(window_width - panel_width);

            toolbar_->move(new_pos);
        }
        else if (event->type() == QEvent::Leave)
        {
            desktop_->setFocus();
        }
        else if (!toolbar_->isPanelHidden())
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
                if (mouse_event->button() == Qt::RightButton)
                {
                    start_panel_pos_.emplace(mouse_event->pos());
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease)
            {
                QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
                if (mouse_event->button() == Qt::RightButton)
                {
                    start_panel_pos_.reset();
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseMove)
            {
                QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
                if ((mouse_event->buttons() & Qt::RightButton) && start_panel_pos_.has_value())
                {
                    QPoint diff = mouse_event->pos() - *start_panel_pos_;
                    QPoint new_pos = QPoint(toolbar_->pos().x() + diff.x(), 0);
                    int panel_width = toolbar_->width();
                    int window_width = width();

                    if (new_pos.x() < 0)
                        new_pos.setX(0);
                    else if (new_pos.x() > (window_width - panel_width))
                        new_pos.setX(window_width - panel_width);

                    panel_pos_x_ = ((new_pos.x() + (panel_width / 2)) * 100) / window_width;
                    toolbar_->move(new_pos);
                    return true;
                }
            }
        }
    }

    return QWidget::eventFilter(object, event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onMouseEvent(const proto::MouseEvent& event)
{
    QPoint pos(event.x(), event.y());

    if (toolbar_->autoScrolling() && toolbar_->scale() != -1)
    {
        QPoint cursor = desktop_->mapTo(scroll_area_, pos);
        QRect client_area = scroll_area_->rect();

        QScrollBar* hscrollbar = scroll_area_->horizontalScrollBar();
        QScrollBar* vscrollbar = scroll_area_->verticalScrollBar();

        if (!hscrollbar->isHidden())
            client_area.setHeight(client_area.height() - hscrollbar->height());

        if (!vscrollbar->isHidden())
            client_area.setWidth(client_area.width() - vscrollbar->width());

        scroll_delta_.setX(0);
        scroll_delta_.setY(0);

        static const int kThresholdDistance = 80;
        static const int kStep = 10;

        if (client_area.width() < desktop_->width())
        {
            if (cursor.x() > client_area.width() - kThresholdDistance)
                scroll_delta_.setX(kStep);
            else if (cursor.x() < kThresholdDistance)
                scroll_delta_.setX(-kStep);
        }

        if (client_area.height() < desktop_->height())
        {
            if (cursor.y() > client_area.height() - kThresholdDistance)
                scroll_delta_.setY(kStep);
            else if (cursor.y() < kThresholdDistance)
                scroll_delta_.setY(-kStep);
        }

        if (!scroll_delta_.isNull())
        {
            if (!scroll_timer_->isActive())
                scroll_timer_->start(15);
        }
        else if (scroll_timer_->isActive())
        {
            scroll_timer_->stop();
        }
    }
    else if (scroll_timer_->isActive())
    {
        scroll_timer_->stop();
    }

    base::Frame* current_frame = desktop_->desktopFrame();
    if (current_frame)
    {
        const base::Size& source_size = current_frame->size();
        QSize scaled_size = desktop_->size();

        double scale_x = (scaled_size.width() * 100) / static_cast<double>(source_size.width());
        double scale_y = (scaled_size.height() * 100) / static_cast<double>(source_size.height());
        double scale = std::min(scale_x, scale_y);

        proto::MouseEvent out_event;

        out_event.set_mask(event.mask());
        out_event.set_x(static_cast<int>(static_cast<double>(pos.x() * 100) / scale));
        out_event.set_y(static_cast<int>(static_cast<double>(pos.y() * 100) / scale));

        desktop_control_proxy_->onMouseEvent(out_event);
    }

    // In MacOS event Leave does not always come to the widget when the mouse leaves its area.
    if (!toolbar_->isPanelHidden() && !toolbar_->isPanelPinned())
    {
        if (!toolbar_->rect().contains(pos))
            QApplication::postEvent(toolbar_, new QEvent(QEvent::Leave));
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onKeyEvent(const proto::KeyEvent& event)
{
    desktop_control_proxy_->onKeyEvent(event);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::changeSettings()
{
    DesktopConfigDialog* dialog = new DesktopConfigDialog(
        session_type_, desktop_config_, video_encodings_, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->enableAudioFeature(!disable_feature_audio_);
    dialog->enableClipboardFeature(!disable_feature_clipboard_);
    dialog->enableCursorShapeFeature(!disable_feature_cursor_shape_);
    dialog->enableCursorPositionFeature(!disable_feature_cursor_position_);
    dialog->enableDesktopEffectsFeature(!disable_feature_desktop_effects_);
    dialog->enableDesktopWallpaperFeature(!disable_feature_desktop_wallpaper_);
    dialog->enableFontSmoothingFeature(!disable_feature_font_smoothing_);
    dialog->enableClearClipboardFeature(!disable_feature_clear_clipboard_);
    dialog->enableLockAtDisconnectFeature(!disable_feature_lock_at_disconnect_);
    dialog->enableBlockInputFeature(!disable_feature_block_input_);

    connect(dialog, &DesktopConfigDialog::sig_configChanged, this, &QtDesktopWindow::onConfigChanged);

    dialog->show();
    dialog->activateWindow();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onConfigChanged(const proto::DesktopConfig& desktop_config)
{
    desktop_config_ = desktop_config;
    desktop_control_proxy_->setDesktopConfig(desktop_config);

    desktop_->enableRemoteCursorPosition(desktop_config_.flags() & proto::CURSOR_POSITION);
    if (!(desktop_config_.flags() & proto::ENABLE_CURSOR_SHAPE))
        desktop_->setCursorShape(QPixmap(), QPoint());
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::autosizeWindow()
{
    if (screen_size_.isEmpty())
        return;

    QWidget *window  = this->window();
    if (!window)
        return;

    QWindow *windowHandle = window->windowHandle();
    if (!windowHandle)
        return;

    QScreen* current_screen = windowHandle->screen();
    QRect local_screen_rect = current_screen->availableGeometry();
    QSize window_size = screen_size_ + frameSize() - size();

    if (window_size.width() < local_screen_rect.width() &&
        window_size.height() < local_screen_rect.height())
    {
        QSize remote_screen_size = scaledSize(screen_size_, toolbar_->scale());

        showNormal();

        resize(remote_screen_size);
        move(local_screen_rect.x() + (local_screen_rect.width() / 2 - window_size.width() / 2),
            local_screen_rect.y() + (local_screen_rect.height() / 2 - window_size.height() / 2));
    }
    else
    {
        showMaximized();
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::takeScreenshot()
{
    QString selected_filter;
    QString file_path = QFileDialog::getSaveFileName(this,
                                                     tr("Save File"),
                                                     QString(),
                                                     tr("PNG Image (*.png);;BMP Image (*.bmp)"),
                                                     &selected_filter);
    if (file_path.isEmpty() || selected_filter.isEmpty())
        return;

    FrameQImage* frame = static_cast<FrameQImage*>(desktop_->desktopFrame());
    if (!frame)
        return;

    const char* format = nullptr;

    if (selected_filter.contains(QLatin1String("*.png")))
        format = "PNG";
    else if (selected_filter.contains(QLatin1String("*.bmp")))
        format = "BMP";

    if (!format)
        return;

    if (!frame->constImage().save(file_path, format))
        QMessageBox::warning(this, tr("Warning"), tr("Could not save image"), QMessageBox::Ok);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::scaleDesktop()
{
    if (screen_size_.isEmpty())
    {
        qInfo() << "No screen size";
        return;
    }

    QSize source_size(screen_size_);
    QSize target_size(size());

    int scale = toolbar_->scale();
    if (scale != -1)
        target_size = scaledSize(source_size, scale);

    desktop_->resize(source_size.scaled(target_size, Qt::KeepAspectRatio));

    if (resize_timer_->isActive())
        resize_timer_->stop();

    qInfo() << "Starting resize timer";
    resize_timer_->start(500);
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onResizeTimer()
{
    QSize desktop_size = desktop_->size();

    QScreen* current_screen = window()->windowHandle()->screen();
    if (current_screen)
        desktop_size *= current_screen->devicePixelRatio();

    qInfo() << "Resize timer: " << desktop_size.width() << "x" << desktop_size.height();

    desktop_control_proxy_->setPreferredSize(desktop_size.width(), desktop_size.height());
    resize_timer_->stop();
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onScrollTimer()
{
    if (scroll_delta_.x() != 0)
    {
        QScrollBar* scrollbar = scroll_area_->horizontalScrollBar();

        int pos = scrollbar->sliderPosition() + scroll_delta_.x();

        pos = std::max(pos, scrollbar->minimum());
        pos = std::min(pos, scrollbar->maximum());

        scrollbar->setSliderPosition(pos);
    }

    if (scroll_delta_.y() != 0)
    {
        QScrollBar* scrollbar = scroll_area_->verticalScrollBar();

        int pos = scrollbar->sliderPosition() + scroll_delta_.y();

        pos = std::max(pos, scrollbar->minimum());
        pos = std::min(pos, scrollbar->maximum());

        scrollbar->setSliderPosition(pos);
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onPasteKeystrokes()
{
    QClipboard* clipboard = QApplication::clipboard();
    if (clipboard)
    {
        QString text = clipboard->text();
        if (text.isEmpty())
        {
            qInfo() << "Empty clipboard";
            return;
        }

        proto::TextEvent event;
        event.set_text(text.toStdString());

        desktop_control_proxy_->onTextEvent(event);
    }
    else
    {
        qWarning() << "QApplication::clipboard failed";
    }
}

//--------------------------------------------------------------------------------------------------
void QtDesktopWindow::onShowHidePanel()
{
    QSize start_panel_size = toolbar_->size();
    QSize end_panel_size = toolbar_->sizeHint();

    int start_x = ((width() * panel_pos_x_) / 100) - (start_panel_size.width() / 2);
    int end_x = ((width() * panel_pos_x_) / 100) - (end_panel_size.width() / 2);

    QPropertyAnimation* animation = new QPropertyAnimation(toolbar_, QByteArrayLiteral("geometry"));
    animation->setStartValue(QRect(QPoint(start_x, 0), start_panel_size));
    animation->setEndValue(QRect(QPoint(end_x, 0), end_panel_size));
    animation->setDuration(150);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

} // namespace client
