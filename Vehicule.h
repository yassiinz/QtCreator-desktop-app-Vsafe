#ifndef VEHICULE_H
#define VEHICULE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include<QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>
#include <QChar>

class Vehicule
{
    QString SERIE_VEHICULE;
    QString Marque,VIN,Categorie;
    QDateTime DPMC;
    double Montant;
    int CIN;
public:
    Vehicule(){}
    Vehicule(QString,QString,QDateTime,QString,QString,double,int);
        QString  getid(){return SERIE_VEHICULE;}
        QString getMarque(){return Marque;}
        QDateTime  getDPMC(){return DPMC;}
        QString getVIN (){return VIN;}
        QString  getCategorie(){return Categorie;}
        int  getMontant(){return Montant;}
        int getCIN(){return CIN;}


        //

        void setid(QString i){SERIE_VEHICULE=i;}
        void setMarque(QString Marque);
        void setDPMC(QDateTime DPMC);
        void setCategorie(QString Categorie);
        void setVIN(QString VIN);
        void setCIN(int CIN);

        //
        bool ajouter();

        QSqlQueryModel * afficher();
        QSqlQueryModel * afficherF();
        bool supprimer (QString SERIE_VEHICULE);
        bool modifier(QString SERIE_VEHICULE);
        bool rechercher(int);
        QSqlQueryModel *chercher(int);
        QSqlQueryModel * rechercher(QString valeur);
        QSqlQueryModel * rechercherF(QString valeur);

        QSqlQueryModel * triID();
        QSqlQueryModel * triMarque();
        QSqlQueryModel * triCat();
        QSqlQueryModel * rechercherM(QString valeur);
        QSqlQueryModel * rechercherC(QString valeur);
        QSqlQueryModel * afficherR();


};
#endif // VEHICULE_H
