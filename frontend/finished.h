#ifndef FINISHED_H
#define FINISHED_H

#include "uitemplate.h"

#include <QWidget>

namespace Ui {
class Finished;
}

class Finished : public UiTemplate
{
    Q_OBJECT

public:
    explicit Finished(QWidget *parent = nullptr);
    virtual ~Finished() override;

public slots:


private:
    Ui::Finished *ui;
    void ThreeSecondDelay();

};

#endif // FINISHED_H
