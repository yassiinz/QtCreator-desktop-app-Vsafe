#include "arduino.h"

Arduino::Arduino()
{

}

int Arduino::connect_arduino()
{
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id)
            {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }
    qDebug() << "Arduino port name : " << arduino_port_name;
    if(arduino_is_available)
    {
        qDebug() << serial.error();
        serial.setPortName(arduino_port_name);
        qDebug() << serial.error();
        if(serial.open(QSerialPort::ReadWrite))
        {
            qDebug() << serial.error();
            serial.setBaudRate(QSerialPort::Baud9600); //Bitrate : 9600 bits/s
            serial.setDataBits(QSerialPort::Data8); //Data length : 8 bits
            serial.setParity(QSerialPort::NoParity); //Parity bit disabled
            serial.setStopBits(QSerialPort::OneStop); // 1 Stop bit
            serial.setFlowControl(QSerialPort::NoFlowControl);
            return 0; //Connection successful
        }
        qDebug() << serial.error();
    }
    return 1; //Connection failed
}

int Arduino::close_arduino()
{
    if(serial.isOpen())
    {
        serial.close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial.isReadable())
    {
        data = serial.readAll(); //Get data
    }
    return data;
}

int Arduino::write_to_arduino(QByteArray d)
{
    if(serial.isWritable())
    {
        serial.write(d); //Send data
        return 1;
    }
    else
    {
        qDebug() << "Couldn't send data!" << serial.error();
        return 0;
    }
}

int Arduino::write_to_arduino2 (QString d)
{
    int i;
    QString x;
    if(serial.isWritable())
    {
        for (i=0;i<d.length();i++)
        {
            x=d[i];
            serial.write(x.toUtf8());
        }  // envoyer des donnés vers Arduino
        return 1;
    }
    else
    {
    qDebug() << "Couldn't write to serial!";
    return 0;
    }
}

/*void Arduino::sendCommand(const QString &command)
{
    if (serial.isOpen()) {
        serial.write(command.toUtf8());
        serial.waitForBytesWritten(1000);
    }
}

*/
