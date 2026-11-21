#ifndef CONNECTIONCONFIGURATIONWIDGET_H
#define CONNECTIONCONFIGURATIONWIDGET_H

#include <QWidget>

namespace Ui { class ConnectionConfigurationWidget; }

class ConnectionConfigurationWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ConnectionConfigurationWidget(QWidget *parent = nullptr);
  ~ConnectionConfigurationWidget();

  void setDriver(const QString& s);

  QString getDriver() const;

  void setDatabase(const QString& s);

  QString getDatabase() const;

  void setUser(const QString& s);

  QString getUser() const;

  void setPassword(const QString& s);

  QString getPassword() const;

private:
  Ui::ConnectionConfigurationWidget *ui;
};

#endif // CONNECTIONCONFIGURATIONWIDGET_H
