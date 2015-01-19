#include <SnoopUdp>

#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopUdp
// ----------------------------------------------------------------------------
bool SnoopUdp::isData(IP_HDR* ipHdr, UDP_HDR* udpHdr, uint8_t** udpData, int* udpDataLen)
{
  Q_UNUSED(ipHdr)

  int _udpDataLen;

  if (udpData != NULL)
    *udpData = (uint8_t*)(udpHdr) + sizeof(UDP_HDR);
  _udpDataLen = ntohs(udpHdr->uh_ulen) - sizeof(UDP_HDR);
  if (udpDataLen != NULL)
    *udpDataLen = _udpDataLen;
  return _udpDataLen > 0;
}

//
// All udpHdr field except udpHdr.uh_sum
// All data buffer(padding)
// ipHdr.ip_src, ipHdr.ip_dst, udpHdrDataLen and IPPROTO_UDP
//
uint16_t SnoopUdp::checksum(IP_HDR* ipHdr, UDP_HDR* udpHdr)
{
  int i;
  int udpHdrDataLen;
  uint16_t *p;
  uint32_t src, dst;
  uint32_t sum;

  udpHdrDataLen = ntohs(udpHdr->uh_ulen);
  sum = 0;

  // Add udpHdr & data buffer as array of uint16_t
  p = (uint16_t*)udpHdr;
  for (i = 0; i < udpHdrDataLen / 2; i++)
  {
    sum += htons(*p);
    p++;
  }

  // If length is odd, add last data(padding)
  if ((udpHdrDataLen / 2) * 2 != udpHdrDataLen)
    sum += (htons(*p) & 0xFF00);

  // Decrease checksum from sum
  sum -= ntohs(udpHdr->uh_sum);

  // Add src address
  src = ntohl(ipHdr->ip_src);
  sum += ((src & 0xFFFF0000) >> 16) + (src & 0x0000FFFF);

  // Add dst address
  dst = ntohl(ipHdr->ip_dst);
  sum += ((dst & 0xFFFF0000) >> 16) + (dst & 0x0000FFFF);

  // Add extra information
  sum += (uint32_t)udpHdrDataLen + IPPROTO_UDP;

  // Recalculate sum
  while ((sum >> 16) > 0)
  {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }
  sum = ~sum;

  return (uint16_t)sum;
}

bool SnoopUdp::parse(SnoopPacket* packet)
{
  if (!SnoopIp::isUdp(packet->ipHdr, &packet->udpHdr)) return false;
  packet->proto = IPPROTO_UDP;
  return true;
}

bool SnoopUdp::parseAll(SnoopPacket* packet)
{
  if (!SnoopIp::parseAll(packet)) return false;
  return parse(packet);
}
