#include "RDV.h"
#include <QMessageBox>
#include <QStandardItem>

RDV::RDV(int id,QString centre,QDate date_rdv,QTime heure_rdv,int num,int cin)
{
    this->id=id;
    this->centre=centre;
    this->date_rdv=date_rdv;
    this->heure_rdv=heure_rdv;
    this->num=num;
    this->cin=cin;
}


//*--------------------------------------------------Ajouter un Rendez_vous----------------------------------------------------------*//


bool RDV ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(id);
    QString ras = QString :: number(num);
    QString ros = QString :: number(cin);
    query.prepare("insert into RDV(ID_RDV,CENTRE,DATE_RDV,HOUR_RDV,N_PISTE,CIN_CLIENT) values(:id,:centre,:date_rdv,:heure_rdv,:num,:cin)");
    //
    query.bindValue(":id",res);
    query.bindValue(":centre",centre);
    query.bindValue(":date_rdv",date_rdv);
    query.bindValue(":heure_rdv",heure_rdv);
    query.bindValue(":num",ras);
    query.bindValue(":cin",cin);


    return query.exec();
}


//*--------------------------------------------------Afficher un Rendez_vous----------------------------------------------------------*//


QSqlQueryModel * RDV :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT ID_RDV , CENTRE , DATE_RDV , HOUR_RDV , N_PISTE , CIN_CLIENT from RDV");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));
//QDateTime dateTime = QDateTime::currentDateTime();
//QString timeString = dateTime.toString("hh:mm:ss");
//QStandardItem *timeItem = new QStandardItem(timeString);
return model;
}


//*--------------------------------------------------Supprimer un Rendez_vous----------------------------------------------------------*//


bool RDV ::supprimer(int id)
{
QSqlQuery query;
QString res=QString ::number(id);
query.prepare("delete from RDV where ID_RDV= :id");
query.bindValue(":id",res);
return query.exec();
}


//*--------------------------------------------------Modifier un Rendez_vous----------------------------------------------------------*//


bool RDV::modifier(int id)
{
    QSqlQuery query;
    QString res=QString ::number(id);
    query.prepare("UPDATE RDV SET ID_RDV=:id,CENTRE=:centre,DATE_RDV=:date_rdv,HOUR_RDV=:heure_rdv,N_PISTE=:num,CIN_CLIENT=:cin where ID_RDV=:id");
    query.bindValue(":id",res);
    query.bindValue(":centre",centre);
    query.bindValue(":date_rdv",date_rdv);
    query.bindValue(":heure_rdv",heure_rdv);
    query.bindValue(":num",num);
    query.bindValue(":cin",cin);
    return query.exec();
}


//*--------------------------------------------------TRI_ID----------------------------------------------------------*//

QSqlQueryModel* RDV::tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV order by ID_RDV");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

   return model;

}


//*--------------------------------------------------TRI_CENTRE----------------------------------------------------------*//


QSqlQueryModel* RDV::tricentre()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV order by CENTRE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

   return model;

}


//*--------------------------------------------------TRI_N°_PISTE----------------------------------------------------------*//


QSqlQueryModel* RDV::tripiste()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV order by N_PISTE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

   return model;

}


//*--------------------------------------------------RECHERCHE_ID----------------------------------------------------------*//

QSqlQueryModel* RDV::recherche(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
                QString res=QString ::number(id);
            model->setQuery("select * from RDV where ID_RDV='"+res+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));
   return model;

}


//*--------------------------------------------------RECHERCHE_CENTRE----------------------------------------------------------*//


QSqlQueryModel* RDV::recherche_centre(QString centre)
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV where CENTRE='"+centre+"'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

   return model;

}


//*--------------------------------------------------RECHERCHE_N°_PISTE----------------------------------------------------------*//

QSqlQueryModel* RDV::recherche_piste(int num)
{
    QSqlQueryModel *model=new QSqlQueryModel();
                QString ras=QString ::number(num);
            model->setQuery("select * from RDV where N_PISTE='"+ras+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("CENTRE"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("N°_PISTE"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_CLIENT"));
   return model;

}


//*--------------------------------------------------STATISTIQUE----------------------------------------------------------*//


void RDV::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select ID_RDV from RDV");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}


//*--------------------------------------------------CALENDRIER----------------------------------------------------------*//


void RDV::calendrier(QTextCharFormat f,QCalendarWidget * w)
  {
      QDate date;
      QSqlQuery query("SELECT DATE_RDV FROM RDV");
      while (query.next())
      {
          date=query.value(0).toDate();
          w->setDateTextFormat(date,f);
      }
      w->setDateTextFormat(date,f);
  }




QSqlQueryModel * RDV::afficherHistorique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Activité"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

    return model;
}

/*bool RDV ::ajouterhistorique()
{
    QSqlQuery query;
    QSqlQuery qry;
            QDateTime dateTime=QDateTime::currentDateTime();

            QString date=dateTime.toString();

            query.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Modification d un piste',:dateTime)");
            query.bindValue(":dateTime",dateTime);


    return query.exec();
}*/
