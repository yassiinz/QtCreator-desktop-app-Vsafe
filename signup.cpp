#include "signup.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_clicked()
{
    QString ID=ui->LE_ID->text();
    QString mdp=ui->LE_mdp->text();
    QString prenom=ui->LE_prenom->text();
    QString nom=ui->LE_nom->text();
    int tlf=ui->LE_tlf->text().toInt();
    QString fonction=ui->comboBox->currentText();
    QDateTime date_emb=ui->dateEdit->dateTime();

    QString mail=ui->LE_mail->text();
    Utilisateur u(ID,mdp,nom,prenom,tlf,mail,date_emb,fonction,NULL);
    bool test=u.ajouter();
    if (test){

        //Refresh !

           QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Succuessfully Added\n"
                                                                          "Click Cancel to exit."),QMessageBox::Cancel);
    this->hide();


    }
    else {

        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),QObject::tr("Failed to Add\n"
                                                                       "Click Cancel to exit."),QMessageBox::Cancel);
        ui->LE_ID->clear();
        ui->LE_mdp->clear();
        ui->LE_prenom->clear();
        ui->LE_nom->clear();
        ui->LE_tlf->clear();

        ui->LE_mail->clear();
        ui->dateEdit->clear();


    }


}
