#ifndef __MainWindow_hpp_
#define __MainWindow_hpp_

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QAction>
#include <QSizePolicy>

#define APP_NAME "TASK 3"
#define N_MAX_COUNT 100

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QSpinBox* nSpinBox;
  QLineEdit* positionLineEdit;

private slots:
  void drawPolygonWidget() const;
};
#endif // __MainWindow_hpp_
