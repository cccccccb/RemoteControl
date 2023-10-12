TEMPLATE = lib
TARGET = RemoteControl-ClientCoreLib

QT += core gui widgets winextras printsupport

CONFIG += c++11 link_prl file_extension
DEFINES += CLIENT_CORE_IMPLEMENTATION

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $${REMOTECONTROL_THREEPARTY_INCLUDE_PATH}   \
    $${PWD}/../../Proto

LIBS += \
    -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-BaseLib -lRemoteControl-CommonLib     \
    -lRemoteControl-ProtocolLib -lRemoteControl-ModPLib -lRemoteControl-X11RegionLib        \
    -lRemoteControl-WebM -lRemoteControl-QtBaseLib                                          \
    -L$${REMOTECONTROL_THREEPARTY_LIBS_PATH} -ljpeg -llibcrypto -llibcurl                   \
    -llibssl -lopus -lsqlite3 -lturbojpeg -lvpx -lzlib -lzstd -llibprotobuf-lite      \

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

RESOURCES += \
    resources/client.qrc
