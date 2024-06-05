#include "adminvehicles.h"
#include "ui_adminvehicles.h"
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QIntValidator>
#include <QFileDialog>
#include <QPdfWriter>
#include <QtDebug>
#include <QPainter>
#include <QDesktopServices>
#include <QTextDocument>
#include <QTimer>
#include <QDate>
#include <QFrame>
#include <QUrl>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>

AdminVehicles::AdminVehicles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminVehicles)
{
    ui->setupUi(this);
    ui->tableView->setModel(tabb.afficher());

    ui->lineEdit_id->setValidator(new QRegExpValidator (QRegExp("[a-z-A-Z]+"),this));
    ui->lineEdit_centre->setValidator(new QRegExpValidator (QRegExp("[a-z-A-Z]+"),this));


    /*buttonOn = new QPushButton("ON", this);
                    buttonOff = new QPushButton("OFF", this);

                    buttonOn->setGeometry(740, 515, 100, 30);
                    buttonOff->setGeometry(740, 610, 100, 30);

                    connect(buttonOn, &QPushButton::clicked, this, &AdminVehicles::onButtonOnClicked);
                    connect(buttonOff, &QPushButton::clicked, this, &AdminVehicles::onButtonOffClicked);
                    connect(&arduino, &Arduino::fireDetected, this, &AdminVehicles::onFireDetected);
                    connect(&arduino, &Arduino::fireCleared, this, &AdminVehicles::onFireCleared);

                    fireDetectedFlag = false;
                    etatPisteLabel = new QLabel(this);
                    fireMessageTimer = new QTimer(this);
                    connect(fireMessageTimer, &QTimer::timeout, this, &AdminVehicles::onFireMessageTimerTimeout);
                    warningLabel = new QLabel(this);
                    warningLabel->setStyleSheet("background-color: red; color: white; font-size: 23px;");
warningLabel->setGeometry(850,515, 225, 125);*/

    cin_query = new QSqlQueryModel();
    cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
    ui->comboBox_cin->setModel(cin_query);
}

AdminVehicles::~AdminVehicles()
{
    delete ui;
}

/*--------------------------------------------------Ajouter Vehicule----------------------------------------------------------*/


void AdminVehicles::on_pushButton_clicked()
{
    QString SERIE_VEHICULE=ui->lineEdit_id->text();
    QString Marque =ui->lineEdit_centre->text();
    QDateTime DPMC=ui->dateEdit->dateTime();
    QString Categorie=ui->lineEdit_centre_2->text();
    QString VIN =ui->lineEdit_piste->text();
    double Montant =ui->lineEdit_3->text().toDouble();
    int CIN = ui->comboBox_cin->currentText().toInt();


    //QDate actual_date=QDate::currentDate();
    //
    Vehicule v (SERIE_VEHICULE,Marque,DPMC,VIN,Categorie,Montant, CIN);
    //
    bool test=v.ajouter ();
    if (test)
    {
           ui->tableView->setModel(tabb.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                     QObject ::tr("Addition made successfully 👍 \n"
                                  "        Press Cancel to exit"),
                QMessageBox:: Cancel);



}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("Try again.\n"
                                         "Click cancel to exit."),QMessageBox::Cancel);


    }
}


//*--------------------------------------------------Afficher Vehicule----------------------------------------------------------*//


void AdminVehicles::on_pushButton_8_clicked()
{
  ui->tableView->setModel(tabb.afficher());
  ui->tableView->setColumnWidth(0,150);
  ui->tableView->setColumnWidth(1,150);
  ui->tableView->setColumnWidth(2,170);
  ui->tableView->setColumnWidth(3,170);
  ui->tableView->setColumnWidth(4,162);

  /*ui->tableView->setItemDelegateForColumn(3, new QStyledItemDelegate);
  ui->tableView->setItemDelegateAlignment(column, Qt::AlignCenter);*/
}

//*--------------------------------------------------Supprimer Vehicule----------------------------------------------------------*//


void AdminVehicles::on_pushButton_3_clicked()
{
    QString SERIE_VEHICULE=ui->lineEdit_id->text();
    bool test=tabb.supprimer(SERIE_VEHICULE);
    if(test)
    {


        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppresion éffectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else{
        QMessageBox::information(nullptr, QObject::tr("Not Ok"),
                    QObject::tr("Suppresion non éffectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//*--------------------------------------------------Modifier Vehicule----------------------------------------------------------*//


void AdminVehicles::on_pushButton_2_clicked()
{
    QString SERIE_VEHICULE=ui->lineEdit_id->text();
    QString Marque =ui->lineEdit_centre->text();
    QDateTime DPMC=ui->dateEdit->dateTime();
    QString VIN =ui->lineEdit_piste->text();
    QString Categorie=ui->lineEdit_centre_2->text();
    double Montant =ui->lineEdit_3->text().toDouble();
    int CIN = ui->comboBox_cin->currentText().toInt();

;
       Vehicule v(SERIE_VEHICULE,Marque,DPMC,VIN,Categorie,Montant, CIN);


       bool test=v.modifier(SERIE_VEHICULE); //Verification de la fonction Modifier
        if (test)
        {
               ui->tableView->setModel(tabb.afficher());
            QMessageBox :: information (nullptr, QObject ::tr("PERFECT !"),
                         QObject ::tr("Modification made successfully 👍 \n"
                                      "        Press Cancel to exit"),
                    QMessageBox:: Cancel);
            ui->lineEdit_id->clear();
            ui->lineEdit_centre->clear();
            ui->lineEdit_piste->clear();
            cin_query = new QSqlQueryModel();
            cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
            ui->comboBox_cin->setModel(cin_query);

    }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
            ui->lineEdit_id->clear();
            ui->lineEdit_centre->clear();
            ui->lineEdit_piste->clear();
            cin_query = new QSqlQueryModel();
            cin_query->setQuery("SELECT CIN FROM client ORDER BY CIN;");
            ui->comboBox_cin->setModel(cin_query);
        }
}





void AdminVehicles::on_pushButton_6_clicked()
{
    QSqlQuery query;

    QString valeur = ui->lineEdit_recherche->text().trimmed();

    if (valeur.isEmpty())
    {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
        return;
    }

    QSqlQueryModel *model = tabb.rechercher(valeur);


    if (model->rowCount() == 0)
    {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
    }
    else
    {
        QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
        QMessageBox::information(this, "Recherche", message);
        ui->tableView->setModel(model);
        ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    }











    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawText(600,700,"Smart Technical Center");
                                          painter.setPen(Qt::red);
                                          painter.setFont(QFont("Arial", 25, QFont::Bold));
                                          painter.drawText(3000,1400,"Liste Des Vehicules");
                                          painter.setPen(Qt::black);
                                          painter.setFont(QFont("Arial", 15));
                                          painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                          painter.drawRect(100,3000,9400,500);
                                          painter.setFont(QFont("Arial", 9));
                                          painter.drawText(300,3300,"Serie");
                                          painter.drawText(2000,3300,"Marque");
                                          painter.drawText(4000,3300,"Categorie");
                                          painter.drawText(5600,3300,"VIN");
                                          painter.drawText(7000,3300,"Montant Total A Payer ");
                                          painter.drawRect(100,3000,9400,10700);
                                          QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);
    QString SERIE_VEHICULE = ui->lineEdit_recherche->text(); // get the entered SERIE_VEHICULE value from the line edit widget

    query.prepare("SELECT SERIE_VEHICULE, MARQUE, Categorie , VIN , Montant FROM VEHICULE WHERE SERIE_VEHICULE = :SERIE_VEHICULE");
       query.bindValue(":SERIE_VEHICULE", SERIE_VEHICULE);
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(4000,i,query.value(2).toString());
        painter.drawText(5600,i,query.value(3).toString());
        painter.drawText(7000,i,query.value(4).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer Facture", " Facture Enregistré ! Voulez Vous Affichez Le Facture ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }
}




void AdminVehicles::on_triID_clicked()
{
    ui->tableView->setModel(tabb.triID());

}
void AdminVehicles::on_ID_desc_clicked()
{
    ui->tableView->setModel(tabb.triMarque());
}

void AdminVehicles::on_triCat_clicked()
{
    ui->tableView->setModel(tabb.triCat());

}


void AdminVehicles:: on_pushButton_9_clicked()
{
       QDialog *dialog = new QDialog();

       dialog->setWindowTitle("Statistics");
       dialog->setFixedSize(QSize(1500, 900));


       int width = 800;
       int height = 600;

       QChart chart;

       chart.setTitle("Type de Marques");

       QPieSeries *series = new QPieSeries();

       QSqlQuery query;
       query.prepare("SELECT Marque, COUNT(*) FROM VEHICULE GROUP BY Marque");
       if(query.exec())
       {
           int total = 0;
           while(query.next())
           {
               QString type = query.value(0).toString();
               int count = query.value(1).toInt();

               series->append(type, count);

               total += count;
           }

           chart.addSeries(series);

           QPieSlice *slice;
           foreach(slice, series->slices()) {
               slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
           }

           QChartView *chartView = new QChartView(&chart, dialog);
           chartView->setRenderHint(QPainter::Antialiasing);
           chartView->resize(width, height);

           QVBoxLayout *layout = new QVBoxLayout();
           layout->addWidget(chartView);
           dialog->setLayout(layout);
       }

       // Show the dialog window
       dialog->exec();

}





void AdminVehicles::addPagination()
{

int currentPage = ui->tableView->currentIndex().row() / m_pageSize;
int rowCount = ui->tableView->model()->rowCount();

int startRow = currentPage * m_pageSize;
int endRow = qMin(startRow + m_pageSize, rowCount) - 1;


for (int row = 0; row < rowCount; row++) {
if (row >= startRow && row <= endRow) {
ui->tableView->setRowHidden(row, false);
} else {
ui->tableView->setRowHidden(row, true);
}
}








}

//PAGINATION
void AdminVehicles::on_moisuivant_clicked()
{
    int m_currentPage = 0;

    QModelIndex currentIndex = ui->tableView->currentIndex();
    int nextIndexRow = currentIndex.row() + m_pageSize;
    int rowCount = ui->tableView->model()->rowCount();
    if (nextIndexRow >= rowCount) {
    nextIndexRow = rowCount - 1;
    }

    m_currentPage = nextIndexRow / m_pageSize;
    addPagination();

    QModelIndex nextIndex = ui->tableView->model()->index(nextIndexRow, currentIndex.column());
    ui->tableView->setCurrentIndex(nextIndex);
}

void AdminVehicles::on_moisprec_clicked()
{    int m_currentPage = 0;

    m_currentPage--;
    if (m_currentPage < 0) {
    m_currentPage = 0;
    }
    addPagination();

    int prevPageStartRow = m_currentPage * m_pageSize;
    int rowCount = ui->tableView->model()->rowCount();
    if (prevPageStartRow < rowCount) {
    QModelIndex prevIndex = ui->tableView->model()->index(prevPageStartRow, 0);
    ui->tableView->setCurrentIndex(prevIndex);
    }
}
/*
 * void AdminVehicles::onButtonOnClicked()
{
    arduino.sendCommand("ON");
}

void AdminVehicles::onButtonOffClicked()
{
    arduino.sendCommand("OFF");
}
*/


/*void AdminVehicles::onFireDetected()
{
    // Define fireDetectedFlag outside of the code block


   if (!fireDetectedFlag ) {

           warningLabel->setText("Warning: Fire Detected");
           // Show the warning label
           warningLabel->show();
           // Set fireDetectedFlag to true to prevent showing the message again
           fireDetectedFlag = true;

   }

        QSqlQuery query;
        query.prepare("UPDATE PISTE SET ETAT_PISTE=:etat WHERE NUM=1");
        query.bindValue(":etat", "Piste incendie");

        if (!query.exec()) {
            qWarning() << "Failed to execute query:" << query.lastError().text();
            return;
        }
    }

void AdminVehicles::onFireMessageTimerTimeout()
{
    fireDetectedFlag = false;
        // Hide the warning label
        warningLabel->hide();
        // Stop the timer
        fireMessageTimer->stop();
}

void AdminVehicles::onFireCleared()
{
    fireDetectedFlag = false;
}

void AdminVehicles::showEtatPiste() {

    QSqlQuery query;
    if (query.exec("SELECT ETAT_PISTE FROM PISTE")) {
        if (query.next()) {
            QString etatPiste = query.value(0).toString();
            etatPisteLabel->setText(etatPiste);
       }

}
}*/
//Facture

double calculateTotalCost(double price, double taxRate)
{
    // Calculate the total cost with taxes
    return price + (price * taxRate / 100);
}
void AdminVehicles::on_pushButton_11_clicked()
{
       QString paymentDateStr = ui->dateEdit->text();

       // Parse payment date
       QDate paymentDate = QDate::fromString(paymentDateStr, "dd/MM/yyyy");

       // Calculate number of days late
       int lateDays = QDate::currentDate().daysTo(paymentDate);


    // Get the input values from the user
        QString brand = ui->lineEdit_centre->text();
        QString cat = ui->lineEdit_centre_2->text();

        double price = ui->lineEdit_2->text().toDouble();

        // Calculate the total cost with taxes based on the brand
        double totalCost;

        const double BRAND_A_TAX_RATE = 20.00;
            const double BRAND_B_TAX_RATE = 25.00;
            const double BRAND_C_TAX_RATE = 5.50;
            const double Privee = 5.00;
            const double Publique = 35.00;


               if (cat == "Publique") {
            totalCost = calculateTotalCost(price, Publique);
        }
        else if (cat == "Privee") {
            totalCost = calculateTotalCost(price, Privee);
        }
        else
               if (brand == "Toyota") {
            totalCost = calculateTotalCost(price, BRAND_A_TAX_RATE);
        } else if (brand == "Porsche") {
            totalCost = calculateTotalCost(price, BRAND_B_TAX_RATE);
        } else if (brand == "KIA") {
            totalCost = calculateTotalCost(price, BRAND_C_TAX_RATE);
        } else {
            QMessageBox::warning(this, "Invalid Brand", "Invalid brand entered. Please enter Toyota, Porsche, or KIA.");
            return;
        }
        // Calculate fines Due To date and time delay
      /* double fines = 25;
       if(lateDays>75)
       {
            fines = price * 0.05 * lateDays;}
*/
        // Output total cost with taxes


               // String to INT valeur
        ui->lineEdit_3->setText(QString("%1").arg(totalCost));


        QString carModel  = ui->lineEdit_centre->text();
            QString review = ui->lineEdit_3->text();
            QString date  = ui->dateEdit->text();
            QString categorie  = ui->lineEdit_centre_2->text();



        QMessageBox::information(this, "Car Details",
               "Marque: " + carModel  + "\n"  +
                                 "Date: " + date  + "\n"  +
                                 "Categorie: " + categorie  + "\n"  +

               "Total Amount: " + review);


}




void AdminVehicles::on_pushButton_4_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawText(400,700,"E-Planner");
                                          painter.setPen(Qt::red);
                                          painter.setFont(QFont("Time New Roman", 25));
                                          painter.drawText(3000,1400,"Liste Des Vehicules");
                                          painter.setPen(Qt::black);
                                          painter.setFont(QFont("Time New Roman", 15));
                                          painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                          painter.drawRect(100,3000,9400,500);
                                          painter.setFont(QFont("Time New Roman", 9));
                                          painter.drawText(300,3300,"Serie");
                                          painter.drawText(2000,3300,"Marque");
                                          painter.drawText(4000,3300,"Categorie");
                                          painter.drawText(5600,3300,"VIN");
                                          painter.drawText(7000,3300,"Montant");
                                          painter.drawRect(100,3000,9400,10700);
                                          QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT SERIE_VEHICULE , MARQUE , VIN , Categorie , Montant from VEHICULE");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(4000,i,query.value(2).toString());
        painter.drawText(5600,i,query.value(3).toString());
        painter.drawText(7000,i,query.value(4).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer Facture", " Facture Enregistré ! Voulez Vous Affichez Le Facture ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }
}
