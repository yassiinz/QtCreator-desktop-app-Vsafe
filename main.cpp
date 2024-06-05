#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "QPushButton"
#include <QSplashScreen>
#include <QTimer>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("VSafe");

    /*//Set the stylesheet
    QFile styleSheetFile("ressources/stylesheet/Darkeum.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString stylesheet = styleSheetFile.readAll();
    a.setStyleSheet(stylesheet);*/

    Connection c;
    //Connet to database
    c.createconnect();

    //Create the window and splash screen
    login l;



    l.setWindowTitle("Connection");
    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap("images/logo.png"));
    splash->show();
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&l,SLOT(show()));

    return a.exec();
}
