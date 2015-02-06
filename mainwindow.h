#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo> //need it for adding availabe serial ports
#include <QtSerialPort/QSerialPort>
#include <MavLinkProtocol.h>
#include <Driver/SerialPortLink.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void on_pushButton_Connect_toggled(bool checked);
    void on_pushButton_sendData_clicked();

//    void on_pushButton_Connect_clicked();

    void on_pushButton_Disconnect_clicked();

  //  void on_pushButton_clicked();

    void on_pushButton_Connect_clicked();

private:
    //understanding between stack and heap
    //'MAVLinkProtocol mavlink' vs 'MAVLinkProtocol *mavlink'
    //http://gribblelab.org/CBootcamp/7_Memory_Stack_vs_Heap.html

    Ui::MainWindow *ui;
    QSerialPort *serial; //need it to set serial port setting
    MAVLinkProtocol mavlink; //for protocol level
    QString currentPortName;
};

#endif // MAINWINDOW_H
