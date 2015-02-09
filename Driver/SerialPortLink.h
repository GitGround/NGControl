#ifndef SERIALPORTLINK_H
#define SERIALPORTLINK_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <QObject>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE


class SerialPortLink : public QObject
{
    Q_OBJECT

public:
    SerialPortLink(QObject *parent = 0);
    ~SerialPortLink();
    bool isConnected();
    void setCurrentPortName(QString currentPortName);
    void writeBytes(const char* data,qint64 size);

private slots:
    void handleReadyRead();

private:
    QSerialPort m_serialPort;
    QByteArray m_serialBuffer; // An internal buffer for receiving data from member functions and actually transmitting them via the serial port.
};

#endif // SERIALPORTLINK_H

//[#Lesson Learned]: Both h file and source files must be same in order to work "F4-> Swither Header/Source"
