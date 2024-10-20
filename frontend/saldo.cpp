#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <Actions.h>
#include "saldo.h"
#include "ui_saldo.h"

Saldo::Saldo(QWidget *parent, RESTClient* rc, AccountTypes ac) :
    UiTemplate(parent),
    ui(new Ui::Saldo),
    chosenAccountType(ac)
{
    ui->setupUi(this);
    restClient = rc;

    connect(pBankTimer,SIGNAL(sendTimerUpdate()),
            this,SLOT(BankTimeHandler()));
    connect(this, SIGNAL(OkButtonPushed()),
            this, SLOT(OkButtonHandler()));

    fetchSaldo();
}

Saldo::~Saldo(){
    delete ui;
}
void Saldo::fetchSaldo(){
    auto url = QString("/atm/account/check_balance/")
               + ((chosenAccountType == AccountTypes::DEBIT) ? "debit" : "credit");
    restClient->makeRequest(RESTClient::Method::GET, url, this, [this](QNetworkReply* reply){
        auto content = reply->readAll();
        qDebug() << "Saldo request reply body content: " << content;
        auto json = QJsonDocument::fromJson(content);
        QString saldo = json.object().take(QString("balance")).toString();
        qDebug() << "SALDO: " << saldo;
        if (chosenAccountType == AccountTypes::CREDIT) {
            QString creditLimit = json.object().take(QString("credit_limit")).toString();
            qDebug() << "CREDIT LIMIT: " << creditLimit;
            this->setCreditLimit(creditLimit.toDouble());
        }
        this -> saldo=saldo;
        this->ShowSaldo();

        reply->deleteLater();
    });
}
void Saldo::ShowSaldo(){
    textStyle = R"(<style> div {line-height: 120%; color:rgb(20, 20, 190); padding : 0px; text-align:center; margin-right: 20px;
                margin-left: 20px;}  p {font-size:1px} h7 {font-size:28px} </style>)";
    if (chosenAccountType == AccountTypes::CREDIT) {
        prompt(textStyle + "<div><h7><br>Tilin käyttövara on <br>" + QString::number(creditLimit + saldo.toDouble(), 'f', 2) + " euroa<br>jatka painamalla ok</div></h7>");
    } else {
        prompt(textStyle + "<div><h7><br>Tilin saldo on <br>" + saldo + " euroa <br>jatka painamalla ok</div></h7>");
    }
}
void Saldo::OkButtonHandler(){
    emit nextState(States::CHOOSE_ACCOUNT);
}
void Saldo::setCreditLimit(double cl){
    creditLimit = cl;
}
