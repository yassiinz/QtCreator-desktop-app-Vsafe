#ifndef SCHEDULERPAGE_H
#define SCHEDULERPAGE_H

#include <QWidget>
#include "utilisateur.h"
#include "mainwindow.h"
#include "adminschedule.h"
namespace Ui {
class schedulerpage;
}

class schedulerpage : public QWidget
{
    Q_OBJECT

public:
    explicit schedulerpage(QWidget *parent = nullptr);
    ~schedulerpage();
    void getEmail(QString email);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::schedulerpage *ui;
AdminSchedule *ads;
    QString sch_email;
};

#endif // SCHEDULERPAGE_H
