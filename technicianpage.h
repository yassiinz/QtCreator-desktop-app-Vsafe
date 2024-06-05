#ifndef TECHNICIANPAGE_H
#define TECHNICIANPAGE_H

#include <QWidget>
#include "utilisateur.h"
#include "mainwindow.h"
#include "adminvehicles.h"
namespace Ui {
class technicianpage;
}

class technicianpage : public QWidget
{
    Q_OBJECT

public:
    explicit technicianpage(QWidget *parent = nullptr);
    ~technicianpage();
    void getEmail(QString email);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::technicianpage *ui;
    AdminVehicles *adv;
    QString tech_email;


};

#endif // TECHNICIANPAGE_H
