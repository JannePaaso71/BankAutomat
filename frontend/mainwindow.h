#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "uitemplate.h"
#include "chooseaccount.h"
#include "saldo.h"
#include "transactions.h"
#include "RESTClient.h"
#include "Actions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

private slots:
    void choose_state(States state);
    void AccountTypeSetterSlot(AccountTypes ac);

private:
    virtual void paintEvent(QPaintEvent *) override;

    UiTemplate * myActiveWidget;

    Ui::MainWindow *ui;

    AccountTypes chosenAccount;
    Actions chosenAction;

    RESTClient * pRESTClient;
};
#endif // MAINWINDOW_H
