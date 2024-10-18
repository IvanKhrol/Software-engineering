#include "RenderArea.hpp"

#include <QPainter>
#include <QPainterPath>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

}

QSize RenderArea::minimumSizeHint() const { return QSize(500, 500); }
QSize RenderArea::sizeHint() const { return QSize(500, 500); }

void RenderArea::setPolygon(const QStringList vertices, 
                            const QVector<QColor> colors, 
                            int polygonNumber) {
  if(polygonNumber != -1) {
    qDebug() << DPREFIX"Change polygon: " << polygonNumber;
    delete polygons.takeAt(polygonNumber);
  }
  Polygon *poly = new Polygon;
  for(int i = 0; i < vertices.size(); ++i) {
    QString vert = vertices.at(i);
    QStringList coords = vert.split(";", Qt::SkipEmptyParts);
    qDebug() << DPREFIX << coords;
    poly->addVertex(coords.at(0).toInt(), 
                    coords.at(1).toInt());
  }
  poly->createEdges(colors);
  polygons.append(poly);
  qDebug() << DPREFIX << poly;
  update();
}

void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPen pen;
  pen.setWidth(4);
  painter.setPen(pen);

  painter.setRenderHint(QPainter::Antialiasing);

  painter.save();
  for(int i = 0; i < polygons.size(); ++i) {
    for(const auto& edge : polygons.at(i)->edges) {
      auto v1 = edge->v1.lock();
      auto v2 = edge->v2.lock();
      if (v1 && v2) {
        pen.setColor(edge->color);
        painter.setPen(pen);
        painter.drawLine(v1->x, v1->y, v2->x, v2->y);
      }
    }
  }
  painter.restore();


  painter.setRenderHint(QPainter::Antialiasing, true);
  int step = 50;
  int margin = 0;

  // Оси координат
  painter.setPen(Qt::black);
  painter.drawRect(QRect(0, 0, width(), height()));

  // // Сетка
  // painter.setPen(Qt::lightGray);
  // for (int i = step + margin; i < width(); i += step) {
  //     painter.drawLine(i, 0, i, height());
  // }
  // for (int i = step + margin; i < height(); i += step) {
  //     painter.drawLine(0, i, width(), i);
  // }

  // Подписи координат
  painter.setPen(Qt::black);
  QFont font = painter.font();
  font.setPointSize(8);
  painter.setFont(font);
  for (int i = step + margin; i < width(); i += step) {
      painter.drawText(i - 10, 15, QString::number(i)); 
  }
  for (int i = step + margin; i < height(); i += step) {
      painter.drawText(10, i + 5, QString::number(i)); 
  }
}

void RenderArea::mousePressEvent(QMouseEvent* event) {
	if(event->button() == Qt::LeftButton) {
    bool isClear = true; // Был ли в области нажатия полигон
    int up;
    // Проверка наличия полигона в позиции курсора
    for(int cur = 0; cur < polygons.size(); ++cur) {
      if(polygons.at(cur)->isContain(event->pos())) {
        up = cur;
        isClear = false;
      }
    }
    if(!isClear) {
      qDebug() << DPREFIX"is not clear";
      emit sendPolygon(polygons.at(up), up, size());
    }
    emit show_editor();
  }			
}


RenderArea::~RenderArea() = default;