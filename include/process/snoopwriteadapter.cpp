#include <SnoopWriteAdapter>

REGISTER_METACLASS(SnoopWriteAdapter, SnoopProcess)

// ----------------------------------------------------------------------------
// SnoopWriteAdapter
// ----------------------------------------------------------------------------
SnoopWriteAdapter::SnoopWriteAdapter(void* owner) : SnoopAdapter(owner)
{
  adapterIndex = SnoopBase::INVALID_ADAPTER_INDEX;
  autoRead     = false;
  autoParse    = false;
  srcMac       = Mac::cleanMac();
  dstMac       = Mac::cleanMac();
}

SnoopWriteAdapter::~SnoopWriteAdapter()
{
  close();
}

void SnoopWriteAdapter::copy(SnoopPacket* packet)
{
  if (!enabled) return;
  LOG_ASSERT(packet->ethHdr != NULL);
  if (!srcMac.isClean()) packet->ethHdr->ether_shost = srcMac;
  if (!dstMac.isClean()) packet->ethHdr->ether_dhost = dstMac;
  SnoopAdapter::write(packet);
  emit copied(packet);
}

void SnoopWriteAdapter::move(SnoopPacket* packet)
{
  if (!enabled) return;
  LOG_ASSERT(packet->ethHdr != NULL);
  if (!srcMac.isClean()) packet->ethHdr->ether_shost = srcMac;
  if (!dstMac.isClean()) packet->ethHdr->ether_dhost = dstMac;
  SnoopAdapter::write(packet);
  packet->drop = true;
  emit moved(packet);
}

void SnoopWriteAdapter::load(VRep& rep)
{
  SnoopAdapter::load(xml);

  srcMac = rep.getStr("srcMac", srcMac.str());
  dstMac = rep.getStr("dstMac", dstMac.str());
}

void SnoopWriteAdapter::save(VRep& rep)
{
  SnoopAdapter::save(xml);

  rep.setStr("srcMac", srcMac.str());
  rep.setStr("dstMac", dstMac.str());
}

#ifdef QT_GUI_LIB
void SnoopWriteAdapter::optionAddWidget(QLayout* layout)
{
  SnoopAdapter::optionAddWidget(layout);

  VOptionable::addLineEdit(layout, "leSrcMac", "Src Mac", srcMac.str());
  VOptionable::addLineEdit(layout, "leDstMac", "Dst Mac", dstMac.str());
}

void SnoopWriteAdapter::optionSaveDlg(QDialog* dialog)
{
  SnoopAdapter::optionSaveDlg(dialog);

  srcMac = dialog->findChild<QLineEdit*>("leSrcMac")->text();
  dstMac = dialog->findChild<QLineEdit*>("leDstMac")->text();
}
#endif // QT_GUI_LIB
