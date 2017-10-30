#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"
#include <QSizePolicy>

Add_User_Dialog::Add_User_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_User_Dialog)
{
    ui->setupUi(this);
    //让notePlainTextEdit 垂直填充 Form Layout
    QSizePolicy policy = ui->notePlainTextEdit->sizePolicy();
    policy.setVerticalStretch(1);
    ui->notePlainTextEdit->setSizePolicy(policy);

}

Add_User_Dialog::~Add_User_Dialog()
{
    delete ui;
}
