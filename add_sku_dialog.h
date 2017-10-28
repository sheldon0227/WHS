#ifndef ADD_SKU_DIALOG_H
#define ADD_SKU_DIALOG_H

#include <QDialog>

namespace Ui {
class Add_Sku_Dialog;
}

class Add_Sku_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Sku_Dialog(QWidget *parent = 0);
    ~Add_Sku_Dialog();

private slots:
    void handleConfirmButton();
    void handleCancelButton();

private:
    Ui::Add_Sku_Dialog *ui;
};

#endif // ADD_SKU_DIALOG_H
