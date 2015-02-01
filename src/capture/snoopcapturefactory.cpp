#include <SnoopCaptureFactory>

#include <VXmlDoc>
#include <SnoopAdapter>
#include <SnoopArpSpoof>
#include <SnoopFile>
#include <SnoopSourcePcap>
#include <SnoopRemote>
#include <SnoopVirtualNat>
#include <SnoopWinDivert>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopCaptureFactory
// ----------------------------------------------------------------------------
void SnoopCaptureFactory::explicitLink()
{
  VFactory& factory = VFactory::instance();
  static const QString categoryName = "SnoopCapture";

  SnoopAdapter     adapter;    factory.registerMetaObjectByCategoryName(adapter.metaObject(),    categoryName);
  SnoopArpSpoof    arpSpoof;   factory.registerMetaObjectByCategoryName(arpSpoof.metaObject(),   categoryName);
  SnoopFile        file;       factory.registerMetaObjectByCategoryName(file.metaObject(),       categoryName);
  SnoopSourcePcap  pcap;       factory.registerMetaObjectByCategoryName(pcap.metaObject(),       categoryName);
#ifdef WIN32
  SnoopRemote      remote;     factory.registerMetaObjectByCategoryName(remote.metaObject(),     categoryName);
#endif // WIN32
  SnoopVirtualNat  virtualNAT; factory.registerMetaObjectByCategoryName(virtualNAT.metaObject(), categoryName);
#ifdef WIN32
  SnoopWinDivert   winDivert;  factory.registerMetaObjectByCategoryName(winDivert.metaObject(),  categoryName);
#endif // WIN32
}

SnoopCapture* SnoopCaptureFactory::createDefaultCapture()
{
  SnoopAdapter* adapter = new SnoopAdapter;
  return adapter;
}
