#include "editcustomers.h"
//#include "ui_editcustomers_.h"
//#include <QtNetwork/QNetworkAccessManager>
//#include "settings.h"
//#include "RESTClient.h"

EditCustomers::EditCustomers(QWidget *parent, RESTClient* rc) :
    QDialog(parent),
    ui(new Ui::EditCustomers),
    p_RESTClient(rc)
{
    ui->setupUi(this);
    connect(ui->buttonCreateNewCustomer, SIGNAL(clicked(bool)), this, SLOT(on_CreateNewCustomer_clicked()));
    connect(ui->buttonModifyCustomer, SIGNAL(clicked(bool)), this, SLOT(on_ModifyCustomer_clicked()));
    connect(ui->buttonSave, SIGNAL(clicked(bool)), this, SLOT(on_Save_clicked()));
    connect(ui->buttonSave, SIGNAL(clicked(bool)), this, SLOT(SaveHandler(bool)));
    connect(ui->buttonBack, SIGNAL(clicked(bool)), this, SLOT(on_Back_clicked()));
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(on_buttonCancel()));
}

EditCustomers::~EditCustomers()
{
    delete ui;
}

void EditCustomers::on_CreateNewCustomer_clicked()
{
    state = 1;
    ui->lineEditCustomerID->hide();
    ui->labelCustomerID->hide();
    ui->buttonModifyCustomer->hide();
}

void EditCustomers::CreateNewCustomerHandler(QNetworkReply *reply)
{

    qDebug() << "SaveHandler: CreateNewCustomer";

    qDebug()<<"CreateNewCustomerHandler";
}

void EditCustomers::on_ModifyCustomer_clicked()
{
    state = 2;
    ui->buttonCreateNewCustomer->hide();
    id = ui->lineEditCustomerID->text();

    qDebug()<<"ModifyCustomerHandler";
}

void EditCustomers::ModifyCustomerHandler(QNetworkReply *reply)
{
}

void EditCustomers::on_Save_clicked()
{
    ui->lineEditCustomerID->show();
    ui->labelCustomerID->show();
    ui->buttonModifyCustomer->show();
}

void EditCustomers::SaveHandler(bool)
{
    if(state == 1){
        lastname = ui->lineEditLastname->text();
        firstname = ui->lineEditFirstname->text();
        QJsonObject jsonObj;
        jsonObj.insert("lastname",lastname);
        jsonObj.insert("firstname",firstname);
        auto content2 = QString(QJsonDocument(jsonObj).toJson());
        QString content = "{\"firstname\":\"";
        content.append(firstname);
        content.append("\",\"lastname\":\"");
        content.append(lastname);
        content.append("\" }");
        auto path = QString("/teller/customer");
        p_RESTClient->makeRequest(RESTClient::Method::POST, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto customerID = json.object().value("insertId").toString();
                // Trying out single shot connections.
                // disconnect(this, SIGNAL(finished(QNetworkReply *)), 0, 0);
                this->ui->lineEditCustomerID->setText(customerID);
                reply->deleteLater();
            }, &content2);
        ui->lineEditInfo->setText("New customer created");
        state = 0;

    }
    if(state == 2){
        state = 0;
        ui->lineEditInfo->setText("Changes saved");
        ui->buttonCreateNewCustomer->show();
        qDebug()<<"SaveHandler; ModifyCustomer";

        id = ui->lineEditCustomerID->text();
        lastname = ui->lineEditLastname->text();
        firstname = ui->lineEditFirstname->text();
        QJsonObject jsonObj;
        jsonObj.insert("id", id);
        jsonObj.insert("lastname",lastname);
        jsonObj.insert("firstname",firstname);
        auto content2 = QString(QJsonDocument(jsonObj).toJson());
        QString content = "{\"id\":\"";
        content.append(id);
        content.append("\",\"firstname\":\"");
        content.append(firstname);
        content.append("\",\"lastname\":\"");
        content.append(lastname);
        content.append("\" }");
        qDebug() << "modifyCustomer() kutsuttu.";
        auto path = QString("/teller/customer/") + id;

        p_RESTClient->makeRequest(RESTClient::Method::PUT, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto customerID = json.object().value("insertId").toString();
                // Trying out single shot connections.
                // disconnect(this, SIGNAL(finished(QNetworkReply *)), 0, 0);
                ui->lineEditInfo->setText("tiedot muokattu");
                reply->deleteLater();
            }, &content2);


        state = 0;
    }
}

void EditCustomers::on_buttonCancel()
{
    if(state == 1){
        ui->lineEditCustomerID->show();
        ui->lineEditCustomerID->clear();
        ui->lineEditLastname->clear();
        ui->lineEditFirstname->clear();
        ui->labelCustomerID->show();
        ui->buttonModifyCustomer->show();
        state = 0;
    }
    if(state == 2){
        ui->buttonCreateNewCustomer->show();
        ui->lineEditCustomerID->clear();
        ui->lineEditLastname->clear();
        ui->lineEditFirstname->clear();
        state = 0;
    }
}

void EditCustomers::on_Back_clicked()
{
    this->destroy();
}



