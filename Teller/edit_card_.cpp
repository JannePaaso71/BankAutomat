#include "edit_card_.h"
#include "ui_edit_card_.h"

Edit_Card_::Edit_Card_(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Edit_Card_)
{
    ui->setupUi(this);
    ui->buttonCreateNewCard, SIGNAL(clicked(bool)), this, SLOT(on_pushButtonCreateNewCard_clicked());
    ui->buttonDeletecard, SIGNAL(clicked(bool)), this, SLOT(on_pushButtonDeletecard_clicked());
    ui->buttonSave, SIGNAL(clicked(bool)), this, SLOT(on_buttonSave_clicked());
    ui->buttonCancel, SIGNAL(clicked(bool)),this, SLOT(on_buttonCancel_clicked());
    ui->buttonBack, SIGNAL(clicked(bool)),this, SLOT(on_pushBack_clicked());
    ui->labelCustomerID->hide();
    ui->lineEditCustomerID->hide();

}

Edit_Card_::~Edit_Card_()
{
    delete ui;
}


void Edit_Card_::on_pushButtonCreateNewCard_clicked()
{
    ui->buttonDeletecard->hide();
    ui->buttonEditCard->hide();
    state = 1;
}

void Edit_Card_::on_CreateNewCard_SLOT()
{

}

void Edit_Card_::on_buttonEditCard_clicked()
{
    ui->buttonCreateNewCard->hide();
    ui->buttonDeletecard->hide();
    state = 2;
}

void Edit_Card_::on_pushButtonDeletecard_clicked()
{
    ui->buttonCreateNewCard->hide();
    ui->buttonEditCard->hide();
    state = 3;
}

void Edit_Card_::on_Deletecard_SLOT()
{

}


void Edit_Card_::on_buttonSave_clicked()
{
    if(state == 1){     //create
        ui->lineEditOwnerID->text();
        //ui->lineEditCustomerID->text();
        ui->lineEditCardType->text();
        ui->lineEditAccountId->text();
        ui->lineEditPinNumber->text();
        QJsonObject jsonObj;
        jsonObj.insert("pin", pin);
        jsonObj.insert("owner_id", owner_id);
        jsonObj.insert("accountId", accountId);
        //jsonObj.insert("card_id", card_id);
        auto content = QString(QJsonDocument(jsonObj).toJson());
        auto path = QString("/teller/customer");
        p_RESTClient->makeRequest(RESTClient::Method::POST, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto customerID = json.object().value("insertId").toString();
                this->ui->lineEditCardInfo->setText(customerID);
                reply->deleteLater();
            }, &content);
        state = 0;
        //ui->lineEditCardInfo->setText("jotain tahan");
    }
    if(state == 2){         //edit
        ui->lineEditOwnerID->text();
        //ui->lineEditCustomerID->text();
        ui->lineEditCardType->text();
        ui->lineEditAccountId->text();
        ui->lineEditPinNumber->text();
        QJsonObject jsonObj;
        jsonObj.insert("pin", pin);
        jsonObj.insert("owner_id", owner_id);
        jsonObj.insert("accountId", accountId);
        //jsonObj.insert("card_id", card_id);
        auto content = QString(QJsonDocument(jsonObj).toJson());
        auto path = QString("/teller/customer");
        p_RESTClient->makeRequest(RESTClient::Method::PUT, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto customerID = json.object().value("insertId").toString();
                this->ui->lineEditCardInfo->setText(customerID);
                reply->deleteLater();
            }, &content);
        state = 0;
        //ui->lineEditCardInfo->setText("jotain tahan");
    }
    if(state == 3){     //delete
        ui->lineEditOwnerID->text();
        //ui->lineEditCustomerID->text();
        ui->lineEditCardType->text();
        ui->lineEditAccountId->text();
        ui->lineEditPinNumber->text();
        QJsonObject jsonObj;
        jsonObj.insert("pin", pin);
        jsonObj.insert("owner_id", owner_id);
        jsonObj.insert("accountId", accountId);
        //jsonObj.insert("card_id", card_id);
        auto content = QString(QJsonDocument(jsonObj).toJson());
        auto path = QString("/teller/customer");
        p_RESTClient->makeRequest(RESTClient::Method::DELETE, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto customerID = json.object().value("insertId").toString();
                this->ui->lineEditCardInfo->setText(customerID);
                reply->deleteLater();
            }, &content);
        state = 0;
    }    //ui->lineEditCardInfo->setText("jotain tahan");
}


void Edit_Card_::on_buttonCancel_clicked()
{
    state = 0;
}

void Edit_Card_::on_pushBack_clicked()
{
    this->destroy();
}



