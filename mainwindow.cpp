#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilisateur.h"
#include <QApplication>
#include <QProcess>
#include <QPainter>
#include <QFileDialog>
#include <QPrinter>
#include <QDebug>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableView_2->setModel(u.afficher());

    proxy = new QSortFilterProxyModel();
        proxy->setSourceModel(u.afficher());
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setFilterKeyColumn(-1);
        ui->tableView_2->setModel(proxy);
            ui->tableView_2->resizeRowsToContents();
            ui->tableView_2->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_4_clicked()
{
    //Récupération des informations saisies dans les champs

QString ID=ui->LE_ID->text();
QString mdp=ui->LE_mdp->text();
QString prenom=ui->LE_prenom->text();
QString nom=ui->LE_nom->text();
int tlf=ui->LE_tlf->text().toInt();
QString fonction=ui->LE_fct->text();
float salaire=ui->LE_fct->text().toFloat();
QDateTime date_emb=ui->dateEdit->dateTime();

QString mail=ui->LE_mail->text();

Utilisateur u(ID,mdp,nom,prenom,tlf,mail,date_emb,fonction,salaire);

bool test=u.ajouter();

if (test){

    //Refresh !
    ui->tableView_2->setModel(u.afficher());

       QMessageBox::information(this,QObject::tr("OK"),QObject::tr("Succuessfully Added\n"
                                                                      "Click Cancel to exit."),QMessageBox::Cancel);
ui->LE_ID->clear();
ui->LE_mdp->clear();
ui->LE_prenom->clear();
ui->LE_nom->clear();
ui->LE_tlf->clear();
ui->LE_fct->clear();
ui->LE_mail->clear();
ui->dateEdit->clear();
ui->LE_salaire->clear();
}
else {
    ui->tableView_2->setModel(u.afficher());

    QMessageBox::critical(this,QObject::tr("warning"),QObject::tr("Failed to Add\n"
                                                                   "Click Cancel to exit."),QMessageBox::Cancel);
    ui->LE_ID->clear();
    ui->LE_mdp->clear();
    ui->LE_prenom->clear();
    ui->LE_nom->clear();
    ui->LE_tlf->clear();
    ui->LE_fct->clear();
    ui->LE_mail->clear();
    ui->dateEdit->clear();
    ui->LE_salaire->clear();


}
}

void MainWindow::on_pushButton_5_clicked()
{
    QString ID=ui->LE_ID_2->text();
        bool test=u.supprimer(ID);
        if(test)
        {
             ui->tableView_2->setModel(u.afficher());
            QMessageBox::information(this,QObject::tr("ok"),QObject::tr("Succuessfully Deleted\n" "Click Cancel to exit."),QMessageBox::Cancel);
            ui->LE_ID_2->clear();

        }
        else
        {
            QMessageBox::critical(this,QObject::tr("not ok"),QObject::tr("Failed to Delete\n" "Click Cancel to exit."),QMessageBox::Cancel);
            ui->LE_ID_2->clear();

        }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString ID=ui->LE_ID->text();
    QString mdp=ui->LE_mdp->text();
    QString prenom=ui->LE_prenom->text();
    QString nom=ui->LE_nom->text();
    int tlf=ui->LE_tlf->text().toInt();
    QString fonction=ui->LE_fct->text();
    float salaire=ui->LE_fct->text().toFloat();
    QDateTime date_emb=ui->dateEdit->dateTime();
    QString mail=ui->LE_mail->text();

    Utilisateur u (ID,mdp,nom,prenom,tlf,mail,date_emb,fonction,salaire);
        bool test=u.update(ID);

        if (test)
        {
            ui->tableView_2->setModel(u.afficher());
            QMessageBox::information(this,QObject::tr("ok"),QObject::tr("Succuessfuly Updated\n" "Click Cancel to exit."),QMessageBox::Cancel);
            ui->LE_ID->clear();
            ui->LE_mdp->clear();
            ui->LE_prenom->clear();
            ui->LE_nom->clear();
            ui->LE_tlf->clear();
            ui->LE_fct->clear();
            ui->LE_mail->clear();
            ui->dateEdit->clear();
            ui->LE_salaire->clear();

        }
        else

        {
QMessageBox::critical(this,QObject::tr("not ok"),QObject::tr("Update Failed\n" "Click Cancel to exit."),QMessageBox::Cancel);


        }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->tableView_2->sortByColumn(index,Qt::AscendingOrder);
}

void MainWindow::on_pushButton_clicked()
{

    QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView_2->model()->rowCount();
        const int columnCount = ui->tableView_2->model()->columnCount();

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
            << "<h1>Users Information</h1>\n"
            << "<br>"
            << "<table border=\"1\" cellspacing=\"0\" cellpadding=\"2\">\n";

        // headers
        out << "<thead>\n"
            << "<tr>\n"
            << "<th>Numero</th>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
            }
        }
        out << "</tr>\n"
            << "</thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>\n"
                << "<td>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->tableView_2->isColumnHidden(column)) {
                    QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
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


void MainWindow::on_pushButton_2_clicked()
{
    // Create a new dialog window

    QDialog *dialog = new QDialog();
    // Set the window title
          dialog->setWindowTitle("Statistics");
          dialog->setFixedSize(QSize(1500, 900));
          // Define the width and height of the chart
          int width = 800;
          int height = 600;

    QSqlQuery query;
    query.exec("SELECT FONCTION, COUNT(*) FROM UTILISATEUR GROUP BY FONCTION");

    // Compute the total number of users
    int totalEmployees = 0;
    while (query.next()) {
        totalEmployees += query.value(1).toInt();
    }

    // Create the pie series
    QPieSeries *series = new QPieSeries();
    while (query.previous()) {
        QString function = query.value(0).toString();
        int count = query.value(1).toInt();
        float percentage = (float)count / totalEmployees * 100.0;
        series->append(QString("%1 (%2%)").arg(function).arg(percentage, 0, 'f', 2), count);
    }

    // Create the chart and add the series to it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Functions");

    // Customize the appearance of the chart
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart, dialog);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->resize(width, height);


    // Create a layout for the dialog window and add the chart view widget to it
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    dialog->setLayout(layout);
    // Show the dialog window
          dialog->exec();
    }




void MainWindow::on_nom_clicked()
{
    this->close();
}
