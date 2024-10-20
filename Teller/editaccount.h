#ifndef EDITACCOUNT_H
#define EDITACCOUNT_H

#include <QDialog>
#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDialog>
#include "RESTClient.h"
#include "ui_editcustomers_.h"
#include <QtNetwork/QNetworkAccessManager>
#include "settings.h"

namespace Ui {
class EditAccount;
}

class EditAccount : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccount(QWidget *parent, RESTClient*);
    ~EditAccount();
    short state = 0;

private slots:
    void on_buttoNewAccount_clicked();
    void on_buttonExistAccount_clicked();
    void on_buttonSave_clicked();
    void on_buttonBack_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::EditAccount *ui;
    RESTClient* p_RESTClient;    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString amount;
    QString credit_limit;
    QString id_customer;
};

#endif // EDITACCOUNT_H
