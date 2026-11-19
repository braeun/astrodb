#include "dbinfodialog.h"
#include "ui_dbinfodialog.h"
#include <astrodb/database.h>

DBInfoDialog::DBInfoDialog(QWidget *parent):QDialog(parent),
  ui(new Ui::DBInfoDialog)
{
  ui->setupUi(this);
  ui->backendLabel->setText(QString::fromStdString(astrodb::Database::get()->getBackend()));
  ui->nameLabel->setText(QString::fromStdString(astrodb::Database::get()->getName()));
}

DBInfoDialog::~DBInfoDialog()
{
  delete ui;
}
