CLIENT_CORE_HEADERS +=                                                  \
    $${_PRO_FILE_PWD_}/client.h                                         \
    $${_PRO_FILE_PWD_}/client_config.h                                  \
    $${_PRO_FILE_PWD_}/client_desktop.h                                 \
    $${_PRO_FILE_PWD_}/client_main.h                                    \
    $${_PRO_FILE_PWD_}/client_proxy.h                                   \
    $${_PRO_FILE_PWD_}/config_factory.h                                 \
    $${_PRO_FILE_PWD_}/desktop_control.h                                \
    $${_PRO_FILE_PWD_}/desktop_control_proxy.h                          \
    $${_PRO_FILE_PWD_}/desktop_window.h                                 \
    $${_PRO_FILE_PWD_}/desktop_window_proxy.h                           \
    $${_PRO_FILE_PWD_}/frame_factory.h                                  \
    $${_PRO_FILE_PWD_}/input_event_filter.h                             \
    $${_PRO_FILE_PWD_}/status_window.h                                  \
    $${_PRO_FILE_PWD_}/status_window_proxy.h                            \
    $${_PRO_FILE_PWD_}/client_core_export.h

CLIENT_CORE_SOURCES +=                               \
    $${_PRO_FILE_PWD_}/client_config.cc                                 \
    $${_PRO_FILE_PWD_}/client_desktop.cc                                \
    $${_PRO_FILE_PWD_}/client.cc                                        \
    $${_PRO_FILE_PWD_}/client_main.cc                                   \
    $${_PRO_FILE_PWD_}/client_proxy.cc                                  \
    $${_PRO_FILE_PWD_}/config_factory.cc                                \
    $${_PRO_FILE_PWD_}/desktop_control_proxy.cc                         \
    $${_PRO_FILE_PWD_}/desktop_window_proxy.cc                          \
    $${_PRO_FILE_PWD_}/input_event_filter.cc                            \
    $${_PRO_FILE_PWD_}/status_window_proxy.cc                           \

CLIENT_CORE_RESOURCES +=
    $${_PRO_FILE_PWD_}/resources/client.qrc

CLIENT_CORE_ONLINE_CHECKER_HEADERS +=                                   \
    $${_PRO_FILE_PWD_}/online_checker/online_checker.h                  \
    $${_PRO_FILE_PWD_}/online_checker/online_checker_direct.h           \
    $${_PRO_FILE_PWD_}/online_checker/online_checker_router.h           \

CLIENT_CORE_ONLINE_CHECKER_SOURCES +=                                   \
    $${_PRO_FILE_PWD_}/online_checker/online_checker.cc                 \
    $${_PRO_FILE_PWD_}/online_checker/online_checker_direct.cc          \
    $${_PRO_FILE_PWD_}/online_checker/online_checker_router.cc          \

CLIENT_CORE_UI_HEADERS +=                                               \
    $${_PRO_FILE_PWD_}/ui/application.h                                 \
    $${_PRO_FILE_PWD_}/ui/authorization_dialog.h                        \
    $${_PRO_FILE_PWD_}/ui/client_window.h                               \
    $${_PRO_FILE_PWD_}/ui/client_settings.h                             \
    $${_PRO_FILE_PWD_}/ui/client_settings_dialog.h                      \
    $${_PRO_FILE_PWD_}/ui/session_window.h                              \
    $${_PRO_FILE_PWD_}/ui/update_settings_dialog.h                      \

CLIENT_CORE_UI_SOURCES +=                                               \
    $${_PRO_FILE_PWD_}/ui/application.cc                                \
    $${_PRO_FILE_PWD_}/ui/authorization_dialog.cc                       \
    $${_PRO_FILE_PWD_}/ui/client_window.cc                              \
    $${_PRO_FILE_PWD_}/ui/client_settings.cc                            \
    $${_PRO_FILE_PWD_}/ui/client_settings_dialog.cc                     \
    $${_PRO_FILE_PWD_}/ui/session_window.cc                             \
    $${_PRO_FILE_PWD_}/ui/update_settings_dialog.cc                     \

CLIENT_CORE_UI_FORMS +=                                                 \
    $${_PRO_FILE_PWD_}/ui/authorization_dialog.ui                       \
    $${_PRO_FILE_PWD_}/ui/client_window.ui                              \
    $${_PRO_FILE_PWD_}/ui/client_settings_dialog.ui                     \
    $${_PRO_FILE_PWD_}/ui/update_settings_dialog.ui                     \

CLIENT_CORE_UI_DESKTOP_HEADERS +=                                       \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_config_dialog.h               \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_toolbar.h                     \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_widget.h                      \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_settings.h                    \
    $${_PRO_FILE_PWD_}/ui/desktop/frame_factory_qimage.h                \
    $${_PRO_FILE_PWD_}/ui/desktop/frame_qimage.h                        \
    $${_PRO_FILE_PWD_}/ui/desktop/qt_desktop_window.h                   \
    $${_PRO_FILE_PWD_}/ui/desktop/record_settings_dialog.h              \
    $${_PRO_FILE_PWD_}/ui/desktop/select_screen_action.h                \
    $${_PRO_FILE_PWD_}/ui/desktop/statistics_dialog.h                   \
    $${_PRO_FILE_PWD_}/ui/desktop/task_manager_settings.h               \
    $${_PRO_FILE_PWD_}/ui/desktop/task_manager_window.h                 \

CLIENT_CORE_UI_DESKTOP_SOURCES +=                                       \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_config_dialog.cc              \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_toolbar.cc                    \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_widget.cc                     \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_settings.cc                   \
    $${_PRO_FILE_PWD_}/ui/desktop/frame_factory_qimage.cc               \
    $${_PRO_FILE_PWD_}/ui/desktop/frame_qimage.cc                       \
    $${_PRO_FILE_PWD_}/ui/desktop/qt_desktop_window.cc                  \
    $${_PRO_FILE_PWD_}/ui/desktop/record_settings_dialog.cc             \
    $${_PRO_FILE_PWD_}/ui/desktop/statistics_dialog.cc                  \
    $${_PRO_FILE_PWD_}/ui/desktop/task_manager_settings.cc              \
    $${_PRO_FILE_PWD_}/ui/desktop/task_manager_window.cc                \

CLIENT_CORE_UI_DESKTOP_FORMS +=                                         \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_config_dialog.ui              \
    $${_PRO_FILE_PWD_}/ui/desktop/desktop_toolbar.ui                    \
    $${_PRO_FILE_PWD_}/ui/desktop/record_settings_dialog.ui             \
    $${_PRO_FILE_PWD_}/ui/desktop/statistics_dialog.ui                  \
    $${_PRO_FILE_PWD_}/ui/desktop/task_manager_window.ui                \

$${upper($${TARGET})}_HEADERS +=                \
    $${CLIENT_CORE_HEADERS}                     \
    $${CLIENT_CORE_UI_HEADERS}                  \
    $${CLIENT_CORE_UI_DESKTOP_HEADERS}          \

$${upper($${TARGET})}_SOURCES +=                \
    $${CLIENT_CORE_SOURCES}                     \
    $${CLIENT_CORE_UI_SOURCES}                  \
    $${CLIENT_CORE_UI_DESKTOP_SOURCES}          \

$${upper($${TARGET})}_RESOURCES +=      \
    $${CLIENT_CORE_RESOURCES}           \

$${upper($${TARGET})}_FORMS +=                  \
    $${CLIENT_CORE_UI_FORMS}                    \
    $${CLIENT_CORE_UI_DESKTOP_FORMS}            \
