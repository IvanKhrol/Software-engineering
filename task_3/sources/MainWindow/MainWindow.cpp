#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle(APP_NAME);
  
  auto centralWidget = new QWidget();
  setCentralWidget(centralWidget);
  auto mainLayout = new QGridLayout(centralWidget);

  auto testLabel  = new QLabel("Здесь будет Polygon Widget");
  mainLayout->addWidget(testLabel, 0, 0, 2, 2, Qt::AlignCenter);

  
  nSpinBox = new QSpinBox();
  nSpinBox->setMinimum(3);
  nSpinBox->setMaximum(N_MAX_COUNT);
  nSpinBox->setSingleStep(1);
  auto nLabel = new QLabel(QString("&N"));
  nLabel->setBuddy(nSpinBox);
  
  

  positionLineEdit = new QLineEdit();
  positionLineEdit->setPlaceholderText(QString(tr("Add point positions in format: (x1, y2), (x2, y2) ...")));
  positionLineEdit->setMinimumSize(fontMetrics().averageCharWidth() * positionLineEdit->placeholderText().size(), 
                                   fontMetrics().height()); 
  auto positionLabel = new QLabel(QString(tr("&Point positions")));
  positionLabel->setBuddy(positionLineEdit);

  auto drawButton = new QPushButton(QString(tr("&Draw")));
  connect(drawButton, &QPushButton::clicked, this, &MainWindow::drawPolygonWidget);

  mainLayout->setColumnStretch(1, 1);
  mainLayout->addWidget(nLabel, 3, 0, Qt::AlignRight);
  mainLayout->addWidget(nSpinBox, 3, 1, Qt::AlignLeft);
  mainLayout->addWidget(positionLabel, 4, 0, Qt::AlignRight);
  mainLayout->addWidget(positionLineEdit, 4, 1, Qt::AlignLeft);
  mainLayout->addWidget(drawButton, 5, 0, 1, 2, Qt::AlignCenter);


  // add ctrl+q shortcut for exit
  auto actionClose = new QAction();
  actionClose->setShortcut(QKeySequence::Quit);
  addAction(actionClose);
  QObject::connect(actionClose, &QAction::triggered, this, &QCoreApplication::quit);
}

MainWindow::~MainWindow() {}

void MainWindow::drawPolygonWidget() const {
  int n = nSpinBox->text().toInt();
  QString base_regex = "(\\s*\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\))\\s*";
  QString out_regex  = "^";

  for(int i = 0; i < n - 1; ++i) {
      out_regex += base_regex + ",\\s*";
  }
  out_regex += base_regex + "$";

  QRegularExpression re(out_regex);
  qDebug() << re.match(positionLineEdit->text()).hasMatch();
}
