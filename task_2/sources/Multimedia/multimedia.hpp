#ifndef __multimedia__hpp__ 
#define __multimedia__hpp__

#include <QWidget>
#include <QtGui>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>


#include <Multimedia/RenderArea/renderarea.hpp>

class Multimedia : public QWidget {
  Q_OBJECT

public:
  Multimedia(QWidget *parent = nullptr);
  ~Multimedia();
private slots:
  void shapeChanged();
  void penChanged();
  void brushChanged();

private:
  RenderArea *renderArea;

  QLabel *shapeLabel;
  QLabel *penWidthLabel;
  QLabel *penStyleLabel;
  QLabel *penCapLabel;
  QLabel *penJoinLabel;
  QLabel *brushStyleLabel;

  QComboBox *shapeComboBox;
  QSpinBox  *penWidthSpinBox;
  QComboBox *penStyleComboBox;
  QComboBox *penCapComboBox;
  QComboBox *penJoinComboBox;
  QComboBox *brushStyleComboBox;
  QCheckBox *antialiasingCheckBox;
};

#endif // __multimedia__hpp__