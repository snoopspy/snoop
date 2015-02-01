#include <SnoopFilterFactory>

#include <SnoopBpFilter>
#include <SnoopProcessFilter>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopFilterFactory
// ----------------------------------------------------------------------------
void SnoopFilterFactory::explicitLink()
{
  VFactory& factory = VFactory::instance();
  static const QString categoryName = "SnoopFilter";

  SnoopBpFilter      bpFilter;      factory.registerMetaObjectByCategoryName(bpFilter.metaObject(),      categoryName);
#ifdef WIN32
  SnoopProcessFilter processFilter; factory.registerMetaObjectByCategoryName(processFilter.metaObject(), categoryName);
#endif // WIN32
}
