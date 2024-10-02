#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setup_MainWindow();
}

MainWindow::~MainWindow() { 
  delete ui; 
}

void MainWindow::setup_MainWindow() {
  setWindowTitle(APP_NAME);
  
  setCentralWidget(ui->layoutWidget);
  mouseHandler = new MouseHandler;
  mouseHandler->hide();
  // mouseHandler->setDisabled(true);
  ui->mainLayout->addWidget(mouseHandler);


  connect(ui->go2MouseHandlerBtn, &QPushButton::clicked, this, &MainWindow::show_MouseHandler);
  connect(ui->go2MultimediaBtn,   &QPushButton::clicked, this, &MainWindow::show_Multimedia);
}

void MainWindow::show_MouseHandler() const {
  if(false) {
    //TODO: hide Multimedia layout if it is show
  }

  if(mouseHandler->isHidden()) {
    
    mouseHandler->show();
  } else {
    mouseHandler->hide();
  }
}

void MainWindow::show_Multimedia() const {
  if(!mouseHandler->isHidden()) {
    mouseHandler->hide();
  }

  if(false) {
    //TODO: show and hide Multimedia layout
  }
}