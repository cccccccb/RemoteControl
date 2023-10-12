CLIENT_CORE_HEADERS +=                                                  \
    $${_PRO_FILE_PWD_}/client.h                                         \
    $${_PRO_FILE_PWD_}/client_config.h                                  \
    $${_PRO_FILE_PWD_}/client_desktop.h                                 \
    $${_PRO_FILE_PWD_}/client_file_transfer.h                           \
    $${_PRO_FILE_PWD_}/client_main.h                                    \
    $${_PRO_FILE_PWD_}/client_proxy.h                                   \
    $${_PRO_FILE_PWD_}/client_system_info.h                             \
    $${_PRO_FILE_PWD_}/client_text_chat.h                               \
    $${_PRO_FILE_PWD_}/config_factory.h                                 \
    $${_PRO_FILE_PWD_}/desktop_control.h                                \
    $${_PRO_FILE_PWD_}/desktop_control_proxy.h                          \
    $${_PRO_FILE_PWD_}/desktop_window.h                                 \
    $${_PRO_FILE_PWD_}/desktop_window_proxy.h                           \
    $${_PRO_FILE_PWD_}/file_control.h                                   \
    $${_PRO_FILE_PWD_}/file_control_proxy.h                             \
    $${_PRO_FILE_PWD_}/file_manager_window.h                            \
    $${_PRO_FILE_PWD_}/file_manager_window_proxy.h                      \
    $${_PRO_FILE_PWD_}/file_remove_queue_builder.h                      \
    $${_PRO_FILE_PWD_}/file_remove_window_proxy.h                       \
    $${_PRO_FILE_PWD_}/file_remover.h                                   \
    $${_PRO_FILE_PWD_}/file_remove_window.h                             \
    $${_PRO_FILE_PWD_}/file_remover_proxy.h                             \
    $${_PRO_FILE_PWD_}/file_transfer.h                                  \
    $${_PRO_FILE_PWD_}/file_transfer_proxy.h                            \
    $${_PRO_FILE_PWD_}/file_transfer_queue_builder.h                    \
    $${_PRO_FILE_PWD_}/file_transfer_window.h                           \
    $${_PRO_FILE_PWD_}/file_transfer_window_proxy.h                     \
    $${_PRO_FILE_PWD_}/frame_factory.h                                  \
    $${_PRO_FILE_PWD_}/input_event_filter.h                             \
    $${_PRO_FILE_PWD_}/router.h                                         \
    $${_PRO_FILE_PWD_}/router_proxy.h                                   \
    $${_PRO_FILE_PWD_}/router_window.h                                  \
    $${_PRO_FILE_PWD_}/router_config.h                                  \
    $${_PRO_FILE_PWD_}/router_window_proxy.h                            \
    $${_PRO_FILE_PWD_}/router_controller.h                              \
    $${_PRO_FILE_PWD_}/router_config_storage.h                          \
    $${_PRO_FILE_PWD_}/status_window.h                                  \
    $${_PRO_FILE_PWD_}/status_window_proxy.h                            \
    $${_PRO_FILE_PWD_}/system_info_control.h                            \
    $${_PRO_FILE_PWD_}/system_info_control_proxy.h                      \
    $${_PRO_FILE_PWD_}/system_info_window.h                             \
    $${_PRO_FILE_PWD_}/system_info_window_proxy.h                       \
    $${_PRO_FILE_PWD_}/text_chat_control.h                              \
    $${_PRO_FILE_PWD_}/text_chat_control_proxy.h                        \
    $${_PRO_FILE_PWD_}/text_chat_window.h                               \
    $${_PRO_FILE_PWD_}/text_chat_window_proxy.h                         \
    $${_PRO_FILE_PWD_}/client_core_export.h

CLIENT_CORE_SOURCES +=                               \
    $${_PRO_FILE_PWD_}/client_config.cc                                 \
    $${_PRO_FILE_PWD_}/client_desktop.cc                                \
    $${_PRO_FILE_PWD_}/client.cc                                        \
    $${_PRO_FILE_PWD_}/client_file_transfer.cc                          \
    $${_PRO_FILE_PWD_}/client_main.cc                                   \
    $${_PRO_FILE_PWD_}/client_proxy.cc                                  \
    $${_PRO_FILE_PWD_}/client_system_info.cc                            \
    $${_PRO_FILE_PWD_}/client_text_chat.cc                              \
    $${_PRO_FILE_PWD_}/config_factory.cc                                \
    $${_PRO_FILE_PWD_}/desktop_control_proxy.cc                         \
    $${_PRO_FILE_PWD_}/desktop_window_proxy.cc                          \
    $${_PRO_FILE_PWD_}/file_control_proxy.cc                            \
    $${_PRO_FILE_PWD_}/file_manager_window_proxy.cc                     \
    $${_PRO_FILE_PWD_}/file_remove_queue_builder.cc                     \
    $${_PRO_FILE_PWD_}/file_remove_window_proxy.cc                      \
    $${_PRO_FILE_PWD_}/file_remover.cc                                  \
    $${_PRO_FILE_PWD_}/file_transfer.cc                                 \
    $${_PRO_FILE_PWD_}/file_transfer_proxy.cc                           \
    $${_PRO_FILE_PWD_}/file_transfer_queue_builder.cc                   \
    $${_PRO_FILE_PWD_}/file_transfer_window_proxy.cc                    \
    $${_PRO_FILE_PWD_}/input_event_filter.cc                            \
    $${_PRO_FILE_PWD_}/router.cc                                        \
    $${_PRO_FILE_PWD_}/router_proxy.cc                                  \
    $${_PRO_FILE_PWD_}/router_window_proxy.cc                           \
    $${_PRO_FILE_PWD_}/router_config.cc                                 \
    $${_PRO_FILE_PWD_}/router_config_storage.cc                         \
    $${_PRO_FILE_PWD_}/router_controller.cc                             \
    $${_PRO_FILE_PWD_}/file_remover_proxy.cc                            \
    $${_PRO_FILE_PWD_}/status_window_proxy.cc                           \
    $${_PRO_FILE_PWD_}/system_info_control_proxy.cc                     \
    $${_PRO_FILE_PWD_}/system_info_window_proxy.cc                      \
    $${_PRO_FILE_PWD_}/text_chat_control_proxy.cc                       \
    $${_PRO_FILE_PWD_}/text_chat_window_proxy.cc                        \

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

CLIENT_CORE_UI_FILE_TRANSFER_HEADERS +=                                 \
    $${_PRO_FILE_PWD_}/ui/file_transfer/address_bar.h                   \
    $${_PRO_FILE_PWD_}/ui/file_transfer/address_bar_model.h             \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_error_code.h               \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_item_delegate.h            \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_list.h                     \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_list_model.h               \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_manager_settings.h         \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_mime_data.h                \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_name_validator.h           \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_panel.h                    \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_remove_dialog.h            \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_transfer_dialog.h          \
    $${_PRO_FILE_PWD_}/ui/file_transfer/qt_file_manager_window.h        \

CLIENT_CORE_UI_FILE_TRANSFER_SOURCES +=                                 \
    $${_PRO_FILE_PWD_}/ui/file_transfer/address_bar.cc                  \
    $${_PRO_FILE_PWD_}/ui/file_transfer/address_bar_model.cc            \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_error_code.cc              \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_item_delegate.cc           \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_list.cc                    \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_list_model.cc              \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_manager_settings.cc        \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_mime_data.cc               \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_name_validator.cc          \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_panel.cc                   \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_remove_dialog.cc           \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_transfer_dialog.cc         \
    $${_PRO_FILE_PWD_}/ui/file_transfer/qt_file_manager_window.cc       \

CLIENT_CORE_UI_FILE_TRANSFER_FORMS +=                                   \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_panel.ui                   \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_remove_dialog.ui           \
    $${_PRO_FILE_PWD_}/ui/file_transfer/file_transfer_dialog.ui         \
    $${_PRO_FILE_PWD_}/ui/file_transfer/qt_file_manager_window.ui       \

CLIENT_CORE_UI_ROUTER_MANAGER_HEADERS +=                                \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_manager_window.h        \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_status_dialog.h         \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_user_dialog.h           \

CLIENT_CORE_UI_ROUTER_MANAGER_SOURCES +=                                \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_manager_window.cc       \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_status_dialog.cc        \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_user_dialog.cc          \

CLIENT_CORE_UI_ROUTER_MANAGER_FORMS +=                                  \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_manager_window.ui       \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_status_dialog.ui        \
    $${_PRO_FILE_PWD_}/ui/router_manager/router_user_dialog.ui          \

CLIENT_CORE_UI_SYS_INFO_HEADERS +=                                      \
    $${_PRO_FILE_PWD_}/ui/sys_info/qt_system_info_window.h              \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget.h                    \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_applications.h       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_connections.h        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_devices.h            \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_drivers.h            \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_env_vars.h           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_event_logs.h         \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_licenses.h           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_users.h        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_user_groups.h  \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_monitors.h           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_shares.h         \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_adapters.h       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_open_files.h         \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_power_options.h      \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_printers.h           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_processes.h          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_routes.h             \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_services.h           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_summary.h            \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_video_adapters.h     \
    $${_PRO_FILE_PWD_}/ui/sys_info/tree_to_html.h                       \

CLIENT_CORE_UI_SYS_INFO_SOURCES +=                                      \
    $${_PRO_FILE_PWD_}/ui/sys_info/qt_system_info_window.cc             \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget.cc                   \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_applications.cc      \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_connections.cc       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_devices.cc           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_drivers.cc           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_env_vars.cc          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_event_logs.cc        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_licenses.cc          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_users.cc       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_user_groups.cc \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_monitors.cc          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_shares.cc        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_adapters.cc      \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_open_files.cc        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_power_options.cc     \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_printers.cc          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_processes.cc         \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_routes.cc            \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_services.cc          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_summary.cc           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_video_adapters.cc    \
    $${_PRO_FILE_PWD_}/ui/sys_info/tree_to_html.cc                      \

CLIENT_CORE_UI_SYS_INFO_FORMS +=                                        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_adapters.ui      \
    $${_PRO_FILE_PWD_}/ui/sys_info/qt_system_info_window.ui             \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_event_logs.ui        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_applications.ui      \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_connections.ui       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_devices.ui           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_drivers.ui           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_env_vars.ui          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_licenses.ui          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_users.ui       \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_local_user_groups.ui \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_monitors.ui          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_net_shares.ui        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_open_files.ui        \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_power_options.ui     \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_printers.ui          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_processes.ui         \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_routes.ui            \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_services.ui          \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_summary.ui           \
    $${_PRO_FILE_PWD_}/ui/sys_info/sys_info_widget_video_adapters.ui    \

CLIENT_CORE_UI_TEXT_CHAT_HEADERS +=                                     \
    $${_PRO_FILE_PWD_}/ui/text_chat/qt_text_chat_window.h

CLIENT_CORE_UI_TEXT_CHAT_SOURCES +=                                     \
    $${_PRO_FILE_PWD_}/ui/text_chat/qt_text_chat_window.cc

CLIENT_CORE_UI_TEXT_CHAT_FORMS +=                                       \
    $${_PRO_FILE_PWD_}/ui/text_chat/qt_text_chat_window.ui

$${upper($${TARGET})}_HEADERS +=                \
    $${CLIENT_CORE_HEADERS}                     \
    $${CLIENT_CORE_UI_HEADERS}                  \
    $${CLIENT_CORE_UI_DESKTOP_HEADERS}          \
    $${CLIENT_CORE_UI_FILE_TRANSFER_HEADERS}    \
    $${CLIENT_CORE_UI_ROUTER_MANAGER_HEADERS}   \
    $${CLIENT_CORE_UI_SYS_INFO_HEADERS}         \
    $${CLIENT_CORE_UI_TEXT_CHAT_HEADERS}        \

$${upper($${TARGET})}_SOURCES +=                \
    $${CLIENT_CORE_SOURCES}                     \
    $${CLIENT_CORE_UI_SOURCES}                  \
    $${CLIENT_CORE_UI_DESKTOP_SOURCES}          \
    $${CLIENT_CORE_UI_FILE_TRANSFER_SOURCES}    \
    $${CLIENT_CORE_UI_ROUTER_MANAGER_SOURCES}   \
    $${CLIENT_CORE_UI_SYS_INFO_SOURCES}         \
    $${CLIENT_CORE_UI_TEXT_CHAT_SOURCES}        \

$${upper($${TARGET})}_RESOURCES +=      \
    $${CLIENT_CORE_RESOURCES}           \

$${upper($${TARGET})}_FORMS +=                  \
    $${CLIENT_CORE_UI_FORMS}                    \
    $${CLIENT_CORE_UI_DESKTOP_FORMS}            \
    $${CLIENT_CORE_UI_FILE_TRANSFER_FORMS}      \
    $${CLIENT_CORE_UI_ROUTER_MANAGER_FORMS}     \
    $${CLIENT_CORE_UI_SYS_INFO_FORMS}           \
    $${CLIENT_CORE_UI_TEXT_CHAT_FORMS}          \
