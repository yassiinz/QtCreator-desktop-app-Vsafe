#ifndef INVOICERPAGE_H
#define INVOICERPAGE_H

#include <QWidget>
#include "utilisateur.h"
#include "mainwindow.h"
#include "admininvoice.h"
#include "clientmanagement.h"
namespace Ui {
class invoicerpage;
}

class invoicerpage : public QWidget
{
    Q_OBJECT

public:
    explicit invoicerpage(QWidget *parent = nullptr);
    ~invoicerpage();
    void getEmail(QString email);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::invoicerpage *ui;
    QString inv_email;
    AdminInvoice *adi;
    clientmanagement *cm;
};

#endif // INVOICERPAGE_H
