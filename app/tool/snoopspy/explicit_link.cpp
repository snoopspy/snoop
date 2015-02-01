// #include "explicit_link.h" // gilgil temp 2013.12.06
#include <VMyObject> // gilgil temp 2012.07.30
#include <VNetFactory> // gilgil temp 2012.07.30
#include <SnoopCaptureFactory>
#include <SnoopFilterFactory>
#include <SnoopProcessFactory>
#include <VLog>

void showList()
{
  VFactory& factory = VFactory::instance();
  VFactory::VCategoryMap& map = factory.categoryMap;
  for (VFactory::VCategoryMap::iterator it = map.begin(); it != map.end(); it++)
  {
    QString categoryName = it.key();
    LOG_DEBUG("categoryName=%s", qPrintable(categoryName));
    VFactory::VMetaObjectList mobjList = it.value();
    foreach (const QMetaObject* mobj, mobjList)
    {
      LOG_DEBUG("  className=%s", mobj->className());
    }
  }
}

void explicitLink()
{
  VMyObject::explicitLink(); // gilgil temp 2012.07.30
  // VNetFactory::explicitLink(); // gilgil temp 2012.07.30
  SnoopCaptureFactory::explicitLink();
  SnoopFilterFactory::explicitLink();
  SnoopProcessFactory::explicitLink();
  showList();
}
