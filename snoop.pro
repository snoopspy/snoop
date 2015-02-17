CONFIG += SNOOP_LIB_BUILD
include (snoop.pri)

TARGET   = $${SNOOP_LIB_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}/lib

SOURCES += \
  src/base/snoopautodetectadapter.cpp \
  src/base/snoopbase.cpp \
  src/base/snoopfindhost.cpp \
  src/base/snoophostlist.cpp \
  src/base/snoopinterface.cpp \
  src/base/snoopnetinfo.cpp \
  src/base/snoopnetstat.cpp \
  src/base/snooppacket.cpp \
  src/base/snooprtm.cpp \
  src/base/snooptype.cpp \
  src/base/snooptypekey.cpp \
  src/capture/snoopadapter.cpp \
  src/capture/snooparpspoof.cpp \
  src/capture/snoopcapture.cpp \
  src/capture/snoopcapturefactory.cpp \
  src/capture/snoopfile.cpp \
  src/capture/snooppcap.cpp \
  src/capture/snoopremote.cpp \
  src/capture/snoopsourcepcap.cpp \
  src/capture/snoopvirtualnat.cpp \
  src/capture/snoopwindivert.cpp \
  src/filter/snoopbpfilter.cpp \
  src/filter/snoopfilter.cpp \
  src/filter/snoopfilterfactory.cpp \
  src/filter/snoopprocessfilter.cpp \
  src/filter/snoopprocessfilterwidget.cpp \
  src/parse/snooparp.cpp \
  src/parse/snoopdns.cpp \
  src/parse/snoopeth.cpp \
  src/parse/snoopicmp.cpp \
  src/parse/snoopip.cpp \
  src/parse/snooptcp.cpp \
  src/parse/snooptcpdata.cpp \
  src/parse/snoopudp.cpp \
  src/parse/snoopudpdata.cpp \
  src/process/snoopblock.cpp \
  src/process/snoopchecksum.cpp \
  src/process/snoopcommand.cpp \
  src/process/snoopcommandwidget.cpp \
  src/process/snoopdatachange.cpp \
  src/process/snoopdatafind.cpp \
  src/process/snoopdelay.cpp \
  src/process/snoopdnschange.cpp \
  src/process/snoopdump.cpp \
  src/process/snoopflowchange.cpp \
  src/process/snoopflowmgr.cpp \
  src/process/snoopflowmgrtest.cpp \
  src/process/snoopprocess.cpp \
  src/process/snoopprocessfactory.cpp \
  src/process/snooptcpblock.cpp \
  src/process/snoopudpchunk.cpp \
  src/process/snoopudpreceiver.cpp \
  src/process/snoopudpsender.cpp \
  src/process/snoopwriteadapter.cpp \
  src/process/snoopwritewindivert.cpp \

HEADERS += \
  src/base/snoop.h \
  src/base/snoopautodetectadapter.h \
  src/base/snoopbase.h \
  src/base/snoopfindhost.h \
  src/base/snoophostlist.h \
  src/base/snoopinterface.h \
  src/base/snoopnetinfo.h \
  src/base/snoopnetstat.h \
  src/base/snooppacket.h \
  src/base/snooprtm.h \
  src/base/snooptype.h \
  src/base/snooptypekey.h \
  src/capture/snoopadapter.h \
  src/capture/snooparpspoof.h \
  src/capture/snoopcapture.h \
  src/capture/snoopcapturefactory.h \
  src/capture/snoopfile.h \
  src/capture/snooppcap.h \
  src/capture/snoopremote.h \
  src/capture/snoopsourcepcap.h \
  src/capture/snoopvirtualnat.h \
  src/capture/snoopwindivert.h \
  src/filter/snoopbpfilter.h \
  src/filter/snoopfilter.h \
  src/filter/snoopfilterfactory.h \
  src/filter/snoopprocessfilter.h \
  src/filter/snoopprocessfilterwidget.h \
  src/libnet/config.h \
  src/libnet/libnet-asn1.h \
  src/libnet/libnet-functions.h \
  src/libnet/libnet-headers.h \
  src/libnet/libnet-macros.h \
  src/libnet/libnet-structures.h \
  src/libnet/libnet-types.h \
  src/parse/snooparp.h \
  src/parse/snoopdns.h \
  src/parse/snoopeth.h \
  src/parse/snoopicmp.h \
  src/parse/snoopip.h \
  src/parse/snooptcp.h \
  src/parse/snooptcpdata.h \
  src/parse/snoopudp.h \
  src/parse/snoopudpdata.h \
  src/process/snoopblock.h \
  src/process/snoopchecksum.h \
  src/process/snoopcommand.h \
  src/process/snoopcommandwidget.h \
  src/process/snoopdatachange.h \
  src/process/snoopdatafind.h \
  src/process/snoopdelay.h \
  src/process/snoopdnschange.h \
  src/process/snoopdump.h \
  src/process/snoopflowchange.h \
  src/process/snoopflowmgr.h \
  src/process/snoopflowmgrtest.h \
  src/process/snoopprocess.h \
  src/process/snoopprocessfactory.h \
  src/process/snooptcpblock.h \
  src/process/snoopudpchunk.h \
  src/process/snoopudpreceiver.h \
  src/process/snoopudpsender.h \
  src/process/snoopwriteadapter.h \
  src/process/snoopwritewindivert.h \
  src/windivert/windivert.h

contains(QT, gui) {
FORMS += \
  src/process/snoopcommandwidget.ui \
  src/filter/snoopprocessfilterwidget.ui
}

