#include "mousehandler.hpp"
#include "ui_mousehandler.h"

MouseHandler::MouseHandler(QWidget *parent) : QWidget(parent), ui(new Ui::MouseHandler) {
  ui->setupUi(this);
  setFocusPolicy(Qt::StrongFocus); 

  ui->label->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->label_2->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->label_3->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->realtime_lineEdit->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->static_lineEdit->setAttribute(Qt::WA_TransparentForMouseEvents);

  setMouseTracking(true); 
}

MouseHandler::~MouseHandler() { 
  delete ui; 
}

void MouseHandler::mouseMoveEvent(QMouseEvent *event) {
  int x = event->pos().x();
  int y = height() - event->pos().y();
  ui->realtime_lineEdit->setText(QString("X: %1, Y: %2").arg(x).arg(y));
}

void MouseHandler::mousePressEvent(QMouseEvent *event) {
  qDebug() << "mousePressEvent";
  if (event->button() == Qt::LeftButton) {
    int x = event->pos().x();
    int y = height() - event->pos().y();

    ui->static_lineEdit->setText(QString("X: %1, Y: %2").arg(x).arg(y));
  }
}

void MouseHandler::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setPen(palette().dark().color());
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
