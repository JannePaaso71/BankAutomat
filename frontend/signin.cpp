#include "signin.h"
#include "ui_signin.h"


SignIn::SignIn(QWidget *parent, RESTClient * pRESTclient):
   UiTemplate(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);

    this -> pRESTClient = pRESTclient;

    textStyle = R"(<style> div {color:rgb(20, 20, 190); padding : 0px; text-align:center;
                    margin-right: 20px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    QString text="<div><h7><br><br>Tervetuloa anna <br> kortin tunnus</h7></div>";
    prompt(textStyle + text);

    connect(this, SIGNAL(OkButtonPushed()),
            this, SLOT(OkButtonHandler()));
    connect(this, SIGNAL(BankTimerTicked()),
            this, SLOT(BankTimeHandler()));


    setNumberKeysEnabled(1);
    pBankTimer -> blockSignals(true);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::OkButtonHandler(){

    if (state ==0){
        cardId=buttonInput;
        qDebug() << "cardId" << cardId;
        buttonInput="";
        prompt(textStyle + "<div><h7><br><br>Anna<br>pin-koodi</h7></div>");
    }
    else if (state ==1) {
        pin=buttonInput;
        qDebug() << "pin" << pin;
        buttonInput="0";
        qDebug() << "cardId" << cardId;
        prompt(textStyle + "<div><h7><br><br>Muodostan<br>verkkoyhteyttä</h7></div>");
        connect(pRESTClient, SIGNAL(authenticated(bool)),
                    this, SLOT(AuthenticationOK(bool)));
        pRESTClient ->authenticateCard(cardId, pin);
    }
    state ++;
}

void SignIn::stopButtonHandler()
{
    qDebug() << "stop button";
}

void SignIn::BankTimeHandler()
{
}
void SignIn::AuthenticationOK(bool authentication)
{
    qDebug() <<  authentication;
    if (authentication == true) {
        emit nextState(CHOOSE_ACCOUNT);

    } else {
        authenticationFailCounter++;
        if (authenticationFailCounter<=3){

           textStyle = R"(<style> div {line-height: 110%; color:rgb(20, 20, 190); padding : 0px; text-align:center;
                        margin-right: 20px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
            prompt(textStyle + "<div><h7><br>Virheellinen kirjautumisyritys<br>Anna kortin tunnus uudelleen<div><h7>");
            buttonInput="";
            state = 0;
            cardId = "";
            pin = "";
        }
        else {
            textStyle = R"(<style> div {line-height: 110%; color:rgb(20, 20, 190); padding : 0px; text-align:center;
                        margin-right: 20px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
            prompt(textStyle + "<div><h7><br>Liian monta kirjautumisyritystä. Toiminta keskeytetään<div><h7>");

        }
        state = 0;
    }
}







