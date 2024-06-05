#include "piste.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QApplication>

piste::piste()
{

}

piste::piste(int num,int capacite,QString etat,QString pisteImg)
{
    this->num=num;
    this->capacite=capacite;
    this->etat=etat;
    this->pisteImg=pisteImg;
}


bool piste::ajouter()
{
    QSqlQuery query;
    QString num_string = QString::number(num);
    QString capacite_string = QString::number(capacite);

    //prepare() prend la requête en paramètre pour la préparer à l'exécution
    query.prepare("insert into PISTE(NUM,CAPACITE,ETAT,IMG)"
                  "values (:num,:capacite,:etat,:img)");

    //création des variables liées
    query.bindValue(":num",num_string);
    query.bindValue(":capacite",capacite_string);
    query.bindValue(":etat",etat);
    query.bindValue(":img",pisteImg);

    return query.exec();
    // exec() envoie la requete pour l'exécution
}

bool piste::modifier()
{
    QSqlQuery query;
    query.prepare("Update PISTE set NUM=:num,CAPACITE=:capacite,ETAT=:etat, IMG=:img where NUM=:num");
    query.bindValue(":num",num);
    query.bindValue(":capacite",capacite);
    query.bindValue(":etat",etat);
    query.bindValue(":img",pisteImg);

    return query.exec();
}


QSqlQueryModel * piste::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Piste");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numéro Piste"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Capacité Piste"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat Piste"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Image"));

    return model;
}


QSqlQueryModel * piste::afficherHistorique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Activité"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

    return model;
}


bool piste::supprimer(int num)
{
    QSqlQuery query;
    QString num_string=QString::number(num);

    query.prepare("Delete from piste where num= :num");
    query.bindValue(":num",num_string);

    return query.exec();
}


QSqlQueryModel* piste::RechercherPiste(QString recherche)
{
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM PISTE WHERE CAPACITE LIKE '"+recherche+"%' OR ETAT LIKE '"+recherche+"%' ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numéro Piste"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Capacité Piste"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat Piste"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Image"));

return model;
}



QSqlQueryModel * piste::trierCapacite()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PISTE ORDER BY CAPACITE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numéro Piste"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Capacité Piste"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat Piste"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Image"));

    return model;
}


QSqlQueryModel * piste::trierEtat()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PISTE ORDER BY ETAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numéro Piste"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Capacité Piste"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat Piste"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Image"));

    return model;
}


