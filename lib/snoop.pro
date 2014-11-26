CONFIG += SNOOP_LIB_BUILD
#QT    -= gui
#QT    += gui widgets

include (snoop.pri)

TARGET   = $${SNOOP_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = ../lib
