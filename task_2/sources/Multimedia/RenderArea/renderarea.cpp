#include "renderarea.hpp"

#include <QPainter>
#include <QPainterPath>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
  shape = Polygon;
  antialiased = false;

  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const { return QSize(100, 100); }
QSize RenderArea::sizeHint() const { return QSize(400, 200); }

void RenderArea::setShape(Shape new_shape) {
  shape = new_shape;
  update();
}

void RenderArea::setPen(const QPen &new_pen) {
    pen = new_pen;
    update();
}

void RenderArea::setBrush(const QBrush &new_brush) {
  brush = new_brush;
  update();
}

void RenderArea::setAntialiased(bool new_antialiased) {
  antialiased = new_antialiased;
  update();
}

void RenderArea::paintEvent(QPaintEvent *event) {
  static const QPoint points[4] = {
      QPoint(10, 80),
      QPoint(20, 10),
      QPoint(80, 30),
      QPoint(90, 70)
  };

  QRect rect(10, 20, 80, 60);

  QPainterPath path;
  path.moveTo(20, 80);
  path.lineTo(20, 30);
  path.cubicTo(80, 0, 50, 50, 80, 80); 

  QPainter painter(this);
  painter.setPen(pen);
  painter.setBrush(brush);
  if (antialiased) {
    painter.setRenderHint(QPainter::Antialiasing, true);
  }

  for (int x = 0; x < width(); x += 100) {
    for (int y = 0; y < height(); y += 100) {
      painter.save();
      painter.translate(x, y);
      switch (shape) {
      case Polygon:
        painter.drawPolygon(points, 4);
        break;
      case Rect:
        painter.drawRect(rect);
        break;
      case RoundedRect:
        painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
        break;
      case Ellipse:
        painter.drawEllipse(rect);
        break;
      case Path:
        painter.drawPath(path);
        break;
      }
      painter.restore();
    }
  }

  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setPen(palette().dark().color());
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
