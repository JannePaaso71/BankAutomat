#ifndef SALDO_H
#define SALDO_H
#include "uitemplate.h"
#include "AccountTypes.h"
#include "RESTClient.h"
#include <QWidget>

namespace Ui {class Saldo;}

class Saldo : public UiTemplate
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent, RESTClient* rc,AccountTypes ac);
    virtual ~Saldo() override;

private:
    Ui::Saldo *ui;
    QString saldo;
    double creditLimit = 0;
    int timerTic=0;
    AccountTypes chosenAccountType;
    RESTClient *restClient;

    void ShowSaldo();
    void fetchSaldo();
    void setCreditLimit(double);

//signals:
//    void SaldoRequest();

private slots:
    void OkButtonHandler();

};

#endif // SALDO_H
