#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QWidget>
#include"utilisateur.h"
#include "smtp.h"
#include <cstdlib>
#include <ctime>
#include "newpassword.h"
namespace Ui {
class ResetPassword;
}

class ResetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ResetPassword(QWidget *parent = nullptr);
    ~ResetPassword();

private slots:

    void sendMail();

        void mailSent(QString);

        void on_verifyBtn_clicked();

private:
    Ui::ResetPassword *ui;
    QString v_codeString;
    NewPassword *np;
    QString m_email;
};

#endif // RESETPASSWORD_H
