#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <qsqlerror.h>
#include <QSizePolicy>
#include <QMessageBox>
#include <QDebug>

Add_User_Dialog::Add_User_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_User_Dialog)
{
    ui->setupUi(this);
    //让notePlainTextEdit 垂直填充 Form Layout
    QSizePolicy policy = ui->notePlainTextEdit->sizePolicy();
    policy.setVerticalStretch(1);
    ui->notePlainTextEdit->setSizePolicy(policy);
    //限制客户电话的输入
    QDoubleValidator *phoneValidator = new QDoubleValidator(0.0,9999999999.0,0,this);
    phoneValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->phoneLineEdit->setValidator(phoneValidator);
    //连接信号

    connect(ui->addUserButton,SIGNAL(released()),this,SLOT(handleAddUserButton()));
    connect(this,SIGNAL(refreshTable()),parent,SLOT(refreshUserTable()));
}

Add_User_Dialog::~Add_User_Dialog()
{
    delete ui;
}

void Add_User_Dialog::handleAddUserButton()
{
    QMessageBox msgBox;
    if(ui->nameLineEdit->text().isEmpty()!=0)
    {
        msgBox.information(this,"警告","用户名不能为空");
    }
    else if(ui->phoneLineEdit->text().isEmpty()!=0)
    {
        msgBox.information(this,"警告","电话号码不能为空");
    }
    else
    {
        QSqlDatabase db;
        if(QSqlDatabase::contains("User"))
            db = QSqlDatabase::database("User");
        else
            db = QSqlDatabase::addDatabase("QSQLITE", "User");
        db.setDatabaseName("data.db");
        if(!db.open())
        {
            qDebug()<< "Database Error";
        }
        else
        {
            QSqlQuery myQuery(db);
            myQuery.prepare("INSERT INTO allUser (wechatid, phone, name, address, note) VALUES (:wechatid, :phone, :name, :address, :note)");
            myQuery.bindValue(":wechatid",ui->idLineEdit->text());
            myQuery.bindValue(":phone",ui->phoneLineEdit->text().toDouble());
            myQuery.bindValue(":name",ui->nameLineEdit->text());
            myQuery.bindValue(":address",ui->addressLineEdit->text());
            myQuery.bindValue(":note",ui->notePlainTextEdit->toPlainText());
            if(!myQuery.exec())
            {
                qDebug()<<myQuery.lastError();
            }
            else
            {
                emit refreshTable();
                ui->idLineEdit->clear();
                ui->phoneLineEdit->clear();
                ui->nameLineEdit->clear();
                ui->addressLineEdit->clear();
                ui->notePlainTextEdit->clear();
            }
            db.close();
        }
    }
}
