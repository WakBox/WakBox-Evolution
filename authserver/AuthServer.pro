#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:24
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = authserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += . ../shared ../worldserver ../worldserver/Game
DEPENDPATH += . ../shared ../worldserver ../worldserver/Game

SOURCES += main.cpp

include(AuthServer.pri)
include(../shared/Shared.pri)
include(../worldserver/Game/Game.pri)
