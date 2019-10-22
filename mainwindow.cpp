#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial_port_setup();

    _100_msec_timer = new QTimer(this);
    _100_msec_timer->setInterval(50);
    _100_msec_timer->start();
    connect(_100_msec_timer, SIGNAL(timeout()),this,SLOT(serial_request_sender()));

    read_timer = new QTimer(this);
    read_timer->setInterval(30);
    read_timer->start();
    connect(read_timer, SIGNAL(timeout()),this,SLOT(serial_response_handler()));

    //connect(serial,SIGNAL(readyRead()),this,SLOT(serial_response_handler()));

    initilize_plot();

//    connect(ui->pushButton_send_pan_left, SIGNAL(clicked()),this,SLOT(send_pan_left()));
//    ui->pushButton_send_pan_left->setStyleSheet("min-width: 80px; min-height: 80px;"
//                                                "border-image: url(:sarı_left.jpg);"
//                                                "border-width: 0px ;");
    connect(this->ui->pushButton_get_zero,SIGNAL(clicked(bool)),this,SLOT(get_zero()));
    connect(this->ui->pushButton_get_cal,SIGNAL(clicked(bool)),this,SLOT(get_cal()));
}
void MainWindow::get_zero(void){
    ui->doubleSpinBox_gyro_x_zero->setValue(GYRO_x);
    ui->doubleSpinBox_gyro_y_zero->setValue(GYRO_y);
    ui->doubleSpinBox_gyro_z_zero->setValue(GYRO_z);
    ui->doubleSpinBox_acc_x_zero->setValue(ACC_x);
    ui->doubleSpinBox_acc_y_zero->setValue(ACC_y);
    ui->doubleSpinBox_acc_z_zero->setValue(ACC_z);
    ui->doubleSpinBox_mag_x_zero->setValue(MAG_x);
    ui->doubleSpinBox_mag_y_zero->setValue(MAG_y);
    ui->doubleSpinBox_mag_z_zero->setValue(MAG_z);
}
void MainWindow::get_cal(void){
    ui->doubleSpinBox_gyro_x_cal->setValue(GYRO_x);
    ui->doubleSpinBox_gyro_y_cal->setValue(GYRO_y);
    ui->doubleSpinBox_gyro_z_cal->setValue(GYRO_z);
    ui->doubleSpinBox_acc_x_cal->setValue(ACC_x);
    ui->doubleSpinBox_acc_y_cal->setValue(ACC_y);
    ui->doubleSpinBox_acc_z_cal->setValue(ACC_z);
    ui->doubleSpinBox_mag_x_cal->setValue(MAG_x);
    ui->doubleSpinBox_mag_y_cal->setValue(MAG_y);
    ui->doubleSpinBox_mag_z_cal->setValue(MAG_z);
}

MainWindow::~MainWindow()
{
    delete ui;
}
