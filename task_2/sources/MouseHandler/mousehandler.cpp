#include "mousehandler.hpp"
#include "ui_mousehandler.h"

MouseHandler::MouseHandler(QWidget *parent) : QWidget(parent), ui(new Ui::MouseHandler) {
  ui->setupUi(this);
  setFocusPolicy(Qt::StrongFocus); 
  setMouseTracking(true);
}

MouseHandler::~MouseHandler() { 
  delete ui; 
}

void MouseHandler::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << "mouseMoveEvent";
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
