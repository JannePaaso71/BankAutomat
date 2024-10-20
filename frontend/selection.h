#ifndef SELECTION_H
#define SELECTION_H

#include "uitemplate.h"
#include "Actions.h"
#include <QWidget>

namespace Ui {class SelectAction;}

class SelectAction : public UiTemplate
{
    Q_OBJECT

public:
    explicit SelectAction(QWidget *parent = nullptr);
    virtual ~SelectAction() override;

    Actions getChosenAction() const;

signals:
    void SelectActionReady();

public slots:
    void OkButtonHandler();
    void StopButtonHandler();
    void WithdrawButtonHandler();
    void SaldoButtonHandler();
    void TransactionsButtonHandler();
    void FinishButtonHandler();

private:
    Ui::SelectAction *ui;

    Actions chosenAction;


};

#endif // SELECTION_H
