#include <SnoopHostList>

// ----------------------------------------------------------------------------
// SnoopHost
// ----------------------------------------------------------------------------
SnoopHost::SnoopHost(Ip ip, Mac mac, QString name)
{
  this->ip   = ip;
  this->mac  = mac;
  this->name = name;
}

SnoopHost::~SnoopHost()
{

}

void SnoopHost::load(VRep& rep)
{
  ip   = rep.getStr("ip",   ip.str());
  mac  = rep.getStr("mac",  mac.str());
  name = rep.getStr("name", name);
}

void SnoopHost::save(VRep& rep)
{
  rep.setStr("ip",   ip.str());
  rep.setStr("mac",  mac.str());
  rep.setStr("name", name);
}

// ----------------------------------------------------------------------------
// SnoopHostList
// ----------------------------------------------------------------------------
SnoopHost* SnoopHostList::findByIp(Ip ip)
{
  for (SnoopHostList::iterator it = begin(); it != end(); it++)
  {
    SnoopHost& host = *it;
    if (host.ip == ip) return &host;
  }
  return NULL;
}

void SnoopHostList::load(VRep& rep)
{
  clear();
  {
    xml_foreach (childXml, rep.childs())
    {
      SnoopHost host;
      host.load(childXml);
      push_back(host);
    }
  }
}

void SnoopHostList::save(VRep& rep)
{
  rep.clearChild();
  for (SnoopHostList::iterator it = begin(); it != end(); it++)
  {
    SnoopHost& host = *it;
    VXml childXml = rep.addChild("host");
    host.save(childXml);
  }
}
