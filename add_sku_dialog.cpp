#include "add_sku_dialog.h"
#include "ui_add_sku_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <qsqlerror.h>
#include <QDebug>
#include <QMessageBox>

Add_Sku_Dialog::Add_Sku_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Sku_Dialog)
{
    ui->setupUi(this);
    ui->idLineEdit->setValidator(new QIntValidator(0,9999,this));
    connect(ui->confirmButton,SIGNAL(released()),this,SLOT(handleConfirmButton()));
    connect(ui->cancelButton, SIGNAL(released()),this,SLOT(handleCancelButton()));
    connect(ui->confirmButton,SIGNAL(released()),parent,SLOT(refreshItemTable()));
}

Add_Sku_Dialog::~Add_Sku_Dialog()
{
    delete ui;
}


void Add_Sku_Dialog::handleConfirmButton()
{
    QMessageBox msgBox;
    if(ui->nameLineEdit->text().isEmpty()!=0)
    {
        msgBox.information(this,"品名为空","sku名称不能为空，请输入名品");
    }
    else
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data.db");
        if (!db.open())
        {
            qDebug() << "Database Error!";
        }
        else
        {
            QSqlQuery myQuery;
            myQuery.prepare("INSERT INTO allItem (id, name) VALUES (:id, :name)");
            myQuery.bindValue(":id",ui->idLineEdit->text().toInt());
            myQuery.bindValue(":name",ui->nameLineEdit->text());
            if(!myQuery.exec())
            {
                qDebug()<<myQuery.lastError();
            }
            db.close();
        }
    }
}

void Add_Sku_Dialog::handleCancelButton()
{
    done(0);
}

