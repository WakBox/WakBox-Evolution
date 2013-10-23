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

LIBS += -L"C:/CryptoCPP/lib" -lcryptopp

INCLUDEPATH += . ../shared ../worldserver ../worldserver/Game C:/CryptoCPP/include
DEPENDPATH += . ../shared ../worldserver ../worldserver/Game

SOURCES += main.cpp \
    WorldServer.cpp

HEADERS += WorldServer.h

include(../shared/Shared.pri)
include(Game/Game.pri)
