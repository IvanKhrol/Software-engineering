#include "Editor.hpp"

Editor::Editor(QWidget *parent) : QDialog(parent),
               nSpinBox(new QSpinBox), pointsLayout(new QVBoxLayout){
  setWindowTitle("Ввод полигона");
  qDebug() << DPREFIX"Create new Editor";
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  QHBoxLayout *nLayout = new QHBoxLayout();
  nLayout->addWidget(new QLabel("Количество вершин:"));
  nSpinBox->setMinimum(3); 
  nSpinBox->setValue(3); 
  nLayout->addWidget(nSpinBox.get());
  mainLayout->addLayout(nLayout);

  // Вертикальный layout для полей вершин
  createPointFields();
  mainLayout->addLayout(pointsLayout.get());

  // Кнопка случайных координат
  QPushButton *randButton = new QPushButton("Установить случайные координаты");
  mainLayout->addWidget(randButton);

  srand(time(0));
  connect(randButton, &QPushButton::clicked, [this]() {
      for(int i = 0; i < pointSpinBoxes.size(); ++i) {
        if(i % 2 == 0) {
          pointSpinBoxes.at(i)->setValue(1 + rand() % renderWidth);
        } else {
          pointSpinBoxes.at(i)->setValue(1 + rand() % renderHeight);
        }
      }
  });

  // Кнопка подтверждения
  QPushButton *okButton = new QPushButton("OK");
  connect(okButton, &QPushButton::clicked, this, &Editor::accept);
  mainLayout->addWidget(okButton);

  // Подключение сигнала изменения значения nSpinBox к слоту
  connect(nSpinBox.get(), QOverload<int>::of(&QSpinBox::valueChanged), 
          this, &Editor::onNValueChanged);
}

QStringList Editor::getPoints() const {
  QStringList points;
  for (int i = 0; i < pointSpinBoxes.size() / 2; ++i) {
    int x = pointSpinBoxes[i * 2]->value();
    int y = pointSpinBoxes[i * 2 + 1]->value();
    points.append(QString("%1;%2").arg(x).arg(y));
  }
  return points;
}

QVector<QColor> Editor::getColors() const {
  QVector<QColor> colors;
  for (int i = 0; i < colorButtons.size(); ++i) {
    colors.append(colorButtons[i]->palette().color(QPalette::Button));
  }
  return colors;
}

int Editor::getPolygonNumber() {
  isNew = true;
  qDebug() << DPREFIX"p_num ==: " << polygonNumber;
  return polygonNumber;
}

void Editor::onNValueChanged(int newValue) {
  int curValue = colorButtons.size();
  int diff = 0;
  if(newValue > curValue) {
    diff = newValue - curValue;
    createPointFields(diff, curValue);
  } else {
    // diff = curValue - newValue;
    deleteLayout(newValue, curValue);
  }
  // Перерисовать диалог
  update();
}

void Editor::getPolygon(const Polygon *polygon, int p_num, const QSize &size) {
  qDebug() << DPREFIX"getPolygon";
  renderWidth   = size.width();
  renderHeight  = size.height();
  qDebug() << DPREFIX"p_num ==: " << p_num;
  polygonNumber = p_num;

  nSpinBox->blockSignals(true);
  nSpinBox->setValue(polygon->edges.size());
  nSpinBox->blockSignals(false);

  deleteLayout(0, colorButtons.size());
  createPointFields(polygon->edges.size(), 0);
  for(int i = 0; i < pointSpinBoxes.size(); i += 2) {
    pointSpinBoxes.at(i)->setValue(polygon->vertices.at(i/2)->x); 
    pointSpinBoxes.at(i+1)->setValue(polygon->vertices.at(i/2)->y);
    colorButtons.at(i/2)->setStyleSheet("background-color: " + 
                                        polygon->edges.at(i/2)->color.name());
  }

  isNew = false;
}

// Создание новых полей
void Editor::createPointFields(int count, int cur) {
  qDebug() << DPREFIX << "createPointFields: " << count << cur;
  for (int i = cur; i < cur + count; ++i) {
    QHBoxLayout *pointLayout = new QHBoxLayout();

    QLabel *xLabel = new QLabel("x" + QString::number(i + 1) + ":");
    pointLayout->addWidget(xLabel);
    QSpinBox *xSpinBox = new QSpinBox();
    xSpinBox->setMinimum(0); 
    xSpinBox->setMaximum(renderWidth);
    pointLayout->addWidget(xSpinBox);

    QLabel *yLabel = new QLabel("y" + QString::number(i + 1) + ":");
    pointLayout->addWidget(yLabel);
    QSpinBox *ySpinBox = new QSpinBox();
    ySpinBox->setMinimum(0); // Задайте желаемые ограничения
    ySpinBox->setMaximum(renderHeight); 
    pointLayout->addWidget(ySpinBox);

    // Кнопка для выбора цвета
    QPushButton *colorButton = new QPushButton("Выбрать цвет");
    colorButton->setStyleSheet("background-color: rgb(0, 0, 0);"); 
    connect(colorButton, &QPushButton::clicked,
    [this, colorButton]() {
      QColor color = QColorDialog::getColor(Qt::white, this, "Выбрать цвет");
      if (color.isValid()) {
        colorButton->setStyleSheet("background-color: " + color.name());
      }
    });    
    pointLayout->addWidget(colorButton);

    pointsLayout->addLayout(pointLayout);
    pointSpinBoxes.append(xSpinBox);
    pointSpinBoxes.append(ySpinBox);
    colorButtons.append(colorButton);
  }
}

// Очистка существующих лишних полей
void Editor::deleteLayout(int newV, int cur) {
  qDebug() << DPREFIX"deleteLayout start: " 
    << pointSpinBoxes.size() << colorButtons.size() 
    << pointsLayout->count();
    
  for(int i = cur - 1; i >= newV; --i) {
    qDebug() << DPREFIX"Start clear: " << i;
    QLayout *pointLayout = pointsLayout->takeAt(i)->layout();
    auto item = pointLayout->takeAt(0);
    while(item != nullptr) {
      delete item->widget();
      delete item;
      item = pointLayout->takeAt(0);
    }
    delete pointLayout;
  }
  qDebug() << DPREFIX"colorButtons.size: " << colorButtons.size();
  colorButtons.resize(newV);
  qDebug() << DPREFIX"pointSpinBoxes.size: " << pointSpinBoxes.size();
  pointSpinBoxes.resize(newV * 2);

  qDebug() << DPREFIX"deleteLayout end: " << 
    pointSpinBoxes.size() << colorButtons.size() 
    << pointsLayout->count();
}