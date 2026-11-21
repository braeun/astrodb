#include "dbinfodialog.h"
#include "ui_dbinfodialog.h"
#include <astrodb/database.h>

DBInfoDialog::DBInfoDialog(QWidget *parent):QDialog(parent),
  ui(new Ui::DBInfoDialog)
{
  ui->setupUi(this);
  auto db = astrodb::Database::get();
  if (db)
  {
    ui->backendLabel->setText(QString::fromStdString(db->getBackend()));
    ui->nameLabel->setText(QString::fromStdString(db->getName()));
  }
}

DBInfoDialog::~DBInfoDialog()
{
  delete ui;
}
