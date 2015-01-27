#include <SnoopCaptureFactory>

// #include <VXmlDoc> // gilgil temp 2015.01.27
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
  SnoopAdapter     adapter;
  SnoopArpSpoof    arpSpoof;
  SnoopFile        file;
  SnoopSourcePcap  pcap;
#ifdef WIN32
  SnoopRemote      remote;
#endif // WIN32
  SnoopVirtualNat  virtualNAT;
#ifdef WIN32
  SnoopWinDivert   winDivert;
#endif // WIN32
}

SnoopCapture* SnoopCaptureFactory::createDefaultCapture()
{
  SnoopAdapter* adapter = new SnoopAdapter;
  return adapter;
}
