#include "graphs.h"
#include "mainwindow.h"
#include "ui_graphs.h"

graphs::graphs(MainWindow *master, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphs)
{
    ui->setupUi(this);
    mainwindow = master;

    connect(this->ui->pushButton_get_zero,SIGNAL(clicked(bool)),this,SLOT(get_zero()));
    connect(this->ui->pushButton_get_cal,SIGNAL(clicked(bool)),this,SLOT(get_cal()));
    connect(this->ui->pushButton_calibrate,SIGNAL(clicked(bool)),this,SLOT(calibrate()));

    for(u8 i = 0; i < 9 ;i++){
        slope[i] = 1;
    }

}
void graphs::get_zero(void){
    ui->doubleSpinBox_gyro_x_zero->setValue(mainwindow->GYRO_x);
    ui->doubleSpinBox_gyro_y_zero->setValue(mainwindow->GYRO_y);
    ui->doubleSpinBox_gyro_z_zero->setValue(mainwindow->GYRO_z);
    ui->doubleSpinBox_acc_x_zero->setValue(mainwindow->filtered_ACC_x);
    ui->doubleSpinBox_acc_y_zero->setValue(mainwindow->filtered_ACC_y);
    ui->doubleSpinBox_acc_z_zero->setValue(mainwindow->filtered_ACC_z);
    ui->doubleSpinBox_mag_x_zero->setValue(mainwindow->MAG_x);
    ui->doubleSpinBox_mag_y_zero->setValue(mainwindow->MAG_y);
    ui->doubleSpinBox_mag_z_zero->setValue(mainwindow->MAG_z);

    //qDebug() << "ACC x" << mainwindow->ACC_x;
}
void graphs::get_cal(void){
    ui->doubleSpinBox_gyro_x_cal->setValue(mainwindow->GYRO_x);
    ui->doubleSpinBox_gyro_y_cal->setValue(mainwindow->GYRO_y);
    ui->doubleSpinBox_gyro_z_cal->setValue(mainwindow->GYRO_z);
    ui->doubleSpinBox_acc_x_cal->setValue(mainwindow->filtered_ACC_x);
    ui->doubleSpinBox_acc_y_cal->setValue(mainwindow->filtered_ACC_y);
    ui->doubleSpinBox_acc_z_cal->setValue(mainwindow->filtered_ACC_z);
    ui->doubleSpinBox_mag_x_cal->setValue(mainwindow->MAG_x);
    ui->doubleSpinBox_mag_y_cal->setValue(mainwindow->MAG_y);
    ui->doubleSpinBox_mag_z_cal->setValue(mainwindow->MAG_z);
}
void graphs::calibrate(void){
    slope[0] = ui->doubleSpinBox_gyro_x_cal_val->value() / (ui->doubleSpinBox_gyro_x_cal->value() - ui->doubleSpinBox_gyro_x_zero->value());
    slope[1] = ui->doubleSpinBox_gyro_y_cal_val->value() / (ui->doubleSpinBox_gyro_y_cal->value() - ui->doubleSpinBox_gyro_y_zero->value());
    slope[2] = ui->doubleSpinBox_gyro_z_cal_val->value() / (ui->doubleSpinBox_gyro_z_cal->value() - ui->doubleSpinBox_gyro_z_zero->value());
    slope[3] = ui->doubleSpinBox_acc_x_cal_val->value() / (ui->doubleSpinBox_acc_x_cal->value() - ui->doubleSpinBox_acc_x_zero->value());
    slope[4] = ui->doubleSpinBox_acc_y_cal_val->value() / (ui->doubleSpinBox_acc_y_cal->value() - ui->doubleSpinBox_acc_y_zero->value());
    slope[5] = ui->doubleSpinBox_acc_z_cal_val->value() / (ui->doubleSpinBox_acc_z_cal->value() - ui->doubleSpinBox_acc_z_zero->value());
    slope[6] = ui->doubleSpinBox_mag_x_cal_val->value() / (ui->doubleSpinBox_mag_x_cal->value() - ui->doubleSpinBox_mag_x_zero->value());
    slope[7] = ui->doubleSpinBox_mag_y_cal_val->value() / (ui->doubleSpinBox_mag_y_cal->value() - ui->doubleSpinBox_mag_y_zero->value());
    slope[8] = ui->doubleSpinBox_mag_z_cal_val->value() / (ui->doubleSpinBox_mag_z_cal->value() - ui->doubleSpinBox_mag_z_zero->value());

    for(u8 i = 0; i < 9; i++){
        qDebug() << QString("slope %1").arg(i) << slope[i];
    }
}

graphs::~graphs()
{
    delete ui;
}
