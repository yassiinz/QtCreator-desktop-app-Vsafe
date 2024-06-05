#ifndef ADMINPISTE_H
#define ADMINPISTE_H

#include <QWidget>
#include "piste.h"
#include "statistic.h"
#include "arduino.h"

namespace Ui {
class AdminPiste;
}

class AdminPiste : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPiste(QWidget *parent = nullptr);
    ~AdminPiste();

private slots:

    void on_pushButtonModifier_clicked();

    void on_pushButtonActualiser_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButtonAnnuler_clicked();

    void on_pushButtonAnnuler_2_clicked();

    void on_pushButtonAjouterPiste_clicked();

    void on_tableViewAffichage_activated(const QModelIndex &index);

    void on_pushButtonPDF_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_comboBoxTrie_activated(const QString &arg1);

    void on_pushButtonStat_clicked();

    void on_selectTraduction_currentIndexChanged(int index);

    void on_pushButtonActualiserHistorique_clicked();

    void on_pushButtonImg_clicked();

    void on_pushButtonImg_2_clicked();

    void on_pushButtonStat_2_clicked();

private:
    Ui::AdminPiste *ui;
    piste p;
    Statistic *statistic;
    Arduino A;
};

#endif // ADMINPISTE_H
