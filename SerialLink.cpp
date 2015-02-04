#include "SerialLink.h"
#include <QDebug>
#include <QTime>

QT_USE_NAMESPACE

SerialLink::SerialLink(QObject *parent) :
        QThread(parent), waitTimeout(0), quit(false) {
}

//! [0]
SerialLink::~SerialLink() {
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}
//! [0]

//! [1] //! [2]

void SerialLink::sendData(const QString &portName, const char* data,
        qint64 size) {
    //! [1]
    QMutexLocker locker(&mutex);

    this->portName = portName;
    this->waitTimeout = 1000; //set time out as 1000 msec
    this->request = request;

    QByteArray byteArray(data, size);
    //append data into serialBuffer
    serialBuffer.append(byteArray);
    //! [3]
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}
//! [2] //! [3]

//! [4]
void SerialLink::run() {
    bool currentPortNameChanged = false;

    mutex.lock();
    //! [4] //! [5]
    QString currentPortName;
    if (currentPortName != portName) {
        currentPortName = portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = waitTimeout;
    QString currentRequest = request;
    mutex.unlock();
    //! [5] //! [6]
    QSerialPort serial;


    while (!quit) {
        //![6] //! [7]
        if (currentPortNameChanged) {
            serial.close();
            serial.setPortName(currentPortName);


            serial.setBaudRate(QSerialPort::Baud57600); //set BaudRate to 57600 // hardcoded for mavlink

            if (!serial.open(QIODevice::ReadWrite)) {
                emit error(
                        tr("Can't open %1, error code %2").arg(portName).arg(
                                serial.error()));
                return;
            }
        }

        //[#Strange] serial need to be closed in order to check Read or Write even tho data can be send
        serial.close();
        //inform the link status
        linkStatus = (serial.open(QIODevice::ReadWrite) == true) ? true : false;

        //! [7] //! [8]
        //write buffer to serial port then return the number of byte actually written
        int numWritten = serial.write(serialBuffer);
        //once all data is written, flush the buffer
        serialBuffer = serialBuffer.remove(0, numWritten);

        if (serial.waitForBytesWritten(waitTimeout)) {
            //! [8] //! [10]
            // read response
            if (serial.waitForReadyRead(currentWaitTimeout)) {
                QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(10))
                    responseData += serial.readAll();

                QString response(responseData);
                //! [12]
                emit
                this->response(response);
                //! [10] //! [11] //! [12]
            } else {
                emit timeout(
                        tr("Wait read response timeout %1").arg(
                                QTime::currentTime().toString()));
            }
            //! [9] //! [11]
        } else {
            emit timeout(
                    tr("Wait write request timeout %1").arg(
                            QTime::currentTime().toString()));
        }
        //! [9]  //! [13]
        mutex.lock();
        cond.wait(&mutex);
        if (currentPortName != portName) {
            currentPortName = portName;
            currentPortNameChanged = true;
        } else {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = waitTimeout;
        currentRequest = request;
        mutex.unlock();
    }
    //! [13]
}

bool SerialLink::isConnected() {
    return linkStatus;
}

//void isConnected
