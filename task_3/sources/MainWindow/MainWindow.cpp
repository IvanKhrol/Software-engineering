#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), 
                        mainLayout(new QGridLayout), renderArea(new RenderArea(this)),
                        nSpinBox(new QSpinBox), positionLineEdit(new QLineEdit),
                        dialogEditor(new Editor) {
  setWindowTitle(APP_NAME);
  setFont(QFont("Times", 16));

  int margin = 25;
  setContentsMargins(margin, margin, margin, margin);
  setCentralWidget(renderArea.get());

  drawPolygon();

  connect(renderArea.get(), &RenderArea::show_editor, 
          this, &MainWindow::drawPolygon);

  connect(renderArea.get(), &RenderArea::sendPolygon,
          [this](const Polygon *p, int p_num, const QSize &size) {
            dialogEditor.get()->getPolygon(p, p_num, size);
          });

  // add ctrl+q shortcut for exit
  auto actionClose = new QAction();
  actionClose->setShortcut(QKeySequence::Quit);
  addAction(actionClose);
  QObject::connect(actionClose, &QAction::triggered, this, &QCoreApplication::quit);
}

void MainWindow::drawPolygon() {
  qDebug() << DPREFIX"drawPolygon";
  if(dialogEditor->isNew) {
    dialogEditor.reset(new Editor());
  }

  if (dialogEditor->exec() == QDialog::Accepted) {
    QStringList     vertices  = dialogEditor->getPoints();
    QVector<QColor> colors    = dialogEditor->getColors();
    int p_num = dialogEditor->getPolygonNumber();
    
    renderArea.get()->setPolygon(vertices, colors, p_num);
  }
}

MainWindow::~MainWindow() = default;