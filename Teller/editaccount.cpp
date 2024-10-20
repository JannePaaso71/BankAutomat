#include "editaccount.h"
#include "ui_editaccount.h"

EditAccount::EditAccount(QWidget *parent, RESTClient* rc) :
    QDialog(parent),
    ui(new Ui::EditAccount),
    p_RESTClient(rc)
{
    ui->setupUi(this);
    connect(ui->buttoNewAccount, SIGNAL(clicked(bool)), this, SLOT(on_buttoNewAccount_clicked()));
    connect(ui->buttonExistAccount, SIGNAL(clicked(bool)), this, SLOT(on_buttonExistAccount_clicked()));
    connect(ui->buttonSave, SIGNAL(clicked(bool)), this, SLOT(on_buttonSave_clicked()));
    connect(ui->buttonBack, SIGNAL(clicked(bool)), this, SLOT(on_buttonBack_clicked()));
}

EditAccount::~EditAccount()
{
    delete ui;
}

void EditAccount::on_buttoNewAccount_clicked()
{
    state = 1;
    ui->buttonExistAccount->hide();
    qDebug() << "buttonNewAccount_clicked ";
}

void EditAccount::on_buttonExistAccount_clicked()
{
    qDebug() << "buttonExistAccount_clicked";
    state = 2;
    ui->buttoNewAccount->hide();
    ui->lineEditSaldo->hide();
    ui->labelSaldo->hide();
}

void EditAccount::on_buttonSave_clicked()
{
    if(state == 1){
        qDebug() << "buttonSaveClicked: state 1";
        id_customer = ui->lineEditCustomerID->text();
        credit_limit = ui->lineEditCreditLimit->text();
        amount = ui->lineEditSaldo->text();
        qDebug() << "buttonSaveClicked: state 1.1";
        QJsonObject jsonObj;
        jsonObj.insert("id_customer", id_customer);
        jsonObj.insert("saldo",amount);
        jsonObj.insert("credit_limit",credit_limit);
        auto content2 = QString(QJsonDocument(jsonObj).toJson());
        qDebug()<<content2;
        qDebug() << "buttonSaveClicked: state 1.2";
        auto path = QString("/teller/teller_account/createaccount/") + id_customer;
        qDebug() << "buttonSaveClicked: state 1.3";
        p_RESTClient->makeRequest(RESTClient::Method::POST, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                qDebug() << "buttonSaveClicked: state 1.4";
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "auth: Setting restToken.";
                auto createAccount = json.object().value("insertId").toString();                
                this->ui->lineEditINFO->setText(createAccount);
                reply->deleteLater();
            }, &content2);
        //ui->lineEditINFO->setText("New account created");
        state =0;
    }
    if(state == 2){
        qDebug() << "buttonSaveClicked: state 2.1";
        ui->lineEditCustomerID->text();
        ui->lineEditCreditLimit->text();
        QJsonObject jsonObj;
        jsonObj.insert("id_customer", id_customer);
        jsonObj.insert("credit_limit",credit_limit);
        auto content2 = QString(QJsonDocument(jsonObj).toJson());
        qDebug() << "buttonSaveClicked: state 2.2";
        auto path = QString("/teller/teller_account") + id_customer;

        p_RESTClient->makeRequest(RESTClient::Method::PUT, path, this, [this](QNetworkReply *reply) {
                auto response = reply->readAll();
                auto json = QJsonDocument::fromJson(response.toStdString().c_str());
                qDebug() << "buttonSaveClicked: state 2.3";
                auto modifyCustomer = json.object().value("insertId").toString();
                //ui->lineEditINFO->setText("tiedot muokattu");
                this->ui->lineEditINFO->setText(modifyCustomer);
                reply->deleteLater();
            }, &content2);
        state =0;
    }
}

void EditAccount::on_buttonCancel_clicked()
{
    if(state == 1){
        qDebug()<<"buttonCancel : newAccount";
        ui->buttonExistAccount->show();
        ui->lineEditCustomerID->show();
        ui->lineEditCustomerID->clear();
        ui->lineEditCreditLimit->clear();
        ui->lineEditSaldo->clear();
        state = 0;
    }
    if(state == 2){
        qDebug()<<"buttonCancel : existingAccount";
        ui->buttoNewAccount->show();
        ui->lineEditCustomerID->clear();
        ui->lineEditCreditLimit->clear();
        ui->lineEditSaldo->clear();
        state = 0;
    }
}
void EditAccount::on_buttonBack_clicked()
{
    this->destroy();
}



