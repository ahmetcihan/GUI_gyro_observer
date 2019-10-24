#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_graphs.h"

u32 MainWindow::crc_chk(u8* data, u8 length){
    int j;
    u32 reg_crc=0xFFFF;

    while( length-- ) {
        reg_crc^= *data++;
        for (j=0; j<8; j++ ) {
            if( reg_crc & 0x01 ) {
                reg_crc = (reg_crc >> 1)^0xA001;
            }
            else {
                reg_crc = (reg_crc>>1);
            }
        }
    }
    return reg_crc;
}
void MainWindow::serial_response_handler(void){
    QByteArray data_array;
    data_array.resize(32);
    u32 fcrc;
    u8 crc_low,crc_high;
    static u32 missed = 0;

    read_timer->stop();
    data_array = serial->readAll();

    fcrc = crc_chk((u8*)data_array.data(),24);
    crc_high = (fcrc)%256;
    crc_low = (fcrc)/256;
    if((crc_high == (u8)data_array[24])&&(crc_low == (u8)data_array[25])){
        if((data_array[0] == 'G') && (data_array[1] == 'Y') && (data_array[2] == 'R')){
            GYRO_x = (u8)data_array[3] + 256*(u8)data_array[4];
            GYRO_y = (u8)data_array[5] + 256*(u8)data_array[6];
            GYRO_z = (u8)data_array[7] + 256*(u8)data_array[8];
            ACC_x = (u8)data_array[10] + 256*(u8)data_array[11];
            ACC_y = (u8)data_array[12] + 256*(u8)data_array[13];
            ACC_z = (u8)data_array[14] + 256*(u8)data_array[15];
            MAG_x = (u8)data_array[17] + 256*(u8)data_array[18];
            MAG_y = (u8)data_array[19] + 256*(u8)data_array[20];
            MAG_z = (u8)data_array[21] + 256*(u8)data_array[22];
//            status = (u8)data_array[9];
//            qDebug() << "GYRO status :" << QString::number((u8)data_array[9],2) << "ACC status :" << QString::number((u8)data_array[16],2)<< "MAG status :" << QString::number((u8)data_array[23],2);
//            if((u8) data_array[23] == 0 ){
//                qDebug() << "MAG status : 0";
//            }
//            if(MAG_z == 0){
//                qDebug() << "MAG Z : 0";
//            }

            if(MAG_x > 0x8000){
                MAG_x = MAG_x - 0x10000;
            }
            if(MAG_y > 0x8000){
                MAG_y = MAG_y - 0x10000;
            }
            if(MAG_z > 0x8000){
                MAG_z = MAG_z - 0x10000;
            }
            if(ACC_x > 0x8000){
                ACC_x = ACC_x - 0x10000;
            }
            if(ACC_y > 0x8000){
                ACC_y = ACC_y - 0x10000;
            }
            if(ACC_z > 0x8000){
                ACC_z = ACC_z - 0x10000;
            }
            if(GYRO_x > 0x8000){
                GYRO_x = GYRO_x - 0x10000;
            }
            if(GYRO_y > 0x8000){
                GYRO_y = GYRO_y - 0x10000;
            }
            if(GYRO_z > 0x8000){
                GYRO_z = GYRO_z - 0x10000;
            }

            ui->label_gyro_x->setText("GYRO X : " + QString::number(GYRO_x));
            ui->label_gyro_y->setText("GYRO Y : " + QString::number(GYRO_y));
            ui->label_gyro_z->setText("GYRO Z : " + QString::number(GYRO_z));
            ui->label_acc_x->setText("ACC X : " + QString::number(ACC_x));
            ui->label_acc_y->setText("ACC Y : " + QString::number(ACC_y));
            ui->label_acc_z->setText("ACC Z : " + QString::number(ACC_z));
            ui->label_mag_x->setText("MAG X : " + QString::number(MAG_x));
            ui->label_mag_y->setText("MAG Y : " + QString::number(MAG_y));
            ui->label_mag_z->setText("MAG Z : " + QString::number(MAG_z));

            graph_page->calibrated[0] = (double) (GYRO_x - graph_page->ui->doubleSpinBox_gyro_x_zero->value()) * graph_page->slope[0];
            graph_page->calibrated[1] = (double) (GYRO_y - graph_page->ui->doubleSpinBox_gyro_y_zero->value()) * graph_page->slope[1];
            graph_page->calibrated[2] = (double) (GYRO_z - graph_page->ui->doubleSpinBox_gyro_z_zero->value()) * graph_page->slope[2];
            graph_page->calibrated[3] = (double) (ACC_x - graph_page->ui->doubleSpinBox_acc_x_zero->value()) * graph_page->slope[3];
            graph_page->calibrated[4] = (double) (ACC_y - graph_page->ui->doubleSpinBox_acc_y_zero->value()) * graph_page->slope[4];
            graph_page->calibrated[5] = (double) (ACC_z - graph_page->ui->doubleSpinBox_acc_z_zero->value()) * graph_page->slope[5];
            graph_page->calibrated[6] = (double) (MAG_x - graph_page->ui->doubleSpinBox_mag_x_zero->value()) * graph_page->slope[6];
            graph_page->calibrated[7] = (double) (MAG_y - graph_page->ui->doubleSpinBox_mag_y_zero->value()) * graph_page->slope[7];
            graph_page->calibrated[8] = (double) (MAG_z - graph_page->ui->doubleSpinBox_mag_z_zero->value()) * graph_page->slope[8];

            graph_page->ui->label_calibrated_gyro_x->setText(QString::number(graph_page->calibrated[0]));
            graph_page->ui->label_calibrated_gyro_y->setText(QString::number(graph_page->calibrated[1]));
            graph_page->ui->label_calibrated_gyro_z->setText(QString::number(graph_page->calibrated[2]));
            graph_page->ui->label_calibrated_acc_x->setText(QString::number(graph_page->calibrated[3]));
            graph_page->ui->label_calibrated_acc_y->setText(QString::number(graph_page->calibrated[4]));
            graph_page->ui->label_calibrated_acc_z->setText(QString::number(graph_page->calibrated[5]));
            graph_page->ui->label_calibrated_mag_x->setText(QString::number(graph_page->calibrated[6]));
            graph_page->ui->label_calibrated_mag_y->setText(QString::number(graph_page->calibrated[7]));
            graph_page->ui->label_calibrated_mag_z->setText(QString::number(graph_page->calibrated[8]));

            filtered_ACC_x = filter_x(ACC_x, X_ax_0, X_ax_1, X_by_0, X_by_1, X_by_2,X_xv,X_yv);
            filtered_ACC_y = filter_y(ACC_y, Y_ax_0, Y_ax_1, Y_by_0, Y_by_1, Y_by_2,Y_xv,Y_yv);
            filtered_ACC_z = filter_z(ACC_z, Z_ax_0, Z_ax_1, Z_by_0, Z_by_1, Z_by_2,Z_xv,Z_yv);
            plot_graph();
        }
    }
    else{
        missed++;
        qDebug() << "CRC missed!!" << missed;
    }


}
void MainWindow::EOL(char *base_array, u8 i){
    base_array[i] 	= 0x0D;
    base_array[i+1] = 0x0A;
}
void MainWindow::serial_request_sender(void){
    QByteArray data;
    data.resize(6);

    data[0] = 'C';
    data[1] = 'O';
    data[2] = 'N';
    data[3] = 'V';

    EOL(data.data(),4);

    serial->write(data);
    read_timer->start();
}
void MainWindow::serial_port_setup(void){
    serial->setPortName("ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

    qDebug() << QString("Serial port status is %1").arg(serial->isOpen());

}

