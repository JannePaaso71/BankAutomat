#ifndef SIGNIN_H
#define SIGNIN_H

//Tämä luoka on UiTemplate luokan aliluokka, joka lukee käyttäjän syöttämät card_id ja pin
//muuttujat ja tarkastaa RestClient luokkan välitykselllä, että tietoja vastaava pankkikortti
//on olemassa. Mikäli tunnistu onnistuu, luokka kysyy kortin tyypin (debt/debit+credit) ja
//tallentaa tiedon, minkä jälkeen luokka lähettää emit SignInReady() signaalin, joka johtaa luokan
//tuhoamiseen ja ohjelman siirtymisen seuraavaan vaiheeseen.

#include "banktimer.h"
#include "uitemplate.h"
#include "RESTClient.h"
#include "AccountTypes.h"
#include <QWidget>

namespace Ui {class SignIn;}

class SignIn : public UiTemplate
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent, RESTClient * pRESTclient);
    virtual ~SignIn() override;

private:

    Ui::SignIn *ui;
    QString cardId="";
    QString pin="";

    int state=0;
    int authenticationFailCounter=0;

    RESTClient * pRESTClient;

private slots:
    void OkButtonHandler();
    void stopButtonHandler();
    void BankTimeHandler();
    void AuthenticationOK(bool);

};

#endif // SIGNIN_H
