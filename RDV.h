#ifndef RDV_H
#define RDV_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>
#include<QDate>
#include<QTime>
#include<QTextCharFormat>
#include<QCalendarWidget>
#include<QComboBox>
class RDV
{
    int num,id;
    QString centre;
    QDate date_rdv;
    QTime heure_rdv;
    int cin;
    QString activite_h;
    QDate date_h;
public:
    RDV(){}
    RDV(int,QString,QDate,QTime,int,int);
        int  getid(){return id;}
        QString getcentre(){return centre;}
        QDate  getdate_s(){return date_rdv;}
        QTime gettime (){return heure_rdv;}
        int  getnum(){return num;}
        int  getcin(){return cin;}

        //

        void setid(int i){id=i;}
        void setnom(QString ce){centre=ce;}
        void setmail(QDate da){date_rdv=da;}
        void setheure(QTime ti){heure_rdv=ti;}
        void setnum(int n){num=n;}
        void setcin(int c){num=c;}

        //
        bool ajouter();
        //bool ajouterhistorique();
        QSqlQueryModel * afficher();
        bool supprimer (int id);
        bool modifier(int id);
        QSqlQueryModel *tri();
        QSqlQueryModel *tricentre();
        QSqlQueryModel *tripiste();
        QSqlQueryModel *recherche(int);
        QSqlQueryModel *recherche_centre(QString);
        QSqlQueryModel *recherche_piste(int);
        void statistique(QVector<double>* ticks,QVector<QString> *labels);
        void calendrier(QTextCharFormat ,QCalendarWidget * );
        QSqlQueryModel * afficherHistorique();

};
#endif // RDV_H
