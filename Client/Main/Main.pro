TEMPLATE = app
TARGET = RemoteControlClient
QT       += core gui widgets

CONFIG  += c++11 link_prl

INCLUDEPATH +=  \
    $${REMOTECONTROL_ROOT_PROJECT_PWD}          \

LIBS += -L$${REMOTECONTROL_DEST_BIN_PATH} -lRemoteControl-ClientCoreLib
QMAKE_RPATHDIR += $${REMOTECONTROL_DEST_BIN_PATH} $${REMOTECONTROL_THREEPARTY_LIBS_PATH}

SOURCES += \
    $$PWD/client_entry_point.cc
