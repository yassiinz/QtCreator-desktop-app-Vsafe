#ifndef CLIENT_H
#define CLIENT_H

#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include "qrencode.h"

class Client
{
    int cin, phone;
    QString fname, lname, mail;
    QImage qr;

public:
    //Constructors and destructors
    Client();
    Client(QString fn, QString ln, int id, int ph, QString m);
    ~Client();
    //Getters
    QString getFn() { return fname; }
    QString getLn() { return lname; }
    int getID() { return cin; }
    int getPh() { return phone; }
    QString getM() { return mail; }
    QImage getQR() { return qr; }
    //Setters
    void setFn(QString val) { fname = val; }
    void setLn(QString val) { lname = val; }
    void setID(int val) { cin = val; }
    void setPh(int val) { phone = val; }
    void setM(QString val) { mail = val; }
    void setQR(QImage val) { qr = val; }
    //Functions
    bool add();
    bool del(int id);
    QSqlQueryModel *show();
    bool update(int id);
    int check(int id);
    void genQR(QString);
};

#endif // CLIENT_H
