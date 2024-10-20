#ifndef LOGIN_H
#define LOGIN_H

#include "tellermenu.h"

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "RESTClient.h"

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr) = delete;
    LogIn(QWidget *parent, RESTClient * rc);
    ~LogIn();
    TellerMenu *o_TellerMenu;



private slots:
    void on_LogIn_clicked();
    void logInSlot ();

private:
    Ui::LogIn *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString password;
    QByteArray token;
    RESTClient* obj_RESTClient;
};

#endif // LOGIN_H
