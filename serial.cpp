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
    unsigned char status;
    static QElapsedTimer elaps;
    static u8 first_in = 1;
    static u32 counter = 0;
    static bool in_action = false;

//    qDebug() << "elasp :" << elaps.elapsed();
//    elaps.restart();

    read_timer->stop();
    data_array = serial->readAll();

    fcrc = crc_chk((u8*)data_array.data(),24);
    crc_high = (fcrc)%256;
    crc_low = (fcrc)/256;
    if((crc_high == (u8)data_array[24])&&(crc_low == (u8)data_array[25])){
        if((data_array[0] == 'G') && (data_array[1] == 'Y') && (data_array[2] == 'R')){

            counter++;
            if(first_in == 1){ //for filter stability at the opening
                if(counter > 100){
                    if(fabs(X.average - X.lpf.GYRO) < 10){
                        first_in = 0;
                    }
                }
            }

            X.GYRO = (u8)data_array[3] + 256*(u8)data_array[4];
            Y.GYRO = (u8)data_array[5] + 256*(u8)data_array[6];
            Z.GYRO = (u8)data_array[7] + 256*(u8)data_array[8];
            //Z.GYRO = data_array[8];
            X.ACC = (u8)data_array[10] + 256*(u8)data_array[11];
            Y.ACC = (u8)data_array[12] + 256*(u8)data_array[13];
            Z.ACC = (u8)data_array[14] + 256*(u8)data_array[15];
            X.MAG = (u8)data_array[17] + 256*(u8)data_array[18];
            Y.MAG = (u8)data_array[19] + 256*(u8)data_array[20];
            Z.MAG = (u8)data_array[21] + 256*(u8)data_array[22];
            status = (u8)data_array[9];
//            qDebug() << "GYRO status :" << QString::number((u8)data_array[9],2) << "ACC status :" << QString::number((u8)data_array[16],2)<< "MAG status :" << QString::number((u8)data_array[23],2);
//            qDebug() << "GYRO status :" << QString::number((u8)data_array[9],2);
//            if(((u8)data_array[9] & 0xF) == 0xF){
//                qDebug() << "elasp :" << elaps.elapsed();
//                elaps.restart();
//            }
//            if((u8) data_array[23] == 0 ){
//                qDebug() << "MAG status : 0";
//            }
//            if(Z.MAG == 0){
//                qDebug() << "MAG Z : 0";
//            }

            if(X.MAG > 0x7FFF){
                X.MAG = X.MAG - 0xFFFF + 1;
            }
            if(Y.MAG > 0x7FFF){
                Y.MAG = Y.MAG - 0xFFFF + 1;
            }
            if(Z.MAG > 0x7FFF){
                Z.MAG = Z.MAG - 0xFFFF + 1;
            }
            if(X.ACC > 0x7FFF){
                X.ACC = X.ACC - 0xFFFF + 1;
            }
            if(Y.ACC > 0x7FFF){
                Y.ACC = Y.ACC - 0xFFFF + 1;
            }
            if(Z.ACC > 0x7FFF){
                Z.ACC = Z.ACC - 0xFFFF + 1;
            }
            if(X.GYRO > 0x7FFF){
                X.GYRO = X.GYRO - 0xFFFF + 1;
            }
            if(Y.GYRO > 0x7FFF){
                Y.GYRO = Y.GYRO - 0xFFFF + 1;
            }
            if(Z.GYRO > 0x7FFF){
                Z.GYRO = Z.GYRO - 0xFFFF + 1;
            }

            X.lpf.GYRO = lpf_x(X.GYRO, X.lpf.a, X.lpf.b, X.lpf.x, X.lpf.y);
            Y.lpf.GYRO = lpf_y(Y.GYRO, Y.lpf.a, Y.lpf.b, Y.lpf.x, Y.lpf.y);
            Z.lpf.GYRO = lpf_z(Z.GYRO, Z.lpf.a, Z.lpf.b, Z.lpf.x, Z.lpf.y);
            X.hpf.GYRO = hpf_x(X.GYRO, X.hpf.a, X.hpf.b, X.hpf.x, X.hpf.y);
            Y.hpf.GYRO = hpf_y(Y.GYRO, Y.hpf.a, Y.hpf.b, Y.hpf.x, Y.hpf.y);
            Z.hpf.GYRO = hpf_z(Z.GYRO, Z.hpf.a, Z.hpf.b, Z.hpf.x, Z.hpf.y);
            X.lpf_of_hpf.GYRO = lpf_of_hpf_x(X.hpf.GYRO, X.lpf.a, X.lpf.b, X.lpf_of_hpf.x, X.lpf_of_hpf.y);
            Y.lpf_of_hpf.GYRO = lpf_of_hpf_y(Y.hpf.GYRO, Y.lpf.a, Y.lpf.b, Y.lpf_of_hpf.x, Y.lpf_of_hpf.y);
            Z.lpf_of_hpf.GYRO = lpf_of_hpf_z(Z.hpf.GYRO, Z.lpf.a, Z.lpf.b, Z.lpf_of_hpf.x, Z.lpf_of_hpf.y);

            if(fabs(X.hpf.GYRO) < 100){  //this detects the base plane of gyro signal
                X.average = classic_MA(X.lpf.GYRO,200,running_average_array);
                ui->label_activation->setText("PASSIVE");
                ui->label_activation->setStyleSheet("background-color:blue");
                in_action = false;
            }
            else{                       // do nothing
                ui->label_activation->setText("ACTIVE");
                ui->label_activation->setStyleSheet("background-color:red");
                in_action = true;
            }

            if(first_in == 0){
                X.dps_angle = X.dps_angle + (X.lpf.GYRO - X.average);
                if(in_action == true){
                    X.integral = definite_integral((X.lpf.GYRO - X.average),100,definite_integral_array);
                }
            }
            else{
                X.dps_angle = 0;
                X.integral = 0;
            }


            graph_page->calibrated[0] = (double) (X.dps_angle - graph_page->ui->doubleSpinBox_gyro_x_zero->value()) * graph_page->slope[0];
            graph_page->calibrated[1] = (double) (Y.dps_angle - graph_page->ui->doubleSpinBox_gyro_y_zero->value()) * graph_page->slope[1];
            graph_page->calibrated[2] = (double) (Z.dps_angle - graph_page->ui->doubleSpinBox_gyro_z_zero->value()) * graph_page->slope[2];
//            graph_page->calibrated[3] = (double) (X.ACC - graph_page->ui->doubleSpinBox_acc_x_zero->value()) * graph_page->slope[3];
//            graph_page->calibrated[4] = (double) (Y.ACC - graph_page->ui->doubleSpinBox_acc_y_zero->value()) * graph_page->slope[4];
//            graph_page->calibrated[5] = (double) (Z.ACC - graph_page->ui->doubleSpinBox_acc_z_zero->value()) * graph_page->slope[5];
//            graph_page->calibrated[6] = (double) (X.MAG - graph_page->ui->doubleSpinBox_mag_x_zero->value()) * graph_page->slope[6];
//            graph_page->calibrated[7] = (double) (Y.MAG - graph_page->ui->doubleSpinBox_mag_y_zero->value()) * graph_page->slope[7];
//            graph_page->calibrated[8] = (double) (Z.MAG - graph_page->ui->doubleSpinBox_mag_z_zero->value()) * graph_page->slope[8];

            graph_page->ui->label_calibrated_gyro_x->setText(QString::number(graph_page->calibrated[0]));
            graph_page->ui->label_calibrated_gyro_y->setText(QString::number(graph_page->calibrated[1]));
            graph_page->ui->label_calibrated_gyro_z->setText(QString::number(graph_page->calibrated[2]));
//            graph_page->ui->label_calibrated_acc_x->setText(QString::number(graph_page->calibrated[3]));
//            graph_page->ui->label_calibrated_acc_y->setText(QString::number(graph_page->calibrated[4]));
//            graph_page->ui->label_calibrated_acc_z->setText(QString::number(graph_page->calibrated[5]));
//            graph_page->ui->label_calibrated_mag_x->setText(QString::number(graph_page->calibrated[6]));
//            graph_page->ui->label_calibrated_mag_y->setText(QString::number(graph_page->calibrated[7]));
//            graph_page->ui->label_calibrated_mag_z->setText(QString::number(graph_page->calibrated[8]));

            ui->label_gyro_x->setText("GYRO X : " + QString::number(X.GYRO));
            ui->label_gyro_y->setText("GYRO Y : " + QString::number(Y.GYRO));
            ui->label_gyro_z->setText("GYRO Z : " + QString::number(Z.GYRO));
            ui->label_acc_x->setText("ACC X : " + QString::number(X.ACC));
            ui->label_acc_y->setText("ACC Y : " + QString::number(Y.ACC));
            ui->label_acc_z->setText("ACC Z : " + QString::number(Z.ACC));
            ui->label_mag_x->setText("MAG X : " + QString::number(X.MAG));
            ui->label_mag_y->setText("MAG Y : " + QString::number(Y.MAG));
            ui->label_mag_z->setText("MAG Z : " + QString::number(Z.MAG));
            ui->label_lpf_gyro_x->setText("LPF GYRO X : " + QString::number(X.lpf.GYRO));
            ui->label_lpf_gyro_y->setText("LPF GYRO Y : " + QString::number(Y.lpf.GYRO));
            ui->label_lpf_gyro_z->setText("LPF GYRO Z : " + QString::number(Z.lpf.GYRO));
            ui->label_hpf_gyro_x->setText("HPF GYRO X : " + QString::number(X.hpf.GYRO));
            ui->label_hpf_gyro_y->setText("HPF GYRO Y : " + QString::number(Y.hpf.GYRO));
            ui->label_hpf_gyro_z->setText("HPF GYRO Z : " + QString::number(Z.hpf.GYRO));
            ui->label_gyro_angle_x->setText("INT(0-inf) X " + QString::number(X.dps_angle));
            ui->label_gyro_angle_y->setText("INTEGRAL Y " + QString::number(Y.dps_angle));
            ui->label_gyro_angle_z->setText("INTEGRAL Z " + QString::number(Z.dps_angle));
            ui->label_cal_gyro_x->setText("CAL X : " + QString::number(graph_page->calibrated[0]));
            ui->label_cal_gyro_y->setText("CAL Y : " + QString::number(graph_page->calibrated[1]));
            ui->label_cal_gyro_z->setText("CAL Z : " + QString::number(graph_page->calibrated[2]));
            ui->label_gyro_integral_x->setText("INT(x1-x2) X " + QString::number(X.integral));

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

