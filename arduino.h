#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>


class Arduino
{
public:
    Arduino(); //Construct
    int connect_arduino(); //Connection
    int close_arduino(); //Disconnect
    int write_to_arduino(QByteArray); //Send data
    int write_to_arduino2( QString );
    QByteArray read_from_arduino(); //Read data
    QSerialPort *getSerial(); //Serial getter
    QString getArduino_port_name() { return arduino_port_name; } //Port name getter

signals:
    void fireDetected();
    void fireCleared();
    void onFireDetected();

private slots:
    void sendCommand(const QString&);
    void onReadyRead();

private:
    QSerialPort serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_producy_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
