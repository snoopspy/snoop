CONFIG(SNOOP_LIB_BUILD_GUI) {
  QT += gui widgets
} else {
  QT -= gui
}

CONFIG += SNOOP_LIB_BUILD
include (snoop.pri)

TARGET   = $${SNOOP_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}

SOURCES += \
  ../include/process/snoopudpsender.cpp \
  ../include/process/snoopwriteadapter.cpp \
  ../include/process/snoopchecksum.cpp \
  ../include/process/snoopblock.cpp \
  ../include/process/snoopudpreceiver.cpp \
  ../include/process/snoopdatafind.cpp \
  ../include/process/snoopprocessfactory.cpp \
  ../include/process/snoopflowmgrtest.cpp \
  ../include/process/snoopdelay.cpp \
  ../include/process/snoopudpchunk.cpp \
  ../include/process/snoopcommandwidget.cpp \
  ../include/process/snoopflowmgr.cpp \
  ../include/process/snoopflowchange.cpp \
  ../include/process/snoopdnschange.cpp \
  ../include/process/snoopdump.cpp \
  ../include/process/snoopwritewindivert.cpp \
  ../include/process/snoopdatachange.cpp \
  ../include/process/snoopcommand.cpp \
  ../include/process/snoopprocess.cpp \
  ../include/process/snooptcpblock.cpp \
  ../include/filter/snoopprocessfilter.cpp \
  ../include/filter/snoopfilter.cpp \
  ../include/filter/snoopprocessfilterwidget.cpp \
  ../include/filter/snoopbpfilter.cpp \
  ../include/filter/snoopfilterfactory.cpp \
  ../include/capture/snooppcap.cpp \
  ../include/capture/snoopwindivert.cpp \
  ../include/capture/snooparpspoof.cpp \
  ../include/capture/snoopcapturefactory.cpp \
  ../include/capture/snoopadapter.cpp \
  ../include/capture/snoopremote.cpp \
  ../include/capture/snoopsourcepcap.cpp \
  ../include/capture/snoopfile.cpp \
  ../include/capture/snoopcapture.cpp \
  ../include/capture/snoopvirtualnat.cpp \
  ../include/parse/snooptcpdata.cpp \
  ../include/parse/snoopudp.cpp \
  ../include/parse/snoopdns.cpp \
  ../include/parse/snoopeth.cpp \
  ../include/parse/snooparp.cpp \
  ../include/parse/snoopicmp.cpp \
  ../include/parse/snooptcp.cpp \
  ../include/parse/snoopip.cpp \
  ../include/parse/snoopudpdata.cpp \
  ../include/base/snoopautodetectadapter.cpp \
  ../include/base/snooptype.cpp \
  ../include/base/snoopfindhost.cpp \
  ../include/base/snooptypekey.cpp \
  ../include/base/snoopnetinfo.cpp \
  ../include/base/snoophostlist.cpp \
  ../include/base/snooprtm.cpp \
  ../include/base/snoopnetstat.cpp \
  ../include/base/snoopinterface.cpp \
  ../include/base/snooppacket.cpp \
	../include/base/snoopbase.cpp

HEADERS += \
  ../include/process/snoopdump.h \
  ../include/process/snoopchecksum.h \
  ../include/process/snoopprocess.h \
  ../include/process/snoopdatachange.h \
  ../include/process/snoopdnschange.h \
  ../include/process/snoopflowmgr.h \
  ../include/process/snoopudpsender.h \
  ../include/process/snoopudpchunk.h \
  ../include/process/snoopflowchange.h \
  ../include/process/snoopwriteadapter.h \
  ../include/process/snoopwritewindivert.h \
  ../include/process/snooptcpblock.h \
  ../include/process/snoopdatafind.h \
  ../include/process/snoopcommand.h \
  ../include/process/snoopdelay.h \
  ../include/process/snoopprocessfactory.h \
  ../include/process/snoopflowmgrtest.h \
  ../include/process/snoopblock.h \
  ../include/process/snoopudpreceiver.h \
  ../include/process/snoopcommandwidget.h \
  ../include/filter/snoopprocessfilterwidget.h \
  ../include/filter/snoopbpfilter.h \
  ../include/filter/snoopfilter.h \
  ../include/filter/snoopprocessfilter.h \
  ../include/filter/snoopfilterfactory.h \
  ../include/windivert/windivert.h \
  ../include/capture/snoopcapture.h \
  ../include/capture/snoopsourcepcap.h \
  ../include/capture/snooparpspoof.h \
  ../include/capture/snoopvirtualnat.h \
  ../include/capture/snoopremote.h \
  ../include/capture/snoopfile.h \
  ../include/capture/snoopcapturefactory.h \
  ../include/capture/snoopadapter.h \
  ../include/capture/snoopwindivert.h \
  ../include/capture/snooppcap.h \
  ../include/parse/snoopudp.h \
  ../include/parse/snooparp.h \
  ../include/parse/snooptcp.h \
  ../include/parse/snoopeth.h \
  ../include/parse/snoopdns.h \
  ../include/parse/snoopip.h \
  ../include/parse/snooptcpdata.h \
  ../include/parse/snoopudpdata.h \
  ../include/parse/snoopicmp.h \
  ../include/base/snoopinterface.h \
  ../include/base/snoopfindhost.h \
  ../include/base/snooptypekey.h \
  ../include/base/snooppacket.h \
  ../include/base/snoopautodetectadapter.h \
  ../include/base/snooprtm.h \
  ../include/base/snoop.h \
  ../include/base/snooptype.h \
  ../include/base/snoopnetinfo.h \
  ../include/base/snoopnetstat.h \
  ../include/base/snoophostlist.h \
  ../include/libnet/libnet-headers.h \
  ../include/libnet/libnet-structures.h \
  ../include/libnet/libnet-functions.h \
  ../include/libnet/libnet-types.h \
  ../include/libnet/config.h \
  ../include/libnet/libnet-asn1.h \
  ../include/libnet/libnet-macros.h \
	../include/base/snoopbase.h
