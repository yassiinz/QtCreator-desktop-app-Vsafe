#include "adminpiste.h"
#include "ui_adminpiste.h"
#include "piste.h"
#include <QMessageBox>
#include <QDateTime>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#define STRING_RX "([A-Z][a-z]*)([\\s\\\'.][A-Z][a-z]*)*"

AdminPiste::AdminPiste(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPiste)
{
    ui->setupUi(this);

    //Controle de saisie sur le num/capacite
    ui->lineEditNum->setValidator(new QIntValidator(1,9999999,this)); //Ajout
    ui->lineEditNum_2->setValidator(new QIntValidator(1,9999999,this)); //Modification
    ui->lineEditCapacite->setValidator(new QIntValidator(1,99,this)); //Ajout
    ui->lineEditCapacite_2->setValidator(new QIntValidator(1,99,this)); //Modification

    ui->tableViewAffichage->setModel(p.afficher());
    //arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getArduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getArduino_port_name();
                 break;
              case(-1):qDebug() << "arduino is not available";
              }
}

AdminPiste::~AdminPiste()
{
    delete ui;
}

QString pisteImg ="";

void AdminPiste::on_pushButtonModifier_clicked()
{
    QString trad=ui->selectTraduction->currentText();
    piste p;
    p.setNum(ui->lineEditNum_2->text().toInt());
    p.setCapacite(ui->lineEditCapacite_2->text().toInt());
    p.setEtat(ui->comboBoxEtat_2->currentText());
    p.setImage(pisteImg);

   bool check=p.modifier();

    if (check)
    {
        //Refresh (Actualiser)
        ui->tableViewAffichage->setModel(p.afficher());
        if (trad=="Français")
        {
            QMessageBox::information(nullptr, QObject::tr("RDI Center"),
                                      QObject::tr("Modification avec succés.\n"
                                                  "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);

        }
        else if (trad=="Anglais")
        {
            QMessageBox::information(nullptr, QObject::tr("RDI Center"),
                                  QObject::tr("Change successfully.\n"
                                              "Click cancel to exit."), QMessageBox::Cancel);
        }
        ui->lineEditNum_2->clear();
        ui->lineEditCapacite_2->clear();
        ui->comboBoxEtat_2->setCurrentText("Veuillez choisir l'etat");

        /*HISTORIQUE*/
        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();

        QString date=dateTime.toString();

        qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Modification d un piste',:dateTime)");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();
    }
    else
    {
        if (trad=="Français")
        {
            QMessageBox::critical(nullptr, QObject::tr("RDI Center"),
                                  QObject::tr("Modification échouée.\n"
                                              "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);
        }
        else if (trad=="Anglais")
        {
            QMessageBox::critical(nullptr, QObject::tr("RDI Center"),
                                  QObject::tr("Change failed.\n"
                                              "Click cancel to exit."), QMessageBox::Cancel);
        }
    }
}



void AdminPiste::on_pushButtonActualiser_clicked()
{
    ui->tableViewAffichage->setModel(p.afficher());
}

void AdminPiste::on_pushButtonSupprimer_clicked()
{
    QString trad=ui->selectTraduction->currentText();
    int num=ui->lineEditSupprimer->text().toInt();
    bool test=p.supprimer(num);

    if(test)
    {

        ui->tableViewAffichage->setModel(p.afficher());

        if (trad=="Français")
        {
            QMessageBox::information(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Suppression effectuée\n"
                                              "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
        }
        else if (trad=="Anglais")
        {
            QMessageBox::information(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Delete made.\n"
                                              "Click cancel to exit."),QMessageBox::Cancel);
        }


        ui->lineEditSupprimer->clear();
        ui->lineEditNum_2->clear();
        ui->lineEditCapacite_2->clear();
        ui->comboBoxEtat_2->setCurrentText("Veuillez choisir l'etat");

        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();

        QString date=dateTime.toString();

        qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Suppression d un piste',:dateTime)");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();
    }
    else
    {
        if (trad=="Français")
        {
            QMessageBox::critical(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
        }
        else if (trad=="Anglais")
        {
            QMessageBox::critical(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Delete not made.\n"
                                              "Click cancel to exit."),QMessageBox::Cancel);
        }

        ui->lineEditSupprimer->clear();
    }
}

void AdminPiste::on_pushButtonAnnuler_clicked()
{
    ui->lineEditNum->clear();
    ui->lineEditCapacite->clear();
    ui->comboBoxEtat->setCurrentText("Veuillez choisir l'etat");
}

void AdminPiste::on_pushButtonAnnuler_2_clicked()
{
    ui->lineEditNum_2->clear();
    ui->lineEditCapacite_2->clear();
    ui->comboBoxEtat_2->setCurrentText("Veuillez choisir l'etat");
}

void AdminPiste::on_pushButtonAjouterPiste_clicked()
{
    QString trad=ui->selectTraduction->currentText();
    //Récupération des données
    int num=ui->lineEditNum->text().toInt();

    QString etat=ui->comboBoxEtat->currentText();
    if(etat == "Non Active" || etat =="Not Active"){
        ui->lineEditCapacite->setText("0");
        ui->lineEditCapacite->setReadOnly(true);
    }

    int capacite=ui->lineEditCapacite->text().toInt();

    piste p(num,capacite,etat,pisteImg);

    bool test=p.ajouter();

    if (test)
    {
        ui->tableViewAffichage->setModel(p.afficher());
        if (trad=="Français")
        {
            QMessageBox::information(nullptr,QObject::tr("RDI Center"),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
        }
        else if (trad=="Anglais")
        {
            QMessageBox::information(nullptr,QObject::tr("RDI Center"),
                                 QObject::tr("Addition made\n"
                                             "Click cancel to exit."),QMessageBox::Cancel);
        }

        ui->lineEditNum->clear();
        ui->lineEditCapacite->clear();


        QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();

        QString date=dateTime.toString();

        qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Ajout d un piste',:dateTime)");
        qry.bindValue(":dateTime",dateTime);

        qry.exec();
    }
    else
    {
        if (trad=="Français")
        {

            QMessageBox::critical(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Ajout non effectué\n"
                                              "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
        }
        else if (trad=="Anglais")
        {
            QMessageBox::critical(nullptr,QObject::tr("RDI Center"),
                                  QObject::tr("Addition not made.\n"
                                              "Click cancel to exit."),QMessageBox::Cancel);
        }

        ui->lineEditNum->clear();
    }
}

void AdminPiste::on_tableViewAffichage_activated(const QModelIndex &index)
{
    QString value=ui->tableViewAffichage->model()->data(index).toString();

    QSqlQuery qry;

    qry.prepare("select * from piste where num='"+value+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEditNum_2->setText(qry.value(0).toString());
            ui->lineEditCapacite_2->setText(qry.value(1).toString());
            if(qry.value(2).toString()=="Active"){
                ui->comboBoxEtat_2->setCurrentText("Active");
            }
            else if(qry.value(2).toString()=="Damagee")
            {
                ui->comboBoxEtat_2->setCurrentText("Damagee");
            }
            else if(qry.value(2).toString()=="Non Active")
            {
                ui->comboBoxEtat_2->setCurrentText("Non Active");
            }

            ui->lineEditSupprimer->setText(qry.value(0).toString());

            QPixmap image (qry.value(3).toString());
            ui->labelImg_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored );
            image = image.scaled(391,321,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            ui->labelImg_2->setPixmap(image);
            ui->labelImg_2->show();
        }
    }
}

void AdminPiste::on_pushButtonPDF_clicked()
{
    QString trad=ui->selectTraduction->currentText();
    QPdfWriter pdf("C:/liste_pistes/listepiste.pdf");

   QPainter painter(&pdf);
   int i = 4200;
   const QImage image("Logo_ESPRIT_Ariana.jpg");
               const QPoint imageCoordinates(155,0);
               int width1 = 1600;
               int height1 = 600;
               QImage img=image.scaled(width1,height1);
               painter.drawImage(imageCoordinates, img );


          QColor dateColor(0x4a5bcf);
          painter.setPen(dateColor);

          painter.setFont(QFont("Montserrat SemiBold", 11));
          QDate cd = QDate::currentDate();
          painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
          painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

          QColor titleColor(0x341763);
          painter.setPen(titleColor);
          painter.setFont(QFont("Montserrat SemiBold", 25));

          painter.drawText(3000,2700,"Liste des pistes");

          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          //painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3300,9400,500);

          painter.setFont(QFont("Montserrat SemiBold", 10));

          painter.drawText(300,3600,"Numero");
          painter.drawText(1300,3600,"Capacite");
          painter.drawText(2300,3600,"Etat");
          painter.drawText(3300,3600,"Image");
          painter.setFont(QFont("Montserrat", 10));
          painter.drawRect(100,3300,9400,9000);

          QSqlQuery query;
          query.prepare("select * from piste");
          query.exec();
          int y=4300;
          while (query.next())
          {
              painter.drawLine(100,y,9490,y);
              y+=500;
              painter.drawText(300,i,query.value(0).toString());
              painter.drawText(1300,i,query.value(1).toString());
              painter.drawText(2300,i,query.value(2).toString());
              const QImage image(query.value(3).toString());
                          const QPoint imageCoordinates(3300,i);
                          int width1 = 400;
                          int height1 = 800;
                          QImage img=image.scaled(width1,height1);
                          painter.drawImage(imageCoordinates, img );

             i = i + 500 ;
          }
          if (trad=="Français")
          {
              int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
              if (reponse == QMessageBox::Yes)
              {
                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/liste_pistes/listepiste.pdf"));
                  painter.end();
              }
              else
              {
                  painter.end();
              }
          }
          else if (trad=="Anglais")
          {
              int reponse = QMessageBox::question(this, "Exported PDF", "PDF Saved.\nYou want to see it ?", QMessageBox::Yes |  QMessageBox::No);
              if (reponse == QMessageBox::Yes)
              {
                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/azizo/OneDrive/Bureau/Liste_Pistes.pdf"));
                  painter.end();
              }
              else
              {
                  painter.end();
              }
          }

          QSqlQuery qry;
          QDateTime dateTime=QDateTime::currentDateTime();

          QString date=dateTime.toString();

          qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Export d un fichier PDF',:dateTime)");
          qry.bindValue(":dateTime",dateTime);

          qry.exec();


}

void AdminPiste::on_lineEditSearch_textChanged(const QString &arg1)
{
    QString rech=ui->lineEditSearch->text();
    ui->tableViewAffichage->setModel(p.RechercherPiste(rech));
}

void AdminPiste::on_comboBoxTrie_activated(const QString &arg1)
{
    QString tri=ui->comboBoxTrie->currentText();

    if (tri=="Capacite" || tri=="Capacity")
    {
        ui->tableViewAffichage->setModel(p.trierCapacite());
    }
    else if (tri=="Etat" || tri=="Status")
    {
        ui->tableViewAffichage->setModel(p.trierEtat());
    }
}

void AdminPiste::on_pushButtonStat_clicked()
{
    statistic = new class Statistic(this);
    statistic->setWindowTitle("RDI CENTER | Statistiques");
    statistic->show();
}


void AdminPiste::on_selectTraduction_currentIndexChanged(int index)
{
    if(index == 0) //fr
    {
        ui->tabWidget->setTabText(0,"Ajouter Piste");
        ui->tabWidget->setTabText(1,"Afficher Pistes");
        ui->tabWidget->setTabText(2,"Modifier Piste");
        ui->tabWidget->setTabText(3,"Supprimer Piste");
        ui->AjouterPiste->setText("Ajouter une Piste");
        ui->labelNum->setText("Numéro Piste :");
        ui->labelCapacite->setText("Capacité Piste :");
        ui->labelEtat->setText("Etat Piste :");
        ui->comboBoxEtat->setItemText(0,"Active");
        ui->comboBoxEtat->setItemText(1,"Damagee");
        ui->comboBoxEtat->setItemText(2,"Non Active");
        ui->pushButtonAjouterPiste->setText("Ajouter");
        ui->pushButtonAnnuler->setText("Annuler");
        ui->labelTraduction->setText("Traduction");
        ui->selectTraduction->setItemText(0,"Français");
        ui->selectTraduction->setItemText(1,"Anglais");
        ui->labelSort->setText("Tri :");
        ui->comboBoxTrie->setItemText(0,"Capacite");
        ui->comboBoxTrie->setItemText(1,"Etat");
        ui->labelSearch->setText("Rechercher :");
        ui->pushButtonStat->setText("Statistiques");
        ui->pushButtonPDF->setText("Enregistrer PDF");
        ui->pushButtonActualiser->setText("Actualiser");
        ui->ModifierPiste->setText("Modifier une Piste");
        ui->labelNum_2->setText("Numéro Piste :");
        ui->labelCapacite_2->setText("Capacité Piste :");
        ui->labelEtat_2->setText("Etat Piste :");
        ui->comboBoxEtat_2->setItemText(0,"Active");
        ui->comboBoxEtat_2->setItemText(1,"Damagee");
        ui->comboBoxEtat_2->setItemText(2,"Non Active");
        ui->pushButtonModifier->setText("Modifier");
        ui->pushButtonAnnuler_2->setText("Annuler");
        ui->labelSupprimer->setText("Saisir le numéro de piste à supprimer :");
        ui->pushButtonSupprimer->setText("Supprimer");
        ui->labelSupprimer_2->setText("NB : Vous pouvez choisir une piste par une double click sur son numéro dans l'affichage.");
        ui->labelImage->setText("Image Piste :");


    }
    if(index == 1) //en
    {
        ui->tabWidget->setTabText(0,"Add Track");
        ui->tabWidget->setTabText(1,"View Tracks");
        ui->tabWidget->setTabText(2,"Edit Track");
        ui->tabWidget->setTabText(3,"Delete Track");
        ui->AjouterPiste->setText("Add a Track");
        ui->labelNum->setText("Track's Number :");
        ui->labelCapacite->setText("Track's Capacity :");
        ui->labelEtat->setText("Track's Status :");
        ui->comboBoxEtat->setItemText(0,"Active");
        ui->comboBoxEtat->setItemText(1,"Damaged");
        ui->comboBoxEtat->setItemText(2,"Not Active");
        ui->pushButtonAjouterPiste->setText("Add");
        ui->pushButtonAnnuler->setText("Cancel");
        ui->labelTraduction->setText("Traduction");
        ui->selectTraduction->setItemText(0,"French");
        ui->selectTraduction->setItemText(1,"English");
        ui->labelSort->setText("Sort :");
        ui->comboBoxTrie->setItemText(0,"Capacity");
        ui->comboBoxTrie->setItemText(1,"Status");
        ui->labelSearch->setText("Search :");
        ui->pushButtonStat->setText("Statistics");
        ui->pushButtonPDF->setText("Export PDF");
        ui->pushButtonActualiser->setText("Load");
        ui->ModifierPiste->setText("Edit a Track");
        ui->labelNum_2->setText("Track's Number :");
        ui->labelCapacite_2->setText("Track's Capacity :");
        ui->labelEtat_2->setText("Track's Status :");
        ui->comboBoxEtat_2->setItemText(0,"Active");
        ui->comboBoxEtat_2->setItemText(1,"Damaged");
        ui->comboBoxEtat_2->setItemText(2,"Not Active");
        ui->pushButtonModifier->setText("Edit");
        ui->pushButtonAnnuler_2->setText("Cancel");
        ui->labelSupprimer->setText("Enter the track's number to delete :");
        ui->pushButtonSupprimer->setText("Delete");
        ui->labelSupprimer_2->setText("NB : You can choose a track by double clicking on its number in the display.");
        ui->labelImage->setText("Truck's Picture :");
    }
}

void AdminPiste::on_pushButtonActualiserHistorique_clicked()
{
    ui->tableViewHistorique->setModel(p.afficherHistorique());
}

void AdminPiste::on_pushButtonImg_clicked()
{
    QString imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png)");

    QFileInfo info(imageFile);
    QFileInfo  filename = info.fileName(); //path de l'image

    QPixmap image (imageFile);
    ui->labelImg->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored );
    image = image.scaled(391,321,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->labelImg->setPixmap(image);
    ui->labelImg->show();


    pisteImg = imageFile;
    qDebug()<< pisteImg;
}

void AdminPiste::on_pushButtonImg_2_clicked()
{
    QString imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png)");

    QFileInfo info(imageFile);
    QFileInfo  filename = info.fileName(); //path de l'image

    QPixmap image (imageFile);
    ui->labelImg_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored );
    image = image.scaled(391,321,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->labelImg_2->setPixmap(image);
    ui->labelImg_2->show();


    pisteImg = imageFile;
    qDebug()<< pisteImg;
}

void AdminPiste::on_pushButtonStat_2_clicked()
{
    QString capacite;
    int num=ui->Id->text().toInt();
    QString numm=QString::number(num);
    QSqlQuery query;
    query.exec("SELECT CAPACITE FROM PISTE WHERE NUM ='"+numm+"';");
    query.next();
   capacite= query.value(0).toString();
   A.write_to_arduino2(capacite);
}
