#include "selection.h"
#include "ui_selectaction.h"

SelectAction::SelectAction(QWidget *parent):
    UiTemplate(parent),
    ui(new Ui::SelectAction)
{
    ui->setupUi(this);

    connect(this, SIGNAL(OkButtonPushed()),
            this, SLOT(OkButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_8Pushed()),
            this, SLOT(WithdrawButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_7Pushed()),
            this, SLOT(SaldoButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_6Pushed()),
            this, SLOT(TransactionsButtonHandler()));
    connect(this, SIGNAL(rightEmptyButton_4Pushed()),
            this, SLOT(FinishButtonHandler()));

    textStyle = "<style>  div {line-height: 131%; color:rgb(20, 20, 190); text-align: right; padding : 0px; text-align:right; margin-top: 65px; margin-right: 25px; margin-left: 20px;}  p {font-size:1px} h7 {font-size:25px} </style>";
    prompt(textStyle + "<div></div><div><h7>Nosta rahaa<br>Näytä saldo<br>Katso tapahtumat<br><br>Lopeta</div></h7></div>");
}

SelectAction::~SelectAction()
{
    delete ui;
}

Actions SelectAction::getChosenAction() const
{
    return chosenAction;
}

void SelectAction::OkButtonHandler()
{
qDebug() <<"okButton selectaction";
}

void SelectAction::StopButtonHandler()
{

}

void SelectAction::WithdrawButtonHandler()
{
//    chosenAction=Actions::WITHDRAW_MONEY;
//    emit SelectActionReady();
    emit nextState(States::WITHDRAW);
    qDebug() <<"withdraw selectaction";
}

void SelectAction::SaldoButtonHandler()
{
    emit nextState(States::SALDO);
    qDebug() <<"saldo selectaction";
}

void SelectAction::TransactionsButtonHandler()
{
    emit nextState(States::TRANSACTIONS);
}

void SelectAction::FinishButtonHandler()
{
    emit nextState(States::FINISHED);
}

