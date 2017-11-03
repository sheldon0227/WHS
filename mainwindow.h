#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendUserPhone(double);

private slots:
    void addSku();
    void addUser();
    void refreshItemTable();
    void refreshUserTable();
    void enterUser(QTableWidgetItem*);

private:
    Ui::MainWindow *ui;
    void initial();
};

#endif // MAINWINDOW_H
