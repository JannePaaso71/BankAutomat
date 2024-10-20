#ifndef BANKTIMER_H
#define BANKTIMER_H

#include <QObject>
#include <QTimer>

class bankTimer : public QObject

{
    Q_OBJECT
public:
    bankTimer(QObject *parent = nullptr);
    virtual ~bankTimer() override;

signals:
    void sendTimerUpdate();

public slots:
   void handleTimeOut();

private:
    QTimer * pQTimer;

};


#endif // BANKTIMER_H
