#include "withdrowal.h"
#include "ui_withdrowal.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QVariant>

Withdrowal::Withdrowal(QWidget *parent, RESTClient *rc, AccountTypes ac):
    UiTemplate(parent),
    ui(new Ui::Withdrowal),
    pRESTClient(rc),
    accountType(ac)
{
    ui->setupUi(this);
    connect(this, SIGNAL(OkButtonPushed()),
            this, SLOT(OkButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_8Pushed()),
            this, SLOT(TypeInSumHandler()));
    connect(this, SIGNAL(rightEmptyButton_7Pushed()),
            this, SLOT(HundredEuroHandler()));
    connect(this, SIGNAL(rightEmptyButton_6Pushed()),
            this, SLOT(FiftyEuroHandler()));
    connect(this, SIGNAL(rightEmptyButton_5Pushed()),
            this, SLOT(FortyEuroHandler()));
    connect(this, SIGNAL(rightEmptyButton_4Pushed()),
            this, SLOT(TwentyEuroHandler()));
    textStyle = R"(<style> div {color:rgb(20, 20, 190); padding : 0px; text-align:right; margin-right: 25px; line-height: 135%;
             margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    prompt(textStyle + "<div><h7>Muu summa<br>100 euroa<br>50 euroa<br>40 euroa<br>20 euroa</h7></div>");
}

Withdrowal::~Withdrowal(){
    delete ui;
}

void Withdrowal::TypeInSumHandler(){
    setNumberKeysEnabled(1);
    qDebug() << "other sum";
    textStyle = R"(<style> div {color:rgb(20, 20, 190); padding : 0px; text-align:center; margin-right: 25px;
                 line-height: 100%; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    prompt(textStyle + "<div><h7><br><br>Syötä nostettava<br> summa</div></h7>");
}
void Withdrowal::HundredEuroHandler(){
    qDebug() << "100";
    withdrowalAmount=100;
    Withdrowal::MakeTransaction(withdrowalAmount);
}
void Withdrowal::FiftyEuroHandler(){
    qDebug() << "50";
    withdrowalAmount=50;
        Withdrowal::MakeTransaction(withdrowalAmount);
}
    void Withdrowal::FortyEuroHandler(){
    qDebug() << "40";
    withdrowalAmount=40;
        Withdrowal::MakeTransaction(withdrowalAmount);
}
void Withdrowal::TwentyEuroHandler(){
    withdrowalAmount=20;
    Withdrowal::MakeTransaction(withdrowalAmount);
}
void Withdrowal::OkButtonHandler(){
    withdrowalAmount=buttonInput.toDouble();
    setNumberKeysEnabled(0);
    Withdrowal::MakeTransaction(withdrowalAmount);
}

void Withdrowal::MakeTransaction(int withdrowAmount){
    qDebug() << withdrowAmount;
    textStyle = R"(<style>  div {line-height: 131%; color:rgb(20, 20, 190); text-align: right; padding : 0px; text-align:right;
                    margin-top: 65px; margin-right: 25px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    auto urlPath = QString("/atm/account/withdrawal");
    auto* body = new QString("{\"accountType\": ");
    body->append(accountType == AccountTypes::CREDIT ? "\"credit\"," : "\"debit\",");
    body->append("\"amount\":");
    body->append(QString::number(withdrowAmount));
    body->append("}");
    pRESTClient->makeRequest(RESTClient::Method::POST, urlPath, this,
    [=](QNetworkReply* reply){
        auto data = reply->readAll();
        qDebug() << data;
        auto json = QJsonDocument::fromJson(data);
        QJsonObject object = json.object();
        QVariant success = object.value(QString("success"));
        qDebug() << success;
        timerTic=0;
        if (success.toInt()) {
            qDebug() << "In success.";
            this -> showSuccessfullWithdraw();
        } else {
            qDebug() << "In unsuccess.";
            this -> showFailedWithdraw();
        }
        reply->deleteLater();
    }, body);
    delete body;
}

void Withdrowal::showSuccessfullWithdraw(){
    auto timer = new QTimer();
    timer->singleShot(2500, [timer, this](){
        delete timer;
        emit nextState(States::FINISHED);
    });
    textStyle = R"(<style>  div {line-height: 100%; color:rgb(20, 20, 190); text-align: center; padding : 0px; margin-top: 65px;
             margin-right: 25px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    prompt( textStyle + "<div><h7><br><br>Nostotapahtuma <br> onnistui</div></h7>");
}

void Withdrowal::showFailedWithdraw()
{
    auto timer = new QTimer();
    timer->singleShot(2500, [timer, this](){
        delete timer;
        emit nextState(States::SELECT_ACTION);
    });
    textStyle = R"(<style>  div {line-height: 100%; color:rgb(20, 20, 190); text-align: center; padding : 0px; margin-top: 65px;
                    margin-right: 25px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    prompt(textStyle + "<div><h7><br><br>Tilillä ei ole <br>riittävästi rahaa</h7></div>");
}
