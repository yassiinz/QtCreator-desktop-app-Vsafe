#include "utilisateur.h"

Utilisateur::Utilisateur(QString id,QString mdp, QString nom, QString prenom, int tlf, QString mail,QDateTime date_emb,QString fonction,float salaire){


this->ID=id;
this->mdp=mdp;
this->prenom=prenom;
this->nom=nom;
this->tlf=tlf;
this->fonction=fonction;
this->salaire=salaire;
this->date_emb=date_emb;
this->mail=mail;
}


bool Utilisateur::ajouter(){
QSqlQuery query;

if (ID.isEmpty() || mdp.isEmpty() || prenom.isEmpty() || nom.isEmpty() || mail.isEmpty()) {
return false;
}


//CNTRL DE SAISIE


QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
QRegularExpressionMatch passwordMatch = passwordRegex.match(mdp);
if (!passwordMatch.hasMatch()) {
    QMessageBox::critical(nullptr, "Error", "The password must contain at least one lowercase letter,one uppercase letter,one digit,one special character andlength of at least 8 characters.");

    return false;
}


    // Vérifier que le prénom et le nom contiennent uniquement des lettres
foreach(QChar c, prenom) {
    if (!c.isLetter()) {
        QMessageBox::critical(nullptr, "Error", "The First Name must be in letters.");

        return false;
    }
}
foreach(QChar c, nom) {
    if (!c.isLetter()) {
        QMessageBox::critical(nullptr, "Error", "The Last Name must be in letters.");

        return false;
    }
}

    // Vérifier que le numéro de téléphone contient uniquement des chiffres
    if (!QString::number(tlf).toInt()) {
        QMessageBox::critical(nullptr, "Error", "The Number must be only in numbers.");

        return false;
    }

    //Vérifier que la salaire est positif
    if (salaire < 0) {
        QMessageBox::critical(nullptr, "Error", "Salary must be a positive number.");

            return false;
        }

    // Vérifier que l'adresse email est valide
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpressionMatch emailMatch = emailRegex.match(mail);
    if (!emailMatch.hasMatch()) {
        QMessageBox::critical(nullptr, "Error", "Invalid E-Mail.");

        return false;
    }




    // Vérifier que la fonction contient uniquement des lettres
foreach(QChar c, fonction) {
    if (!c.isLetter()) {
        QMessageBox::critical(nullptr, "Error", "The Function must be in letters.");

        return false;
    }
}





QByteArray hashedPassword = QCryptographicHash::hash(mdp.toUtf8(), QCryptographicHash::Sha1).toHex();
qDebug() << "Hashed password: " << hashedPassword;

QString res = QString::number(tlf);
QString sal = QString::number(salaire);

query.prepare("INSERT INTO UTILISATEUR (ID_UTIL,MDP_UTIL, PRENOM_UTIL, NOM_UTIL, TLF_UTIL, MAIL_UTIL, DATE_EMBAUCHE, FONCTION, SALAIRE)" "VALUES (:ID, :mdp, :nom, :prenom, :tlf, :mail, :date_embauche, :fonction, :salaire)");

query.bindValue(":ID",ID);
query.bindValue(":mdp",hashedPassword);
query.bindValue(":prenom",prenom);
query.bindValue(":nom",nom);
query.bindValue(":tlf",res);
query.bindValue(":fonction",fonction);
query.bindValue(":salaire",sal);
query.bindValue(":date_embauche",date_emb);
query.bindValue(":mail",mail);

return query.exec();

}

QSqlQueryModel * Utilisateur::afficher()
{

QSqlQueryModel * model=new  QSqlQueryModel();

model->setQuery("SELECT * FROM UTILISATEUR");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("User ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Password"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("First Name"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Last Name")),
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Phone Number"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("E-Mail"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Hire Date"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("Position"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("Salary"));

return model;
}

bool Utilisateur::supprimer(QString ID)
{
    QSqlQuery query;
if (ID.isEmpty()){
    QMessageBox::warning(0, "ERROR", "ID CANNOT BE NULL");
    return false;}

 if (!verifierid(ID)) {
               QMessageBox::warning(0, "ERROR", "ID DOES NOT EXIST!");
               return false;
           }

       query.prepare("Delete from utilisateur where ID_UTIL= :ID");
        query.bindValue(":ID",ID);
        return query.exec();



}

bool Utilisateur::update(QString ID){
    QSqlQuery query;
if (ID.isEmpty()){
    QMessageBox::warning(0, "ERROR", "ID CANNOT BE NULL");

    return false;}
    if (!verifierid(ID)) {
                  QMessageBox::warning(0, "ERROR", "ID DOES NOT EXIST!");
                  return false;
              }
    if (ID.isEmpty() || mdp.isEmpty() || prenom.isEmpty() || nom.isEmpty() || mail.isEmpty()) {
    return false;
    }


    //CNTRL DE SAISIE


    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    QRegularExpressionMatch passwordMatch = passwordRegex.match(mdp);
    if (!passwordMatch.hasMatch()) {
        QMessageBox::critical(nullptr, "Error", "The password must contain at least one lowercase letter,one uppercase letter,one digit,one special character andlength of at least 8 characters.");

        return false;
    }


        // Vérifier que le prénom et le nom contiennent uniquement des lettres
    foreach(QChar c, prenom) {
        if (!c.isLetter()) {
            QMessageBox::critical(nullptr, "Error", "The First Name must be in letters.");

            return false;
        }
    }
    foreach(QChar c, nom) {
        if (!c.isLetter()) {
            QMessageBox::critical(nullptr, "Error", "The Last Name must be in letters.");

            return false;
        }
    }

        // Vérifier que le numéro de téléphone contient uniquement des chiffres
        if (!QString::number(tlf).toInt()) {
            QMessageBox::critical(nullptr, "Error", "The Number must be only in numbers.");

            return false;
        }

        //Vérifier que la salaire est positif
        if (salaire < 0) {
            QMessageBox::critical(nullptr, "Error", "Salary must be a positive number.");

                return false;
            }

        // Vérifier que l'adresse email est valide
        QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
        QRegularExpressionMatch emailMatch = emailRegex.match(mail);
        if (!emailMatch.hasMatch()) {
            QMessageBox::critical(nullptr, "Error", "Invalid E-Mail.");

            return false;
        }




//prepare the query
    QString res = QString::number(tlf);
    QString sal = QString::number(salaire);
    QByteArray hashedPassword = QCryptographicHash::hash(mdp.toUtf8(), QCryptographicHash::Sha1).toHex();
    qDebug() << "Hashed password: " << hashedPassword;
    query.prepare("UPDATE UTILISATEUR SET ID_UTIL=:id, MDP_UTIL=:mdp, PRENOM_UTIL=:prenom, NOM_UTIL=:nom, TLF_UTIL=:tlf, MAIL_UTIL=:mail, DATE_EMBAUCHE=:date_embauche, FONCTION=:fonction, SALAIRE=:salaire WHERE ID_UTIL=:id;");

    //BIND VALUES

    query.bindValue(":id",ID);
    query.bindValue(":mdp",hashedPassword);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":tlf",res);
    query.bindValue(":fonction",fonction);
    query.bindValue(":salaire",sal);
    query.bindValue(":date_embauche",date_emb);
    query.bindValue(":mail",mail);

    return query.exec();

}
bool Utilisateur::verifierid(QString ID) {
    QSqlQuery query;
    query.prepare("SELECT ID_UTIL FROM UTILISATEUR WHERE ID_UTIL = :ID_UTIL");
    query.bindValue(":ID_UTIL", ID);
    if (query.exec())
        if(query.next())

        // id existe déjà
        return true;


    // id n'existe pas encore
    return false;
}
