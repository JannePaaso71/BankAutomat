#include "editcard.h"
#include "ui_editcard.h"

EditCard::EditCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCard)
{
    ui->setupUi(this);
}

EditCard::~EditCard()
{
    delete ui;
}


void EditCard::on_CreateNewCard_clicked()
{
/*
    //auto url = restProtocol + "://" + restHost + ":" + restPort + restPrependPath + "/login/login_card";
    auto content = "{\"id\":" + id + ", \"pin\": " + "\"" + pin + "\"" "}";
    qDebug() << "authenticateTeller() kutsuttu.";
    auto path = QString("/login/login_operator");
    makeRequest(Method::POST, path, this, [this](QNetworkReply *reply) {
        auto response = reply->readAll();
        auto json = QJsonDocument::fromJson(response.toStdString().c_str());
        qDebug() << "auth: Setting restToken.";
        restToken = json.object().value("access_token").toString().toStdString().c_str();
        // Trying out single shot connections.
        // disconnect(this, SIGNAL(finished(QNetworkReply *)), 0, 0);
        restToken.isEmpty() ? emit authenticated(false) : emit authenticated(true);
        reply->deleteLater();
        }, &content);
*/
}


void EditCard::on_Deletecard_clicked()
{
    /*
    //auto url = restProtocol + "://" + restHost + ":" + restPort + restPrependPath + "/login/login_card";
    auto content = "{\"id\":" + id + ", \"pin\": " + "\"" + pin + "\"" "}";
    qDebug() << "authenticateTeller() kutsuttu.";
    auto path = QString("/login/login_operator");
    makeRequest(Method::POST, path, this, [this](QNetworkReply *reply) {
        auto response = reply->readAll();
        auto json = QJsonDocument::fromJson(response.toStdString().c_str());
        qDebug() << "auth: Setting restToken.";
        restToken = json.object().value("access_token").toString().toStdString().c_str();
        // Trying out single shot connections.
        // disconnect(this, SIGNAL(finished(QNetworkReply *)), 0, 0);
        restToken.isEmpty() ? emit authenticated(false) : emit authenticated(true);
        reply->deleteLater();
        }, &content);
*/
}

