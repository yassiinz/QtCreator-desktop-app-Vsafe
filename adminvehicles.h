#ifndef ADMINVEHICLES_H
#define ADMINVEHICLES_H

#include <QWidget>
#include <QStandardItemModel>
#include "connection.h"
#include "Vehicule.h"
#include "arduino.h"

namespace Ui {
class AdminVehicles;
}

class AdminVehicles : public QWidget
{
    Q_OBJECT

public:
    explicit AdminVehicles(QWidget *parent = nullptr);
    ~AdminVehicles();
    int m_currentPage = 0;
        const int m_pageSize = 5;
        //QSortFilterProxyModel* proxyModel;
        QStandardItemModel *model;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();
    void on_pushButton_4_clicked();// Facture + PDF


    void on_pushButton_6_clicked(); // Metier 1 // Rechercher

    void on_triID_clicked(); // Metier 3 // ID
    void on_ID_desc_clicked(); // Metier 3 // ID
    void on_triCat_clicked(); // Metier 3 // ID

    void on_pushButton_9_clicked();//Stat

    void onButtonOnClicked();
        void onButtonOffClicked();
        void onFireDetected();
        void onFireCleared();
        void showEtatPiste();
        void onFireMessageTimerTimeout();



        void on_pushButton_11_clicked();



    void addPagination(); // Pagination

        void on_moisuivant_clicked();

        void on_moisprec_clicked();

private:
    Ui::AdminVehicles *ui;
    Vehicule tabb;

        QSqlDatabase *db;
        QPushButton *button;
        QPushButton *buttonOn;
        QPushButton *buttonOff;
        Arduino arduino;
        Connection c;
        QTimer *fireMessageTimer;
        QLabel *etatPisteLabel;
        QLabel *warningLabel;
        bool fireDetectedFlag;
        QSqlQueryModel *cin_query;
};

#endif // ADMINVEHICLES_H
