#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <masterthread.h>
#include <QtSerialPort/QSerialPort> //need it for QSerialPort


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
    void on_pushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    MasterThread thread; //for MasterThread class
    QSerialPort *serial; //need it to set serial port setting
};

#endif // MAINWINDOW_H
