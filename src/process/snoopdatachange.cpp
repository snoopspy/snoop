#include <SnoopDataChange>
#include <SnoopIp>
#include <SnoopTcp>
#include <SnoopUdp>

// REGISTER_METACLASS(SnoopDataChange, SnoopProcess) // gilgil temp 2015.02.01

// ----------------------------------------------------------------------------
// SnoopDataChange
// ----------------------------------------------------------------------------
SnoopDataChange::SnoopDataChange(void* owner) : SnoopProcess(owner)
{
  flowMgr   = NULL;
  tcpChange = true;
  udpChange = true;
  dataChange.clear();

  tcpFlowOffset = 0;
}

SnoopDataChange::~SnoopDataChange()
{
  close();
}

bool SnoopDataChange::doOpen()
{
  if (tcpChange && flowMgr == NULL)
  {
    SET_ERROR(SnoopError, "flowMgr is null", VError::OBJECT_IS_NULL);
    return false;
  }

  if (!dataChange.prepare(error)) return false;

  if (tcpChange)
  {
    // ----- by gilgil 2014.03.13 -----
    // All SnoopDataChange objects should share SnoopDataChangeFlowItem contents.
    // So id parameter value set into the same value.
    // tcpFlowOffset = flowMgr->requestMemory_TcpFlow(this, sizeof(SnoopDataChangeFlowItem));
    tcpFlowOffset = flowMgr->requestMemory_TcpFlow((void*)"SnoopDataChange", sizeof(SnoopDataChangeFlowItem)); // gilgil temp 2014.03.13
    // --------------------------------

    flowMgr->connect(SIGNAL(__tcpFlowCreated(SnoopTcpFlowKey*,SnoopFlowValue*)), this, SLOT(__tcpFlowCreate(SnoopTcpFlowKey*,SnoopFlowValue*)), Qt::DirectConnection);
    flowMgr->connect(SIGNAL(__tcpFlowDeleted(SnoopTcpFlowKey*,SnoopFlowValue*)), this, SLOT(__tcpFlowDelete(SnoopTcpFlowKey*,SnoopFlowValue*)), Qt::DirectConnection);
  }

  return SnoopProcess::doOpen();
}

bool SnoopDataChange::doClose()
{
  if (tcpChange && flowMgr == NULL)
  {
    SET_ERROR(SnoopError, "flowMgr is null", VError::OBJECT_IS_NULL);
    return true;
  }

  if (tcpChange)
  {
    flowMgr->disconnect(SIGNAL(__tcpFlowCreated(SnoopTcpFlowKey*,SnoopFlowValue*)), this, SLOT(__tcpFlowCreate(SnoopTcpFlowKey*,SnoopFlowValue*)));
    flowMgr->disconnect(SIGNAL(__tcpFlowDeleted(SnoopTcpFlowKey*,SnoopFlowValue*)), this, SLOT(__tcpFlowDelete(SnoopTcpFlowKey*,SnoopFlowValue*)));
  }

  return SnoopProcess::doClose();
}

void SnoopDataChange::change(SnoopPacket* packet)
{
  if (packet->ipHdr == NULL)
  {
    emit unchanged(packet);
    return;
  }

  bool _changed = false;
  if (packet->tcpHdr != NULL)
  {
    if (tcpChange)
    {
      //
      // check modified seq and ack
      //
      SnoopDataChangeFlowItem* flowItem = (SnoopDataChangeFlowItem*)(packet->flowValue->totalMem + tcpFlowOffset);
      //LOG_DEBUG("flowItem=%p seqDiff=%d ackDiff=%d", flowItem, flowItem->seqDiff, flowItem->ackDiff); // gilgil temp 2014.03.13

      if (flowItem->seqDiff != 0)
      {
        uint32_t oldSeq = ntohl(packet->tcpHdr->th_seq);
        uint32_t newSeq = oldSeq + flowItem->seqDiff;
        packet->tcpHdr->th_seq = htonl(newSeq);
        packet->tcpHdr->th_sum = htons(SnoopIp::recalculateChecksum(ntohs(packet->tcpHdr->th_sum), oldSeq, newSeq));
      }

      if (flowItem->ackDiff != 0)
      {
        uint32_t oldAck = ntohl(packet->tcpHdr->th_ack);
        uint32_t newAck = oldAck + flowItem->ackDiff;
        packet->tcpHdr->th_ack = htonl(newAck);
        packet->tcpHdr->th_sum = htons(SnoopIp::recalculateChecksum(ntohs(packet->tcpHdr->th_sum), oldAck, newAck));
      }

      //
      // check data change
      //
      int16_t diff = 0;
      _changed = _change(packet, &diff);
      if (_changed)
      {
        if (diff != 0)
        {
          flowItem->seqDiff += diff;

          //
          // change other flow ack value
          //
          SnoopTcpFlowKey* flowKey = (SnoopTcpFlowKey*)packet->flowKey;
          SnoopTcpFlowKey rflowKey = flowKey->reverse();
          Snoop_TcpFlow_Map::iterator it = flowMgr->tcpFlow_Map.find(rflowKey);
          if (it != flowMgr->tcpFlow_Map.end())
          {
            SnoopFlowValue rvalue = it.value();
            SnoopDataChangeFlowItem* rflowItem = (SnoopDataChangeFlowItem*)(rvalue.totalMem + tcpFlowOffset);
            rflowItem->ackDiff -= diff;
            // LOG_DEBUG("rflowItem=%p seqDiff=%d ackDiff=%d", rflowItem, rflowItem->seqDiff, rflowItem->ackDiff); // gilgil temp 2014.03.13
          }
        }
        packet->tcpHdr->th_sum = htons(SnoopTcp::checksum(packet->ipHdr, packet->tcpHdr));
      }
    }
  } else
  if (packet->udpHdr != NULL)
  {
    if (udpChange)
    {
      //
      // check data change
      //
      int16_t diff = 0;
      _changed = _change(packet, &diff);
      if (_changed)
      {
        if (diff != 0)
        {
          uint16_t oldLen = ntohs(packet->udpHdr->uh_ulen);
          uint16_t newLen = oldLen + diff;
          packet->udpHdr->uh_ulen = htons(newLen);
        }
        packet->udpHdr->uh_sum = htons(SnoopUdp::checksum(packet->ipHdr, packet->udpHdr));
      }
    }
  }

  if (_changed)
  {
    emit changed(packet);
  } else
  {
    emit unchanged(packet);
  }
}

bool SnoopDataChange::_change(SnoopPacket* packet, int16_t* diff)
{
  uint8_t* data = packet->data;
  int   len  = packet->dataLen;
  if (data == NULL || len == 0) return false;

  bool _changed = false;

  QByteArray ba((const char*)data, (uint)len);
  if (dataChange.change(ba))
  {
    _changed   = true;
    int newLen = (uint16_t)ba.size();
    memcpy(data, ba.constData(), (size_t)ba.size());

    if (newLen != len)
    {
      int16_t  diff16   = newLen- len;
      uint16_t oldLen16 = ntohs(packet->ipHdr->ip_len);
      uint16_t newLen16 = oldLen16 + (uint16_t)diff16;

      packet->pktHdr->caplen += (uint32_t)diff16;
      if (packet->pktHdr->caplen > 1514)
      {
        LOG_WARN("packet->pktHdr->caplen is %u", packet->pktHdr->caplen);
      }
      packet->ipHdr->ip_len   = htons(newLen16);
      packet->ipHdr->ip_sum   = htons(SnoopIp::recalculateChecksum(ntohs(packet->ipHdr->ip_sum), oldLen16, newLen16));

      *diff = diff16;
    }
  }
  return _changed;
}

void SnoopDataChange::__tcpFlowCreate(SnoopTcpFlowKey* key, SnoopFlowValue* value)
{
  SnoopDataChangeFlowItem* flowItem = (SnoopDataChangeFlowItem*)(value->totalMem + tcpFlowOffset);
  flowItem->seqDiff = 0;
  flowItem->ackDiff = 0;
  // LOG_DEBUG("flowItem=%p seqDiff=%d", flowItem, flowItem->seqDiff); // gilgil temp 2014.03.13
  SnoopTcpFlowKey rkey = key->reverse();
  Snoop_TcpFlow_Map::iterator it = flowMgr->tcpFlow_Map.find(rkey);
  if (it != flowMgr->tcpFlow_Map.end())
  {
    SnoopFlowValue& rvalue = it.value();
    SnoopDataChangeFlowItem* rflowItem = (SnoopDataChangeFlowItem*)(rvalue.totalMem + tcpFlowOffset);
    flowItem->ackDiff = -rflowItem->seqDiff;
  }
}

void SnoopDataChange::__tcpFlowDelete(SnoopTcpFlowKey* key, SnoopFlowValue* value)
{
  Q_UNUSED(key)
  Q_UNUSED(value)
  // LOG_DEBUG(""); // gilgil temp 2014.03.13
}

void SnoopDataChange::load(VXml xml)
{
  SnoopProcess::load(xml);

  QString flowMgrName = xml.getStr("flowMgr", "");
  if (flowMgrName != "") flowMgr = (SnoopFlowMgr*)(((VGraph*)owner)->objectList.findObjectByName(flowMgrName));
  tcpChange = xml.getBool("tcpChange", tcpChange);
  udpChange = xml.getBool("udpChange", udpChange);
  dataChange.load(xml.gotoChild("dataChange"));
}

void SnoopDataChange::save(VXml xml)
{
  SnoopProcess::save(xml);

  QString flowMgrName = flowMgr == NULL ? "" : flowMgr->objectName();
  xml.setStr("flowMgr", flowMgrName);
  xml.setBool("tcpChange", tcpChange);
  xml.setBool("udpChange", udpChange);
  dataChange.save(xml.gotoChild("dataChange"));
}

#ifdef QT_GUI_LIB
void SnoopDataChange::optionAddWidget(QLayout* layout)
{
  SnoopProcess::optionAddWidget(layout);

  QStringList flowMgrList = ((VGraph*)owner)->objectList.findObjectNamesByClassName("SnoopFlowMgr");
  VOptionable::addComboBox(layout, "cbxFlowMgr", "FlowMgr", flowMgrList, -1, flowMgr == NULL ? "" : flowMgr->objectName());
  VOptionable::addCheckBox(layout, "chkTcpChange", "TCP Change", tcpChange);
  VOptionable::addCheckBox(layout, "chkUdpChange", "UDP Change", udpChange);
  dataChange.optionAddWidget(layout);
}

void SnoopDataChange::optionSaveDlg(QDialog* dialog)
{
  SnoopProcess::optionSaveDlg(dialog);

  flowMgr = (SnoopFlowMgr*)(((VGraph*)owner)->objectList.findObjectByName(dialog->findChild<QComboBox*>("cbxFlowMgr")->currentText()));
  tcpChange = dialog->findChild<QCheckBox*>("chkTcpChange")->checkState() == Qt::Checked;
  udpChange = dialog->findChild<QCheckBox*>("chkUdpChange")->checkState() == Qt::Checked;
  dataChange.optionSaveDlg(dialog);
}
#endif // QT_GUI_LIB
