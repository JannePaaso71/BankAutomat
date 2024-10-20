#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QWidget>
#include <vector>
#include <map>
#include "uitemplate.h"
#include "AccountTypes.h"
#include "RESTClient.h"


namespace Ui {class transactions;}

class Transactions : public UiTemplate
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent, RESTClient* rc,AccountTypes ac);
    ~Transactions() override;

private:
    Ui::transactions *ui;
    AccountTypes chosenAccountType;
    RESTClient *restClient;
    int page=1;
    int emptyPageIndex;
    void getPage(int);

private slots:
    void nextPage();
    void previousPage();
    void goBack();

//signals:
//    void signalGetPage(int);

};

#endif // TRANSACTIONS_H
