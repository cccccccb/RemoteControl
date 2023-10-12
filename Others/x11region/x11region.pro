TEMPLATE = lib
TARGET = RemoteControl-X11RegionLib

QT -= core gui

CONFIG += staticlib

DESTDIR = $${REMOTECONTROL_DEST_BIN_PATH}

HEADERS += x11region.h
SOURCES += x11region.c
