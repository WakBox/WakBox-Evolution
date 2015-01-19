#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:56
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = authserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    LIBS += -L"/usr/lib/libcryptopp" -lcryptopp
}

win32 {
    LIBS += -L"C:/CryptoCPP/lib" -lcryptopp562
    INCLUDEPATH += C:/CryptoCPP/include
}

INCLUDEPATH += . ../shared
DEPENDPATH  += . ../shared

SOURCES += main.cpp \
    AuthServer.cpp \
    AuthSession.cpp

HEADERS += AuthServer.h \
    AuthSession.h

include(../shared/Shared.pri)
