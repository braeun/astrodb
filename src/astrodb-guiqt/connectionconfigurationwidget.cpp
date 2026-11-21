#include "connectionconfigurationwidget.h"
#include "ui_connectionconfigurationwidget.h"
#include <astrodb/database.h>

ConnectionConfigurationWidget::ConnectionConfigurationWidget(QWidget *parent):QWidget(parent),
  ui(new Ui::ConnectionConfigurationWidget)
{
  ui->setupUi(this);
  for (const std::string& s : astrodb::Database::getDrivers())
  {
    ui->databaseDriverBox->addItem(QString::fromStdString(s));
  }
}

ConnectionConfigurationWidget::~ConnectionConfigurationWidget()
{
  delete ui;
}

void ConnectionConfigurationWidget::setDriver(const QString& s)
{
  for (int i=0;i<ui->databaseDriverBox->count();++i)
  {
    if (ui->databaseDriverBox->itemText(i) == s)
    {
      ui->databaseDriverBox->setCurrentIndex(i);
      break;
    }
  }
}

QString ConnectionConfigurationWidget::getDriver() const
{
  return ui->databaseDriverBox->currentText();
}

void ConnectionConfigurationWidget::setDatabase(const QString& s)
{
  ui->databaseField->setText(s);
}

QString ConnectionConfigurationWidget::getDatabase() const
{
  return ui->databaseField->text();
}

void ConnectionConfigurationWidget::setUser(const QString& s)
{
  ui->databaseUserField->setText(s);
}

QString ConnectionConfigurationWidget::getUser() const
{
  return ui->databaseUserField->text();
}

void ConnectionConfigurationWidget::setPassword(const QString& s)
{
  ui->databasePasswordField->setText(s);
}

QString ConnectionConfigurationWidget::getPassword() const
{
  return ui->databasePasswordField->text();
}

