SOURCE_HOST_CORE_HEADERS +=                                 \
    $${_PRO_FILE_PWD_}/client_session.h                     \
    $${_PRO_FILE_PWD_}/client_session_desktop.h             \
    $${_PRO_FILE_PWD_}/client_session_file_transfer.h       \
    $${_PRO_FILE_PWD_}/client_session_system_info.h         \
    $${_PRO_FILE_PWD_}/client_session_text_chat.h           \
    $${_PRO_FILE_PWD_}/desktop_agent_main.h                 \
    $${_PRO_FILE_PWD_}/desktop_session.h                    \
    $${_PRO_FILE_PWD_}/desktop_session_manager.h            \
    $${_PRO_FILE_PWD_}/desktop_session_agent.h              \
    $${_PRO_FILE_PWD_}/desktop_session_fake.h               \
    $${_PRO_FILE_PWD_}/desktop_session_ipc.h                \
    $${_PRO_FILE_PWD_}/desktop_session_proxy.h              \
    $${_PRO_FILE_PWD_}/desktop_session_process.h            \
    $${_PRO_FILE_PWD_}/file_transfer_agent.h                \
    $${_PRO_FILE_PWD_}/file_transfer_agent_main.h           \
    $${_PRO_FILE_PWD_}/host_export.h                        \
    $${_PRO_FILE_PWD_}/host_ipc_storage.h                   \
    $${_PRO_FILE_PWD_}/host_key_storage.h                   \
    $${_PRO_FILE_PWD_}/input_injector.h                     \
    $${_PRO_FILE_PWD_}/integrity_check.h                    \
    $${_PRO_FILE_PWD_}/router_controller.h                  \
    $${_PRO_FILE_PWD_}/server.h                             \
    $${_PRO_FILE_PWD_}/service.h                            \
    $${_PRO_FILE_PWD_}/service_constants.h                  \
    $${_PRO_FILE_PWD_}/service_main.h                       \
    $${_PRO_FILE_PWD_}/system_settings.h                    \
    $${_PRO_FILE_PWD_}/unconfirmed_client_session.h         \
    $${_PRO_FILE_PWD_}/user_session.h                       \
    $${_PRO_FILE_PWD_}/user_session_agent.h                 \
    $${_PRO_FILE_PWD_}/user_session_agent_proxy.h           \
    $${_PRO_FILE_PWD_}/user_session_manager.h               \
    $${_PRO_FILE_PWD_}/user_session_window.h                \
    $${_PRO_FILE_PWD_}/user_session_window_proxy.h          \
    $${_PRO_FILE_PWD_}/input_injector_win.h                 \
    $${_PRO_FILE_PWD_}/process_monitor.h                    \
    $${_PRO_FILE_PWD_}/system_info.h                        \
    $${_PRO_FILE_PWD_}/task_manager.h                       \
    $${_PRO_FILE_PWD_}/win/sas_injector.h                   \
    $${_PRO_FILE_PWD_}/win/updater_launcher.h               \

SOURCE_HOST_CORE_SOURECES +=                                \
    $${_PRO_FILE_PWD_}/client_session.cc                    \
    $${_PRO_FILE_PWD_}/client_session_desktop.cc            \
    $${_PRO_FILE_PWD_}/client_session_file_transfer.cc      \
    $${_PRO_FILE_PWD_}/client_session_system_info.cc        \
    $${_PRO_FILE_PWD_}/client_session_text_chat.cc          \
    $${_PRO_FILE_PWD_}/desktop_agent_main.cc                \
    $${_PRO_FILE_PWD_}/desktop_session.cc                   \
    $${_PRO_FILE_PWD_}/desktop_session_manager.cc           \
    $${_PRO_FILE_PWD_}/desktop_session_agent.cc             \
    $${_PRO_FILE_PWD_}/desktop_session_fake.cc              \
    $${_PRO_FILE_PWD_}/desktop_session_ipc.cc               \
    $${_PRO_FILE_PWD_}/desktop_session_process.cc           \
    $${_PRO_FILE_PWD_}/desktop_session_proxy.cc             \
    $${_PRO_FILE_PWD_}/file_transfer_agent.cc               \
    $${_PRO_FILE_PWD_}/file_transfer_agent_main.cc          \
    $${_PRO_FILE_PWD_}/host_ipc_storage.cc                  \
    $${_PRO_FILE_PWD_}/host_key_storage.cc                  \
    $${_PRO_FILE_PWD_}/integrity_check.cc                   \
    $${_PRO_FILE_PWD_}/router_controller.cc                 \
    $${_PRO_FILE_PWD_}/server.cc                            \
    $${_PRO_FILE_PWD_}/service.cc                           \
    $${_PRO_FILE_PWD_}/service_constants.cc                 \
    $${_PRO_FILE_PWD_}/service_main.cc                      \
    $${_PRO_FILE_PWD_}/system_settings.cc                   \
    $${_PRO_FILE_PWD_}/unconfirmed_client_session.cc        \
    $${_PRO_FILE_PWD_}/user_session.cc                      \
    $${_PRO_FILE_PWD_}/user_session_agent.cc                \
    $${_PRO_FILE_PWD_}/user_session_agent_proxy.cc          \
    $${_PRO_FILE_PWD_}/user_session_manager.cc              \
    $${_PRO_FILE_PWD_}/user_session_window_proxy.cc         \
    $${_PRO_FILE_PWD_}/input_injector_win.cc                \
    $${_PRO_FILE_PWD_}/process_monitor.cc                   \
    $${_PRO_FILE_PWD_}/system_info.cc                       \
    $${_PRO_FILE_PWD_}/task_manager.cc                      \
    $${_PRO_FILE_PWD_}/win/sas_injector.cc                  \
    $${_PRO_FILE_PWD_}/win/updater_launcher.cc              \

SOURCE_HOST_CORE_UI_HEADERS +=                              \
    $${_PRO_FILE_PWD_}/ui/application.h                     \
    $${_PRO_FILE_PWD_}/ui/change_password_dialog.h          \
    $${_PRO_FILE_PWD_}/ui/check_password_dialog.h           \
    $${_PRO_FILE_PWD_}/ui/config_dialog.h                   \
    $${_PRO_FILE_PWD_}/ui/connect_confirm_dialog.h          \
    $${_PRO_FILE_PWD_}/ui/host_main.h                       \
    $${_PRO_FILE_PWD_}/ui/main_window.h                     \
    $${_PRO_FILE_PWD_}/ui/notifier_window.h                 \
    $${_PRO_FILE_PWD_}/ui/settings_util.h                   \
    $${_PRO_FILE_PWD_}/ui/user_dialog.h                     \
    $${_PRO_FILE_PWD_}/ui/user_settings.h                   \
    $${_PRO_FILE_PWD_}/ui/user_tree_item.h                  \

SOURCE_HOST_CORE_UI_SOURCES +=                              \
    $${_PRO_FILE_PWD_}/ui/application.cc                    \
    $${_PRO_FILE_PWD_}/ui/change_password_dialog.cc         \
    $${_PRO_FILE_PWD_}/ui/check_password_dialog.cc          \
    $${_PRO_FILE_PWD_}/ui/config_dialog.cc                  \
    $${_PRO_FILE_PWD_}/ui/host_main.cc                      \
    $${_PRO_FILE_PWD_}/ui/main_window.cc                    \
    $${_PRO_FILE_PWD_}/ui/notifier_window.cc                \
    $${_PRO_FILE_PWD_}/ui/settings_util.cc                  \
    $${_PRO_FILE_PWD_}/ui/connect_confirm_dialog.cc         \
    $${_PRO_FILE_PWD_}/ui/user_dialog.cc                    \
    $${_PRO_FILE_PWD_}/ui/user_settings.cc                  \
    $${_PRO_FILE_PWD_}/ui/user_tree_item.cc                 \

SOURCE_HOST_CORE_UI_FORMS +=                                \
    $${_PRO_FILE_PWD_}/ui/change_password_dialog.ui         \
    $${_PRO_FILE_PWD_}/ui/check_password_dialog.ui          \
    $${_PRO_FILE_PWD_}/ui/config_dialog.ui                  \
    $${_PRO_FILE_PWD_}/ui/connect_confirm_dialog.ui         \
    $${_PRO_FILE_PWD_}/ui/main_window.ui                    \
    $${_PRO_FILE_PWD_}/ui/notifier_window.ui                \
    $${_PRO_FILE_PWD_}/ui/user_dialog.ui                    \

SOURCE_HOST_CORE_UI_RESOURCES +=                            \
    $${_PRO_FILE_PWD_}/ui/resources.qrc

$${upper($${TARGET})}_HEADERS +=                \
    $${SOURCE_HOST_CORE_HEADERS}                \
    $${SOURCE_HOST_CORE_UI_HEADERS}             \

$${upper($${TARGET})}_SOURCES +=                \
    $${SOURCE_HOST_CORE_SOURECES}               \
    $${SOURCE_HOST_CORE_UI_SOURCES}             \

$${upper($${TARGET})}_FORMS +=                  \
    $${SOURCE_HOST_CORE_UI_FORMS}               \

$${upper($${TARGET})}_RESOURCES +=              \
    $${SOURCE_HOST_CORE_UI_RESOURCES}
