#ifndef DBINFODIALOG_H
#define DBINFODIALOG_H

#include <QDialog>

namespace Ui {
class DBInfoDialog;
}

class DBInfoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DBInfoDialog(QWidget *parent = nullptr);
  ~DBInfoDialog();

private:
  Ui::DBInfoDialog *ui;
};

#endif // DBINFODIALOG_H
