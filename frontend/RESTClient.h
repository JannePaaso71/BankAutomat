//
// Created by mkuja on 13.11.2023.
//

#ifndef FRONTEND_NEW_RESTCLIENT_H
#define FRONTEND_NEW_RESTCLIENT_H

#include <QtNetwork/QNetworkAccessManager>
#include <functional>
#include "AccountTypes.h"
#include "settings.h"

class RESTClient : public QNetworkAccessManager {
Q_OBJECT

public:
    RESTClient(QObject *parent);

    virtual ~RESTClient() override;

    enum Method {
        GET, POST, PUT, DELETE
    };

    /**
     * @brief makeRequest Is used to make a request.
     * @param method Is the enum RESTClient::Method.
     * @param url For example "http://localhost:3000/"
     * @param receiver Is the receiver object of the Qt signal.
     * @param callback Is a lambda expression. Eg. [this](auto reply){doSomething();}
     * @param body If the request has a body (POST or PUT), this is it.
     */
    template<typename T>
    void makeRequest(Method method, QString &urlPath, T *receiver,
                     std::function<void (QNetworkReply *)> callback,
                     QString *body = nullptr) {
        auto cs = Settings::getInstance()->value("connectionString").toString();
        auto url_ = QUrl(cs + urlPath);
        qDebug() << "Rest token: " << restToken;
        auto request = QNetworkRequest(url_);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        if (!restToken.isEmpty()) {
            qDebug() << "Adding Authorization header.";
            auto bearer = std::string("Bearer ");
            request.setRawHeader("Authorization", QByteArray::fromStdString(bearer) + restToken);
        }
        QByteArray content = "";
        if (body) {
            content = body->toStdString().c_str();
        }

        switch (method) {
        case GET:
            connect(this, &QNetworkAccessManager::finished,
                    receiver, callback,
                    Qt::ConnectionType::SingleShotConnection);
            get(request);
            break;
        case POST:
            connect(this, &QNetworkAccessManager::finished,
                    receiver, callback,
                    Qt::ConnectionType::SingleShotConnection);
            post(request, content);
            break;
        case PUT:
            connect(this, &QNetworkAccessManager::finished,
                    receiver, callback,
                    Qt::ConnectionType::SingleShotConnection);
            put(request, content);
            break;
        case Method::DELETE:
            connect(this, &QNetworkAccessManager::finished,
                    receiver, callback,
                    Qt::ConnectionType::SingleShotConnection);
            deleteResource(request);
            break;
        default:
            qDebug() << "Unexpected execution path: RESTClient::makeRequest";
            break;
        }
    }


    /**
     * Authenticates card user.
     *
     * Signals authenticated(bool) after receiving response from the backend.
     * @param id
     * @param pin
     * @return
     */
    void authenticateCard(QString &id, QString &pin);


    /**
     * Requests the card typy debit/debit + credit from datatabase.
     *
     * Signals authenticated(bool) after receiving response from the backend.
     */
    void RequestCardType(AccountTypes& ct);


signals:
    void authenticated(bool);
    void responseCardType(AccountTypes reply);


private:
    QString restProtocol;
    QString restHost;
    QString restPort;
    QString restPrependPath;
    QString restAuthenticationToken;

    QByteArray restToken;
};


#endif //FRONTEND_NEW_RESTCLIENT_H
