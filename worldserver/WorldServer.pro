#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:56
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = worldserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    LIBS += -L"/usr/lib/libcryptopp" -lcryptopp
}

win32 {
    LIBS += -L"C:/CryptoPP/lib" -lcryptopp563
    INCLUDEPATH += C:/CryptoPP/include
}

INCLUDEPATH += . ../dep ../shared ../worldserver ../worldserver/Game
DEPENDPATH += . ../dep ../shared ../worldserver ../worldserver/Game

SOURCES += main.cpp \
    WorldServer.cpp

HEADERS += WorldServer.h

include(../dep/Dep.pri)
include(../shared/Shared.pri)
include(Game/Game.pri)
include(Scripts/Scripts.pri)
