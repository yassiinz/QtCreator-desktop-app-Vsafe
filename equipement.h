#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include<QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>
#include <QChar>
#include <QImage>
#include <QMainWindow>

class equipement
{
    int ref,qte;
    QString libelle,type,etat;
    QByteArray imageData;


public:
      equipement();
      equipement(int,int,QString,QString,QString,QByteArray);
      int getref(){return ref;}
      int getqte(){return qte;}
      QString getlibelle(){return libelle;}
      QString gettype(){return type;}
      QString getetat(){return etat;}
      QByteArray getimage(){return imageData;}

      void setref(int r){this->ref=r;}
      void setqte(int q){this->qte=q;}
      void setlibelle(QString l){this->libelle=l;}
      void settype(QString t){this->type=t;}
      void setetat(QString e){this->etat=e;}
      void setimage(QByteArray i){this->imageData=i;}

      bool ajouter();
      QSqlQueryModel * afficher();
      bool supprimer(int ref);
      bool modifier(int ref);
      void displayImage1(int ref);
      void displayImage();
      QByteArray getImageDataFromDatabase(int ref);
      void btnDisplayImage();
      void checkPrimaryKeyCount(int target_number);

private slots:


      void on_btnDisplayImage_clicked();

private:






};

#endif // EQUIPEMENT_H
