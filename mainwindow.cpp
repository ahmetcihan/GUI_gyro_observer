#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial_port_setup();

    this->setGeometry(0,0,this->width(),this->height());

    graph_page = new graphs(this);
    graph_page->show();
    graph_page->setGeometry(this->width() + 10,0,graph_page->width(),graph_page->height());

    _100_msec_timer = new QTimer(this);
    _100_msec_timer->setInterval(50);
    _100_msec_timer->start();
    connect(_100_msec_timer, SIGNAL(timeout()),this,SLOT(serial_request_sender()));

    read_timer = new QTimer(this);
    read_timer->setInterval(30);
    read_timer->start();
    connect(read_timer, SIGNAL(timeout()),this,SLOT(serial_response_handler()));

    initilize_plot();

    butterworth_filter_coeffs(&X.ax_0, &X.ax_1, &X.by_0, &X.by_1, &X.by_2);
    butterworth_filter_coeffs(&Y.ax_0, &Y.ax_1, &Y.by_0, &Y.by_1, &Y.by_2);
    butterworth_filter_coeffs(&Z.ax_0, &Z.ax_1, &Z.by_0, &Z.by_1, &Z.by_2);

    filter_x = & butterworth_filter;
    filter_y = & butterworth_filter;
    filter_z = & butterworth_filter;
}

void MainWindow::closeEvent(QCloseEvent *event){
    graph_page->close();
}
MainWindow::~MainWindow(){
    delete ui;
}
