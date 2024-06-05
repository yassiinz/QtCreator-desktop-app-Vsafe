#include "adminpage.h"
#include "ui_adminpage.h"
#include <QSqlQuery>

adminpage::adminpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);
}

adminpage::~adminpage()
{
    delete ui;
}

void adminpage::getEmail(QString email)
 {
        ad_email = email;
        QSqlQuery query;
        query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :email");
        query.bindValue(":email", ad_email);
        if (query.exec())
        {
            QTextBrowser *textBrowser = new QTextBrowser();
            QStringList data;
            while (query.next())
            {
                QString name = query.value(3).toString();
                data << "Welcome Dear " << name;
            }
            textBrowser->setText(data.join(""));

            // Bind to UI QTextBrowser widget
            QTextBrowser *uiTextBrowser = this->findChild<QTextBrowser*>("textBrowser");
            if (uiTextBrowser != nullptr)
                uiTextBrowser->setText(textBrowser->toPlainText());
        }
    }

void adminpage::on_pushButton_clicked()
{
    m= new MainWindow(this);
    m->setWindowTitle("User Management");
    m->show();
}

void adminpage::on_pushButton_4_clicked()
{
    cm = new clientmanagement();
    cm->setWindowTitle("Client Management");
    cm->show();
}

void adminpage::on_pushButton_5_clicked()
{
    asc = new AdminSchedule();
    asc->setWindowTitle("Schedule Management");
    asc->show();
}

void adminpage::on_pushButton_3_clicked()
{
    ae = new equipmanagement();
    ae->setWindowTitle("Equipment Management");
    ae->show();
}

void adminpage::on_pushButton_2_clicked()
{
    av = new AdminVehicles();
    av->setWindowTitle("Vehicle Management");
    av->show();
}

void adminpage::on_pushButton_6_clicked()
{
    ap = new AdminPiste();
    ap->setWindowTitle("Track Management");
    ap->show();
}
