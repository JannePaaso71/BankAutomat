#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QNetworkReply>
#include "transactions.h"
#include "ui_transactions.h"

Transactions::Transactions(QWidget *parent, RESTClient* rc, AccountTypes ac):
    UiTemplate(parent),
    ui(new Ui::transactions),
    chosenAccountType(ac),
    restClient(rc)

{
    ui->setupUi(this);

    connect(this, SIGNAL(leftEmptyButton_8Pushed()),
            this, SLOT(previousPage()));
    connect(this, SIGNAL(rightEmptyButton_8Pushed()),
            this, SLOT(nextPage()));
    connect(this, SIGNAL(rightEmptyButton_4Pushed()),
            this, SLOT(goBack()));


    getPage(1);
}

Transactions::~Transactions()
{
    delete ui;
}


void Transactions::getPage(int page_)
{
    auto path = QString("/atm/transactions/") + (chosenAccountType == AccountTypes::DEBIT ? "debit/" : "credit/") + QString::number(page_);
    restClient->makeRequest(RESTClient::Method::GET, path, this, [this](QNetworkReply *reply){
        auto data = reply->readAll();
        auto json = QJsonDocument::fromJson(data);
        QJsonArray lala = json.array();
        emptyPageIndex=lala.size();
        QString style = R"( <style>
                            div {margin-left: 25px;}
                            th {color: rgb(20, 20, 190); font-size: 18px; font-weight: normal;}
                            h5 { color: rgb(20, 20, 190); font-size: 18; font-weight: normal; text-align: right; margin-right: 25px;line-height: 90%;}

                            table {width: 100%; padding: 0px; }
                            p {margin-left: 0px; margin-top: 0px; padding-top: 0px; color: rgb(20,20,190); font-size: 17px; line-height: 50%;}
                            td {font-size: 16px; color: rgb(20, 20, 190); margin-right: 35px;text-align: left}
                            span {color: rgb(20,20, 190); font-size: 18; margin-right: 15px; text-align: right;}
                        </style>)";
        auto text1 = QString(style + R"(
                            <div><table><tr><th id=uudemmat><h5>Uudemmat<h5></th><th><h5>&nbsp;&nbsp;&nbsp;&nbsp;Vanhemmat</h5></th></tr></table>)");
        for (int i =0; i<5; i ++) {
            if (i < emptyPageIndex){
                auto la=lala[i];
                QJsonObject obj = la.toObject();
                text1.append("<p>");
                text1.append(obj.value("datetime").toString());
                auto amount = obj.value("amount").toInt();
                text1.append(amount > 0 ? "PANO&nbsp;&nbsp;&nbsp;" : " OTTO&nbsp;&nbsp;");
                text1.append(obj.value("amount").toString() + " euroa");
                text1.append("</p>");
            }
        else {
                text1.append(R"(<p>)");
                text1.append("*");
                text1.append("</p>");
            }
        }
        text1.append(R"(<h5 style="margin-top:25px;">Lopeta&nbsp;&nbsp;</h5>)");
        prompt(text1);
        reply->deleteLater();
    });
}

void Transactions::nextPage()
{
    if (! (emptyPageIndex < 5)) {getPage(++page);}
    qDebug() << "nextpage" << page;

}

void Transactions::previousPage()
{
    qDebug() << "previouspage" << page;
    if (page > 1) {getPage(--page);}
    qDebug() << "previouspage" << page;
}

void Transactions::goBack()
{
    emit nextState(States::CHOOSE_ACCOUNT);
}

