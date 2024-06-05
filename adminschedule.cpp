#include "adminschedule.h"
#include "ui_adminschedule.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QIntValidator>
#include<QPainter>
#include <QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include"QFileDialog"
#include"QTextStream"
#include<QTextDocument>
#include "qcustomplot.h"


AdminSchedule::AdminSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminSchedule)
{
    ui->setupUi(this);
    ui->tableView->setModel(tabb.afficher());
    ui->tableView->setColumnWidth(0,125);
    ui->tableView->setColumnWidth(1,125);
    ui->tableView->setColumnWidth(2,151);
    ui->tableView->setColumnWidth(3,151);
    ui->tableView->setColumnWidth(4,125);
    ui->tableView->setColumnWidth(5,125);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    ui->lineEdit_id->setValidator(new QIntValidator(1,99,this));
    ui->lineEdit_piste->setValidator(new QIntValidator(1,6,this));
    //ui->lineEdit_cin->setValidator(new QIntValidator(99999999,99999999,this));
    QRegularExpression rx("\\b[A-Z]{2,10}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_centre->setValidator(new QRegularExpressionValidator(rx, this));
    cin_query = new QSqlQueryModel();
    cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
    ui->comboBox->setModel(cin_query);
}

AdminSchedule::~AdminSchedule()
{
    delete ui;
}

void AdminSchedule::on_calendarWidget_selectionChanged()
{
    ui->dateEdit->setDate(ui->calendarWidget->selectedDate());
QDate date=ui->dateEdit->date();
        /*QDate datet;
        datet=date;*/
    QSqlQueryModel *mod = new QSqlQueryModel();
    QSqlQuery qry;

    qry.prepare("SELECT * FROM RDV WHERE DATE_RDV=:date");
    qry.bindValue(":date", date);

    if(qry.exec())
    {
        mod->setQuery(qry);
        ui->tableView->setModel(mod);
    }
    else
    {
        QMessageBox::warning(this, tr("Erreur"), tr("La requête a échoué."));
    }
}
//*--------------------------------------------------Ajouter un Rendez_vous----------------------------------------------------------*//


void AdminSchedule::on_pushButton_clicked()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString date=dateTime.toString();
    int id=ui->lineEdit_id->text().toInt();
    QString centre =ui->lineEdit_centre->text();
    QDate date_rdv =ui->dateEdit->date();
    QTime heure_rdv=ui->timeEdit->time();
    int num =ui->lineEdit_piste->text().toInt();
    int cin =ui->comboBox->currentText().toInt();
    RDV r(id,centre,date_rdv,heure_rdv,num,cin);
    //
    bool test=r.ajouter ();
    if (test)
    {
           ui->tableView->setModel(tabb.afficher());
           ui->tableView->setColumnWidth(0,125);
           ui->tableView->setColumnWidth(1,125);
           ui->tableView->setColumnWidth(2,151);
           ui->tableView->setColumnWidth(3,151);
           ui->tableView->setColumnWidth(4,125);
           ui->tableView->setColumnWidth(5,125);
        QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                     QObject ::tr("Addition made successfully 👍 \n"
                                  "        Press Cancel to exit"),
                QMessageBox:: Cancel);
        ui->lineEdit_centre->clear();
        ui->lineEdit_piste->clear();
        cin_query = new QSqlQueryModel();
        cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
        ui->comboBox->setModel(cin_query);
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime::currentTime());
        his.save("appointment n°"+ui->lineEdit_id->text()," has been added in : "+ui->dateEdit->text() +""+ui->timeEdit->text());
        ui->lineEdit_id->clear();
}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("try again.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
        ui->lineEdit_id->clear();
        ui->lineEdit_centre->clear();
        ui->lineEdit_piste->clear();
        cin_query = new QSqlQueryModel();
        cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
        ui->comboBox->setModel(cin_query);
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime::currentTime());
    }
}


//*--------------------------------------------------Afficher un Rendez_vous----------------------------------------------------------*//


void AdminSchedule::on_pushButton_8_clicked()
{
  ui->tableView->setModel(tabb.afficher());
  ui->tableView->setColumnWidth(0,125);
  ui->tableView->setColumnWidth(1,125);
  ui->tableView->setColumnWidth(2,151);
  ui->tableView->setColumnWidth(3,151);
  ui->tableView->setColumnWidth(4,125);
  ui->tableView->setColumnWidth(5,125);
  //ui->tableView->setItemDelegateForColumn(3, new QStyledItemDelegate);
  //ui->tableView->setItemDelegateAlignment(3, Qt::AlignCenter);
}


//*--------------------------------------------------Supprimer un Rendez_vous----------------------------------------------------------*//


void AdminSchedule::on_pushButton_3_clicked()
{
    int id =ui->lineEdit_id->text().toInt();
     bool test=tabb.supprimer(id);
     if (test)
     {
         his.save("appointment n°"+ui->lineEdit_id->text()," has been deleted in : "+ui->dateEdit->text()+""+ui->timeEdit->text());
         ui->tableView->setModel(tabb.afficher());
         ui->tableView->setColumnWidth(0,125);
         ui->tableView->setColumnWidth(1,125);
         ui->tableView->setColumnWidth(2,151);
         ui->tableView->setColumnWidth(3,151);
         ui->tableView->setColumnWidth(4,125);
         ui->tableView->setColumnWidth(5,125);
        QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                      QObject ::tr("deletion made successfully 👍 \n"
                                   "        Press Cancel to exit"),
                 QMessageBox:: Cancel);
        ui->lineEdit_id->clear();

    }
     else
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
         ui->lineEdit_id->clear();
     }
}


//*--------------------------------------------------Modifier un Rendez_vous----------------------------------------------------------*//


void AdminSchedule::on_pushButton_2_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString centre =ui->lineEdit_centre->text();
    QDate date_rdv =ui->dateEdit->date();
    QTime heure_rdv=ui->timeEdit->time();
    int num=ui->lineEdit_piste->text().toInt();
    int cin =ui->comboBox->currentText().toInt();
       RDV r(id,centre,date_rdv,heure_rdv,num,cin);
        bool test=r.modifier(id);
        if (test)
        {
               his.save("appointment n°"+ui->lineEdit_id->text()," has been modified in : "+ui->dateEdit->text()+""+ui->timeEdit->text());
               ui->tableView->setModel(tabb.afficher());
               ui->tableView->setColumnWidth(0,125);
               ui->tableView->setColumnWidth(1,125);
               ui->tableView->setColumnWidth(2,151);
               ui->tableView->setColumnWidth(3,151);
               ui->tableView->setColumnWidth(4,125);
               ui->tableView->setColumnWidth(5,125);
            QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                         QObject ::tr("modification made successfully 👍 \n"
                                      "        Press Cancel to exit"),
                    QMessageBox:: Cancel);
            ui->lineEdit_id->clear();
            ui->lineEdit_centre->clear();
            ui->lineEdit_piste->clear();
            cin_query = new QSqlQueryModel();
            cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
            ui->comboBox->setModel(cin_query);
            ui->dateEdit->setDate(QDate::currentDate());
            ui->timeEdit->setTime(QTime::currentTime());

    }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
            ui->lineEdit_id->clear();
            ui->lineEdit_centre->clear();
            ui->lineEdit_piste->clear();
            cin_query = new QSqlQueryModel();
            cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
            ui->comboBox->setModel(cin_query);
            ui->dateEdit->setDate(QDate::currentDate());
            ui->timeEdit->setTime(QTime::currentTime());
        }
}


//*-------------------------------------------------------------TRI_ID--------------------------------------------------------------------------*//


void AdminSchedule::on_pushButton_4_clicked()
{
   ui->tableView->setModel(tabb.tri());
}


//*-------------------------------------------------------------TRI_CENTRE---------------------------------------------------------------------*//


void AdminSchedule::on_pushButton_5_clicked()
{
    ui->tableView->setModel(tabb.tricentre());
}


//*-------------------------------------------------------------TRI_N°_PISTE---------------------------------------------------------------------*//


void AdminSchedule::on_pushButton_11_clicked()
{
  ui->tableView->setModel(tabb.tripiste());
}


//*-------------------------------------------------------------EXPORT_PDF---------------------------------------------------------------------*//


void AdminSchedule::on_pushButton_7_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tableView->model()->rowCount();
   const int columnCount = ui->tableView->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des RDV </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tableView->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
     QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}


//*-------------------------------------------------------------RECHERCHE_ID---------------------------------------------------------------------*//

void AdminSchedule::on_pushButton_6_clicked()
{
    int id=ui->lineEdit_recherche->text().toInt();
    if (id==NULL) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Number."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche(id));
    }
}


//*-------------------------------------------------------------RECHERCHE_CENTRE----------------------------------------------------------------*//


void AdminSchedule::on_pushButton_10_clicked()
{
    QString centre=ui->lineEdit_recherche->text();
    if (centre.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a CENTRE."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche_centre(centre));
    }
}


//*-------------------------------------------------------------RECHERCHE_N°_PISTE--------------------------------------------------------------*//


void AdminSchedule::on_pushButton_12_clicked()
{
    int num=ui->lineEdit_recherche->text().toInt();
    if (num==NULL) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter PISTE."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche_piste(num));
    }
}


//*-------------------------------------------------------------STATISTIQUE--------------------------------------------------------------*//


void AdminSchedule::on_tabWidget_currentChanged(int index)
{
    // background //
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(90, 90, 90));
              gradient.setColorAt(0.38, QColor(105, 105, 105));
              gradient.setColorAt(1, QColor(70, 70, 70));
              ui->plot->setBackground(QBrush(gradient));

              QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
              amande->setAntialiased(false);
              amande->setStackingGap(1);
               //couleurs
              amande->setName("ID");
              amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
              amande->setBrush(QColor(0, 168, 140));

               //axe des abscisses
              QVector<double> ticks;
              QVector<QString> labels;
              tabb.statistique(&ticks,&labels);

              QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
              textTicker->addTicks(ticks, labels);
              ui->plot->xAxis->setLabel("ID RDV");
              ui->plot->xAxis->setTicker(textTicker);
              ui->plot->xAxis->setTickLabelRotation(60);
              ui->plot->xAxis->setSubTicks(false);
              ui->plot->xAxis->setTickLength(0, 4);
              ui->plot->xAxis->setRange(0, 8);
              ui->plot->xAxis->setBasePen(QPen(Qt::white));
              ui->plot->xAxis->setTickPen(QPen(Qt::white));
              ui->plot->xAxis->grid()->setVisible(true);
              ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
              ui->plot->xAxis->setTickLabelColor(Qt::white);
              ui->plot->xAxis->setLabelColor(Qt::white);

              // axe des ordonnées
              ui->plot->yAxis->setRange(0,10);
              ui->plot->yAxis->setPadding(5);
              ui->plot->yAxis->setLabel("Numéro Piste");
              ui->plot->yAxis->setBasePen(QPen(Qt::white));
              ui->plot->yAxis->setTickPen(QPen(Qt::white));
              ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
              ui->plot->yAxis->grid()->setSubGridVisible(true);
              ui->plot->yAxis->setTickLabelColor(Qt::white);
              ui->plot->yAxis->setLabelColor(Qt::white);
              ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
              ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

              // ajout des données  (statistiques de la quantité)//

              QVector<double> PlaceData;
              QSqlQuery q1("select N_PISTE from RDV");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              amande->setData(ticks, PlaceData);

              ui->plot->legend->setVisible(true);
              ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
              ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
              ui->plot->legend->setBorderPen(Qt::NoPen);
              QFont legendFont = font();
              legendFont.setPointSize(5);
              ui->plot->legend->setFont(legendFont);
              ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

              QTextCharFormat f=ui->calendarWidget->weekdayTextFormat(Qt::Saturday);

              tabb.calendrier(f,ui->calendarWidget);

}
