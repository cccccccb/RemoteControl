TEMPLATE = lib
TARGET = RemoteControl-WebM

QT -= core gui

CONFIG += staticlib c++11

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

HEADERS += \
    $${PWD}/common/webmids.h            \
    $${PWD}/mkvmuxer/mkvmuxer.h         \
    $${PWD}/mkvmuxer/mkvmuxertypes.h    \
    $${PWD}/mkvmuxer/mkvmuxerutil.h     \
    $${PWD}/mkvmuxer/mkvwriter.h        \
    $${PWD}/mkvparser/mkvparser.h       \
    $${PWD}/mkvparser/mkvreader.h

SOURCES += \
    $${PWD}/mkvmuxer/mkvmuxer.cc        \
    $${PWD}/mkvmuxer/mkvmuxerutil.cc    \
    $${PWD}/mkvmuxer/mkvwriter.cc       \
    $${PWD}/mkvparser/mkvparser.cc      \
    $${PWD}/mkvparser/mkvreader.cc      \
