#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include<QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>
#include <QChar>
#include <QSortFilterProxyModel>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QHBoxLayout>
#include <QCryptographicHash>
#include <QByteArray>
#include "smtp.h"
#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QIntValidator>
#include <QMainWindow>
#include <QPrinter>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextDocument>
#include <QTextStream>
#include <QUrl>
#include <QUrlQuery>

class Utilisateur
{
    QString ID , prenom , nom , fonction , mail , mdp;
    QDateTime date_emb;
    int tlf;
    float salaire;

public:
    //Constructeurs
    Utilisateur(){}
    Utilisateur(QString,QString,QString,QString,int,QString,QDateTime,QString,float );

    //Getters
    QString getID(){return ID;}
    QString getMDP(){return mdp;}
    QString getPrenom(){return prenom;}
    QString getNom(){return nom;}
    int getTlf(){return tlf;}
    QString getFonction(){return fonction;}
    float getSalaire(){return salaire;}
    QDateTime getHD(){return date_emb;}
    QString getMail(){return mail;}

   //Setters
    void setID(QString id) {this->ID=id;}
    void setMdp(QString pw){this->mdp=pw;}
    void setPrenom(QString p){this->prenom=p;}
    void setNom(QString n){this->nom=n;}
    void setTlf(int t){this->tlf=t;}
    void setFonction(QString f){this->fonction=f;}
    void setSalaire(float s){this->salaire=s;}
    void setHD(QDateTime d){this->date_emb=d;}
    void setMail(QString m){this->mail=m;}

    //FONCTIONS de bases relatives a l'entité Utilisateur
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
   bool update(QString);
   bool verifierid(QString);
};

#endif // UTILISATEUR_H
