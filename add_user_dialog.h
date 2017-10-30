#ifndef ADD_USER_DIALOG_H
#define ADD_USER_DIALOG_H

#include <QDialog>

namespace Ui {
class Add_User_Dialog;
}

class Add_User_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_User_Dialog(QWidget *parent = 0);
    ~Add_User_Dialog();

private:
    Ui::Add_User_Dialog *ui;
};

#endif // ADD_USER_DIALOG_H
