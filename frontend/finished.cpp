#include "finished.h"
#include "ui_finished.h"

Finished::Finished(QWidget *parent) :
    UiTemplate(parent),
    ui(new Ui::Finished)
{
    ui->setupUi(this);
    textStyle = "<style> div {line-height: 100%; color:rgb(20, 20, 190); padding : 0px; text-align:center; margin-right: 20px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>";

    prompt(textStyle + "<div><h7><br><br>Kiitos käynnistä<br>Tervetuloa uudestaan</div></h7>");
    ThreeSecondDelay();
}
Finished::~Finished(){
    delete ui;
}
void Finished::ThreeSecondDelay(){
    QTimer * threeSeconds = new QTimer();
    threeSeconds -> singleShot(3000,[=](){
        delete threeSeconds;
        emit nextState(States::SIGNIN);
    });
}


