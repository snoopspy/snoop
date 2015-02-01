#include <SnoopIp>

#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopIp
// ----------------------------------------------------------------------------
bool SnoopIp::is(IP_HDR* ipHdr, uint8_t protocol, void** transportHdr)
{
  if (ipHdr->ip_p != protocol)
    return false;
  if (transportHdr != NULL)
    *transportHdr = (void*)((uint8_t*)(ipHdr) + ipHdr->ip_hl * sizeof(uint32_t));
  return true;
}

bool SnoopIp::isTcp(IP_HDR* ipHdr, TCP_HDR** tcpHdr)
{
  if (ipHdr->ip_p != IPPROTO_TCP)
    return false;
  if (tcpHdr != NULL)
    *tcpHdr = (TCP_HDR*)((uint8_t*)(ipHdr) + ipHdr->ip_hl * sizeof(uint32_t));
  return true;
}

bool SnoopIp::isUdp(IP_HDR* ipHdr, UDP_HDR** udpHdr)
{
  if (ipHdr->ip_p != IPPROTO_UDP)
    return false;
  if (udpHdr != NULL)
    *udpHdr = (UDP_HDR*)((uint8_t*)(ipHdr) + ipHdr->ip_hl * sizeof(uint32_t));
  return true;
}

bool SnoopIp::isIcmp(IP_HDR* ipHdr, ICMP_HDR** icmpHdr)
{
  if (ipHdr->ip_p != IPPROTO_ICMP)
    return false;
  if (icmpHdr != NULL)
    *icmpHdr = (ICMP_HDR*)((uint8_t*)(ipHdr) + ipHdr->ip_hl * sizeof(uint32_t));
  return true;
}

//
// All ipHdr field except ipHdr.ip_sum
//
uint16_t SnoopIp::checksum(IP_HDR* ipHdr)
{
  int i;
  uint32_t sum;
  uint16_t *p;

  sum = 0;

  // Add ipHdr buffer as array of uint16_t
  p = (uint16_t*)(ipHdr);
  for (i = 0; i < (int)sizeof(IP_HDR) / 2; i++)
  {
    sum += ntohs(*p);
    p++;
  }
  
  // Do not consider padding because ip header length is always multilpe of 2.

  // Decrease checksum from sum
  sum -= ntohs(ipHdr->ip_sum);

  // Recalculate sum
  while(sum >> 16)
  {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }
  sum = ~sum;

  return (uint16_t)sum;
}

//
// Calculate Checksum on condition that only one value(uint16_t) is changed.
//
uint16_t SnoopIp::recalculateChecksum(uint16_t oldChecksum, uint16_t oldValue, uint16_t newValue)
{
  uint32_t sum;

  sum = oldValue + (~newValue & 0xFFFF);
  sum += oldChecksum;
  sum = (sum & 0xFFFF) + (sum >> 16);
  return (uint16_t)(sum + (sum >> 16));
}

uint16_t SnoopIp::recalculateChecksum(uint16_t oldChecksum, uint32_t oldValue, uint32_t newValue)
{
  uint16_t oldValue16;
  uint16_t newValue16;
  uint16_t sum;

  oldValue16 = (oldValue & 0xFFFF0000) >> 16;
  newValue16 = (newValue & 0xFFFF0000) >> 16;
  sum        = recalculateChecksum(oldChecksum, oldValue16, newValue16);

  oldValue16 = oldValue & 0x0000ffff;
  newValue16 = newValue & 0x0000ffff;
  sum        = recalculateChecksum(sum, oldValue16, newValue16);

  return sum;
}

bool SnoopIp::parse(SnoopPacket* packet)
{
  if (!SnoopEth::isIp(packet->ethHdr, &packet->ipHdr)) return false;
  packet->netType = ETHERTYPE_IP;
  return true;
}

bool SnoopIp::parseAll(SnoopPacket* packet)
{
  if (!SnoopEth::parseAll(packet)) return false;
  return parse(packet);
}
