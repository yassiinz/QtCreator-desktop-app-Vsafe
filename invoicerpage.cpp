#include "invoicerpage.h"
#include "ui_invoicerpage.h"

invoicerpage::invoicerpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoicerpage)
{
    ui->setupUi(this);
}

invoicerpage::~invoicerpage()
{
    delete ui;
}

void invoicerpage::getEmail(QString email)
 {
        inv_email = email;

        QSqlQuery query;
        query.prepare("SELECT * FROM UTILISATEUR WHERE MAIL_UTIL = :email");
        query.bindValue(":email", inv_email);
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

void invoicerpage::on_pushButton_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void invoicerpage::on_pushButton_4_clicked()
{
  cm = new clientmanagement();
  cm->show();
}

void invoicerpage::on_pushButton_5_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void invoicerpage::on_pushButton_3_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}

void invoicerpage::on_pushButton_2_clicked()
{
    QMessageBox::warning(this, tr("Warning"), tr("This page is inaccessible "));

}
