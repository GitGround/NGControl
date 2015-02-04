#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtSerialPort/QSerialPort>

//Ref: http://doc.qt.io/qt-5/qtserialport-blockingmaster-example.html

//! [0]
class SerialLink : public QThread
{
    Q_OBJECT

public:
    SerialLink(QObject *parent = 0);
    ~SerialLink();
    void sendData(const QString &portName, const char* data, qint64 size);
    void writeBytes(const char* data, qint64 size);
    void run();
    bool isConnected();

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);
   // void isConnected (int value);

private:
    QString portName;
    QString request;
    int waitTimeout;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
    QByteArray serialBuffer; // An internal buffer for receiving data from member functions and actually transmitting them via the serial port.
    bool linkStatus;
    //  QSerialPort serial;

};
//! [0]

#endif // MASTERTHREAD_H
