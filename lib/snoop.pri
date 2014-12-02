include(../../../vdream/vdream91/lib/vdream.pri)

#-------------------------------------------------
# pcap
#-------------------------------------------------
win32 {
	WINPCAP_PATH  = $$PWD/../../winpcap
	INCLUDEPATH  += $${WINPCAP_PATH}/Include
	contains(QMAKE_TARGET.arch, x86_64) {
		LIBS     += -L$${WINPCAP_PATH}/Lib/x64
	} else {
		LIBS     += -L$${WINPCAP_PATH}/Lib
		LIBS     += -lwpcap -lIphlpapi
	}
}
linux {
	LIBS         += -lpcap
}

#-------------------------------------------------
# library name
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
# snoop
#-------------------------------------------------
SNOOP_PATH  =  $${PWD}/..
INCLUDEPATH += $${SNOOP_PATH}/include
# DEPENDPATH  += $${SNOOP_PATH} ## gilgil temp 2014.12.02
!CONFIG(SNOOP_LIB_BUILD) {
	win32-msvc*:PRE_TARGETDEPS +=  $${SNOOP_PATH}/lib/$${SNOOP_LIB_NAME}.lib
	gcc:PRE_TARGETDEPS         +=  $${SNOOP_PATH}/lib/lib$${SNOOP_LIB_NAME}.a
	LIBS                       += -L$${SNOOP_PATH}/lib
	LIBS                       += -l$${SNOOP_LIB_NAME}
}
