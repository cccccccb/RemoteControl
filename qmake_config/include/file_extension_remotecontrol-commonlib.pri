SOURCE_COMMON_HEADERS +=                                            \
    $${_PRO_FILE_PWD_}/clipboard.h                                  \
    $${_PRO_FILE_PWD_}/clipboard_monitor.h                          \
    $${_PRO_FILE_PWD_}/desktop_session_constants.h                  \
    $${_PRO_FILE_PWD_}/file_depacketizer.h                          \
    $${_PRO_FILE_PWD_}/file_enumerator.h                            \
    $${_PRO_FILE_PWD_}/file_packet.h                                \
    $${_PRO_FILE_PWD_}/file_packetizer.h                            \
    $${_PRO_FILE_PWD_}/file_platform_util.h                         \
    $${_PRO_FILE_PWD_}/file_task.h                                  \
    $${_PRO_FILE_PWD_}/file_task_consumer.h                         \
    $${_PRO_FILE_PWD_}/file_task_consumer_proxy.h                   \
    $${_PRO_FILE_PWD_}/file_task_factory.h                          \
    $${_PRO_FILE_PWD_}/file_task_producer.h                         \
    $${_PRO_FILE_PWD_}/file_task_producer_proxy.h                   \
    $${_PRO_FILE_PWD_}/file_worker.h                                \
    $${_PRO_FILE_PWD_}/file_worker_impl.h                           \
    $${_PRO_FILE_PWD_}/http_file_downloader.h                       \
    $${_PRO_FILE_PWD_}/keycode_converter.h                          \
    $${_PRO_FILE_PWD_}/system_info_constants.h                      \
    $${_PRO_FILE_PWD_}/update_checker.h                             \
    $${_PRO_FILE_PWD_}/update_info.h                                \
    $${_PRO_FILE_PWD_}/clipboard_win.h                              \
    $${_PRO_FILE_PWD_}/common_export.h

SOURCE_COMMON_SOURCES +=                                            \
    $${_PRO_FILE_PWD_}/clipboard.cc                                 \
    $${_PRO_FILE_PWD_}/clipboard_monitor.cc                         \
    $${_PRO_FILE_PWD_}/desktop_session_constants.cc                 \
    $${_PRO_FILE_PWD_}/file_depacketizer.cc                         \
    $${_PRO_FILE_PWD_}/file_packetizer.cc                           \
    $${_PRO_FILE_PWD_}/file_task.cc                                 \
    $${_PRO_FILE_PWD_}/file_task_consumer_proxy.cc                  \
    $${_PRO_FILE_PWD_}/file_task_factory.cc                         \
    $${_PRO_FILE_PWD_}/file_task_producer_proxy.cc                  \
    $${_PRO_FILE_PWD_}/file_worker.cc                               \
    $${_PRO_FILE_PWD_}/file_worker_impl.cc                          \
    $${_PRO_FILE_PWD_}/http_file_downloader.cc                      \
    $${_PRO_FILE_PWD_}/keycode_converter.cc                         \
    $${_PRO_FILE_PWD_}/system_info_constants.cc                     \
    $${_PRO_FILE_PWD_}/update_checker.cc                            \
    $${_PRO_FILE_PWD_}/update_info.cc                               \
    $${_PRO_FILE_PWD_}/clipboard_win.cc                             \
    $${_PRO_FILE_PWD_}/file_enumerator_win.cc                       \
    $${_PRO_FILE_PWD_}/file_platform_util_win.cc                    \

SOURCE_COMMON_UI_HEADERS +=                                         \
    $${_PRO_FILE_PWD_}/ui/about_dialog.h                            \
    $${_PRO_FILE_PWD_}/ui/download_dialog.h                         \
    $${_PRO_FILE_PWD_}/ui/language_action.h                         \
    $${_PRO_FILE_PWD_}/ui/session_type.h                            \
    $${_PRO_FILE_PWD_}/ui/status_dialog.h                           \
    $${_PRO_FILE_PWD_}/ui/text_chat_incoming_message.h              \
    $${_PRO_FILE_PWD_}/ui/text_chat_message.h                       \
    $${_PRO_FILE_PWD_}/ui/text_chat_outgoing_message.h              \
    $${_PRO_FILE_PWD_}/ui/text_chat_status_message.h                \
    $${_PRO_FILE_PWD_}/ui/text_chat_widget.h                        \
    $${_PRO_FILE_PWD_}/ui/update_dialog.h                           \

SOURCE_COMMON_UI_SOURCES +=                                         \
    $${_PRO_FILE_PWD_}/ui/about_dialog.cc                           \
    $${_PRO_FILE_PWD_}/ui/download_dialog.cc                        \
    $${_PRO_FILE_PWD_}/ui/language_action.cc                        \
    $${_PRO_FILE_PWD_}/ui/session_type.cc                           \
    $${_PRO_FILE_PWD_}/ui/status_dialog.cc                          \
    $${_PRO_FILE_PWD_}/ui/text_chat_incoming_message.cc             \
    $${_PRO_FILE_PWD_}/ui/text_chat_outgoing_message.cc             \
    $${_PRO_FILE_PWD_}/ui/text_chat_status_message.cc               \
    $${_PRO_FILE_PWD_}/ui/text_chat_widget.cc                       \
    $${_PRO_FILE_PWD_}/ui/update_dialog.cc                          \

SOURCE_COMMON_UI_FORMS +=                                           \
    $${_PRO_FILE_PWD_}/ui/about_dialog.ui                           \
    $${_PRO_FILE_PWD_}/ui/download_dialog.ui                        \
    $${_PRO_FILE_PWD_}/ui/status_dialog.ui                          \
    $${_PRO_FILE_PWD_}/ui/text_chat_incoming_message.ui             \
    $${_PRO_FILE_PWD_}/ui/text_chat_outgoing_message.ui             \
    $${_PRO_FILE_PWD_}/ui/text_chat_status_message.ui               \
    $${_PRO_FILE_PWD_}/ui/text_chat_widget.ui                       \
    $${_PRO_FILE_PWD_}/ui/update_dialog.ui                          \

SOURCE_COMMON_RESOURCES +=                      \
    $${_PRO_FILE_PWD_}/resources/common.qrc

$${upper($${TARGET})}_HEADERS +=                \
    $${SOURCE_COMMON_HEADERS}                   \
    $${SOURCE_COMMON_UI_HEADERS}                \

$${upper($${TARGET})}_SOURCES +=                \
    $${SOURCE_COMMON_SOURCES}                   \
    $${SOURCE_COMMON_UI_SOURCES}                \

$${upper($${TARGET})}_FORMS +=                  \
    $${SOURCE_COMMON_UI_FORMS}                  \

$${upper($${TARGET})}_RESOURCES +=              \
    $${SOURCE_COMMON_RESOURCES}
