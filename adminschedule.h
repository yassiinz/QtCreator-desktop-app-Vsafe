#ifndef ADMINSCHEDULE_H
#define ADMINSCHEDULE_H

#include <QWidget>
#include "RDV.h"
#include "historique.h"

namespace Ui {
class AdminSchedule;
}

class AdminSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit AdminSchedule(QWidget *parent = nullptr);
    ~AdminSchedule();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    //void update_label();

    void on_calendarWidget_selectionChanged();

private:
    Ui::AdminSchedule *ui;
    RDV tabb;
    historique his;
    QSqlQueryModel *cin_query;
};

#endif // ADMINSCHEDULE_H
