#include <SnoopCommand>
#include <VDebugNew>

REGISTER_METACLASS(SnoopCommand, SnoopProcess)

// ----------------------------------------------------------------------------
// SnoopCommandItem
// ----------------------------------------------------------------------------
SnoopCommandItem::SnoopCommandItem()
{
  enabled = true;
  command = "";
  sync    = "";
  process = NULL;
}

SnoopCommandItem::~SnoopCommandItem()
{
  if (process != NULL)
  {
    delete process;
    process = NULL;
  }
}

void SnoopCommandItem::load(VRep& rep)
{
  enabled = rep.getBool("enabled", enabled);
  command = rep.getStr("command",  command);
  sync    = rep.getBool("sync",    sync);
}

void SnoopCommandItem::save(VRep& rep)
{
  rep.setBool("enabled", enabled);
  rep.setStr("command",  command);
  rep.setBool("sync",    sync);
}

bool SnoopCommandItem::execute(VError& error)
{
  if (!enabled) return true;
  if (process == NULL) process = new QProcess;
  process->start(command);
  if (!process->waitForStarted())
  {
    SET_ERROR(VError, QString("process->waitForStarted(%1) return false").arg(command), VError::RUN_PROCESS);
    return false;
  }

  if (sync)
  {
    if (!process->waitForFinished())
    {
      SET_ERROR(VError, QString("process->waitForFinished(%1) return false").arg(command), VError::RUN_PROCESS);
      return false;
    }
  }
  return true;
}

#ifdef QT_GUI_LIB
void operator << (QTreeWidgetItem& treeWidgetItem, SnoopCommandItem& item)
{
  treeWidgetItem.setCheckState(SnoopCommandItem::ENABLED_IDX, item.enabled ? Qt::Checked : Qt::Unchecked);
  treeWidgetItem.setText(SnoopCommandItem::COMMAND_IDX, item.command);
  treeWidgetItem.setCheckState(SnoopCommandItem::SYNC_IDX, item.sync ? Qt::Checked : Qt::Unchecked);
  treeWidgetItem.setFlags(treeWidgetItem.flags() | Qt::ItemIsEditable);
}

void operator << (SnoopCommandItem& item, QTreeWidgetItem& treeWidgetItem)
{
  item.enabled = treeWidgetItem.checkState(SnoopCommandItem::ENABLED_IDX) == Qt::Checked;
  item.command = treeWidgetItem.text(SnoopCommandItem::COMMAND_IDX);
  item.sync    = treeWidgetItem.checkState(SnoopCommandItem::SYNC_IDX) == Qt::Checked;
}
#endif // QT_GUI_LIB

// ----------------------------------------------------------------------------
// SnoopCommandItems
// ----------------------------------------------------------------------------
bool SnoopCommandItems::execute(VError& error)
{
  for (int i = 0; i < this->count(); i++)
  {
    SnoopCommandItem& item = (SnoopCommandItem&)this->at(i);
    if (!item.execute(error)) return false;
  }
  return true;
}

void SnoopCommandItems::load(VRep& rep)
{
  clear();
  xml_foreach (childXml, rep.childs())
  {
    SnoopCommandItem item;
    item.load(childXml);
    push_back(item);
  }
}

void SnoopCommandItems::save(VRep& rep)
{
  rep.clearChild();
  for (int i = 0; i < this->count(); i++)
  {
    SnoopCommandItem& item = (SnoopCommandItem&)this->at(i);
    item.save(rep.gotoChild("command" + QString::number(i)));
  }
}

#ifdef QT_GUI_LIB
void operator << (QTreeWidget& treeWidget, SnoopCommandItems& items)
{
  treeWidget.clear();
  QList<QTreeWidgetItem*> treeWidgetItems;
  for (int i = 0; i < items.count(); i++)
  {
    SnoopCommandItem& item = (SnoopCommandItem&)items.at(i);
    QTreeWidgetItem* newWidgetItem = new QTreeWidgetItem(&treeWidget);
    *newWidgetItem << item;
    treeWidgetItems.push_back(newWidgetItem);
  }
  treeWidget.insertTopLevelItems(0, treeWidgetItems);
}

void operator << (SnoopCommandItems& items, QTreeWidget& treeWidget)
{
  items.clear();
  int count = treeWidget.topLevelItemCount();
  for (int i = 0; i < count; i++)
  {
    QTreeWidgetItem* treeWidgetItem = treeWidget.topLevelItem(i);
    SnoopCommandItem newItem;
    newItem << *treeWidgetItem;
    items.push_back(newItem);
  }
}
#endif // QT_GUI_LIB

// ----------------------------------------------------------------------------
// SnoopCommand
// ----------------------------------------------------------------------------
SnoopCommand::SnoopCommand(void* owner) : SnoopProcess(owner)
{
  openCommands.clear();
  closeCommands.clear();
}

SnoopCommand::~SnoopCommand()
{
  close();
}

bool SnoopCommand::doOpen()
{
  if (!SnoopProcess::doOpen()) return false;

  if (!openCommands.execute(error))
  {
    return false;
  }

  return true;
}

bool SnoopCommand::doClose()
{
  if (!closeCommands.execute(error))
  {
    return false;
  }

  return SnoopProcess::doClose();
}

void SnoopCommand::load(VRep& rep)
{
  SnoopProcess::load(xml);

  if (!rep.findChild("open").isNull())  openCommands.load(rep.gotoChild("open"));
  if (!rep.findChild("close").isNull()) closeCommands.load(rep.gotoChild("close"));
}

void SnoopCommand::save(VRep& rep)
{
  SnoopProcess::save(xml);

  openCommands.save(rep.gotoChild("open"));
  closeCommands.save(rep.gotoChild("close"));
}

#ifdef QT_GUI_LIB
#include "snoopcommandwidget.h"
#include "ui_snoopcommandwidget.h"
void SnoopCommand::optionAddWidget(QLayout* layout)
{
  SnoopProcess::optionAddWidget(layout);

  SnoopCommandWidget* widget = new SnoopCommandWidget(layout->parentWidget());
  widget->setObjectName("snoopCommandWidget");
  *(widget->ui->tvOpen)  << openCommands;
  *(widget->ui->tvClose) << closeCommands;
  layout->addWidget(widget);
}

void SnoopCommand::optionSaveDlg(QDialog* dialog)
{
  SnoopProcess::optionSaveDlg(dialog);

  SnoopCommandWidget* widget = dialog->findChild<SnoopCommandWidget*>("snoopCommandWidget");
  LOG_ASSERT(widget != NULL);
  openCommands  << *(widget->ui->tvOpen);
  closeCommands << *(widget->ui->tvClose);
}
#endif // QT_GUI_LIB
