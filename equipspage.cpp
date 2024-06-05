#include "equipspage.h"
#include "ui_equipspage.h"

equipspage::equipspage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::equipspage)
{
    ui->setupUi(this);
}

equipspage::~equipspage()
{
    delete ui;
}



void equipspage::getEmail(QString email)
 {
        eq_email = email;
        QSqlQuery query;
        query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :email");
        query.bindValue(":email", eq_email);
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

void equipspage::on_pushButton_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void equipspage::on_pushButton_4_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void equipspage::on_pushButton_5_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void equipspage::on_pushButton_3_clicked()
{
    ade = new equipmanagement();
    ade->show();
}

void equipspage::on_pushButton_2_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}
