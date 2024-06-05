#ifndef EQUIPMANAGEMENT_H
#define EQUIPMANAGEMENT_H

#include "equipement.h"
#include <QBuffer>
#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableView>
#include <QWidget>

namespace Ui {
class equipmanagement;
}

class equipmanagement : public QWidget
{
    Q_OBJECT

public:
    explicit equipmanagement(QWidget *parent = nullptr);
    ~equipmanagement();
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
    Ui::equipmanagement *ui;
    equipement e;
    QSqlTableModel *model, *setupModel();
    QTableView *view, *setupView();
    QStringList *dbInfo;
    QSqlDatabase *db;
    QPushButton *button;

    void setupMyUi();
};

#endif // EQUIPMANAGEMENT_H
