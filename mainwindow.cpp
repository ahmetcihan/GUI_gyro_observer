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
        if(i < 3){
            X.lpf.xv[i] = 0;
            Y.lpf.xv[i] = 0;
            Z.lpf.xv[i] = 0;
            X.lpf.yv[i] = 0;
            Y.lpf.yv[i] = 0;
            Z.lpf.yv[i] = 0;
        }
    }

    connect(this->ui->pushButton_offset_gyro_x,SIGNAL(clicked()),this,SLOT(take_offset_gyro_x()));
    connect(this->ui->pushButton_offset_gyro_y,SIGNAL(clicked()),this,SLOT(take_offset_gyro_y()));
    connect(this->ui->pushButton_offset_gyro_z,SIGNAL(clicked()),this,SLOT(take_offset_gyro_z()));

    butterworth_lpf_coeffs(&X.lpf.ax_0, &X.lpf.ax_1, &X.lpf.by_0, &X.lpf.by_1, &X.lpf.by_2);
    butterworth_lpf_coeffs(&Y.lpf.ax_0, &Y.lpf.ax_1, &Y.lpf.by_0, &Y.lpf.by_1, &Y.lpf.by_2);
    butterworth_lpf_coeffs(&Z.lpf.ax_0, &Z.lpf.ax_1, &Z.lpf.by_0, &Z.lpf.by_1, &Z.lpf.by_2);

    lpf_x = &butterworth_lpf;
    lpf_y = &butterworth_lpf;
    lpf_z = &butterworth_lpf;

    butterworth_hpf_coeffs(&X.hpf.ax_0, &X.hpf.ax_1, &X.hpf.by_0, &X.hpf.by_1, &X.hpf.by_2);
    butterworth_hpf_coeffs(&Y.hpf.ax_0, &Y.hpf.ax_1, &Y.hpf.by_0, &Y.hpf.by_1, &Y.hpf.by_2);
    butterworth_hpf_coeffs(&Z.hpf.ax_0, &Z.hpf.ax_1, &Z.hpf.by_0, &Z.hpf.by_1, &Z.hpf.by_2);

    hpf_x = &butterworth_hpf;
    hpf_y = &butterworth_hpf;
    hpf_z = &butterworth_hpf;

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
