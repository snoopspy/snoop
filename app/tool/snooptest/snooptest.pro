#-------------------------------------------------
#
# Project created by QtCreator 2012-06-06T20:03:28
#
#-------------------------------------------------

QT -= gui

include(../../../lib/snoop.pri)

TARGET   = snooptest
CONFIG  += console
CONFIG  -= app_bundle
TEMPLATE = app
DESTDIR   = $${PWD}/../../../bin

SOURCES += \
    main.cpp

HEADERS += \
    main.h
