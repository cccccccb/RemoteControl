TEMPLATE = lib
TARGET = RemoteControl-QtBaseLib

QT += core gui widgets network

CONFIG += staticlib c++11 create_prl file_extension

INCLUDEPATH += \
    $${PWD}/../

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}
