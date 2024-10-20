//Tämä luokka on kantaluokka, jonka muut käyttöliittymäluokat perivät. Luokka luo graafisen käyttöliittymän.
//Lisäksi luokassa on nuomeronäppäimien  lukutoiminto, jonka voi aktivoida tai passivoida asettamall numberKeysEnabled
// muuttujalle arvon - 0 = lukjittu, 1 = toiminnassa. asettamista varten luokassa on setNumberKeysEnable funktio.

#ifndef UITEMPLATE_H
#define UITEMPLATE_H

#include "banktimer.h"
#include <QWidget>
#include "AccountTypes.h"
#include "states.h"
#include "RESTClient.h"


namespace Ui {class UiTemplate;}

class UiTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit UiTemplate(QWidget *parent = nullptr);
    virtual ~UiTemplate() override;
    void prompt(QString tInput);
    void setNumberKeysEnabled(bool);

signals:

    void OkButtonPushed();
    void BankTimerTicked();
    void rightEmptyButton_4Pushed();
    void rightEmptyButton_5Pushed();
    void rightEmptyButton_6Pushed();
    void rightEmptyButton_7Pushed();
    void rightEmptyButton_8Pushed();
    void leftEmptyButton_8Pushed();

    void nextState(States state);
    void AccountChosen(AccountTypes);

protected:
    QString buttonInput = "";
    QString textStyle="";
    int timerCounter=0;
    bankTimer * pBankTimer;

private:

    bool numberKeysEnabled = 0;
    Ui::UiTemplate *ui;
    QString monitorText;

private slots:
    void NumberClickedHandler();
    void OkButtonHandler();
    void stopButtonHandler();
    virtual void uiBankTimeHandler();
    void rightEmptyButton_4Handler();
    void rightEmptyButton_5Handler();
    void rightEmptyButton_6Handler();
    void rightEmptyButton_7Handler();
    void rightEmptyButton_8Handler();
    void leftEmptyButton_8Handler();
};

#endif // UITEMPLATE_H
