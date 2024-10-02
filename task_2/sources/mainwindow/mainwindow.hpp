#ifndef __mainwindow_hpp_
#define __mainwindow_hpp_

#include <QMainWindow>
#include <QWidget>
#include <QtGui>

#include <MouseHandler/mousehandler.hpp>

#define APP_NAME "TASK 3"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void setup_MainWindow();

  Ui::MainWindow *ui;
  MouseHandler *mouseHandler;

private slots:
  void show_MouseHandler() const;
  void show_Multimedia() const;
};
#endif // __mainwindow_hpp_
