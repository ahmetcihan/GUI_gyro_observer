#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial_port_setup();

    this->setGeometry(2000,0,this->width(),this->height());

    graph_page = new graphs(this);
    graph_page->show();
    graph_page->setGeometry(this->width() + 2010,0,graph_page->width(),graph_page->height());

    _100_msec_timer = new QTimer(this);
    _100_msec_timer->setInterval(50);
    _100_msec_timer->start();
    connect(_100_msec_timer, SIGNAL(timeout()),this,SLOT(serial_request_sender()));

    read_timer = new QTimer(this);
    read_timer->setInterval(30);
    read_timer->start();
    connect(read_timer, SIGNAL(timeout()),this,SLOT(serial_response_handler()));

    initilize_plot();

    for(u8 i = 0; i < 64; i++){
        X.running_average_array[i] = 0;
        Y.running_average_array[i] = 0;
        Z.running_average_array[i] = 0;
        if(i < 2){
            X.lpf.x[i] = 0;
            Y.lpf.x[i] = 0;
            Z.lpf.x[i] = 0;
            X.lpf.y[i] = 0;
            Y.lpf.y[i] = 0;
            Z.lpf.y[i] = 0;
        }
    }

    connect(this->ui->pushButton_offset_gyro_x,SIGNAL(clicked()),this,SLOT(take_offset_gyro_x()));
    connect(this->ui->pushButton_offset_gyro_y,SIGNAL(clicked()),this,SLOT(take_offset_gyro_y()));
    connect(this->ui->pushButton_offset_gyro_z,SIGNAL(clicked()),this,SLOT(take_offset_gyro_z()));

    butterworth_lpf_coeffs(X.lpf.a, X.lpf.b);
    butterworth_lpf_coeffs(Y.lpf.a, Y.lpf.b);
    butterworth_lpf_coeffs(Z.lpf.a, Z.lpf.b);
    butterworth_hpf_coeffs(X.hpf.a, X.hpf.b);
    butterworth_hpf_coeffs(Y.hpf.a, Y.hpf.b);
    butterworth_hpf_coeffs(Z.hpf.a, Z.hpf.b);


    lpf_x = &butterworth_filter;
    lpf_y = &butterworth_filter;
    lpf_z = &butterworth_filter;
    hpf_x = &butterworth_filter;
    hpf_y = &butterworth_filter;
    hpf_z = &butterworth_filter;

    classic_MA_x = &classic_MA;
    classic_MA_y = &classic_MA;
    classic_MA_z = &classic_MA;
    X.offset = 0;
    Y.offset = 0;
    Z.offset = 0;
    X.offset_status = false;
    Y.offset_status = false;
    Z.offset_status = false;
}
void MainWindow::take_offset_gyro_x(){
    X.offset = X.lpf.GYRO;
    X.dps_angle = 0;
    X.offset_status = true;
}
void MainWindow::take_offset_gyro_y(){
    Y.offset = Y.lpf.GYRO;
    Y.dps_angle = 0;
    Y.offset_status = true;
}
void MainWindow::take_offset_gyro_z(){
    Z.offset = Z.lpf.GYRO;
    Z.dps_angle = 0;
    Z.offset_status = true;
}

void MainWindow::closeEvent(QCloseEvent *event){
    graph_page->close();
}
MainWindow::~MainWindow(){
    delete ui;
}
