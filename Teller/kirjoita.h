
#ifndef KIRJOITA_H
#define KIRJOITA_H

#include <QTextBrowser>
#include <QKeyEvent>


class Kirjoita : public QTextBrowser
{
public:
    Kirjoita();
    void nappaimisto(QKeyEvent *event);
protected:
};

#endif // KIRJOITA_H
