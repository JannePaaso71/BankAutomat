//
// Created by mkuja on 13.11.2023.
//

#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include <iostream>
#include "settings.h"
#include "RESTClient.h"


RESTClient::~RESTClient() {

}


RESTClient::RESTClient(QObject *parent) :
        QNetworkAccessManager(parent) {}


void RESTClient::authenticateCard(QString &id, QString &pin) {
    //auto url = restProtocol + "://" + restHost + ":" + restPort + restPrependPath + "/login/login_card";
    auto content = "{\"id\":" + id + ", \"pin\": " + "\"" + pin + "\"" "}";
    qDebug() << "authenticateCard() kutsuttu.";
    auto path = QString("/login/login_card");
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
}

void RESTClient::RequestCardType(AccountTypes& ct)
{
    auto url = QString("/atm/account/query_accounts");
    makeRequest(Method::GET, url, this, [&](QNetworkReply *reply) {
        auto response = reply->readAll();
        auto json = QJsonDocument::fromJson(response.toStdString().c_str());
        auto replyCardType = json.object().value("account2_type").toString();
        if (replyCardType=="credit"){
            ct = AccountTypes::CREDIT;
            emit responseCardType(ct);
        }
        else{
            ct = AccountTypes::DEBIT;
            emit responseCardType(ct);
        }
        reply->deleteLater();
    });
}



