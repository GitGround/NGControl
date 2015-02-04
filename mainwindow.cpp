#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //ui->serialPortComboBox->addItem("hello"); //simple example to item to comboxBox

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    ui->serialPortComboBox->addItem(info.portName());//adding all avaiable ports to comboBox

    ui->pushButton_sendData->setEnabled(false);
    //Example: only checkable button emit (bool checked) // ui->pushButton->setCheckable(true);

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_sendData_clicked() {
    //send heart beat to check the connection [To Do: still strange to me]
     mavlink.sendHeartbeat();

    if (mavlink.isConnected()){
        ui->label_linkStatus->setText("Connected");
    }
    else
    {
      ui->label_linkStatus->setText("Invlid Connection");
    }

}

void MainWindow::on_pushButton_Disconnect_clicked()
{       //these are to simply lock user from sending data while connection is not estiblished yet
        ui->pushButton_Connect->setEnabled(true);
        ui->pushButton_Disconnect->setEnabled(false);
        ui->serialPortComboBox->setEnabled(true);
        ui->pushButton_sendData->setEnabled(false);
}

void MainWindow::on_pushButton_Connect_clicked()
{
        currentPortName = ui->serialPortComboBox->currentText();
        mavlink.setCurrentPortName(currentPortName);
        //these are to simply lock user from sending data while connection is not estiblished yet.
        ui->pushButton_Connect->setEnabled(false);
        ui->pushButton_Disconnect->setEnabled(true);
        ui->serialPortComboBox->setEnabled(false);
        ui->pushButton_sendData->setEnabled(true);
}
