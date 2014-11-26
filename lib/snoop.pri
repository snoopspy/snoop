include(../../../vdream/vdream91/lib/vdream.pri)

#-------------------------------------------------
# SNOOP_LIB_NAME
#-------------------------------------------------
SNOOP_LIB_NAME=snoop
CONFIG(debug, debug|release) {
	SNOOP_LIB_NAME=$${SNOOP_LIB_NAME}_d
}

contains(QT, gui) {
	SNOOP_LIB_NAME=$${SNOOP_LIB_NAME}_gui
}

android-g++ {
	SNOOP_LIB_NAME=$${SNOOP_LIB_NAME}_android
}

#-------------------------------------------------
# winpcap
#-------------------------------------------------
WINPCAP_PATH  =   $$PWD/../../winpcap
INCLUDEPATH  +=   $${WINPCAP_PATH}/Include
win32:contains(QMAKE_TARGET.arch, x86_64) {
	LIBS       += -L$${WINPCAP_PATH}/Lib/x64
} else {
	LIBS       += -L$${WINPCAP_PATH}/Lib
}
LIBS         += -lwpcap -lIphlpapi

#-------------------------------------------------
# snoop
#-------------------------------------------------
SNOOP_PATH             =   $$PWD/..
INCLUDEPATH           +=   $${SNOOP_PATH}/include
INCLUDEPATH           +=   $${SNOOP_PATH}/lib
DEPENDPATH            +=   $${SNOOP_PATH}
LIBS                  += -L$${SNOOP_PATH}/lib -l$${SNOOP_LIB_NAME}
CONFIG(SNOOP_LIB_BUILD) {
} else {
	win32:PRE_TARGETDEPS       +=   $${SNOOP_PATH}/lib/$${SNOOP_LIB_NAME}.lib
	linux-g++:PRE_TARGETDEPS   +=  $${VDREAM_PATH}/lib/lib$${SNOOP_LIB_NAME}.a
	android-g++:PRE_TARGETDEPS +=  $${VDREAM_PATH}/lib/lib$${SNOOP_LIB_NAME}.so
	linux:LIBS                 +=  -lpcap
}
