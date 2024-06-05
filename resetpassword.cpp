#include "resetpassword.h"
#include "ui_resetpassword.h"

ResetPassword::ResetPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetPassword)
{
    ui->setupUi(this);
    connect(ui->sendmail, SIGNAL(clicked()),this, SLOT(sendMail()));

}

ResetPassword::~ResetPassword()
{
    delete ui;
}

void ResetPassword::sendMail()
{
    Smtp* smtp = new Smtp("ilyess.saoudi@gmail.com","elqvwycqcwpyiqxd", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    QSqlQuery query;

query.prepare("SELECT MAIL_UTIL FROM UTILISATEUR WHERE MAIL_UTIL= :mail");
query.bindValue(":mail",ui->Email->text());
query.exec();
if (query.next()){

         srand(time(0));
    int code= rand();
    QString codeString = QString::number(code);
    smtp->sendMail("ilyess.saoudi@gmail.com", ui->Email->text() , "Password Reset","Your password reset code is: " + codeString);

v_codeString=codeString;
m_email = ui->Email->text();}

else
{
     QMessageBox::warning( this, tr( "Password Reset" ), tr( "Email does not exist !\n\n" ) );
}


}

void ResetPassword::mailSent(QString status)
{

    if(status == "Message sent")
{
        QMessageBox::information(this,QObject::tr("Password Reset"),QObject::tr("Mail transferred successfully!"));
    }





}

void ResetPassword::on_verifyBtn_clicked()
{
 QString userCode = ui->code->text();
 if (userCode == v_codeString){
     this->hide();
np = new NewPassword();
np->getEmail(m_email);
np->show();
 }
 else {
     QMessageBox::warning( this, tr( "Password Reset" ), tr( "Code incorrect!\n\n" ) );
 }

ui->code->clear();

}
