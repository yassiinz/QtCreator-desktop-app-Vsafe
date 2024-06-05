#include "schedulerpage.h"
#include "ui_schedulerpage.h"

schedulerpage::schedulerpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedulerpage)
{
    ui->setupUi(this);
}

schedulerpage::~schedulerpage()
{
    delete ui;
}

void schedulerpage::getEmail(QString email)
 {
        sch_email = email;

        QSqlQuery query;
        query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :email");
        query.bindValue(":email", sch_email);
        if (query.exec()) {
            QTextBrowser *textBrowser = new QTextBrowser();
            QStringList data;
            while (query.next()) {
                QString name = query.value(3).toString();
                data << "Welcome Dear " << name;
            }
            textBrowser->setText(data.join(""));


            // Bind to UI QTextBrowser widget
            QTextBrowser *uiTextBrowser = this->findChild<QTextBrowser*>("textBrowser");
            if (uiTextBrowser != nullptr) {


                uiTextBrowser->setText(textBrowser->toPlainText());
            }
        }
    }

void schedulerpage::on_pushButton_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void schedulerpage::on_pushButton_4_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void schedulerpage::on_pushButton_5_clicked()
{
    ads = new AdminSchedule();
    ads->show();
}

void schedulerpage::on_pushButton_3_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void schedulerpage::on_pushButton_2_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}
