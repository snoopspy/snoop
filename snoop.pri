#------------------------------------------------------------------------------
# library name
#------------------------------------------------------------------------------
SNOOP_LIB_NAME = snoop
android-g++:                 SNOOP_LIB_NAME = $${SNOOP_LIB_NAME}_android
contains(QT, gui)            SNOOP_LIB_NAME = $${SNOOP_LIB_NAME}_gui
CONFIG(GTEST)                SNOOP_LIB_NAME = $${SNOOP_LIB_NAME}_test
CONFIG(debug, debug|release) SNOOP_LIB_NAME = $${SNOOP_LIB_NAME}_d
message($${SNOOP_LIB_NAME}) # gilgil temp 2015.01.20

#------------------------------------------------------------------------------
# snoop
#------------------------------------------------------------------------------
SNOOP_PATH  =  $${PWD}
INCLUDEPATH += $${SNOOP_PATH}/src
!CONFIG(SNOOP_LIB_BUILD) {
  gcc:PRE_TARGETDEPS +=  $${SNOOP_PATH}/lib/lib$${SNOOP_LIB_NAME}.a
  LIBS               += -L$${SNOOP_PATH}/lib
  LIBS               += -l$${SNOOP_LIB_NAME}
}

#------------------------------------------------------------------------------
# pcap
#------------------------------------------------------------------------------
win32 {
  WINPCAP_PATH  = $$PWD/../winpcap
  INCLUDEPATH  += $${WINPCAP_PATH}/Include
  contains(QMAKE_TARGET.arch, x86_64) {
    LIBS     += -L$${WINPCAP_PATH}/Lib/x64
  } else {
    LIBS     += -L$${WINPCAP_PATH}/Lib
    LIBS     += -lwpcap -lIphlpapi
  }
}
linux: LIBS += -lpcap

#------------------------------------------------------------------------------
# vdream
#------------------------------------------------------------------------------
include(../../vdream/vdream/vdream.pri)
