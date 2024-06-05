#include "client.h"

Client::Client()
{

}

Client::Client(QString fn, QString ln, int id, int ph, QString m)
{
    this->fname = fn;
    this->lname = ln;
    this->cin = id;
    this->phone = ph;
    this->mail = m;
}

Client::~Client()
{

}

bool Client::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO client (CIN, PRENOM_CLIENT, NOM_CLIENT, TLF_CLIENT, MAIL_CLIENT) VALUES (:id, :fn, :ln, :ph, :m);");
    query.bindValue(":id",cin);
    query.bindValue(":fn",fname);
    query.bindValue(":ln",lname);
    query.bindValue(":ph",phone);
    query.bindValue(":m",mail);

    return query.exec();
}

bool Client::del(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM client WHERE CIN = :id");
    query.bindValue(":id",id);
    return query.exec();
}

QSqlQueryModel *Client::show()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Last Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("First Name"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Phone Number"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("E-Mail"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("QR Code"));
    return model;
}

bool Client::update(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE client SET CIN = :id, PRENOM_CLIENT = :fn, NOM_CLIENT = :ln, TLF_CLIENT = :ph, MAIL_CLIENT = :m WHERE CIN = :id2;");
    query.bindValue(":id2",id);
    query.bindValue(":id",cin);
    query.bindValue(":fn",fname);
    query.bindValue(":ln",lname);
    query.bindValue(":ph",phone);
    query.bindValue(":m",mail);
    return query.exec();
}

int Client::check(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM client WHERE CIN = :id;");
    query.bindValue(":id",id);
    query.exec();
    int rows = 0;
    if(query.next())
        rows = query.value(0).toInt();
    return rows;
}

void Client::genQR(QString input)
{
    // Create QR code using libqrencode
    QRcode *qr = QRcode_encodeString(input.toLatin1().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);

    // Create an image to hold the QR code
    int size = qr->width;
    int pixelsize = 10;
    QImage img(size * pixelsize, size * pixelsize, QImage::Format_ARGB32);

    // Fill the image with white background
    img.fill(Qt::white);

    // Create a painter to draw the QR code on the image
    QPainter painter(&img);
    painter.setPen(Qt::NoPen);

    // Loop through the QR code matrix and draw black squares on the image
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qr->data[y * size + x] & 1) {
                painter.setBrush(Qt::black);
            } else {
                painter.setBrush(Qt::white);
            }
            painter.drawRect(x * pixelsize , y * pixelsize , pixelsize, pixelsize);
        }
    }

    // Save the QR code image to file
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save QR Code", input, "PNG (*.png)");
    img.save(filename, "PNG");

    // Clean up
    QRcode_free(qr);
}
