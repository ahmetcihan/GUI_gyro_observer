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
            X.xv[i] = 0;
            Y.xv[i] = 0;
            Z.xv[i] = 0;
            X.yv[i] = 0;
            Y.yv[i] = 0;
            Z.yv[i] = 0;
        }
    }

    connect(this->ui->pushButton_offset_gyro_x,SIGNAL(clicked()),this,SLOT(take_offset_gyro_x()));
    connect(this->ui->pushButton_offset_gyro_y,SIGNAL(clicked()),this,SLOT(take_offset_gyro_y()));
    connect(this->ui->pushButton_offset_gyro_z,SIGNAL(clicked()),this,SLOT(take_offset_gyro_z()));

    butterworth_filter_coeffs(&X.ax_0, &X.ax_1, &X.by_0, &X.by_1, &X.by_2);
    butterworth_filter_coeffs(&Y.ax_0, &Y.ax_1, &Y.by_0, &Y.by_1, &Y.by_2);
    butterworth_filter_coeffs(&Z.ax_0, &Z.ax_1, &Z.by_0, &Z.by_1, &Z.by_2);

    filter_x = &butterworth_filter;
    filter_y = &butterworth_filter;
    filter_z = &butterworth_filter;

    classic_MA_x = &classic_MA;
    classic_MA_y = &classic_MA;
    classic_MA_z = &classic_MA;
    X.offset = 0;
    Y.offset = 0;
    Z.offset = 0;
}
void MainWindow::take_offset_gyro_x(){
    X.offset = X.secondary_filtered_GYRO;
}
void MainWindow::take_offset_gyro_y(){
    Y.offset = Y.secondary_filtered_GYRO;
}
void MainWindow::take_offset_gyro_z(){
    Z.offset = Z.secondary_filtered_GYRO;
}

void MainWindow::closeEvent(QCloseEvent *event){
    graph_page->close();
}
MainWindow::~MainWindow(){
    delete ui;
}
