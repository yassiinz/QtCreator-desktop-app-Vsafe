#include "newpassword.h"
#include "ui_newpassword.h"

NewPassword::NewPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPassword)
{
    ui->setupUi(this);
}

NewPassword::~NewPassword()
{
    delete ui;
}

void NewPassword::on_pushButton_clicked()
{
    QString newpw= ui->newPw->text();
    QString cpw= ui->confirmPw->text();

    if (newpw==cpw){
    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    QRegularExpressionMatch passwordMatch = passwordRegex.match(newpw);
    if (!passwordMatch.hasMatch()) {
        QMessageBox::critical(this, "Error", "The password must contain at least one lowercase letter,one uppercase letter,one digit,one special character andlength of at least 8 characters.");
    }

    else {
QSqlQuery query;
 QByteArray hashedPassword = QCryptographicHash::hash(cpw.toUtf8(), QCryptographicHash::Sha1).toHex();
query.prepare("UPDATE UTILISATEUR SET MDP_UTIL = :newPassword WHERE MAIL_UTIL = :email");
query.bindValue(":newPassword", hashedPassword);
query.bindValue(":email", l_email);


query.exec();
      QMessageBox::information(this,QObject::tr("Password Reset"),QObject::tr("Password Succesfully updated !"));
this->close();
    }
}
    else
    {
         QMessageBox::warning( this, tr( "Password Reset" ), tr( "Passwords do not match !\n\n" ) );
    }
}




void NewPassword::getEmail(QString email)
 {
        l_email = email;
    }
