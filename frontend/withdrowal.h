    /**
     * Luokka k
     *
     * Signals authenticated(bool) after receiving response from the backend.
     * @param id
     * @param pin
     * @return
     */

#ifndef WITHDROWAL_H
#define WITHDROWAL_H

#include "RESTClient.h"
#include "uitemplate.h"
#include <QWidget>

namespace Ui {class Withdrowal;}

class Withdrowal : public UiTemplate
{
    Q_OBJECT

public:
    explicit Withdrowal(QWidget *parent, RESTClient *, AccountTypes);
    virtual ~Withdrowal() override;

private:
    Ui::Withdrowal *ui;
    int withdrowalAmount;
    AccountTypes accountType = AccountTypes::DEBIT;
    int timerTic=0;
    bool timerEnable=false;
    RESTClient * pRESTClient;

    void MakeTransaction(int withdrowAmount);
    void showSuccessfullWithdraw();
    void showFailedWithdraw();

private slots:
    void OkButtonHandler();
    void TypeInSumHandler();
    void HundredEuroHandler();
    void FiftyEuroHandler();
    void FortyEuroHandler();
    void TwentyEuroHandler();
};

#endif // WITHDROWAL_H
