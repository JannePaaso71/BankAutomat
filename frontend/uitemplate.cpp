#include "uitemplate.h"
#include "ui_uitemplate.h"

UiTemplate::UiTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiTemplate)
{
    ui->setupUi(this);

    pBankTimer = new bankTimer;

    connect(ui ->nr1Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr2Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr3Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr4Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr5Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr6Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr7Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr8Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr9Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));
    connect(ui ->nr0Button, SIGNAL(clicked()),
            this, SLOT(NumberClickedHandler()));

    connect(ui ->okButton, SIGNAL(clicked()),
            this, SLOT(OkButtonHandler()));
    connect(ui ->stopButton, SIGNAL(clicked()),
            this, SLOT(stopButtonHandler()));

    connect(ui ->rightEmptyButton_4, SIGNAL(clicked()),
            this, SLOT(rightEmptyButton_4Handler()));
    connect(ui ->rightEmptyButton_5, SIGNAL(clicked()),
            this, SLOT(rightEmptyButton_5Handler()));
    connect(ui ->rightEmptyButton_6, SIGNAL(clicked()),
            this, SLOT(rightEmptyButton_6Handler()));
    connect(ui ->rightEmptyButton_7, SIGNAL(clicked()),
            this, SLOT(rightEmptyButton_7Handler()));
    connect(ui ->rightEmptyButton_8, SIGNAL(clicked()),
            this, SLOT(rightEmptyButton_8Handler()));
    connect(ui ->leftEmptyButton_8, SIGNAL(clicked()),
            this, SLOT(leftEmptyButton_8Handler()));

    connect(pBankTimer,SIGNAL(sendTimerUpdate()),
            this,SLOT(uiBankTimeHandler()));

    ui->monitor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    textStyle = R"(<style> div {color:rgb(20, 20, 190); padding : 0px; text-align:center; margin-top: 90px;
                margin-right: 20px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>)";
    monitorText = textStyle +"<div><p><br></p></div><div><h7>";

}

UiTemplate::~UiTemplate(){
    delete ui;
}

void UiTemplate::prompt(QString tInput){
    ui -> monitor -> setHtml(tInput);
}

void UiTemplate::NumberClickedHandler()
{
    if (numberKeysEnabled==true){
    QPushButton * button = (QPushButton *)sender();
    QString labelnumber = button->text();
    buttonInput = buttonInput + labelnumber;
    qDebug() << "numberClickedHandler" <<buttonInput;
    prompt(textStyle + monitorText + buttonInput +"</h7></div>");
    //    ui -> monitor -> setHtml(monitorText+ buttonInput);

    }
}

void UiTemplate::OkButtonHandler()
{
    emit OkButtonPushed();
    qDebug() << "OkButton uitemplate";
    timerCounter=0;
}

void UiTemplate::stopButtonHandler()
{
emit nextState(States::FINISHED);
}

void UiTemplate::uiBankTimeHandler()
{
    emit BankTimerTicked();

timerCounter ++;
    if (timerCounter> 30) {stopButtonHandler();}
}

void UiTemplate::rightEmptyButton_4Handler(){
   timerCounter =0;
   emit rightEmptyButton_4Pushed();
   qDebug() << "emptyButton 4";
}
void UiTemplate::rightEmptyButton_5Handler(){
   timerCounter =0;
   emit rightEmptyButton_5Pushed();
   qDebug() << "emptyButton 5";
}
void UiTemplate::rightEmptyButton_6Handler(){
   timerCounter =0;
   emit rightEmptyButton_6Pushed();
   qDebug() << "emptyButton 6";
}
void UiTemplate::rightEmptyButton_7Handler(){
   timerCounter =0;
   emit rightEmptyButton_7Pushed();
   qDebug() << "emptyButton 7";
}
void UiTemplate::rightEmptyButton_8Handler(){
   timerCounter =0;
   emit rightEmptyButton_8Pushed();
   qDebug() << "emptyButton 8";
}

void UiTemplate::leftEmptyButton_8Handler(){
   timerCounter =0;
   emit leftEmptyButton_8Pushed();
   qDebug() << "left emptyButton 8";
}

void UiTemplate::setNumberKeysEnabled(bool NumberKeysEn)
{
   numberKeysEnabled = NumberKeysEn;
}
