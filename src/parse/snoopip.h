// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_IP_H__
#define __SNOOP_IP_H__

#include <SnoopEth>

// ----------------------------------------------------------------------------
// SnoopIp
// ----------------------------------------------------------------------------
class SnoopIp
{
public:
  static bool   is    (IP_HDR* ipHdr, uint8_t protocol, void** transportHdr);
  static bool   isTcp (IP_HDR* ipHdr, TCP_HDR**  tcpHdr);
  static bool   isUdp (IP_HDR* ipHdr, UDP_HDR**  udpHdr);
  static bool   isIcmp(IP_HDR* ipHdr, ICMP_HDR** icmpHdr);
  static uint16_t checksum(IP_HDR* ipHdr);
  static uint16_t recalculateChecksum(uint16_t oldChecksum, uint16_t oldValue, uint16_t newValue);
  static uint16_t recalculateChecksum(uint16_t oldChecksum, uint32_t oldValue, uint32_t newValue);

public:
  static bool parse(SnoopPacket* packet);
  static bool parseAll(SnoopPacket* packet);
};

#endif // __SNOOP_IP_H__
