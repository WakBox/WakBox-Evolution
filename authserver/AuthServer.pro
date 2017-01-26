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

unix:!macx {
    LIBS += -L"/usr/lib/libcryptopp" -lcryptopp
}

macx: {
    LIBS += -L"/usr/local/lib/" -lcryptopp
}

win32 {
    LIBS += -L"C:/CryptoPP/lib" -lcryptopp563
    INCLUDEPATH += C:/CryptoPP/include
}

INCLUDEPATH += . ../dep ../shared
DEPENDPATH  += . ../dep ../shared

SOURCES += main.cpp \
    AuthServer.cpp \
    AuthSession.cpp

HEADERS += AuthServer.h \
    AuthSession.h

include(../dep/Dep.pri)
include(../shared/Shared.pri)
