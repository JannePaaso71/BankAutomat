#ifndef EDIT_CARD__H
#define EDIT_CARD__H

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
class Edit_Card_;
}

class Edit_Card_ : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_Card_(QWidget *parent = nullptr);
    ~Edit_Card_();
    short state = 0;

private slots:


    void on_pushButtonCreateNewCard_clicked();
    void on_CreateNewCard_SLOT();
    void on_buttonEditCard_clicked();
    void on_pushButtonDeletecard_clicked();   
    void on_Deletecard_SLOT();
    void on_buttonSave_clicked();
    void on_buttonCancel_clicked();
    void on_pushBack_clicked();



private:
    Ui::Edit_Card_ *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString owner_id;
    QString customer_id;
    QString card_id;
    QString accountId;
    QString pin;
    RESTClient* p_RESTClient;
};

#endif // EDIT_CARD__H
