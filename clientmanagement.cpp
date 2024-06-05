#include "clientmanagement.h"
#include "ui_clientmanagement.h"
#include <QStandardItem>

#define NAME_RX "([A-Z][a-z]*)([\\s\\\'-][A-Z][a-z]*)*"
#define EMAIL_RX "^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+"  \
                 "(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$"

clientmanagement::clientmanagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientmanagement)
{
    ui->setupUi(this);

    //Arduino connection
    int con = A.connect_arduino();
    switch(con) //Establish connection
    {
        case 0 : qDebug() << "Arduino available and connected to : " << A.getArduino_port_name();
        break;
        case 1 : qDebug() << "Arduino available but not connected to : " << A.getArduino_port_name();
        break;
        case -1 : qDebug() << "Arduino unavailable!";
        break;
    }

    //Pattern check for input validation
    QRegExp nm(NAME_RX);
    QRegExp rx(EMAIL_RX);
    mailVali = new QRegExpValidator(rx, this);
    nameVali = new QRegExpValidator(nm, this);
    numVali = new QIntValidator(1,99999999);
    ui->fnEdit->setValidator(nameVali);
    ui->lnEdit->setValidator(nameVali);
    ui->idEdit->setValidator(numVali);
    ui->phEdit->setValidator(numVali);
    ui->mEdit->setValidator(mailVali);
    ui->ascClient->setChecked(true);

    //Search filter model
    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(cl->show());
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(-1);
    refreshClient();

    //Mail signals
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

void clientmanagement::refreshClient() //Refresh function
{
    proxy->setSourceModel(cl->show());
    ui->clientTable->setModel(proxy);
    ui->clientTable->resizeRowsToContents();
    ui->clientTable->resizeColumnsToContents();
    ui->count->setText(QString::number(ui->clientTable->model()->rowCount()));
    if(ui->ascClient->isChecked())
        ui->clientTable->sortByColumn(ui->sort->currentIndex(),Qt::AscendingOrder);
    else
        ui->clientTable->sortByColumn(ui->sort->currentIndex(),Qt::DescendingOrder);
    const int col1 = 0, col2 = 3;
    int rowCount = ui->clientTable->model()->rowCount();
    for(int row = 0; row < rowCount; row++)
    {
        QModelIndex index1 = ui->clientTable->model()->index(row, col1);
        QModelIndex index2 = ui->clientTable->model()->index(row, col2);
        double num1 = ui->clientTable->model()->data(index1).toDouble();
        double num2 = ui->clientTable->model()->data(index2).toDouble();
        QString format1 = formatNumber(num1);
        QString format2 = formatNumber(num2);
        ui->clientTable->model()->setData(index1, format1);
        ui->clientTable->model()->setData(index2, format2);
    }
}

void clientmanagement::clear() //Clear inputs function
{
    ui->fnEdit->clear();
    ui->lnEdit->clear();
    ui->idEdit->clear();
    ui->phEdit->clear();
    ui->mEdit->clear();
}

QString clientmanagement::formatNumber(double number)
{
    // Convert the number to string and format it
    QString formattedNumber = QString::number(number, 'f', 2);

    // Remove trailing zeros
    formattedNumber = formattedNumber.trimmed();

    if (formattedNumber.endsWith(".00"))
    {
        // Remove decimal point and ".00" if present
        formattedNumber.chop(3);
    }
    return formattedNumber;
}

clientmanagement::~clientmanagement()
{
    delete ui;
    delete proxy;
    delete cl;
    delete mailVali;
    delete nameVali;
    delete numVali;
    A.close_arduino();
}


void clientmanagement::on_addClient_clicked() //Add client
{
    //Get input
    QString fn = ui->fnEdit->text();
    QString ln = ui->lnEdit->text();
    int cin = ui->idEdit->text().toUInt();
    int ph = ui->phEdit->text().toUInt();
    QString m = ui->mEdit->text();

    //Validate form
    QRegExp nm(NAME_RX);
    QRegExp rx(EMAIL_RX);
    if(!fn.contains(nm) || !ln.contains(nm) || !m.contains(rx) || ui->idEdit->text().isEmpty() || ui->phEdit->text().isEmpty())
    {
        bool state = ui->addClient->blockSignals(true);
        QMessageBox::critical(nullptr, QObject::tr("Adding client..."),
                              QObject::tr("Please fill in all fields!"), QMessageBox::Cancel);
        ui->addClient->blockSignals(state);
    }
    else
    {
        //Create an instance of class
        Client c (fn,ln,cin,ph,m);
        if(c.check(cin) == 1) //Check if the client exists
            QMessageBox::critical(nullptr, QObject::tr("Adding client..."),
                                  QObject::tr("A client with the same ID already exists!"), QMessageBox::Cancel);
        else
        {
            bool test = c.add(); //Query return

            if(test) //Execution successful
            {
                QString input = QString::number(c.getID());
                c.genQR(input);
                clear();
                refreshClient();
                QMessageBox::information(nullptr, QObject::tr("Adding client..."),
                                         QObject::tr("The client was added successfully!\n"), QMessageBox::Ok);
                autoMail(c);
            }
            else //Execution failed
                QMessageBox::critical(nullptr, QObject::tr("Adding client..."),
                                         QObject::tr("Failed to add client!\n"), QMessageBox::Cancel);
        }
    }
}

void clientmanagement::on_clientTable_activated(const QModelIndex &index) //Edit client pt.1
{
    QString val = ui->clientTable->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE CIN = :val OR PRENOM_CLIENT = :val OR NOM_CLIENT = :val OR TLF_CLIENT = :val OR MAIL_CLIENT = :val;");
    query.bindValue(":val",val);
    if(query.exec())
    {
        while(query.next())
        {
            ui->fnEdit->clear();
            ui->fnEdit->setText(query.value(2).toString());
            ui->lnEdit->clear();
            ui->lnEdit->setText(query.value(1).toString());
            ui->idEdit->clear();
            ui->idEdit->setText(query.value(0).toString());
            ui->phEdit->clear();
            ui->phEdit->setText(query.value(3).toString());
            ui->mEdit->clear();
            ui->mEdit->setText(query.value(4).toString());
        }
    }
}

void clientmanagement::on_editClient_clicked() //Edit client pt.2
{
    //Get input
    QString fn = ui->fnEdit->text();
    QString ln = ui->lnEdit->text();
    int cin = ui->idEdit->text().toUInt();
    int ph = ui->phEdit->text().toUInt();
    QString m = ui->mEdit->text();

    //Validate form
    QRegExp nm(NAME_RX);
    QRegExp rx(EMAIL_RX);
    if(!fn.contains(nm) || !ln.contains(nm) || !m.contains(rx) || ui->idEdit->text().isEmpty() || ui->phEdit->text().isEmpty())
    {
        bool state = ui->editClient->blockSignals(true);
        QMessageBox::critical(nullptr, QObject::tr("Editing client..."),
                              QObject::tr("Please fill in all fields!"), QMessageBox::Cancel);
        ui->editClient->blockSignals(state);
    }
    else
    {
        //Create an instance of class
        Client c (fn,ln,cin,ph,m);
        bool test = c.update(cin); //Query return

        if(test) //Execution successful
        {
            clear();
            refreshClient();
            QMessageBox::information(nullptr, QObject::tr("Editing client..."),
                                     QObject::tr("The client was edited successfully\n"), QMessageBox::Ok);
        }
        else //Execution failed
            QMessageBox::critical(nullptr, QObject::tr("Editing client..."),
                                     QObject::tr("Failed to edit the client!\n"), QMessageBox::Cancel);
    }
}

void clientmanagement::on_delClient_clicked() //Delete client
{
    if(ui->idEdit->text().isEmpty()) //Check if ID is inserted
    {
        bool state = ui->delClient->blockSignals(true);
        QMessageBox::critical(nullptr, QObject::tr("Deleting client..."),
                              QObject::tr("Please insert the client ID!"), QMessageBox::Cancel);
        ui->delClient->blockSignals(state);
    }
    else
    {
        int cin = ui->idEdit->text().toUInt();
        if(cl->check(cin) != 1)
            QMessageBox::critical(nullptr, QObject::tr("Deleting client..."),
                                  QObject::tr("The client does not exists!"), QMessageBox::Cancel);
        else {
            //Confirm action
            QMessageBox::StandardButton reply = QMessageBox::question(nullptr, QObject::tr("Deleting client..."),
                                     QObject::tr("Are you sure you want to delete this client?\n"), QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                //Call delete function
                bool test = cl->del(cin);

                if(test) //Execution successful
                {
                    clear();
                    refreshClient();
                    QMessageBox::information(nullptr, QObject::tr("Deleting client..."),
                                             QObject::tr("The client was deleted successfully!\n"), QMessageBox::Ok);
                }
                else //Execution failed
                    QMessageBox::critical(nullptr, QObject::tr("Deleting client..."),
                                             QObject::tr("Failed to delete the client!\n"), QMessageBox::Cancel);
            }
        }
    }
}

void clientmanagement::on_searchBox_textChanged(const QString &arg1) //Filter search
{
    proxy->setFilterFixedString(arg1);
}

void clientmanagement::on_refresh_clicked() //Refresh button
{
    refreshClient();
}

void clientmanagement::on_sort_currentIndexChanged(int index) //Sorting
{
    if(ui->ascClient->isChecked())
        ui->clientTable->sortByColumn(index,Qt::AscendingOrder);
    else
        ui->clientTable->sortByColumn(index,Qt::DescendingOrder);
}

void clientmanagement::on_pdfClient_clicked() //PDF
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->clientTable->model()->rowCount();
                const int columnCount =ui->clientTable->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1 align='center'>Clients list</h1>"

                            "<table align='center' border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->clientTable->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->clientTable->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->clientTable->isColumnHidden(column)) {
                                   QString data = ui->clientTable->model()->data(ui->clientTable->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "<footer align='center'>\n"
                           "VSafe ©. All rights reserved.\n"
                           "</footer\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Clients.pdf");
        document->print(&printer);
}

void clientmanagement::on_ascClient_toggled(bool checked) //Ascneding sorting
{
    if(checked)
        ui->clientTable->sortByColumn(ui->sort->currentIndex(),Qt::AscendingOrder);
}

void clientmanagement::on_descClient_toggled(bool checked) //Descending sorting
{
    if(checked)
        ui->clientTable->sortByColumn(ui->sort->currentIndex(),Qt::DescendingOrder);
}

void clientmanagement::browse() //Mailing (to be automated)
{
    files.clear();
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
        files = dialog.selectedFiles();
    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );
    ui->file->setText( fileListString );
}

void clientmanagement::sendMail()
{
    Smtp* smtp = new Smtp("mohamedamine.fezzani@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    if( !files.isEmpty() )
        smtp->sendMail("mohamedamine.fezzani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedamine.fezzani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void clientmanagement::autoMail(Client c)
{
    Smtp* smtp = new Smtp("mohamedamine.fezzani@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString message = "Dear " + c.getFn() + " " + c.getLn() + ", the following QR code is to be presented at the entrance before your appointment. Thank you for choosing us!";
    QString subject = "QR Code";
    browse();
    if( files.isEmpty() )
        QMessageBox::critical(nullptr,QObject::tr("Mail Transfer"),QObject::tr("Cannot send mail! (no QR code included!)"));
    else
        smtp->sendMail("mohamedamine.fezzani@esprit.tn", c.getM() , subject, message, files );
}

void clientmanagement::mailSent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("Mail Transfer"),QObject::tr("Mail transferred successfully!"));
        ui->rcpt->clear();
        ui->subject->clear();
        ui->file->clear();
        ui->msg->clear();
    }
    else if(status == "Failed to send message")
        QMessageBox::critical(nullptr,QObject::tr("Mail Transfer"),QObject::tr("Failed to transfer mail!"));
}

int clientmanagement::checkQR()
{
    QString id = QString::fromStdString(A.read_from_arduino().toStdString());
    qDebug() <<id;
    int cin = id.toInt();
    qDebug() <<cin;
    int rows = cl->check(cin);
    if(rows == 1)
    {
        qDebug() << "QR Valid!";
        A.write_to_arduino("1");
        qDebug() << A.write_to_arduino("1");
        return 1;
    }
    else
    {
        qDebug() << "QR Not Valid!";
        A.write_to_arduino("0");
        qDebug() << A.write_to_arduino("0");
        return 0;
    }
}

void clientmanagement::on_pushButton_clicked()
{
    if(checkQR() == 1)
        QMessageBox::information(nullptr,QObject::tr("Qr Check"),QObject::tr("Qr Code is valid!"));
    else
        QMessageBox::information(nullptr,QObject::tr("Qr Check"),QObject::tr("Qr Code is not valid!"));

}
