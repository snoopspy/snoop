#include <QApplication>
#include <VApp>
#include <SnoopCommon>
#include "mainwindow.h"
#include "explicit_link.h"

int run(QApplication& a)
{
  MainWindow w;
  w.show();
  return a.exec();
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  VApp::initialize(false, true);
  LOG_INFO("snoopspy version 3 started %s / %s", VDREAM_VERSION, SNOOP_VERSION);
  // VApp::instance().setArguments(argc, argv); // gilgil temp 2015.01.21
  explicitLink();
  int res = run(a);
  VApp::finalize();
  LOG_INFO("SnoopSpy version 3 terminated");
  return res;
}
