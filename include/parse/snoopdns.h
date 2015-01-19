// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_DNS_H__
#define __SNOOP_DNS_H__

#include <SnoopUdp>

// ----------------------------------------------------------------------------
// SnoopDnsQuestion
// ----------------------------------------------------------------------------
class SnoopDnsQuestion
{
public:
  QString name;
  uint16_t  type;
  uint16_t  _class;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);
};

class SnoopDnsQuestions : public QList<SnoopDnsQuestion>
{
public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int count, int* offset);
};

// ----------------------------------------------------------------------------
// SnoopDnsResourceRecord
// ----------------------------------------------------------------------------
class SnoopDnsResourceRecord
{
public:
  QString    name;
  uint16_t     type;
  uint16_t     _class;
  uint32_t     ttl;
  uint16_t     dataLength;
  QByteArray data;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);
};

// ----------------------------------------------------------------------------
// SnoopDnsResourceRecords
// ----------------------------------------------------------------------------
class SnoopDnsResourceRecords : public QList<SnoopDnsResourceRecord>
{
public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int count, int* offset);
};

// ----------------------------------------------------------------------------
// SnoopDns
// ----------------------------------------------------------------------------
class SnoopDns
{
public:
  DNS_HDR dnsHdr;
  SnoopDnsQuestions questions;
  SnoopDnsResourceRecords answers;
  SnoopDnsResourceRecords authorities;
  SnoopDnsResourceRecords additionals;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);

public:
  static QByteArray encodeName(QString name);
  static QString    decodeName(uint8_t* udpData, int dataLen, int* offset);
};

#endif // __SNOOP_DNS_H__
