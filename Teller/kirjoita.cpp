
#include "kirjoita.h"


Kirjoita::Kirjoita()
{

}

void Kirjoita::nappaimisto(QKeyEvent *event)
{
    if(event->text().isEmpty()){
        QTextBrowser::keyPressEvent(event);
    }
    else {
        this->insertPlainText(event->text());
    }

}

