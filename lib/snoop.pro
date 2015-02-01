CONFIG += SNOOP_LIB_BUILD
include (snoop.pri)

TARGET   = $${SNOOP_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}

SOURCES += \
  ../src/process/snoopudpsender.cpp \
  ../src/process/snoopwriteadapter.cpp \
  ../src/process/snoopchecksum.cpp \
  ../src/process/snoopblock.cpp \
  ../src/process/snoopudpreceiver.cpp \
  ../src/process/snoopdatafind.cpp \
  ../src/process/snoopprocessfactory.cpp \
  ../src/process/snoopflowmgrtest.cpp \
  ../src/process/snoopdelay.cpp \
  ../src/process/snoopudpchunk.cpp \
  ../src/process/snoopcommandwidget.cpp \
  ../src/process/snoopflowmgr.cpp \
  ../src/process/snoopflowchange.cpp \
  ../src/process/snoopdnschange.cpp \
  ../src/process/snoopdump.cpp \
  ../src/process/snoopwritewindivert.cpp \
  ../src/process/snoopdatachange.cpp \
  ../src/process/snoopcommand.cpp \
  ../src/process/snoopprocess.cpp \
  ../src/process/snooptcpblock.cpp \
  ../src/filter/snoopprocessfilter.cpp \
  ../src/filter/snoopfilter.cpp \
  ../src/filter/snoopprocessfilterwidget.cpp \
  ../src/filter/snoopbpfilter.cpp \
  ../src/filter/snoopfilterfactory.cpp \
  ../src/capture/snooppcap.cpp \
  ../src/capture/snoopwindivert.cpp \
  ../src/capture/snooparpspoof.cpp \
  ../src/capture/snoopcapturefactory.cpp \
  ../src/capture/snoopadapter.cpp \
  ../src/capture/snoopremote.cpp \
  ../src/capture/snoopsourcepcap.cpp \
  ../src/capture/snoopfile.cpp \
  ../src/capture/snoopcapture.cpp \
  ../src/capture/snoopvirtualnat.cpp \
  ../src/parse/snooptcpdata.cpp \
  ../src/parse/snoopudp.cpp \
  ../src/parse/snoopdns.cpp \
  ../src/parse/snoopeth.cpp \
  ../src/parse/snooparp.cpp \
  ../src/parse/snoopicmp.cpp \
  ../src/parse/snooptcp.cpp \
  ../src/parse/snoopip.cpp \
  ../src/parse/snoopudpdata.cpp \
  ../src/base/snoopautodetectadapter.cpp \
  ../src/base/snooptype.cpp \
  ../src/base/snoopfindhost.cpp \
  ../src/base/snooptypekey.cpp \
  ../src/base/snoopnetinfo.cpp \
  ../src/base/snoophostlist.cpp \
  ../src/base/snooprtm.cpp \
  ../src/base/snoopnetstat.cpp \
  ../src/base/snoopinterface.cpp \
  ../src/base/snooppacket.cpp \
	../src/base/snoopbase.cpp

HEADERS += \
  ../src/process/snoopdump.h \
  ../src/process/snoopchecksum.h \
  ../src/process/snoopprocess.h \
  ../src/process/snoopdatachange.h \
  ../src/process/snoopdnschange.h \
  ../src/process/snoopflowmgr.h \
  ../src/process/snoopudpsender.h \
  ../src/process/snoopudpchunk.h \
  ../src/process/snoopflowchange.h \
  ../src/process/snoopwriteadapter.h \
  ../src/process/snoopwritewindivert.h \
  ../src/process/snooptcpblock.h \
  ../src/process/snoopdatafind.h \
  ../src/process/snoopcommand.h \
  ../src/process/snoopdelay.h \
  ../src/process/snoopprocessfactory.h \
  ../src/process/snoopflowmgrtest.h \
  ../src/process/snoopblock.h \
  ../src/process/snoopudpreceiver.h \
  ../src/process/snoopcommandwidget.h \
  ../src/filter/snoopprocessfilterwidget.h \
  ../src/filter/snoopbpfilter.h \
  ../src/filter/snoopfilter.h \
  ../src/filter/snoopprocessfilter.h \
  ../src/filter/snoopfilterfactory.h \
  ../src/windivert/windivert.h \
  ../src/capture/snoopcapture.h \
  ../src/capture/snoopsourcepcap.h \
  ../src/capture/snooparpspoof.h \
  ../src/capture/snoopvirtualnat.h \
  ../src/capture/snoopremote.h \
  ../src/capture/snoopfile.h \
  ../src/capture/snoopcapturefactory.h \
  ../src/capture/snoopadapter.h \
  ../src/capture/snoopwindivert.h \
  ../src/capture/snooppcap.h \
  ../src/parse/snoopudp.h \
  ../src/parse/snooparp.h \
  ../src/parse/snooptcp.h \
  ../src/parse/snoopeth.h \
  ../src/parse/snoopdns.h \
  ../src/parse/snoopip.h \
  ../src/parse/snooptcpdata.h \
  ../src/parse/snoopudpdata.h \
  ../src/parse/snoopicmp.h \
  ../src/base/snoopinterface.h \
  ../src/base/snoopfindhost.h \
  ../src/base/snooptypekey.h \
  ../src/base/snooppacket.h \
  ../src/base/snoopautodetectadapter.h \
  ../src/base/snooprtm.h \
  ../src/base/snoop.h \
  ../src/base/snooptype.h \
  ../src/base/snoopnetinfo.h \
  ../src/base/snoopnetstat.h \
  ../src/base/snoophostlist.h \
  ../src/libnet/libnet-headers.h \
  ../src/libnet/libnet-structures.h \
  ../src/libnet/libnet-functions.h \
  ../src/libnet/libnet-types.h \
  ../src/libnet/config.h \
  ../src/libnet/libnet-asn1.h \
  ../src/libnet/libnet-macros.h \
  ../src/base/snoopbase.h

contains(QT, gui) {
FORMS += \
  ../src/process/snoopcommandwidget.ui \
  ../src/filter/snoopprocessfilterwidget.ui
}

