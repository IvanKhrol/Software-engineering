#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->debugBtn, &QPushButton::clicked, [](){
        qDebug() << "DEBUG: " << "debug message from button";
    });

    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::send_text);
    ui->sendBtn->setCheckable(true);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::send_text() {
    QString text = ui->input_textEdit->toPlainText();
    if(ui->sendBtn->isChecked()) {
        qInfo() << "INFO: " << "button was pushed";
        ui->output_textEdit->setText(text);
    } else {
        qInfo() << "INFO: " << "button was unpushed";
    }

}
