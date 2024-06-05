#include "login.h"
#include "ui_login.h"

#define EMAIL_RX "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+"  \
                 "(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QRegExp rx(EMAIL_RX);
    QRegExpValidator *mailVali = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(mailVali);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString User_mail =ui->lineEdit->text().trimmed();
    QString Password= ui->lineEdit_2->text();
    QByteArray hashedPassword = QCryptographicHash::hash(Password.toUtf8(), QCryptographicHash::Sha1).toHex();
    QSqlQuery query;

    query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :User_mail AND MDP_UTIL = :Password");
    query.bindValue(":User_mail", User_mail);
    query.bindValue(":Password", hashedPassword);
    query.exec();

    if(query.next())
    {
         QString function = query.value(7).toString();
         if (function == "admin")
         {
            this->hide();
            a= new adminpage();
            a->setWindowTitle("Welcome to VSafe");
            a->getEmail(User_mail);
            a->show();
         }
         else if (function == "scheduler")
         {
             this->hide();
             sp = new schedulerpage();
             sp->setWindowTitle("Welcome to VSafe");
             sp->getEmail(User_mail);
             sp->show();
         }
         else if (function == "invoicer")
         {
             this->hide();
             ip = new invoicerpage();
             ip->setWindowTitle("Welcome to VSafe");
             ip->getEmail(User_mail);
             ip->show();
         }
         else if (function == "technician")
         {
             this->hide();
             tp = new technicianpage;
             tp->setWindowTitle("Welcome to VSafe");
             tp->getEmail(User_mail);
             tp->show();
         }
         else if (function == "equipment specialist")
         {
             this->hide();
             ep = new equipspage();
             ep->setWindowTitle("Welcome to VSafe");
             ep->getEmail(User_mail);
             ep->show();
         }
     }
     else
         QMessageBox::warning(this, tr("Warning"), tr("Incorrect Mail or Password"));
}

void login::on_pushButton_2_clicked()
{
    s= new Signup();
    s->setWindowTitle("Sign Up");
    s->show();
}

void login::on_sendbutton_clicked()
{
    rp = new ResetPassword();
    rp->setWindowTitle("Reset Password");
    rp->show();
}
