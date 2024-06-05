#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QWidget>
#include "utilisateur.h"
namespace Ui {
class NewPassword;
}

class NewPassword : public QWidget
{
    Q_OBJECT

public:
    explicit NewPassword(QWidget *parent = nullptr);
    ~NewPassword();

void getEmail(QString email);

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewPassword *ui;
    QString l_email;
};

#endif // NEWPASSWORD_H
