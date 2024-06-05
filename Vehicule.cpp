#include "Vehicule.h"
#include <QMessageBox>
#include <QStandardItem>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include<QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>
#include <QChar>







Vehicule::Vehicule(QString SERIE_VEHICULE,QString Marque,QDateTime DPMC,QString Categorie,QString VIN,double Montant,int CIN)
{
    this->SERIE_VEHICULE=SERIE_VEHICULE;
    this->Marque=Marque;
    this->DPMC=DPMC;
    this->Categorie=Categorie;
    this->VIN=VIN;
    this->Montant=Montant;
    this->CIN=CIN;
}


//*--------------------------------------------------Ajouter Vehicule----------------------------------------------------------*//


bool Vehicule ::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO VEHICULE(SERIE_VEHICULE, MARQUE, DPMC, VIN, Categorie,Montant,CIN)" "VALUES(:SERIE_VEHICULE, :MARQUE, :DPMC, :VIN, :Categorie, :Montant,:CIN)");

      query.bindValue(":SERIE_VEHICULE",SERIE_VEHICULE);
      query.bindValue(":MARQUE",Marque);
      query.bindValue(":DPMC",DPMC);
      query.bindValue(":Categorie",Categorie);
      query.bindValue(":VIN",VIN);
      query.bindValue(":Montant",Montant);
      query.bindValue(":CIN",CIN);

    return query.exec();

}


//*--------------------------------------------------Afficher Vehicule----------------------------------------------------------*//


QSqlQueryModel * Vehicule :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT SERIE_VEHICULE , MARQUE , Categorie , VIN , DPMC , Montant, CIN from VEHICULE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("License Plate"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("VIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Category"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("DPMC"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Amount (TND)"));


QDateTime dateTime = QDateTime::currentDateTime();
//QStandardItem *timeItem = new QStandardItem(timeString);
//model->setItem(row, column, timeItem);

return model;
}
QSqlQueryModel * Vehicule :: afficherF()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT SERIE_VEHICULE , MARQUE , Montant from VEHICULE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("License Plate"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Amount"));

QDateTime dateTime = QDateTime::currentDateTime();
//QStandardItem *timeItem = new QStandardItem(timeString);
//model->setItem(row, column, timeItem);

return model;
}
QSqlQueryModel * Vehicule :: afficherR()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT * FROM VEHICULE ORDER BY SERIE_VEHICULE DESC LIMIT 1");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("License Plate"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("VIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Category"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Amount"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Client ID"));


QDateTime dateTime = QDateTime::currentDateTime();
//QStandardItem *timeItem = new QStandardItem(timeString);
//model->setItem(row, column, timeItem);

return model;
}
//*--------------------------------------------------Supprimer Vehicule----------------------------------------------------------*//


bool Vehicule ::supprimer(QString SERIE_VEHICULE)
{


    QSqlQuery query;

     query.prepare("Delete from VEHICULE where SERIE_VEHICULE= :SERIE_VEHICULE");
     query.bindValue(":SERIE_VEHICULE",SERIE_VEHICULE);
     return query.exec();
}


bool Vehicule::rechercher(int SERIE_VEHICULE)
{
    // Requête SQL pour récupérer les informations du véhicule avec l'identifiant id
    QSqlQuery query;
    query.prepare("SELECT * FROM VEHICULE WHERE SERIE_VEHICULE= :SERIE_VEHICULE");
    query.bindValue(":SERIE_VEHICULE", SERIE_VEHICULE);
    if (query.exec() && query.first()) {
// Si la vehicule = 1 , alors il y a un mise a jour
        this->setid(query.value("SERIE_VEHICULE").toString());

        return true;
    }
    return false;
}

//*--------------------------------------------------Modifier Vehicule----------------------------------------------------------*//

bool Vehicule::modifier(QString SERIE_VEHICULE)
{

    QSqlQuery query;
    query.prepare("UPDATE VEHICULE SET SERIE_VEHICULE=:SERIE_VEHICULE,MARQUE=:MARQUE,VIN=:VIN,Categorie=:Categorie,DPMC=:DPMC,Montant=:Montant, CIN=:CIN where SERIE_VEHICULE=:SERIE_VEHICULE");
    query.bindValue(":SERIE_VEHICULE",SERIE_VEHICULE);
    query.bindValue(":MARQUE",Marque);
    query.bindValue(":DPMC",DPMC);
    query.bindValue(":Categorie",Categorie);
    query.bindValue(":VIN",VIN);
    query.bindValue(":Montant",Montant);
    query.bindValue(":CIN",CIN);
    return query.exec();
}

QSqlQueryModel* Vehicule::rechercher(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT SERIE_VEHICULE , MARQUE , VIN , DPMC , Categorie , Montant, CIN from VEHICULE  WHERE SERIE_VEHICULE LIKE :valeur or Marque LIKE :valeur or VIN LIKE :valeur or DPMC LIKE :valeur or Categorie LIKE :valeur or Montant LIKE :valeur or CIN LIKE :valeur");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Vehicule::rechercherF(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT SERIE_VEHICULE , MARQUE , VIN , DPMC , Categorie , Montant, CIN from VEHICULE  WHERE SERIE_VEHICULE LIKE :valeur or Marque LIKE :valeur or VIN LIKE :valeur or DPMC LIKE :valeur or Categorie LIKE :valeur or Montant LIKE :valeur or CIN LIKE :valeur");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel* Vehicule::rechercherM(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT SERIE_VEHICULE , MARQUE , VIN , DPMC , Categorie , Montant, CIN from VEHICULE  WHERE SERIE_VEHICULE LIKE :valeur or Marque LIKE :valeur or VIN LIKE :valeur or DPMC LIKE :valeur or Categorie LIKE :valeur or Montant LIKE :valeur or CIN like :va8leur");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel* Vehicule::rechercherC(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT SERIE_VEHICULE , MARQUE , Categorie , DPMC , VIN, CIN from VEHICULE  WHERE Categorie LIKE :valeur or Marque LIKE :valeur or VIN LIKE :valeur or DPMC LIKE :valeur or Categorie LIKE :valeur or CIN LIKE :valeur");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}



QSqlQueryModel * Vehicule::triID()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT SERIE_VEHICULE , MARQUE , Categorie , DPMC , VIN, CIN from VEHICULE order by SERIE_VEHICULE ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("License Plate"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Brand"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VIN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DPMC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Client ID"));

    return model;
}

QSqlQueryModel * Vehicule::triMarque()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT SERIE_VEHICULE , MARQUE , Categorie , DPMC , VIN, CIN from VEHICULE order by MARQUE ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("License Plate"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Brand"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VIN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DPMC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Client ID"));
    return model;
}


QSqlQueryModel * Vehicule::triCat()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT SERIE_VEHICULE , MARQUE , Categorie , DPMC , VIN, CIN from VEHICULE order by Categorie ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("License Plate"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Brand"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VIN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DPMC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Client ID"));

    return model;
}
