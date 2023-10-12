TEMPLATE = app
TARGET = RemoteControlDesktopAgent
QT       += core gui widgets

CONFIG  += c++11 link_prl

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $$PWD/../Core

LIBS += -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-HostCoreLib

SOURCES += \
    $$PWD/desktop_agent_entry_point.cc
