#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include "utilisateur.h"
#include "clientmanagement.h"
#include "mainwindow.h"
#include "adminequipment.h"
#include "admininvoice.h"
#include "adminschedule.h"
#include "adminvehicles.h"
#include "adminpiste.h"
#include "clientmanagement.h"
#include "equipmanagement.h"

namespace Ui {
class adminpage;
}

class adminpage : public QWidget
{
    Q_OBJECT

public:
    explicit adminpage(QWidget *parent = nullptr);
    ~adminpage();

    void getEmail(QString email);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::adminpage *ui;
    MainWindow *m;
    AdminVehicles *av;
    AdminSchedule *asc;
    equipmanagement *ae;
    QString ad_email;
    AdminInvoice *ai;
    clientmanagement *cm;
    AdminPiste *ap;


};

#endif // ADMINPAGE_H
