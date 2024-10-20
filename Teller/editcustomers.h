#ifndef EDITCUSTOMERS_H
#define EDITCUSTOMERS_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
//#include <QJsonObject>
//#include <string>
//#include <iostream>
#include <QDialog>
#include "RESTClient.h"
#include "ui_editcustomers_.h"
#include <QtNetwork/QNetworkAccessManager>
#include "settings.h"
//#include <functional>
//#include "AccountTypes.h"


namespace Ui {
class EditCustomers;
}

class EditCustomers : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomers(QWidget *parent, RESTClient*);
    ~EditCustomers();
    short state = 0;

signals:
    void openMenu();

private slots:
    void on_CreateNewCustomer_clicked();
    void CreateNewCustomerHandler (QNetworkReply *reply);
    void on_ModifyCustomer_clicked();
    void ModifyCustomerHandler (QNetworkReply *reply);
    void on_Save_clicked();
    void SaveHandler (bool);
    void on_Back_clicked();

    void on_buttonCancel();

private:
    Ui::EditCustomers *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString id;
    QString lastname;
    QString firstname;
    QString newID; //setter vai getter?
    RESTClient* p_RESTClient;
};

#endif // EDITCUSTOMERS_H
