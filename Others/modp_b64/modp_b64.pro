TEMPLATE = lib
TARGET = RemoteControl-ModPLib

QT -= core gui

CONFIG += staticlib c++11

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

HEADERS += \
    $${PWD}/modp_b64_data.h \
    $${PWD}/modp_b64.h

SOURCES += \
    $${PWD}/modp_b64.c

INCLUDEPATH += \
    $${PWD}/../../
