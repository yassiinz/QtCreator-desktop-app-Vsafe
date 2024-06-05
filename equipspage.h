#ifndef EQUIPSPAGE_H
#define EQUIPSPAGE_H

#include <QWidget>
#include "utilisateur.h"
#include "mainwindow.h"
#include "adminequipment.h"
#include "equipmanagement.h"

namespace Ui {
class equipspage;
}

class equipspage : public QWidget
{
    Q_OBJECT

public:
    explicit equipspage(QWidget *parent = nullptr);
    ~equipspage();
    void getEmail(QString email);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::equipspage *ui;
    QString eq_email;
    equipmanagement *ade;
};

#endif // EQUIPSPAGE_H
