#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    MainWindow w;
    w.setWindowFlags(flags);
    w.setFixedSize(550,790);
    w.setWindowTitle("桃子公主仓储系统");
    w.show();
    //qDebug()<<QSqlDatabase::drivers(); 检测Qt支持的SQL种类

    return a.exec();
}
