#include "historique.h"



historique::historique()
{

}
void historique::save(QString date , QString heure)
{    QFile file ("C:/history/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<date+"\t"+ heure+"\n"<< "\n""\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/history/historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}

