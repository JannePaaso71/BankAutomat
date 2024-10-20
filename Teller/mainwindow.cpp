
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , obj_RESTClient(RESTClient(this))
{
    ui->setupUi(this);
    o_LogIn = new LogIn(this, &obj_RESTClient);
    o_LogIn->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

