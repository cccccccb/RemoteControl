TEMPLATE = lib
TARGET = RemoteControl-HostCoreLib

QT += core gui widgets winextras network

CONFIG += c++11 link_prl file_extension

DEFINES += HOST_IMPLEMENTATION
DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

LIBS += \
    -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-CommonLib -lRemoteControl-BaseLib     \
    -lRemoteControl-ProtocolLib -lRemoteControl-ModPLib -lRemoteControl-X11RegionLib        \
    -lRemoteControl-WebM -lRemoteControl-QtBaseLib                                          \
    -L$${REMOTECONTROL_THREEPARTY_LIBS_PATH} -ljpeg -llibcrypto -llibcurl                   \
    -llibssl -lopus -lsqlite3 -lturbojpeg -lvpx -lzlib -lzstd -llibprotobuf-lite      \

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $${REMOTECONTROL_THREEPARTY_INCLUDE_PATH}   \
    $${PWD}/../../Proto
