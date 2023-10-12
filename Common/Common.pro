TEMPLATE = lib
TARGET = RemoteControl-CommonLib

QT += core gui widgets winextras network

CONFIG += c++11 create_prl link_prl file_extension
DEFINES += COMMON_IMPLEMENTATION

INCLUDEPATH +=  \
    $${REMOTECONTROL_THREEPARTY_INCLUDE_PATH}   \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $${PWD}/../Proto

LIBS += \
    -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-BaseLib                               \
    -lRemoteControl-ProtocolLib -lRemoteControl-ModPLib -lRemoteControl-X11RegionLib        \
    -lRemoteControl-WebM -lRemoteControl-QtBaseLib                                          \
    -L$${REMOTECONTROL_THREEPARTY_LIBS_PATH} -ljpeg -llibcrypto -llibcurl                   \
    -llibssl -lopus -lsqlite3 -lturbojpeg -lvpx -lzlib -lzstd -llibprotobuf-lite      \

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}
