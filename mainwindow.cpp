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
    butterworth_filter_coeffs(&X_ax_0, &X_ax_1, &X_by_0, &X_by_1, &X_by_2);
    butterworth_filter_coeffs(&Y_ax_0, &Y_ax_1, &Y_by_0, &Y_by_1, &Y_by_2);
    butterworth_filter_coeffs(&Z_ax_0, &Z_ax_1, &Z_by_0, &Z_by_1, &Z_by_2);

    filter_x = & butterworth_filter;
    filter_y = & butterworth_filter;
    filter_z = & butterworth_filter;
}


MainWindow::~MainWindow()
{
    delete ui;
}
