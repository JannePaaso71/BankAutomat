#include "chooseaccount.h"
#include "ui_chooseaccount.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

ChooseAccount::ChooseAccount(QWidget *parent, RESTClient * rc) :
    UiTemplate(parent),
    ui(new Ui::ChooseAccount),
    pRESTClient(rc)
{
    ui->setupUi(this);

    connect(this, SIGNAL(OkButtonPushed()),
            this, SLOT(OkButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_4Pushed()),
            this, SLOT(CreditButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_8Pushed()),
            this, SLOT(DebitButtonHandler()));
    connect(this, SIGNAL(BankTimerTicked()),
            this, SLOT(BankTimeHandler()));

    FetchAccountType();
}

ChooseAccount::~ChooseAccount() {
    delete ui;
}

void ChooseAccount::FetchAccountType(){
    auto url = QString("/atm/account/query_accounts");
    pRESTClient->makeRequest(RESTClient::Method::GET, url, this, [&](QNetworkReply *reply) {
        auto response = reply->readAll();
        auto json = QJsonDocument::fromJson(response.toStdString().c_str());
        QString replyCardType = json.object().value("account2_type").toString();
        qDebug() << "ChooseAccount" << replyCardType;
        if (replyCardType=="credit"){
            qDebug() << "Choose account debit account mode";
            SelectAction();
        }
        else{
            qDebug() << "Choose account debit account mode";
            emit AccountChosen(AccountTypes::DEBIT);
            emit nextState(States::SELECT_ACTION);
        }
        reply->deleteLater();
    });
}

void ChooseAccount::SelectAction(){
        textStyle =     textStyle = "<style> div {color:rgb(20, 20, 190); padding : 50px; text-align:right; margin-top: 10px; margin-right: 30px; margin-left: 30px;}  p {font-size:1px} h7 {paddin:30px; font-size:30 px} </style>";


        prompt(textStyle + "<div><p></p></div><div><h7><div>Debit<br><br><br><br><br>Credit<h7></div>");
}
void ChooseAccount::OkButtonHandler() {
}


void ChooseAccount::CreditButtonHandler(){
    // emit ChooseAccountReady();
        qDebug() << "CreditButtonHandler()";
    emit AccountChosen(AccountTypes::CREDIT);
    emit nextState(States::SELECT_ACTION);
}
void ChooseAccount::DebitButtonHandler(){
    // emit ChooseAccountReady();
    qDebug() << "DebitButtonHandler()";
    emit AccountChosen(AccountTypes::DEBIT);
    emit nextState(States::SELECT_ACTION);
}

