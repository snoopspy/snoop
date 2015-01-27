// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_WIN_DIVERT_H__
#define __SNOOP_WIN_DIVERT_H__

#ifdef WIN32

#include <QLibrary>
#include <SnoopCapture>
#include <SnoopIp>
#include <SnoopTcp>
#include <SnoopUdp>
#include <windivert/windivert.h>

// ----------------------------------------------------------------------------
// SnoopWinDivert
// ----------------------------------------------------------------------------
class SnoopWinDivert : public SnoopCapture
{
public:
  SnoopWinDivert(void* owner = NULL);
  virtual ~SnoopWinDivert();

protected:
  virtual bool doOpen();
  virtual bool doClose();

public:
  virtual int read(SnoopPacket* packet);
  virtual int write(SnoopPacket* packet);
  virtual int write(u_char* buf, int size, WINDIVERT_ADDRESS* divertAddr = NULL);

public:
  virtual SnoopCaptureType captureType();
  virtual int              dataLink()    { return DLT_EN10MB; } // gilgil temp 2013.11.29
  virtual bool             relay(SnoopPacket* packet);

public:
  QString      filter;
  uint16_t       priority;
  DIVERT_LAYER layer;
  UINT64       flags;
  UINT64       queueLen;
  UINT64       queueTime;
  uint8_t        tos;
  bool         correctChecksum;

public:
  HANDLE       handle;

protected:
  static const int MAXBUF = 0xFFFF;
  u_char         pktData[MAXBUF];
  PKT_HDR        pktHdr;

public:
  virtual void load(VRep& rep);
  virtual void save(VRep& rep);

#ifdef QT_GUI_LIB
public: // for VOptionable
  virtual void optionAddWidget(QLayout* layout);
  virtual void optionSaveDlg(QDialog* dialog);
#endif // QT_GUI_LIB
};

// ----------------------------------------------------------------------------
// VWinDivertError
// ----------------------------------------------------------------------------
class VWinDivertError : public VError {};

#endif // WIN32

#endif // __SNOOP_WIN_DIVERT_H__
