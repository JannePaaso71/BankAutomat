#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent, RESTClient * rc) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    connect(ui->buttonLogIn, SIGNAL(clicked(bool)),
            this, SLOT(logInSlot()));
//    connect(ui->buttonLogIn, SIGNAL(clicked(bool)),
//            this, SLOT(on_LogIn_clicked()));
    obj_RESTClient = rc;
    qDebug() << "login.cpp: constructor";
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_LogIn_clicked() //tyo aikainen kaytto
{
    qDebug() << "login.cpp:lofIn_clicked";
    o_TellerMenu = new TellerMenu(this, obj_RESTClient);
    o_TellerMenu->show();
    this->hide();
}

void LogIn::logInSlot()
{
    qDebug() << "login.cpp:logInSLOT";
    QString idLogin = ui->lineEdit_id->text();
    qDebug()<<"idLogin"<<idLogin;
    QString pinLogin = ui->lineEdit_pin->text();
    qDebug()<<"pin"<<pinLogin;
    qDebug()<<"client: "<<obj_RESTClient;
    qDebug()<<"authenticated: "<<&RESTClient::authenticated;
    qDebug()<<"this: "<<this;
    connect(obj_RESTClient, &RESTClient::authenticated, this, [=](bool success){
        if(success){
            qDebug()<<"Success";
            o_TellerMenu = new TellerMenu(this, obj_RESTClient);
            o_TellerMenu->show();
        } else {
            qDebug()<<"Not success";
            ui->lineEditInfo->setText("Log in failed");
        }
        }, Qt::SingleShotConnection);
    obj_RESTClient->authenticateTeller(idLogin, pinLogin);
}



