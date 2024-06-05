#ifndef PISTE_H
#define PISTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class piste
{

public:

    QString etat,pisteImg;
    int num,capacite;

public:
    //Constructeurs
    piste();
    piste(int,int,QString,QString);

    //Getters
    int getNum(){return num;}
    int getCapacite(){return capacite;}
    QString getEtat(){return etat;}
    QString getImage(){return pisteImg;}


    //Setters
    void setNum(int numm)
    {
        num=numm;
    }

    void setCapacite(int capacitee)
    {
        capacite=capacitee;
    }

    void setEtat(QString etatt)
    {
        etat=etatt;
    }

    void setImage(QString Img)
    {
        pisteImg=Img;
    }



    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherHistorique();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* RechercherPiste(QString);
    QSqlQueryModel * trierCapacite();
    QSqlQueryModel * trierEtat();
    void sendSMS(QString, QString, QString, QString, QString);



};

#endif // PISTE_H
