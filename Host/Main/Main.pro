TEMPLATE = app
TARGET = RemoteControlHost
QT       += core gui widgets

CONFIG  += c++11 link_prl

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $$PWD/../Core

LIBS += -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-HostCoreLib

SOURCES += \
    $$PWD/host_entry_point.cc
