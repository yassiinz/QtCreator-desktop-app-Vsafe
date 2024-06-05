#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include<QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>
#include <QChar>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include "utilisateur.h"

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Signup *ui;
    Utilisateur u;

};

#endif // SIGNUP_H
