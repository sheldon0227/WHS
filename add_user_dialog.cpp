#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"
#include <QSizePolicy>
#include <QMessageBox>

Add_User_Dialog::Add_User_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_User_Dialog)
{
    ui->setupUi(this);
    //让notePlainTextEdit 垂直填充 Form Layout
    QSizePolicy policy = ui->notePlainTextEdit->sizePolicy();
    policy.setVerticalStretch(1);
    ui->notePlainTextEdit->setSizePolicy(policy);

    ui->phoneLineEdit->setValidator(new QIntValidator(0,9999999999,this));
    connect(ui->addUserButton,SIGNAL(released()),parent,SLOT(refreshUserTable()));
    connect(ui->addUserButton,SIGNAL(released()),this,SLOT(handleAddUserButton()));
}

Add_User_Dialog::~Add_User_Dialog()
{
    delete ui;
}

void Add_User_Dialog::handleAddUserButton()
{
    QMessageBox msgBox;

}
