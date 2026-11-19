#include "databasedialog.h"
#include "ui_databasedialog.h"
#include "dbinfodialog.h"
#include <astrodb/database.h>
#include <astrodb/cameratable.h>
#include <astrodb/objecttable.h>
#include <astrodb/observertable.h>
#include <astrodb/telescopetable.h>

DatabaseDialog::DatabaseDialog(QWidget *parent):QDialog(parent),
  ui(new Ui::DatabaseDialog),
  updating(false)
{
  ui->setupUi(this);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  ui->listWidget->setCurrentRow(0);
  changeTable(0);
  connect(ui->listWidget,&QListWidget::currentRowChanged,this,&DatabaseDialog::changeTable);
  connect(ui->infoButton,&QAbstractButton::clicked,this,&DatabaseDialog::info);
  connect(ui->addButton,&QAbstractButton::clicked,this,&DatabaseDialog::addItem);
  connect(ui->removeButton,&QAbstractButton::clicked,this,&DatabaseDialog::removeItems);
  connect(ui->tableWidget,&QTableWidget::cellChanged,this,&DatabaseDialog::cellChanged);
}

DatabaseDialog::~DatabaseDialog()
{
  delete ui;
}

void DatabaseDialog::refresh()
{
  updateTable();
}




void DatabaseDialog::changeTable(int row)
{
  currentTable = row;
  switch (currentTable)
  {
    case 0:
      setupCameraTable();
      break;
    case 1:
      setupObjectTable();
      break;
    case 2:
      setupObserverTable();
      break;
    case 3:
      setupTelescopeTable();
      break;
  }
}

void DatabaseDialog::updateTable()
{
  switch (currentTable)
  {
    case 0:
      updateCameraTable();
      break;
    case 1:
      updateObjectTable();
      break;
    case 2:
      updateObserverTable();
      break;
    case 3:
      updateTelescopeTable();
      break;
  }
}

void DatabaseDialog::setupCameraTable()
{
  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(6);
  ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Max.Pixel X"));
  ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Max.Pixel Y"));
  ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Pixel Size X [µm]"));
  ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Pixel Size Y [µm]"));
  updateCameraTable();
}

void DatabaseDialog::setupObjectTable()
{
  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  updateObjectTable();
}

void DatabaseDialog::setupObserverTable()
{
  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  updateObserverTable();
}

void DatabaseDialog::setupTelescopeTable()
{
  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(4);
  ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Focal Length [mm]"));
  ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Aperture [mm]"));
  updateTelescopeTable();
}

void DatabaseDialog::updateCameraTable()
{
  updating = true;
  auto db = astrodb::Database::get();
  auto table = db->getCameraTable();
  ui->tableWidget->clearContents();
  cameras = table->getAll();
  ui->tableWidget->setRowCount(cameras.size());
  int row = 0;
  for (const auto& c : cameras)
  {
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(c.getId())));
    ui->tableWidget->item(row,0)->setFlags(ui->tableWidget->item(row,0)->flags()^Qt::ItemIsEditable);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(c.getModel())));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(c.getWidth())));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(c.getHeight())));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(c.getPixelWidth()*1.0E6)));
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(c.getPixelHeight()*1.0E6)));
    ++row;
  }
  updating = false;
}

void DatabaseDialog::updateObjectTable()
{
  updating = true;
  auto db = astrodb::Database::get();
  auto table = db->getObjectTable();
  ui->tableWidget->clearContents();
  objects = table->getAll();
  ui->tableWidget->setRowCount(objects.size());
  int row = 0;
  for (const auto& o : objects)
  {
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(o.getId())));
    ui->tableWidget->item(row,0)->setFlags(ui->tableWidget->item(row,0)->flags()^Qt::ItemIsEditable);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(o.getName())));
    ++row;
  }
  updating = false;
}

void DatabaseDialog::updateObserverTable()
{
  updating = true;
  auto db = astrodb::Database::get();
  auto table = db->getObserverTable();
  ui->tableWidget->clearContents();
  observers = table->getAll();
  ui->tableWidget->setRowCount(observers.size());
  int row = 0;
  for (const auto& o : observers)
  {
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(o.getId())));
    ui->tableWidget->item(row,0)->setFlags(ui->tableWidget->item(row,0)->flags()^Qt::ItemIsEditable);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(o.getName())));
    ++row;
  }
  updating = false;
}

void DatabaseDialog::updateTelescopeTable()
{
  updating = true;
  auto db = astrodb::Database::get();
  auto table = db->getTelescopeTable();
  ui->tableWidget->clearContents();
  telescopes = table->getAll();
  ui->tableWidget->setRowCount(telescopes.size());
  int row = 0;
  for (const auto& t : telescopes)
  {
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(t.getId())));
    ui->tableWidget->item(row,0)->setFlags(ui->tableWidget->item(row,0)->flags()^Qt::ItemIsEditable);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(t.getModel())));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(t.getFocalLength()*1000.0)));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(t.getAperture()*1000.0)));
    ++row;
  }
  updating = false;
}

void DatabaseDialog::info()
{
  DBInfoDialog* d = new DBInfoDialog(this);
  d->exec();
  d->deleteLater();
}

void DatabaseDialog::addItem()
{
  auto db = astrodb::Database::get();
  switch (currentTable)
  {
    case 0:
      db->getCameraTable()->add(astrodb::Camera("",0,0));
      break;
    case 1:
      db->getObjectTable()->add(astrodb::Object(""));
      break;
    case 2:
      db->getObserverTable()->add(astrodb::Observer(""));
      break;
    case 3:
      db->getTelescopeTable()->add(astrodb::Telescope("",0,0));
      break;
  }
  refresh();
}

void DatabaseDialog::removeItems()
{
  auto db = astrodb::Database::get();
  auto selection = ui->tableWidget->selectionModel()->selectedRows();
  for (const auto& index : selection)
  {
    int row = index.row();
    switch (currentTable)
    {
      case 0:
        db->getCameraTable()->remove(cameras[row].getModel());
        break;
      case 1:
        db->getObjectTable()->remove(objects[row].getName());
        break;
      case 2:
        db->getObserverTable()->remove(observers[row].getName());
        break;
      case 3:
        db->getTelescopeTable()->remove(telescopes[row].getModel());
        break;
    }
  }
  updateTable();
}

void DatabaseDialog::cellChanged(int row, int col)
{
  if (updating) return;
  switch (currentTable)
  {
    case 0:
      cameraChanged(row,col);
      break;
    case 1:
      objectChanged(row,col);
      break;
    case 2:
      observerChanged(row,col);
      break;
    case 3:
      telescopeChanged(row,col);
      break;
  }
}

void DatabaseDialog::cameraChanged(int row, int col)
{
  astrodb::Camera& c = cameras[row];
  switch (col)
  {
    case 1:
      c.setModel(ui->tableWidget->item(row,col)->text().toStdString());
      break;
    case 2:
      c.setWidth(ui->tableWidget->item(row,col)->text().toInt());
      c.setSensorWidth(c.getPixelWidth()*c.getWidth());
      break;
    case 3:
      c.setHeight(ui->tableWidget->item(row,col)->text().toInt());
      c.setSensorHeight(c.getPixelHeight()*c.getHeight());
      break;
    case 4:
      c.setPixelWidth(ui->tableWidget->item(row,col)->text().toDouble()*1.0E-6);
      c.setSensorWidth(c.getPixelWidth()*c.getWidth());
      break;
    case 5:
      c.setPixelHeight(ui->tableWidget->item(row,col)->text().toDouble()*1.0E-6);
      c.setSensorHeight(c.getPixelHeight()*c.getHeight());
      break;
  }
  astrodb::Database::get()->getCameraTable()->update(c);
}

void DatabaseDialog::objectChanged(int row, int col)
{
  astrodb::Object& o = objects[row];
  if (col == 1)
  {
    o.setName(ui->tableWidget->item(row,col)->text().toStdString());
  }
  astrodb::Database::get()->getObjectTable()->update(o);
}

void DatabaseDialog::observerChanged(int row, int col)
{
  astrodb::Observer& o = observers[row];
  if (col == 1)
  {
    o.setName(ui->tableWidget->item(row,col)->text().toStdString());
  }
  astrodb::Database::get()->getObserverTable()->update(o);
}

void DatabaseDialog::telescopeChanged(int row, int col)
{
  astrodb::Telescope& t = telescopes[row];
  if (col == 1)
  {
    t.setModel(ui->tableWidget->item(row,col)->text().toStdString());
  }
  else if (col == 2)
  {
    t.setFocalLength(ui->tableWidget->item(row,col)->text().toDouble()*1.0E-3);
  }
  else if (col == 3)
  {
    t.setAperture(ui->tableWidget->item(row,col)->text().toDouble()*1.0E-3);
  }
  astrodb::Database::get()->getTelescopeTable()->update(t);
}

