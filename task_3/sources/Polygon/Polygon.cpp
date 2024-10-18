#include "Polygon.hpp"

//========================================Vertex========================================

Vertex::Vertex(int x, int y): x(x), y(y) {
  qDebug() << DPREFIX << QString("Create vertex:") << this;
}

QDebug operator<<(QDebug debug, const Vertex &obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << "Vertex(" << "x = " << obj.x << ";" << " y = " << obj.y << ")";
  return debug;
}

QDebug operator<<(QDebug debug, const Vertex *obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << *obj;
  return debug;
}


//========================================Edge========================================

Edge::Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2, QColor color): 
          v1(v1), v2(v2), color(color) {
  qDebug() << DPREFIX << QString("Create edge:") << this;
}

QDebug operator<<(QDebug debug, const Edge &obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << "Edge(" << "v1: " << obj.v1.lock().get() << ";" 
                  << " v2: " << obj.v2.lock().get() 
                  << " color = " << obj.color << ")";
  return debug;
}

QDebug operator<<(QDebug debug, const Edge *obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << *obj;
  return debug;
}

//========================================Polygon========================================

void Polygon::addVertex(int x, int y) {
  vertices.push_back(std::make_shared<Vertex>(x, y));
}

void Polygon::createEdges(const QVector<QColor> colors) {
  for(size_t i = 0; i < vertices.size(); ++i) {
    size_t j = (i + 1) % vertices.size();
    auto edge = std::make_shared<Edge>(vertices[i], vertices[j], colors.at(i)); // property set to 0 for now
    edges.push_back(edge);
    vertices[i]->adjacentEdges.push_back(edge);
    vertices[j]->adjacentEdges.push_back(edge);
  }  
}
bool Polygon::isContain(const QPoint &pos) const {
  QPolygon scanPolygon;
  for(const auto &v: vertices){
    scanPolygon.append(QPoint(v->x, v->y));
  }
  return scanPolygon.containsPoint(pos, Qt::OddEvenFill);
}

QDebug operator<<(QDebug debug, const Polygon &obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << "Polygon(";
  for(int i = 0; i < obj.edges.size(); ++i) {
    debug.nospace() << "\n\tedge " << i << ": "  << obj.edges.at(i).get(); 
  }
  debug.nospace() << ")";

  return debug;
}

QDebug operator<<(QDebug debug, const Polygon *obj) {
  QDebugStateSaver saver(debug);
  debug.nospace() << *obj;
  return debug;
}

