#ifndef __renderarea_hpp__
#define __renderarea_hpp__

#include <QBrush>
#include <QPen>
#include <QList>
#include <QWidget>
#include <QMouseEvent>

#include "Polygon/Polygon.hpp"

#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Render Area Debug: "

class RenderArea : public QWidget {
  Q_OBJECT

public:
  explicit RenderArea(QWidget *parent = nullptr);
  ~RenderArea();

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void setPolygon(const QStringList vertices, const QVector<QColor> colors, int polygonNumber);

signals:
  void show_editor();
  void sendPolygon(const Polygon *, int , const QSize &);

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent* event) override;

private:
  QList<Polygon*> polygons;
};

#endif // __renderarea_hpp__
