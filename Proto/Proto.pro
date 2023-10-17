TEMPLATE = lib
TARGET = RemoteControl-ProtocolLib

QT -= core gui

CONFIG += staticlib c++11 create_prl protobuf_generate

INCLUDEPATH += \
    $${REMOTECONTROL_THREEPARTY_INCLUDE_PATH}

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

PROTOBUF_OUT_PWD = $${_PRO_FILE_PWD_}/proto
PROTOBUF_INPUT_FILES += \
    $${_PRO_FILE_PWD_}/common.proto                     \
    $${_PRO_FILE_PWD_}/desktop.proto                    \
    $${_PRO_FILE_PWD_}/desktop_extensions.proto         \
    $${_PRO_FILE_PWD_}/desktop_internal.proto           \
    $${_PRO_FILE_PWD_}/key_exchange.proto               \
    $${_PRO_FILE_PWD_}/host_internal.proto              \
    $${_PRO_FILE_PWD_}/relay_peer.proto                 \
    $${_PRO_FILE_PWD_}/task_manager.proto               \
    $${_PRO_FILE_PWD_}/user.proto                       \
