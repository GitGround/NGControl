#include "SerialPortLink.h"

QT_USE_NAMESPACE

SerialPortLink::SerialPortLink( QObject *parent)
    : QObject(parent)
{

     m_serialPort.setBaudRate(QSerialPort::Baud57600); //default baud rate for mavlink

     /*
     [#Explanation]:'readyRead' is signal auto-genetated by QSerialPort whenever it receives data
     when data is received (which is same as signal is activated), handlerReadyRead is called.
      */

     QObject::connect(&m_serialPort, &QSerialPort::readyRead,
                 this, &SerialPortLink::handleReadyRead);

}

void SerialPortLink::handleReadyRead()
{
    qDebug()<<"received";
}

SerialPortLink::~SerialPortLink()
{
}

void SerialPortLink::setCurrentPortName(QString currentPortName) {
    m_serialPort.setPortName(currentPortName);
}

bool SerialPortLink::isConnected() {
 return (m_serialPort.open(QIODevice::ReadWrite) == true) ? true : false; //check whether is connected or not
}

void SerialPortLink::writeBytes(const char* data,qint64 size) {
m_serialPort.open(QIODevice::ReadWrite); //[#strange]: need this statement to open everytime.

/*
[#Explanation]:write data to serial port
[#Ref]: from QGroundControl
 */

    QByteArray byteArray(data, size);
    //append data into serialBuffer
    m_serialBuffer.append(byteArray);

    int numWritten = m_serialPort.write(m_serialBuffer);

    //once all data is written, flush the buffer
    m_serialBuffer = m_serialBuffer.remove(0, numWritten);
}



