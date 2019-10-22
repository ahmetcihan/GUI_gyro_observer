#include "graphs.h"
#include "mainwindow.h"
#include "ui_graphs.h"

graphs::graphs(MainWindow *master, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphs)
{
    ui->setupUi(this);
    mainwin = master;

    connect(this->ui->pushButton_get_zero,SIGNAL(clicked(bool)),this,SLOT(get_zero()));
    connect(this->ui->pushButton_get_cal,SIGNAL(clicked(bool)),this,SLOT(get_cal()));

}
void graphs::get_zero(void){
    ui->doubleSpinBox_gyro_x_zero->setValue(mainwin->GYRO_x);
    ui->doubleSpinBox_gyro_y_zero->setValue(mainwin->GYRO_y);
    ui->doubleSpinBox_gyro_z_zero->setValue(mainwin->GYRO_z);
    ui->doubleSpinBox_acc_x_zero->setValue(mainwin->ACC_x);
    ui->doubleSpinBox_acc_y_zero->setValue(mainwin->ACC_y);
    ui->doubleSpinBox_acc_z_zero->setValue(mainwin->ACC_z);
    ui->doubleSpinBox_mag_x_zero->setValue(mainwin->MAG_x);
    ui->doubleSpinBox_mag_y_zero->setValue(mainwin->MAG_y);
    ui->doubleSpinBox_mag_z_zero->setValue(mainwin->MAG_z);
}
void graphs::get_cal(void){
    ui->doubleSpinBox_gyro_x_cal->setValue(mainwin->GYRO_x);
    ui->doubleSpinBox_gyro_y_cal->setValue(mainwin->GYRO_y);
    ui->doubleSpinBox_gyro_z_cal->setValue(mainwin->GYRO_z);
    ui->doubleSpinBox_acc_x_cal->setValue(mainwin->ACC_x);
    ui->doubleSpinBox_acc_y_cal->setValue(mainwin->ACC_y);
    ui->doubleSpinBox_acc_z_cal->setValue(mainwin->ACC_z);
    ui->doubleSpinBox_mag_x_cal->setValue(mainwin->MAG_x);
    ui->doubleSpinBox_mag_y_cal->setValue(mainwin->MAG_y);
    ui->doubleSpinBox_mag_z_cal->setValue(mainwin->MAG_z);
}

graphs::~graphs()
{
    delete ui;
}
