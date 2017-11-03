#include "single_user_dialog.h"
#include "ui_single_user_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <qsqlerror.h>
#include <QDebug>
using namespace std;
static double PHONE;

Single_User_dialog::Single_User_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Single_User_dialog)
{
    ui->setupUi(this);
    //时间输入默认当天
    ui->dateEdit->setDate(QDate::currentDate());
    //让notePlainTextEdit&buyPlainTextEdit 垂直填充 Form Layout
    QSizePolicy policy = ui->notePlainTextEdit->sizePolicy();
    policy.setVerticalStretch(1);
    ui->notePlainTextEdit->setSizePolicy(policy);
    ui->buyPlainTextEdit->setSizePolicy(policy);

    //限制客户电话的输入
    QDoubleValidator *phoneValidator = new QDoubleValidator(0.0,9999999999.0,0,this);
    phoneValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->phoneLineEdit->setValidator(phoneValidator);

    //连接信号
    connect(ui->editPushButton,SIGNAL(released()),this,SLOT(handleEditPushButton()));
    connect(ui->orderPushButton,SIGNAL(released()),this,SLOT(handleOrderPushButton()));
    connect(this,SIGNAL(refreshTable()),parent,SLOT(refreshUserTable()));
}

Single_User_dialog::~Single_User_dialog()
{
    delete ui;
}

void Single_User_dialog::receiveUserPhone(double phone)
{
    PHONE = phone;
    QSqlDatabase db;
    if(QSqlDatabase::contains("User"))
        db = QSqlDatabase::database("User");
    else
        db = QSqlDatabase::addDatabase("QSQLITE", "User");
    db.setDatabaseName("data.db");
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else{
        QSqlQuery myQuery(db);
        myQuery.prepare("SELECT wechatid,phone,name,address,note FROM allUser WHERE phone = :phone ");
        myQuery.bindValue(":phone",phone);
        if(!myQuery.exec())
        {
            qDebug()<<myQuery.lastError();
        }
        while(myQuery.next())
        {
            ui->idLineEdit->setText(myQuery.value(0).toString());
            ui->phoneLineEdit->setText(myQuery.value(1).toString());
            ui->nameLineEdit->setText(myQuery.value(2).toString());
            ui->addressLineEdit->setText(myQuery.value(3).toString());
            ui->notePlainTextEdit->setPlainText(myQuery.value(4).toString());
        }
        db.close();
    }
}

void Single_User_dialog::handleEditPushButton()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("User"))
        db = QSqlDatabase::database("User");
    else
        db = QSqlDatabase::addDatabase("QSQLITE", "User");
    db.setDatabaseName("data.db");
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else{
        QSqlQuery myQuery(db);
        myQuery.prepare("UPDATE allUser SET wechatid=:wechatid, phone=:phone, name=:name, address=:address, note=:note WHERE phone=:oldphone");
        myQuery.bindValue(":phone",ui->phoneLineEdit->text().toDouble());
        myQuery.bindValue(":wechatid",ui->idLineEdit->text());
        myQuery.bindValue(":name",ui->nameLineEdit->text());
        myQuery.bindValue(":address",ui->addressLineEdit->text());
        myQuery.bindValue(":note",ui->notePlainTextEdit->toPlainText());
        myQuery.bindValue(":oldphone",PHONE);
        if(!myQuery.exec())
        {
            qDebug()<<myQuery.lastError();
        }
        else
        {
            emit refreshTable();
        }
        db.close();
    }
}

void Single_User_dialog::handleOrderPushButton()
{

}
