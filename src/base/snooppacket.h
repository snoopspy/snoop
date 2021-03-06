// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_PACKET_H__
#define __SNOOP_PACKET_H__

#include <SnoopType>
#ifdef WIN32
#include <windivert/windivert.h>
#endif // WIN32

// ----------------------------------------------------------------------------
// SnoopFlowValue
// ----------------------------------------------------------------------------
class SnoopFlowValue
{
public:
  size_t         packets;
  size_t         bytes;
  struct timeval ts;
  bool           created;
  uint8_t*       totalMem;
};

#ifndef WIN32
struct WINDIVERT_ADDRESS {};
#endif // WIN32

// ----------------------------------------------------------------------------
// SnoopPacket
// ----------------------------------------------------------------------------
class SnoopCapture;
class SnoopPacket
{
public:
  ///
  /// packet
  ///
  PKT_HDR*  pktHdr;
  uint8_t*     pktData;

  ///
  /// datalink layer
  ///
  int       linkType; // DLT_EN10MB, ...
  ETH_HDR*  ethHdr;

  ///
  /// network layer
  ///
  uint16_t    netType; // ETHERTYPE_IP, ETHERTYPE_ARP, ...
  IP_HDR*   ipHdr;
  ARP_HDR*  arpHdr;

  ///
  /// transport layer(protocol)
  ///
  uint8_t     proto; // IPPROTO_TCP, IPPROTO_UDP, IPPROTO_ICMP, ...
  TCP_HDR*  tcpHdr;
  UDP_HDR*  udpHdr;
  ICMP_HDR* icmpHdr;

  ///
  /// data
  ///
  uint8_t*     data;
  int       dataLen;

  ///
  /// control
  ///
  // SnoopCapture* sender; // gilgil temp 2014.04.41
  bool          drop;
  // bool      ipChanged;  // issue14_remove_changed_in_snoop_packet
  // bool      tcpChanged; // issue14_remove_changed_in_snoop_packet
  // bool      udpChanged; // issue14_remove_changed_in_snoop_packet

  ///
  /// flow
  ///
  void*           flowKey;  // SnoopMacFlowKey, SnoopIpFlowKey, SnoopTcpFlowKey, SnoopUdpFlowKey, ...
  SnoopFlowValue* flowValue;

  ///
  /// windivert
  ///
  WINDIVERT_ADDRESS divertAddr;

public:
  void clear();
  int  write(QByteArray& ba);
};

#endif // __SNOOP_PACKET_H__
