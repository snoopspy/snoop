#include <QApplication>
#include <VApp>
#include <SnoopBase>
#include "dialog.h"
#include "explicit_link.h"

int run(QApplication& a)
{
  Dialog w;
  w.show();
  return a.exec();
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  VApp::initialize();
  LOG_INFO("httpsniff version 3 started %s / %s", VBase::VDREAM_VERSION, SnoopBase::SNOOP_VERSION);
  VApp::instance().setArguments(argc, argv);
  explicitLink();
  int res = run(argc, argv);
  VApp::finalize();
  LOG_INFO("httpsniff version 3 terminated");
  return res;
}
