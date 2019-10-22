#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial_port_setup();

    graph_page = new graphs(this);
    graph_page->show();

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

}


MainWindow::~MainWindow()
{
    delete ui;
}
