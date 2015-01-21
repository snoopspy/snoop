// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.01
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_BASE_H__
#define __SNOOP_BASE_H__

#include <VBase>
#include <VNet>
#include <VError>
#include <VLog>
#include <VXml>

#ifdef WIN32
  #define  WPCAP
  #define  HAVE_REMOTE
  #include <Iphlpapi.h>
  #include <pcap.h>
#endif // WIN32
#ifdef linux
  #include <pcap.h>
#endif // linux

// ----------------------------------------------------------------------------
// Link Library
// ----------------------------------------------------------------------------
// ----- gilgil temp 2014.03.28 -----
/*
#ifdef _MSC_VER
  #ifdef _DEBUG
    #ifdef QT_GUI_LIB
      #pragma comment(lib, "snoopd_gui.lib")
    #else
      #pragma comment(lib, "snoopd.lib")
    #endif // QT_GUI_LIB
  #else  _DEBUG
    #ifdef QT_GUI_LIB
      #pragma comment(lib, "snoop_gui.lib")
    #else
      #pragma comment(lib, "snoop.lib")
    #endif // QT_GUI_LIB
  #endif // _DEBUG
  #pragma comment(lib, "wpcap.lib")
  #pragma comment(lib, "Iphlpapi.lib")
#endif // _MSC_VER
*/
// ----------------------------------

// ----------------------------------------------------------------------------
// Snoop Version
// ----------------------------------------------------------------------------
extern const char* SNOOP_VERSION;

// ----------------------------------------------------------------------------
// Constant
// ----------------------------------------------------------------------------
namespace snoop
{
  static const int DEFAULT_READTIMEOUT    =  1;
  static const int DEFAULT_SNAPLEN        =  1600;
  static const int DEFAULT_TIMEOUT        =  5000;
  static const int INVALID_ADAPTER_INDEX  =  -1;
  static const int DEFAULT_ADAPTER_INDEX  =  0;
};

// ----------------------------------------------------------------------------
// SnoopCaptureType
// ----------------------------------------------------------------------------
class SnoopCaptureType
{
public:
  enum _SnoopCaptureType
  {
    None,
    InPath,
    OutOfPath
  };

protected:
  _SnoopCaptureType value;

public:
  SnoopCaptureType()                              {                      } // default ctor
  SnoopCaptureType(const _SnoopCaptureType value) { this->value = value; } // conversion ctor
  operator _SnoopCaptureType() const              { return value;        } // cast operator

public:
  SnoopCaptureType(const QString s);
  QString str() const;
};

// ----------------------------------------------------------------------------
// SnoopError
// ----------------------------------------------------------------------------
class SnoopError : public VError
{
public:
  enum {
    INVALID_ADAPTER_INDEX = VERR_CATEGORY_SNOOP,
    IN_PCAP_OPEN,
    IN_PCAP_COMPILE,
    IN_PCAP_SETFILTER,
    IN_PCAP_NEXT_EX,
    IN_PCAP_FINDALLDEVS_EX,
    CANCELED_BY_USER,
    IN_PCAP_OPEN_DEAD,
    HOST_NOT_SPECIFIED,
    CAN_NOT_FIND_ALL_HOST,
    SESSION_COUNT_IS_ZERO,
    THE_SAME_SOURCE_AND_TARGET_IP,
    CAN_NOT_FIND_HOST,
    THE_SAME_REAL_AND_TARGET_MAC,
    CAN_NOT_OPEN_INFECT_THREAD,
    IN_PCAP_DUMP_OPEN,
    CAN_NOT_SPOOF_MYSELF
  };
};

#endif // __SNOOP_BASE_H__
