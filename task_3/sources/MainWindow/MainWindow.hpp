#ifndef __MainWindow_hpp_
#define __MainWindow_hpp_

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QAction>
#include <QSizePolicy>
#include <QScopedPointer>
#include <QDebug>

#include <vector>
#include <memory>

#include "RenderArea/RenderArea.hpp"
#include "Editor/Editor.hpp"

#ifdef DPREFIX
  #undef DPREFIX
#endif // DPREFIX
#define DPREFIX "Main Window Debug: "

#ifdef CPREFIX
  #undef CPREFIX
#endif // CPREFIX
#define CPREFIX "Main Window Error!!:\n\t"


#define APP_NAME "TASK 3"
#define N_MAX_COUNT 100

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QScopedPointer<QGridLayout> mainLayout;
  QScopedPointer<QSpinBox>    nSpinBox;
  QScopedPointer<QLineEdit>   positionLineEdit;
  QScopedPointer<RenderArea>  renderArea;
  QScopedPointer<Editor>      dialogEditor;

private slots:
  void drawPolygon();
};
#endif // __MainWindow_hpp_
