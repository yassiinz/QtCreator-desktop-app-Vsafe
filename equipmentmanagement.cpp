#include "equipmentmanagement.h"
#include "ui_equipmentmanagement.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <iostream>
#include <QDebug>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include <QPrinter>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QTimer>

QByteArray getImageDataFromDatabase(int ref)
{

    QSqlQuery query;
    query.prepare("SELECT img FROM EQUIPEMENT WHERE REF = :ref");
    query.bindValue(":ref", ref);

    // Execute the query and retrieve the image data
    if (!query.exec() || !query.next()) {
        qWarning() << "Failed to retrieve image data from database";
        return QByteArray();
    }

    return query.value(0).toByteArray();
}



equipmentmanagement::equipmentmanagement(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::equipmentmanagement)
{
    ui->setupUi(this);

                proxy2 = new QSortFilterProxyModel();
                proxy2->setSourceModel(e.afficher());
                proxy2->setFilterCaseSensitivity(Qt::CaseInsensitive);
                proxy2->setFilterKeyColumn(-1);
                ui->tableView->setModel(proxy2);
}


equipmentmanagement::~equipmentmanagement()
{

    delete ui;
}


void equipmentmanagement::refreshEquip()
{
    proxy2->setSourceModel(e.afficher());
        ui->tableView->setModel(proxy2);

}

void equipmentmanagement::on_pb_supprimer_2_clicked()
    {
    int ref=ui->lineEdit_ref_4->text().toInt();
        bool test=e.supprimer(ref);
        if(test)
        {

            refreshEquip();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("suppresion éffectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);


        }
        else{
            QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                        QObject::tr("suppresion non éffectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }

void equipmentmanagement::on_pb_ajouter_clicked()
{
    int ref=ui->lineEdit_ref->text().toInt();
    int qte=ui->lineEdit_3->text().toInt();
    QString libelle=ui->lineEdit_2->text();
    QString type = ui->comboBox->currentText();

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage image(imagePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        return;
    }
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    equipement e(ref, qte, libelle, type, imageData);
    bool test=e.ajouter();
    if (test)
    {

        refreshEquip();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout éffectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


     }
    else{
        QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                    QObject::tr("ajout non éffectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}








}

void equipmentmanagement::on_pushButton_5_clicked()
{

    int ref=ui->lineEdit_ref->text().toInt();
    int qte=ui->lineEdit_3->text().toInt();
    QString libelle=ui->lineEdit_2->text();
    QString type = ui->comboBox->currentText();

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage image(imagePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        return;
    }
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

           equipement e(ref,qte,libelle,type,imageData);
           bool test=e.modifier(ref);
            if (test)
            {
                refreshEquip();
                QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                             QObject ::tr("modification effectuée 👍 \n"
                                          "      Click Cancel to exit."),
                        QMessageBox:: Cancel);
                ui->lineEdit_ref->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->comboBox->clear();

        }
            else
            {
                QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                     QObject::tr("try again.\n"
                                                 "click cancel to exit."),QMessageBox::Cancel);
                ui->lineEdit_ref->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->comboBox->clear();

            }

}

void equipmentmanagement::on_lineEdit_5_textChanged(const QString &arg1)
{
    proxy2->setFilterFixedString(arg1);
}


void equipmentmanagement::on_pushButton_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out << "<html>\n"
        << "<head>\n"
        << "<meta content=\"text/html; charset=utf-8\">\n"
        << QString("<title>%1</title>\n").arg("strTitle")
        << "<style>\n"
        << "table {border-collapse: collapse; width: 100%;}\n"
        << "th, td {text-align: left; padding: 8px;}\n"
        << "th {background-color: #008080; color: #fff;}\n"
        << "tr:nth-child(even) {background-color: #f2f2f2;}\n"
        << "</style>\n"
        << "</head>\n"
        << "<body>\n"
        << "<center>\n"
        << "<h1>Liste Des suivi</h1>\n"
        << "<br>"
        << "<table border=\"1\" cellspacing=\"0\" cellpadding=\"2\">\n";

    // headers
    out << "<thead>\n"
        << "<tr>\n"
        << "<th>Numero</th>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->tableView->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr>\n"
        << "</thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>\n"
            << "<td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</table>\n"
        << "</center>\n"
        << "</body>\n"
        << "</html>\n";

    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);
}








void equipmentmanagement::on_pushButton_2_clicked()
{


        // Create a new dialog window
           QDialog *dialog = new QDialog();

           // Set the window title
           dialog->setWindowTitle("Statistics");
           dialog->setFixedSize(QSize(1500, 900));
           // Define the width and height of the chart
           int width = 800;
           int height = 600;

           // Create a chart object
           QChart chart;

           // Set the chart title
           chart.setTitle("Type d'equipement");

           // Create a pie series and add it to the chart
           QPieSeries *series = new QPieSeries();

           // Query the database to get the data for the chart
           QSqlQuery query;
           query.prepare("SELECT TYPE, COUNT(*) FROM EQUIPEMENT GROUP BY type");
           if(query.exec())
           {
               int total = 0;
               while(query.next())
               {
                   // Get the type and count for the current row
                   QString type = query.value(0).toString();
                   int count = query.value(1).toInt();

                   // Add the type and count to the series
                   series->append(type, count);

                   // Increment the total count
                   total += count;
               }

               // Set the series as the data source for the chart
               chart.addSeries(series);

               // Set the chart legend to show the percentage values
               QPieSlice *slice;
               foreach(slice, series->slices()) {
                   slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
               }

               // Create a chart view and set its size
               QChartView *chartView = new QChartView(&chart, dialog);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->resize(width, height);

               // Create a layout for the dialog window and add the chart view widget to it

           }

           // Show the dialog window
           dialog->exec();

    }

void equipmentmanagement::on_InsertImage_clicked()
{
    {
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Images (*.png *.xpm *.jpg *.bmp)"));
        if (imagePath.isEmpty()) {
            return;
        }

        QImage image(imagePath);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // Choose the appropriate format here

        QSqlQuery query;
        query.prepare("INSERT INTO EQUIPEMENT (IMG) VALUES (:image)");
        query.bindValue(":image", byteArray);
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Failed to insert image into the database.\n"
                                     "Error: %1").arg(query.lastError().text()),
                                  QMessageBox::Ok);
        } else {
            QMessageBox::information(this, tr("Success"),
                                     tr("Image successfully inserted into the database."),
                                     QMessageBox::Ok);
        }
    }

}


void equipmentmanagement::on_btnDisplayImage_clicked()
{
    // Get the ID of the image to display from a QLineEdit widget
        int ref = ui->lineEdit->text().toInt();

        // Retrieve the image data from the database using the image ID
        QByteArray imageData = getImageDataFromDatabase(ref);

        // Create a QImage object from the image data
        QImage image;
        image.loadFromData(imageData);

        // Display the image in a QLabel widget
        ui->label_4->setPixmap(QPixmap::fromImage(image));
}


void equipmentmanagement::on_checkButton_clicked()
{
      int target_number = 4; // Change this to the target number you want to check
      equipement equipement;
      equipement.checkPrimaryKeyCount(target_number);

}

void equipmentmanagement::on_comboBox_2_currentIndexChanged(int index)
{
    ui->tableView->sortByColumn(index,Qt::AscendingOrder);
}


