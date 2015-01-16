#include <SnoopEth>

#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopEth
// ----------------------------------------------------------------------------
bool SnoopEth::is(ETH_HDR* ethHdr, UINT16 etherType, void** networkHdr)
{
  if (ntohs(ethHdr->ether_type) != etherType)
    return false;
  if (networkHdr != NULL)
    *networkHdr = (void*)((BYTE*)(ethHdr) + sizeof(ETH_HDR));
  return true;
}

bool SnoopEth::isIp(ETH_HDR* ethHdr, IP_HDR** ipHdr)
{
  if (htons(ethHdr->ether_type) != ETHERTYPE_IP)
    return false;
  if (ipHdr != NULL)
    *ipHdr = (IP_HDR*)((BYTE*)(ethHdr) + sizeof(ETH_HDR));
  return true;
}

bool SnoopEth::isArp(ETH_HDR* ethHdr, ARP_HDR** arpHdr)
{
  if (htons(ether_type) != ETHERTYPE_ARP)
    return false;
  if (arpHdr != NULL)
    *arpHdr = (ARP_HDR*)((BYTE*)(ethHdr) + sizeof(ETH_HDR));
  return true;
}

bool SnoopEth::parse(SnoopPacket* packet)
{
  if (packet->linkType != DLT_EN10MB) return false;
  packet->ethHdr = (ETH_HDR*)packet->pktData;
  return true;
}

bool SnoopEth::parseAll(SnoopPacket* packet)
{
  return parse(packet);
}
