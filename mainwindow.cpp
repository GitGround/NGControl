#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<masterthread.h>
#include <QtSerialPort/QSerialPortInfo> //need it for QSerialPortInfo

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->serialPortComboBox->addItem("hello"); //simple example to item to comboxBox

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->serialPortComboBox->addItem(info.portName()); //adding all avaiable ports to comboBox

    ui->pushButton->setCheckable(true);   //only checkable button emit (bool checked)
    serial = new QSerialPort(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_toggled(bool checked)
{

   // serial->setBaudRate(QSerialPort::Baud57600);
    QString currentPortName = ui->serialPortComboBox->currentText();

    if (checked)
    {


        ui->statusLabel->setText("Connected");
            thread.transaction(currentPortName,
                               1000,
                               "test");
    }
    else
    {


            ui->statusLabel->setText("Not connected");

    }
}
