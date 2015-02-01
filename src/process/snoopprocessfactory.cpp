#include <SnoopProcessFactory>

#include <SnoopBlock>
#include <SnoopChecksum>
#include <SnoopCommand>
#include <SnoopDataChange>
#include <SnoopDataFind>
#include <SnoopDelay>
#include <SnoopDnsChange>
#include <SnoopFlowChange>
#include <SnoopFlowMgr>
#include <SnoopFlowMgrTest>
#include <SnoopDump>
#include <SnoopTcpBlock>
#include <SnoopUdpReceiver>
#include <SnoopUdpSender>
#include <SnoopWriteAdapter>
#include <SnoopWriteWinDivert>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopProcessFactory
// ----------------------------------------------------------------------------
void SnoopProcessFactory::explicitLink()
{
  VFactory& factory = VFactory::instance();
  static const QString categoryName = "SnoopProcess";

  SnoopBlock          block;          factory.registerMetaObjectByCategoryName(block.metaObject(),          categoryName);
  SnoopChecksum       checksum;       factory.registerMetaObjectByCategoryName(checksum.metaObject(),       categoryName);
  SnoopCommand        command;        factory.registerMetaObjectByCategoryName(command.metaObject(),        categoryName);
  SnoopDataChange     dataChange;     factory.registerMetaObjectByCategoryName(dataChange.metaObject(),     categoryName);
  SnoopDataFind       dataFind;       factory.registerMetaObjectByCategoryName(dataFind.metaObject(),       categoryName);
  SnoopDelay          delay;          factory.registerMetaObjectByCategoryName(delay.metaObject(),          categoryName);
  SnoopDnsChange      dnsChange;      factory.registerMetaObjectByCategoryName(dnsChange.metaObject(),      categoryName);
  SnoopDump           dump;           factory.registerMetaObjectByCategoryName(dump.metaObject(),           categoryName);
  SnoopFlowChange     flowChange;     factory.registerMetaObjectByCategoryName(flowChange.metaObject(),     categoryName);
  SnoopFlowMgr        flowMgr;        factory.registerMetaObjectByCategoryName(flowMgr.metaObject(),        categoryName);
  SnoopFlowMgrTest    flowMgrTest;    factory.registerMetaObjectByCategoryName(flowMgrTest.metaObject(),    categoryName);
  SnoopTcpBlock       tcpBlock;       factory.registerMetaObjectByCategoryName(tcpBlock.metaObject(),       categoryName);
  SnoopUdpReceiver    udpReceiver;    factory.registerMetaObjectByCategoryName(udpReceiver.metaObject(),    categoryName);
  SnoopUdpSender      udpSender;      factory.registerMetaObjectByCategoryName(udpSender.metaObject(),      categoryName);
  SnoopWriteAdapter   writeAdapter;   factory.registerMetaObjectByCategoryName(writeAdapter.metaObject(),   categoryName);
#ifdef WIN32
  SnoopWriteWinDivert writeWinDivert; factory.registerMetaObjectByCategoryName(writeWinDivert.metaObject(), categoryName);
#endif // WIN32
}

SnoopProcess* SnoopProcessFactory::createDefaultProcess()
{
  // ----- gilgil temp 2012.06.08 -----
  // return new SnoopProcessLog;
  // ----------------------------------
  return NULL;
}
