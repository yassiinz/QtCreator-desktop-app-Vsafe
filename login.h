#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "utilisateur.h"
#include "signup.h"
#include "adminpage.h"
#include "resetpassword.h"
#include "equipspage.h"
#include "invoicerpage.h"
#include "technicianpage.h"
#include "schedulerpage.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();




    void on_sendbutton_clicked();

private:
    Ui::login *ui;
    MainWindow *m;
   Signup *s;
adminpage *a;
ResetPassword *rp;
technicianpage *tp;
invoicerpage *ip;
equipspage *ep;
schedulerpage *sp;


};

#endif // LOGIN_H
