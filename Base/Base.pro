TEMPLATE = lib
TARGET = RemoteControl-BaseLib

QT += core gui widgets

CONFIG += c++11 link_prl file_extension
DEFINES += BASE_IMPLEMENTATION

INCLUDEPATH +=  \
    $${REMOTECONTROL_THREEPARTY_INCLUDE_PATH}   \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $${PWD}/../Proto

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

LIBS += \
    -L$${REMOTECONTROL_THREEPARTY_LIBS_PATH} -ljpeg -llibcrypto -llibcurl                   \
    -llibssl -lopus -lsqlite3 -lturbojpeg -lvpx -lzlib -lzstd -llibprotobuf-lite -lyuv      \
    -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-ProtocolLib                           \
    -lRemoteControl-ModPLib -lRemoteControl-X11RegionLib -lRemoteControl-WebM               \
