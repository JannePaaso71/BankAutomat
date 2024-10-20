#ifndef EDITCARD_H
#define EDITCARD_H

#include <QDialog>

namespace Ui {
class EditCard;
}

class EditCard : public QDialog
{
    Q_OBJECT

public:
    explicit EditCard(QWidget *parent = nullptr);
    ~EditCard();

private slots:
    void on_CreateNewCard_clicked();

    void on_Deletecard_clicked();

private:
    Ui::EditCard *ui;
};

#endif // EDITCARD_H
