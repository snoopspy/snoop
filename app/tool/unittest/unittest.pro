#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T13:04:08
#
#-------------------------------------------------

QT       += core
QT       -= gui

include(../../../../../google/gtest/gtest.pri)
include(../../../lib/snoop.pri)

TARGET    = unittest
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
DESTDIR   = $${PWD}/../../../bin

SOURCES += main.cpp
