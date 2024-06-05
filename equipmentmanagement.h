#ifndef EQUIPMENTMANAGEMENT_H
#define EQUIPMENTMANAGEMENT_H

#include "equipement.h"
#include <QSortFilterProxyModel>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QBuffer>
#include <QFileInfo>
#include <QFileDialog>
#include <QSqlError>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class equipmentmanagement;}
QT_END_NAMESPACE

class equipmentmanagement : public QMainWindow
{
    Q_OBJECT

public:
    equipmentmanagement(QMainWindow *parent = nullptr);
    ~equipmentmanagement();
    QSortFilterProxyModel *proxy2;

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_2_clicked();

    void refreshEquip();

    void on_pushButton_5_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);


    void on_pushButton_pdf_clicked();



    void on_pushButton_2_clicked();


    void on_btnDisplayImage_clicked();

    void on_InsertImage_clicked();

    void on_checkButton_clicked();

    void on_comboBox_2_currentIndexChanged(int index);


private:
    Ui::equipmentmanagement *ui;
    equipement e;
    QSqlTableModel *model, *setupModel();
    QTableView *view, *setupView();
    QStringList *dbInfo;
    QSqlDatabase *db;
    QPushButton *button;

    void setupMyUi();

};

#endif // EQUIPMENTMANAGEMENT_H
