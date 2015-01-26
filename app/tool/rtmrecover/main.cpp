#include <iostream>
#include <QCoreApplication>
#include <VApp>
#include <SnoopRtm>
#include <VDebugNew>

void run(QCoreApplication& a)
{
  QString fileName;
  if (a.arguments().count() > 1) fileName = a.arguments().at(1);

  SnoopRtm& rtm = SnoopRtm::instance();
  if (fileName == "")
  {
    if (!rtm.loadFromSystem())
    {
      std::cout << "rtm.loadFromSystem return false " << qPrintable(rtm.error.msg) << std::endl;
      return;
    }
    if (!rtm.saveToFile(SnoopRtm::DEFAULT_RTM_FILE_NAME, ""))
    {
      std::cout << "rtm.saveToFile return false " << qPrintable(rtm.error.msg) << std::endl;
      return;
    }
  } else
  {
    if (!rtm.loadFromFile(fileName, ""))
    {
      std::cout << qPrintable(QString("can not open file(%1)").arg(fileName)) << std::endl;
    }
    if (!rtm.recoverSystem())
    {
      std::cout << "can not recover rtm" << std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);
  VApp::initialize(true, false, "stdout");
  run(a);
  VApp::finalize(false);
}
