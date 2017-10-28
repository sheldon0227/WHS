#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void addSku();
    void refreshItemTable();

private:
    Ui::MainWindow *ui;
    void initial();
};

#endif // MAINWINDOW_H
