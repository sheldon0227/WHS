#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_sku_dialog.h"
#include <QSqlQuery>
#include <QSql>
#include <qsqlerror.h>
#include <QLabel>
#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <qfileinfo.h>
using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setSizeGripEnabled(false);
    QLabel *version = new QLabel(this);
    //版本号
    version->setText("Version 1.0 beta ");
    version->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addPermanentWidget(version);


    //初始化(仅第一次)
    QFileInfo database("data.db");
    if (database.isFile())
    {
        ui->statusBar->showMessage(tr("轩轩：检测到数据库！"),4000);
        qDebug()<<"database is set!";
    }
    else
    {
        ui->statusBar->showMessage(tr("轩轩：检测第一次使用，初始化数据库"),4000);
        initial();//数据库不存在时初始化数据库
    }

    connect(ui->addSkuAction,SIGNAL(triggered(bool)),this,SLOT(addSku()));
    //Test Area

    //初始化tabwidget
    ui->tabWidget->addTab(ui->tab1,"桃子公主sku清单");
    ui->tabWidget->addTab(ui->tab2,"微信出货助手");




    //初始化总sku table
    ui->itemMainTable->setColumnCount(2);
    QStringList itemTableHorizontalHeader;
    itemTableHorizontalHeader.append("SKU ID");
    itemTableHorizontalHeader.append("SKU 名称");
    ui->itemMainTable->verticalHeader()->setVisible(false);
    ui->itemMainTable->setHorizontalHeaderLabels(itemTableHorizontalHeader);
    ui->itemMainTable->setColumnWidth(0,100);
    ui->itemMainTable->setColumnWidth(1,410);
    ui->itemMainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->itemMainTable->setSelectionMode((QAbstractItemView::SingleSelection));
    ui->itemMainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshItemTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","Main");
    db.setDatabaseName("data.db");
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else{
        QSqlQuery myQuery(db);
        myQuery.prepare("CREATE TABLE allItem (id INTEGER UNIQUE PRIMARY KEY, name NCHAR)");
        if(!myQuery.exec())
        {
            qDebug()<<myQuery.lastError();
        }
        db.close();
    }
}

void MainWindow::addSku()
{
    Add_Sku_Dialog dialog(this);
    dialog.setWindowTitle("添加新SKU");
    //connect(&Dialog,SIGNAL(valueSend(QString)),this,SLOT(valueRec(QString)));
    dialog.exec();
}

void MainWindow::refreshItemTable()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("Main"))
        db = QSqlDatabase::database("Main");
    else
        db = QSqlDatabase::addDatabase("QSQLITE", "Main");
    db.setDatabaseName("data.db");
    if (!db.open()) {
        qDebug() << "Database Error!";
    }
    else{
        QSqlQuery myQuery(db);
        myQuery.prepare("SELECT * FROM allItem ORDER BY id");
        if(!myQuery.exec())
        {
            qDebug()<<myQuery.lastError();
        }
        ui->itemMainTable->clearContents();
        ui->itemMainTable->setRowCount(0);
        while(myQuery.next())
        {
            ui->itemMainTable->setRowCount(ui->itemMainTable->rowCount()+1);
            ui->itemMainTable->setItem(ui->itemMainTable->rowCount()-1,0,new QTableWidgetItem(myQuery.value(0).toString()));
            ui->itemMainTable->setItem(ui->itemMainTable->rowCount()-1,1,new QTableWidgetItem(myQuery.value(1).toString()));
        }
        db.close();
    }
    db.close();
}

//void MainWindow::valueRec(QString v)
//{
//    VALUE = v;
//}

//MainWindow::clickResetButton()
//{

//}
