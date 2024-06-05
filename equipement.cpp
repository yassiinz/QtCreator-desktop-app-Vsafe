#include "equipement.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QtCore/QBuffer>
#include <QFile>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QBuffer>
#include <QImage>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QSortFilterProxyModel>


equipement::equipement()
{
    ref=0 ;qte=0; libelle=""; type=""; etat=""; imageData ;
}

equipement::equipement(int ref, int qte, const QString libelle, const QString type,  const QString etat ,const QByteArray imageData)
{
    this->ref=ref;
    this->qte=qte;
    this->libelle=libelle;
    this->type=type;
    this->etat=etat;
    this->imageData=imageData;
}

int getref();
int getqte();
QString getlibelle();
QString gettype();
QString getetat();
QByteArray getimageData();

void setref(int);
void setqte(int);
void setlibelle(QString);
void settype(QString);
void setetat(QString);
void setimageData(QByteArray());

bool equipement::ajouter()
{

    foreach(QChar c, libelle) {
         if (!c.isLetter()) {
             QMessageBox::critical(nullptr, "Error", "libelle Must be in letters.");

             return false;
         }
     }

    QSqlQuery query;

    QString res = QString::number(ref);




    query.prepare(" insert into EQUIPEMENT (ref, qte, libelle, type, etat, img) values(:ref, :qte, :libelle, :type, :etat, :image)");
    query.bindValue(":ref", res);
    query.bindValue(":qte", qte);
    query.bindValue(":libelle", libelle);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":image", imageData);





    return query.exec();
}

QSqlQueryModel * equipement::afficher()
{


    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from EQUIPEMENT");

    model->setHeaderData (0,Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QTE"));
    model->setHeaderData (3,Qt::Horizontal,QObject::tr("LIBELLE"));
    model->setHeaderData (5,Qt::Horizontal,QObject::tr("TYPE"));
     model->setHeaderData (6,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData (7,Qt::Horizontal,QObject::tr("IMG"));

    QSqlQuery query;

    query.prepare("SELECT IMG FROM EQUIPEMENT WHERE ref = ?");
    query.addBindValue(ref);
    query.exec();

    if (query.next()) {
        // Get the image data from the query result
        QByteArray imageData = query.value(0).toByteArray();

        // Convert the image data to a QPixmap
        QPixmap image;
        image.loadFromData(imageData);


    }

    return model;
}

bool equipement::supprimer(int ref)
{

    QSqlQuery query;

    QString res = QString::number(ref);
    query.prepare("delete from EQUIPEMENT where ref= :ref");
    query.bindValue(":ref",res);
    return query.exec();



}

bool equipement::modifier(int ref)
{
    foreach(QChar c, libelle) {
         if (!c.isLetter()) {
             QMessageBox::critical(nullptr, "Error", "libelle Must be in letters.");

             return false;
         }
     }

    QSqlQuery query;
    QString res = QString::number(ref);
    query.prepare("UPDATE  EQUIPEMENT SET REF= :ref,QTE= :qte, LIBELLE= :libelle, TYPE= :type where REF=:ref");
    query.bindValue(":ref", ref);
    query.bindValue(":qte", qte);
    query.bindValue(":libelle", libelle);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    return query.exec();
}// changer un onglet






QByteArray equipement::getImageDataFromDatabase(int ref)
{


    QSqlQuery query;
    query.prepare("SELECT img FROM EQUIPEMENT WHERE REF = :ref");
    query.bindValue(":ref", ref);

    // Execute the query and retrieve the image data
    if (!query.exec() || !query.next()) {
        qWarning() << "Failed to retrieve image data from database";
        return QByteArray();
    }

    return query.value(0).toByteArray();
}



void equipement::checkPrimaryKeyCount(int target_number)
{
    QSqlQuery query(QSqlDatabase::database());
    QString column_name = "ETAT";
    QString column_value = "Non Fonctionnel";
    QString qte_column_name = "QTE";

    query.prepare("SELECT FROM EQUIPEENT  ETAT, COUNT(*), SUM(QTE) FROM EQUIPEMENT WHERE ETAT=:value GROUP BY TYPE");

    query.bindValue(":value", column_value);
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Query Error", query.lastError().text());
        return;
    }
    QString result = "TYPE\\SUM\n";
        while (query.next()) {
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();
            int sum = query.value(2).toInt();
            result += type + "\t" + QString::number(count) + "\t" + QString::number(sum) + "\n";


        QMessageBox::information(nullptr, "Results", result);

        QMessageBox::information(nullptr, "Results", result + "\nPrimary key count: " + QString::number(count) + "\nQTE sum: " + QString::number(sum));

        if (result >= target_number) {
            QMessageBox::information(nullptr, "Notification", "Target number of primary keys reached!");
        } else {
            QMessageBox::information(nullptr, "Notification", "You still have some space.");
        }
}
}


