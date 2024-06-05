#ifndef CLIENTMANAGEMENT_H
#define CLIENTMANAGEMENT_H

#include "client.h"
#include "utilisateur.h"
#include "arduino.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class clientmanagement; }
QT_END_NAMESPACE

class clientmanagement : public QWidget
{
    Q_OBJECT
public:
    clientmanagement(QWidget *parent = nullptr);
    ~clientmanagement();
    void refreshClient(); //Refresh client function
    void clear(); //Clear client input function
    Client *cl;
    QIntValidator *numVali;
    QRegExpValidator *mailVali;
    QRegExpValidator *nameVali;
    QSortFilterProxyModel *proxy;

private slots:
    void on_addClient_clicked();

    void on_clientTable_activated(const QModelIndex &index);

    void on_editClient_clicked();

    void on_delClient_clicked();

    void on_searchBox_textChanged(const QString &arg1);

    void on_refresh_clicked();

    QString formatNumber(double);

    void on_sendBtn_clicked();

    void on_sort_currentIndexChanged(int index);

    void on_pdfClient_clicked();

    void on_ascClient_toggled(bool checked);

    void on_descClient_toggled(bool checked);

    void sendMail();

    void autoMail(Client c);

    void mailSent(QString);

    void browse();

    int checkQR();

    void on_pushButton_clicked();

private:
    Ui::clientmanagement *ui;
    QByteArray data;
    QStringList files;
    Arduino A;
};
#endif // CLIENTMANAGEMENT_H
