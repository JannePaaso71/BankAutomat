#ifndef CHOOSEACCOUNT_H
#define CHOOSEACCOUNT_H

#include "uitemplate.h"
#include "AccountTypes.h"
#include <QWidget>

namespace Ui { class ChooseAccount;}

class ChooseAccount : public UiTemplate
{
    Q_OBJECT

public:
    ChooseAccount(QWidget *parent, RESTClient * );
    virtual ~ChooseAccount() override;
    AccountTypes getAccountType();

signals:
    void ChooseAccountReady();

public slots:
    void OkButtonHandler();
    void CreditButtonHandler();
    void DebitButtonHandler();

private:
    Ui::ChooseAccount *ui;
    void FetchAccountType();
    void SelectAction();

    RESTClient * pRESTClient;
};

#endif // CHOOSEACCOUNT_H
