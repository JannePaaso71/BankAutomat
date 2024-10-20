#include "banktimer.h"
#include "qdebug.h"
bankTimer::bankTimer(QObject *parent)
{
    pQTimer=new QTimer;
    connect(pQTimer,SIGNAL(timeout()),
            this,SLOT(handleTimeOut()));
    pQTimer -> start(1000);
    qDebug() <<"timer";
}

bankTimer::~bankTimer()
{
    delete pQTimer;
    pQTimer=nullptr;
}

void bankTimer::handleTimeOut()
{
    emit sendTimerUpdate();
}
