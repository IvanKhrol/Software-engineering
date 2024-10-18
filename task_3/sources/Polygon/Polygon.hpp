#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPainterPath>
#include <QMetaType>
#include <QColor>

#include <vector>
#include <memory>

#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Polygon Debug: "

class Vertex;
class Edge;

//========================================Vertex========================================

class Vertex {
public:
  Vertex(int x, int y);
  
  int x, y;
  std::vector<std::weak_ptr<Edge>> adjacentEdges;
};

QDebug operator<<(QDebug debug, const Vertex &obj);
QDebug operator<<(QDebug debug, const Vertex *obj);

//========================================Edge========================================

class Edge {
public:
  Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2, QColor color);

  std::weak_ptr<Vertex> v1, v2;
  QColor color;
};

QDebug operator<<(QDebug debug, const Edge &obj);
QDebug operator<<(QDebug debug, const Edge *obj);

//========================================Polygon========================================

class Polygon {
public:
  Polygon() = default;
  ~Polygon() = default;
  std::vector<std::shared_ptr<Vertex>> vertices;
  std::vector<std::shared_ptr<Edge>> edges;

  void addVertex(int x, int y);
  void createEdges(const QVector<QColor> colors);

  bool isContain(const QPoint &pos) const;
};
  QDebug operator<<(QDebug debug, const Polygon &obj);
  QDebug operator<<(QDebug debug, const Polygon *obj);

#endif //POLYGON_HPP