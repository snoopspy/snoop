#ifdef WIN32

#include <SnoopWinDivert>
#include <VDebugNew>

REGISTER_METACLASS(SnoopWinDivert, SnoopCapture)

// ----------------------------------------------------------------------------
// SnoopWinDivertLib
// ----------------------------------------------------------------------------
class SnoopWinDivertLib
{
protected:
  QLibrary* lib;

public:
  typedef HANDLE (*WinDivertOpenFunc)(
      __in        const char *filter,
      __in        DIVERT_LAYER layer,
      __in        int16_t priority,
      __in        UINT64 flags);
  WinDivertOpenFunc WinDivertOpen;

  typedef BOOL (*WinDivertCloseFunc)(
      __in        HANDLE handle);
  WinDivertCloseFunc WinDivertClose;

  typedef BOOL (*WinDivertSetParamFunc)(
      __in        HANDLE handle,
      __in        DIVERT_PARAM param,
      __in        UINT64 value);
  WinDivertSetParamFunc WinDivertSetParam;

  typedef BOOL (*WinDivertRecvFunc)(
      __in        HANDLE handle,
      __out       PVOID pPacket,
      __in        UINT packetLen,
      __out_opt   PDIVERT_ADDRESS pAddr,
      __out_opt   UINT *readLen);
  WinDivertRecvFunc WinDivertRecv;

  typedef BOOL (*WinDivertSendFunc)(
      __in        HANDLE handle,
      __in        PVOID pPacket,
      __in        UINT packetLen,
      __in        PDIVERT_ADDRESS pAddr,
      __out_opt   UINT *writeLen);
  WinDivertSendFunc WinDivertSend;

public:
  bool   ok;
  VError error;

private: // singleton
  SnoopWinDivertLib()
  {
    WinDivertOpen     = NULL;
    WinDivertClose    = NULL;
    WinDivertSetParam = NULL;
    WinDivertRecv     = NULL;
    WinDivertSend     = NULL;
    ok                = false;
    error.clear();

    SetLastError(ERROR_SUCCESS);
    lib = new QLibrary("WinDivert.dll");
    if (!lib->load())
    {
      DWORD lastError = GetLastError();
      QString errorMsg = "";
      switch (lastError)
      {
        case ERROR_INVALID_PARAMETER: errorMsg = "ERROR_INVALID_PARAMETER"; break;
        case ERROR_MOD_NOT_FOUND    : errorMsg = "ERROR_MOD_NOT_FOUND"; break;
      }
      QString msg = QString("load(\"WinDivert.dll\") return false error=%1(%2)").arg(errorMsg).arg(lastError);
      SET_ERROR(VWinDivertError, msg, (int)lastError);
      return;
    }

    if ((WinDivertOpen     = (WinDivertOpenFunc)    lib->resolve("WinDivertOpen"))     == NULL) LOG_FATAL("can not find WinDivertOpen");
    if ((WinDivertClose    = (WinDivertCloseFunc)   lib->resolve("WinDivertClose"))    == NULL) LOG_FATAL("can not find WinDivertClose");
    if ((WinDivertSetParam = (WinDivertSetParamFunc)lib->resolve("WinDivertSetParam")) == NULL) LOG_FATAL("can not find WinDivertSetParam");
    if ((WinDivertRecv     = (WinDivertRecvFunc)    lib->resolve("WinDivertRecv"))     == NULL) LOG_FATAL("can not find WinDivertRecv");
    if ((WinDivertSend     = (WinDivertSendFunc)    lib->resolve("WinDivertSend"))     == NULL) LOG_FATAL("can not find WinDivertSend");

    ok = true;
  }

  virtual ~SnoopWinDivertLib()
  {
    lib->unload();
    SAFE_DELETE(lib);
  }

public:
  static SnoopWinDivertLib& instance()
  {
    static SnoopWinDivertLib windivertLib;
    return windivertLib;
  }
};

// ----------------------------------------------------------------------------
// SnoopWinDivert
// ----------------------------------------------------------------------------
SnoopWinDivert::SnoopWinDivert(void* owner) : SnoopCapture(owner)
{
  filter          = "true";
  priority        = 0;
  layer           = WINDIVERT_LAYER_NETWORK;
  flags           = 0;
  queueLen        = 8192;
  queueTime       = 1024;
  tos             = 0;
  correctChecksum = true;

  handle    = 0;
}

SnoopWinDivert::~SnoopWinDivert()
{
  close();
}

#ifndef ERROR_INVALID_IMAGE_HASH
#define ERROR_INVALID_IMAGE_HASH 577
#endif // ERROR_INVALID_IMAGE_HASH
bool SnoopWinDivert::doOpen()
{
  if (!enabled)
  {
    LOG_DEBUG("enabled is false");
    return true;
  }
  
  SnoopWinDivertLib& lib = SnoopWinDivertLib::instance();
  if (!lib.ok)
  {
    error = lib.error;
    return false;
  }

  handle = lib.WinDivertOpen(qPrintable(filter), layer, priority, flags);
  if (handle == INVALID_HANDLE_VALUE)
  {
    DWORD lastError = GetLastError();

    QString msg;
    switch (lastError)
    {
      case ERROR_INVALID_PARAMETER:  msg = "ERROR_INVALID_PARAMETER";     break;
      case ERROR_FILE_NOT_FOUND:     msg = "ERROR_FILE_NOT_FOUND";        break;
      case ERROR_ACCESS_DENIED:      msg = "ERROR_ACCESS_DENIED";         break;
      case ERROR_INVALID_IMAGE_HASH: msg = "ERROR_INVALID_IMAGE_HASH";    break;
      default:                       msg = QString("unknown error %1").arg(lastError); break;
    }
    SET_ERROR(VWinDivertError, QString("error in WinDivertOpen %1").arg(msg), lastError);
    return false;
  }

  if (!lib.WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_LEN, queueLen))
  {
    DWORD lastError = GetLastError();
    SET_ERROR(VWinDivertError, "error in DivertSetParam(DIVERT_PARAM_QUEUE_LEN)" , lastError);
    return false;
  }
  if (!lib.WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_TIME, queueTime))
  {
    DWORD lastError = GetLastError();
    SET_ERROR(VWinDivertError, "error in DivertSetParam(DIVERT_PARAM_QUEUE_TIME)" , lastError);
    return false;
  }

  if (!SnoopCapture::doOpen()) return false;

  return true;
}

bool SnoopWinDivert::doClose()
{
  if (!enabled)
  {
    LOG_DEBUG("enabled is false");
    return true;
  }
  
  SnoopWinDivertLib& lib = SnoopWinDivertLib::instance();
  if (!lib.ok)
  {
    error = lib.error;
    return false;
  }

  if (!lib.WinDivertClose(handle))
  {
    DWORD lastError = GetLastError();
    LOG_ERROR("WinDivertClose return FALSE last error=%lu(0x%lx)", lastError, lastError);
  }
  handle = 0;

  bool res = SnoopCapture::doClose();
  return res;
}

#ifdef WIN32
int gettimeofday(struct timeval* tv, struct timezone* tz)
{
  Q_UNUSED(tz)

  static LONGLONG birthunixhnsec = 116444736000000000;  /*in units of 100 ns */

  FILETIME systemtime;
  GetSystemTimeAsFileTime(&systemtime);

  ULARGE_INTEGER utime;
  utime.LowPart  = systemtime.dwLowDateTime;
  utime.HighPart = systemtime.dwHighDateTime;

  ULARGE_INTEGER birthunix;
  birthunix.LowPart  = (DWORD)birthunixhnsec;
  birthunix.HighPart = birthunixhnsec >> 32;

  LONGLONG usecs;
  usecs = (LONGLONG)((utime.QuadPart - birthunix.QuadPart) / 10);

  tv->tv_sec  = (long)(usecs / 1000000);
  tv->tv_usec = (long)(usecs % 1000000);

  return 0;
}
#endif // WIN32

int SnoopWinDivert::read(SnoopPacket* packet)
{
  SnoopWinDivertLib& lib = SnoopWinDivertLib::instance();
  if (!lib.ok)
  {
    error = lib.error;
    return VError::FAIL;
  }

  packet->clear();
  UINT readLen;
  BOOL res = lib.WinDivertRecv(handle, this->pktData + sizeof(ETH_HDR), MAXBUF - sizeof(ETH_HDR), &packet->divertAddr, &readLen);
  if (!res)
  {
    DWORD lastError = GetLastError();
    SET_DEBUG_ERROR(VWinDivertError, QString("WinDivertRecv return FALSE last error=%1(0x%2)").arg(lastError).arg(lastError, 0, 16), lastError);
    return VError::FAIL;
  }
  readLen += sizeof(ETH_HDR);

  // LOG_DEBUG("ifIdx=%u subIfIdx=%u Direction=%u readLen=%u", packet->divertAddr.IfIdx, packet->divertAddr.SubIfIdx, packet->divertAddr.Direction, readLen); // gilgil temp 2013.12.05

  this->pktHdr.caplen = readLen;
  this->pktHdr.len    = readLen;
  gettimeofday(&this->pktHdr.ts, NULL);

  packet->pktHdr   = &this->pktHdr;
  packet->pktData  = this->pktData;
  packet->linkType = dataLink();

  packet->ethHdr              = (ETH_HDR*)pktData;
  packet->ethHdr->ether_dhost = Mac::cleanMac();
  packet->ethHdr->ether_shost = Mac::cleanMac();
  packet->ethHdr->ether_type  = htons(ETHERTYPE_IP);

  bool parsed = false;
  if (tos != 0)
  {
    parse(packet);
    parsed = true;
    if (packet->ipHdr != NULL) packet->ipHdr->ip_tos = tos;
  }

  if (correctChecksum)
  {
    if (!parsed)
    {
      parse(packet);
      parsed = true;
    }
    if (packet->ipHdr != NULL)
    {
      if (packet->tcpHdr != NULL)
      {
        packet->tcpHdr->th_sum = htons(SnoopTcp::checksum(packet->ipHdr, packet->tcpHdr));
      } else
      if (packet->udpHdr != NULL)
      {
        packet->udpHdr->uh_sum = htons(SnoopUdp::checksum(packet->ipHdr, packet->udpHdr));
      }
      packet->ipHdr->ip_sum = htons(SnoopIp::checksum(packet->ipHdr));
    }
  }

  if (autoParse)
  {
    if (!parsed)
    {
      parse(packet);
    }
  }

  return (int)readLen;
}

int SnoopWinDivert::write(SnoopPacket* packet)
{
  return write(packet->pktData, packet->pktHdr->caplen, &packet->divertAddr);
}

int SnoopWinDivert::write(u_char* buf, int size, WINDIVERT_ADDRESS* divertAddr)
{
  LOG_ASSERT(divertAddr != NULL);
  SnoopWinDivertLib& lib = SnoopWinDivertLib::instance();
  if (!lib.ok)
  {
    error = lib.error;
    return false;
  }

  UINT writeLen;
  BOOL res = lib.WinDivertSend(handle, buf + sizeof(ETH_HDR), (UINT)size - sizeof(ETH_HDR), divertAddr, &writeLen);
  if (!res)
  {
    DWORD lastError = GetLastError();
    SET_DEBUG_ERROR(VWinDivertError, QString("WinDivertSend return FALSE last error=%1(0x%2)").arg(lastError).arg(lastError, 0, 16), lastError);
    return VError::FAIL;
  }
  return (int)writeLen;
}

SnoopCaptureType SnoopWinDivert::captureType()
{
  if (flags & DIVERT_FLAG_SNIFF) return SnoopCaptureType::OutOfPath;
  return SnoopCaptureType::InPath;
}

bool SnoopWinDivert::relay(SnoopPacket* packet)
{
  return write(packet) != VError::FAIL;
}

void SnoopWinDivert::load(VRep& rep)
{
  SnoopCapture::load(xml);

  filter          = rep.getStr("filter", filter);
  priority        = (uint16_t)rep.getInt("priority", (int)priority);
  layer           = (DIVERT_LAYER)rep.getInt("layer", (int)layer);
  flags           = (UINT64)rep.getInt("flags", (int)flags);
  queueLen        = (UINT64)rep.getInt("queueLen", (int)queueLen);
  queueTime       = (UINT64)rep.getInt("queueTime", (int)queueTime);
  tos             = (uint8_t) rep.getInt("tos", (int)tos);
  correctChecksum = rep.getBool("correctChecksum", correctChecksum);
}

void SnoopWinDivert::save(VRep& rep)
{
  SnoopCapture::save(xml);

  rep.setStr("filter", filter);
  rep.setInt("priority", (int)priority);
  rep.setInt("layer", (int)layer);
  rep.setInt("flags", (int)flags);
  rep.setInt("queueLen", (int)queueLen);
  rep.setInt("queueTime", (int)queueTime);
  rep.setInt("tos", (int)tos);
  rep.setBool("correctChecksum", correctChecksum);
}

#ifdef QT_GUI_LIB
void SnoopWinDivert::optionAddWidget(QLayout* layout)
{
  SnoopCapture::optionAddWidget(layout);

  VOptionable::addLineEdit(layout, "leFilter",           "Filter",                filter);
  VOptionable::addLineEdit(layout, "lePriority",         "Priority",              QString::number(priority));
  VOptionable::addLineEdit(layout, "leLayer",            "Layer",                 QString::number(layer));
  VOptionable::addCheckBox(layout, "chkFlagSniff",       "Flag Sniff(OutOfPath)", flags & WINDIVERT_FLAG_SNIFF);
  VOptionable::addCheckBox(layout, "chkFlagDrop",        "Flag Drop",             flags & WINDIVERT_FLAG_DROP);
  VOptionable::addCheckBox(layout, "chkFlagNoChecksum",  "Flag No Checksum",      flags & WINDIVERT_FLAG_NO_CHECKSUM);
  VOptionable::addLineEdit(layout, "leQueueLen",         "Queue Len",             QString::number(queueLen));
  VOptionable::addLineEdit(layout, "leQueueTime",        "Queue Time",            QString::number(queueTime));
  VOptionable::addLineEdit(layout, "leTos",              "Tos",                   QString::number(tos));
  VOptionable::addCheckBox(layout, "chkCorrectChecksum", "Correct Checksum",      correctChecksum);
}

void SnoopWinDivert::optionSaveDlg(QDialog* dialog)
{
  SnoopCapture::optionSaveDlg(dialog);

  filter    = dialog->findChild<QLineEdit*>("leFilter")->text();
  priority  = dialog->findChild<QLineEdit*>("lePriority")->text().toUShort();
  layer     = (DIVERT_LAYER) dialog->findChild<QLineEdit*>("leLayer")->text().toInt();

  flags     = 0;
  if (dialog->findChild<QCheckBox*>("chkFlagSniff")->checkState()      == Qt::Checked) flags |= WINDIVERT_FLAG_SNIFF;
  if (dialog->findChild<QCheckBox*>("chkFlagDrop")->checkState()       == Qt::Checked) flags |= WINDIVERT_FLAG_DROP;
  if (dialog->findChild<QCheckBox*>("chkFlagNoChecksum")->checkState() == Qt::Checked) flags |= WINDIVERT_FLAG_NO_CHECKSUM;
  queueLen  = dialog->findChild<QLineEdit*>("leQueueLen")->text().toULongLong();
  queueTime = dialog->findChild<QLineEdit*>("leQueueTime")->text().toULongLong();
  tos       = dialog->findChild<QLineEdit*>("leQueueTime")->text().toUInt();
  correctChecksum = dialog->findChild<QCheckBox*>("chkCorrectChecksum")->checkState() == Qt::Checked;
}

#endif // WIN32

#endif // QT_GUI_LIB
