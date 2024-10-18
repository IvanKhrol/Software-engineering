#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <QPushButton>
#include <QScopedPointer>
#include <QCoreApplication>

#include "Polygon/Polygon.hpp"

#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Editor Debug: "


class Editor : public QDialog {
  Q_OBJECT

public:
  explicit Editor(QWidget *parent = nullptr);

  QStringList getPoints() const;
  QVector<QColor> getColors() const;
  int getPolygonNumber();

  bool isNew = true;

public slots:
  void getPolygon(const Polygon *, int , const QSize &);

private slots:
  void onNValueChanged(int newValue);


private:
  void createPointFields(int count = 3, int cur = 0);

  void deleteLayout(int newV, int cur);

  QScopedPointer<QSpinBox>    nSpinBox;
  QScopedPointer<QVBoxLayout> pointsLayout;
  QList<QSpinBox*>            pointSpinBoxes;
  QList<QPushButton*>         colorButtons;

  // bool isFromPolygon = false;
  int polygonNumber = -1;
  int renderWidth = 500, renderHeight = 500;
};

#endif // EDITOR_HPP