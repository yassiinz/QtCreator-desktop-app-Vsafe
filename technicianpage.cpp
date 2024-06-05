#include "technicianpage.h"
#include "ui_technicianpage.h"

technicianpage::technicianpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::technicianpage)
{
    ui->setupUi(this);
}

technicianpage::~technicianpage()
{
    delete ui;
}

void technicianpage::getEmail(QString email)
 {
        tech_email = email;

        QSqlQuery query;
        query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :email");
        query.bindValue(":email", tech_email);
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

void technicianpage::on_pushButton_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void technicianpage::on_pushButton_4_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void technicianpage::on_pushButton_5_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void technicianpage::on_pushButton_3_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void technicianpage::on_pushButton_2_clicked()
{
    adv = new AdminVehicles();
    adv->show();
}
