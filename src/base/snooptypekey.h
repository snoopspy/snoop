// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_TYPE_KEY_H__
#define __SNOOP_TYPE_KEY_H__

#include <SnoopType>

// ----------------------------------------------------------------------------
// SnoopMacKey
// ----------------------------------------------------------------------------
class SnoopMacKey
{
public:
  Mac mac;

  bool operator < (const SnoopMacKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopMacFlowKey
// ----------------------------------------------------------------------------
class SnoopMacFlowKey
{
public:
  Mac srcMac;
  Mac dstMac;

  bool operator < (const SnoopMacFlowKey& rhs) const;
  SnoopMacFlowKey reverse();
};

// ----------------------------------------------------------------------------
// SnoopMacSessionKey
// ----------------------------------------------------------------------------
class SnoopMacSessionKey
{
public:
  Mac mac1;
  Mac mac2;

  bool operator < (const SnoopMacSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopIpKey
// ----------------------------------------------------------------------------
class SnoopIpKey
{
public:
  Ip ip;

  bool operator < (const SnoopIpKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopIpFlowKey
// ----------------------------------------------------------------------------
class SnoopIpFlowKey
{
public:
  Ip srcIp;
  Ip dstIp;

  bool operator < (const SnoopIpFlowKey& rhs) const;
  SnoopIpFlowKey reverse();
};

// ----------------------------------------------------------------------------
// SnoopIpSessionKey
// ----------------------------------------------------------------------------
class SnoopIpSessionKey
{
public:
  Ip ip1;
  Ip ip2;

  bool operator < (const SnoopIpSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopPortKey
// ----------------------------------------------------------------------------
class SnoopPortKey
{
public:
  int port;

  bool operator < (const SnoopPortKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopPortFlowKey
// ----------------------------------------------------------------------------
class SnoopPortFlowKey
{
public:
  uint16_t srcPort;
  uint16_t dstPort;

  bool operator < (const SnoopPortFlowKey& rhs) const;
  SnoopPortFlowKey reverse();
};

// ----------------------------------------------------------------------------
// SnoopPortSessionKey
// ----------------------------------------------------------------------------
class SnoopPortSessionKey
{
public:
  uint16_t port1;
  uint16_t port2;

  bool operator < (const SnoopPortSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// SnoopTransportKey
// ----------------------------------------------------------------------------
class SnoopTransportKey
{
public:
  Ip     ip;
  uint16_t port;

  bool operator < (const SnoopTransportKey& rhs) const;
};

typedef SnoopTransportKey SnoopTcpKey;
typedef SnoopTransportKey SnoopUdpKey;

// ----------------------------------------------------------------------------
// SnoopTransportFlowKey
// ----------------------------------------------------------------------------
class SnoopTransportFlowKey
{
public:
  Ip     srcIp;
  uint16_t srcPort;
  Ip     dstIp;
  uint16_t dstPort;

  bool operator < (const SnoopTransportFlowKey& rhs) const;
  bool operator == (const SnoopTransportFlowKey& rhs) const;
  SnoopTransportFlowKey reverse();
};

typedef SnoopTransportFlowKey SnoopTcpFlowKey;
typedef SnoopTransportFlowKey SnoopUdpFlowKey;

// ----------------------------------------------------------------------------
// SnoopTransportSessionKey
// ----------------------------------------------------------------------------
class SnoopTransportSessionKey
{
public:
  Ip     ip1;
  uint16_t port1;
  Ip     ip2;
  uint16_t port2;

  bool operator < (const SnoopTransportSessionKey& rhs) const;
};

typedef SnoopTransportSessionKey SnoopTcpSessionKey;
typedef SnoopTransportSessionKey SnoopUdpSessionKey;

// ----------------------------------------------------------------------------
// SnoopTupleFlowKey
// ----------------------------------------------------------------------------
class SnoopTupleFlowKey
{
public:
  uint8_t                 proto;
  SnoopTransportFlowKey flow;

  bool operator < (const SnoopTupleFlowKey& rhs) const;
  SnoopTupleFlowKey reverse();
};

#endif // __SNOOP_TYPE_KEY_H__
