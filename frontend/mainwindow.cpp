#include "finished.h"
#include "mainwindow.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qnetworkreply.h"
#include "selection.h"
#include "signin.h"
#include "ui_mainwindow.h"
#include "withdrowal.h"
#include <qlayout.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pRESTClient = new RESTClient (this);

    // Start Sign In.
    myActiveWidget = nullptr;
    choose_state(States::SIGNIN);
}

MainWindow::~MainWindow() {
    delete ui;
    delete pRESTClient;
}

void MainWindow::AccountTypeSetterSlot(AccountTypes ac) {
    this->chosenAccount = ac;
    qDebug() << "chosenAccount: " << chosenAccount;
}

void MainWindow::choose_state(States state) {
    qDebug()<< "States" << state;
    UiTemplate * tmp =nullptr;
    switch(state) {


    case States::SIGNIN:
        if (myActiveWidget) {
            delete myActiveWidget;
        }
       myActiveWidget = new SignIn(this, pRESTClient);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::CHOOSE_ACCOUNT:
       tmp = myActiveWidget;
       myActiveWidget = new ChooseAccount(this, pRESTClient);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       connect(myActiveWidget,SIGNAL(AccountChosen(AccountTypes)),
               this, SLOT(AccountTypeSetterSlot(AccountTypes)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::SELECT_ACTION:
       tmp = myActiveWidget;
       myActiveWidget = new SelectAction(this);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::SALDO:
       tmp = myActiveWidget;
       myActiveWidget = new Saldo(this, pRESTClient, chosenAccount);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::TRANSACTIONS:
       tmp = myActiveWidget;
       myActiveWidget = new Transactions(this, pRESTClient, chosenAccount);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::WITHDRAW:
       tmp = myActiveWidget;
       myActiveWidget = new Withdrowal(this, pRESTClient, chosenAccount);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;


    case States::FINISHED:
       tmp = myActiveWidget;
       myActiveWidget = new Finished(this);
       connect(myActiveWidget,SIGNAL(nextState(States)),
               this, SLOT(choose_state(States)), Qt::SingleShotConnection);
       delete tmp;
       this->layout()->addWidget(myActiveWidget);
       break;
    }
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    QLinearGradient linearGradient(QPointF(200,100), QPointF(50,300));
    linearGradient.setColorAt(0, QColor(230,236,246,200));
    linearGradient.setColorAt(0.5, QColor(220,224,234,200));
    linearGradient.setColorAt(1, QColor(215,224,255,200));
    QRect rectangle (75,75,810,280);
    painter.fillRect(rectangle,linearGradient);
    painter.drawRoundedRect(rectangle, 20.0, 15.0);
}
