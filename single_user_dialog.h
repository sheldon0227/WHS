#ifndef SINGLE_USER_DIALOG_H
#define SINGLE_USER_DIALOG_H

#include <QDialog>

namespace Ui {
class Single_User_dialog;
}

class Single_User_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Single_User_dialog(QWidget *parent = 0);
    ~Single_User_dialog();

private slots:
    void receiveUserPhone(double);
    void handleEditPushButton();
    void handleOrderPushButton();

signals:
    void refreshTable();

private:
    Ui::Single_User_dialog *ui;
};

#endif // SINGLE_USER_DIALOG_H
