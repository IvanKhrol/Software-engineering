#ifndef __renderarea_hpp__
#define __renderarea_hpp__

#include <QBrush>
#include <QPen>
#include <QWidget>

class RenderArea : public QWidget {
  Q_OBJECT

public:
  enum Shape { Polygon, Rect, RoundedRect, Ellipse,  Path };

  explicit RenderArea(QWidget *parent = nullptr);

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

public slots:
  void setShape(Shape new_shape);
  void setPen(const QPen &new_pen);
  void setBrush(const QBrush &new_brush);
  void setAntialiased(bool new_antialiased);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Shape shape;
  QPen pen;
  QBrush brush;
  bool antialiased;
};

#endif // __renderarea_hpp__
