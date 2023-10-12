TEMPLATE = app
TARGET = RemoteControlService

CONFIG -= app_bundle qt
CONFIG += console c++11 link_prl

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \
    $$PWD/../Core

LIBS += -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-HostCoreLib

SOURCES += \
    $$PWD/service_entry_point.cc

