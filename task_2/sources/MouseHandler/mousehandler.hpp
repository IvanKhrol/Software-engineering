#ifndef __mousehandler_hpp_
#define __mousehandler_hpp_

#include <QWidget>
#include <QtGui>
#include <QDebug>

#define APP_NAME "TASK 3"

QT_BEGIN_NAMESPACE
namespace Ui {
class MouseHandler;
}
QT_END_NAMESPACE

class MouseHandler : public QWidget {
  Q_OBJECT

public:
  MouseHandler(QWidget *parent = nullptr);
  ~MouseHandler();

private:

  Ui::MouseHandler *ui;

protected:

  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

};
#endif // __mousehandler_hpp_
