#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <astrodb/data/camera.h>
#include <astrodb/data/object.h>
#include <astrodb/data/observer.h>
#include <astrodb/data/telescope.h>
#include <QDialog>
#include <vector>

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DatabaseDialog(QWidget *parent = nullptr);
  ~DatabaseDialog();

  void refresh();

private:
  void changeTable(int row);
  void updateTable();
  void setupCameraTable();
  void setupObjectTable();
  void setupObserverTable();
  void setupTelescopeTable();
  void updateCameraTable();
  void updateObjectTable();
  void updateObserverTable();
  void updateTelescopeTable();
  void info();
  void addItem();
  void removeItems();
  void cellChanged(int row, int col);
  void cameraChanged(int row, int col);
  void objectChanged(int row, int col);
  void observerChanged(int row, int col);
  void telescopeChanged(int row, int col);

  Ui::DatabaseDialog *ui;
  int currentTable;
  bool updating;
  std::vector<astrodb::Camera> cameras;
  std::vector<astrodb::Object> objects;
  std::vector<astrodb::Observer> observers;
  std::vector<astrodb::Telescope> telescopes;
};

#endif // DATABASEDIALOG_H
