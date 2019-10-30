#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_graphs.h"

void MainWindow::initilize_plot(void){
    X.customPlot_gyro = new QCustomPlot(this->ui->plot_gyro_x);
    Y.customPlot_gyro = new QCustomPlot(this->ui->plot_gyro_y);
    Z.customPlot_gyro = new QCustomPlot(this->ui->plot_gyro_z);
    X.customPlot_acc = new QCustomPlot(this->ui->plot_acc_x);
    Y.customPlot_acc = new QCustomPlot(this->ui->plot_acc_y);
    Z.customPlot_acc = new QCustomPlot(this->ui->plot_acc_z);
    X.customPlot_mag = new QCustomPlot(this->ui->plot_mag_x);
    Y.customPlot_mag = new QCustomPlot(this->ui->plot_mag_y);
    Z.customPlot_mag = new QCustomPlot(this->ui->plot_mag_z);
    X.customPlot_calibrated_acc = new QCustomPlot(this->ui->plot_calibrated_acc_x);
    Y.customPlot_calibrated_acc = new QCustomPlot(this->ui->plot_calibrated_acc_y);
    Z.customPlot_calibrated_acc = new QCustomPlot(this->ui->plot_calibrated_acc_z);

    // create graph and assign data to it:
    X.customPlot_gyro->addGraph();
    Y.customPlot_gyro->addGraph();
    Z.customPlot_gyro->addGraph();
    X.customPlot_acc->addGraph();
    Y.customPlot_acc->addGraph();
    Z.customPlot_acc->addGraph();
    X.customPlot_mag->addGraph();
    Y.customPlot_mag->addGraph();
    Z.customPlot_mag->addGraph();
    X.customPlot_calibrated_acc->addGraph();
    Y.customPlot_calibrated_acc->addGraph();
    Z.customPlot_calibrated_acc->addGraph();

    X.customPlot_calibrated_acc->graph(0)->setPen(QPen(Qt::blue));
    Y.customPlot_calibrated_acc->graph(0)->setPen(QPen(Qt::blue));
    Z.customPlot_calibrated_acc->graph(0)->setPen(QPen(Qt::blue));

    X.customPlot_calibrated_acc->addGraph();
    Y.customPlot_calibrated_acc->addGraph();
    Z.customPlot_calibrated_acc->addGraph();

    X.customPlot_calibrated_acc->graph(1)->setPen(QPen(Qt::red));
    Y.customPlot_calibrated_acc->graph(1)->setPen(QPen(Qt::red));
    Z.customPlot_calibrated_acc->graph(1)->setPen(QPen(Qt::red));

    X.customPlot_calibrated_acc->graph(1)->setLineStyle(QCPGraph::lsLine);
    Y.customPlot_calibrated_acc->graph(1)->setLineStyle(QCPGraph::lsLine);
    Z.customPlot_calibrated_acc->graph(1)->setLineStyle(QCPGraph::lsLine);

    X.customPlot_calibrated_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    Y.customPlot_calibrated_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    Z.customPlot_calibrated_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    X.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_x->width(),ui->plot_gyro_x->height());
    Y.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_y->width(),ui->plot_gyro_y->height());
    Z.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_z->width(),ui->plot_gyro_z->height());
    X.customPlot_acc->setGeometry(0,0,ui->plot_acc_x->width(),ui->plot_acc_x->height());
    Y.customPlot_acc->setGeometry(0,0,ui->plot_acc_y->width(),ui->plot_acc_y->height());
    Z.customPlot_acc->setGeometry(0,0,ui->plot_acc_z->width(),ui->plot_acc_z->height());
    X.customPlot_mag->setGeometry(0,0,ui->plot_mag_x->width(),ui->plot_mag_x->height());
    Y.customPlot_mag->setGeometry(0,0,ui->plot_mag_y->width(),ui->plot_mag_y->height());
    Z.customPlot_mag->setGeometry(0,0,ui->plot_mag_z->width(),ui->plot_mag_z->height());
    X.customPlot_calibrated_acc->setGeometry(0,0,ui->plot_calibrated_acc_x->width(),ui->plot_calibrated_acc_x->height());
    Y.customPlot_calibrated_acc->setGeometry(0,0,ui->plot_calibrated_acc_y->width(),ui->plot_calibrated_acc_y->height());
    Z.customPlot_calibrated_acc->setGeometry(0,0,ui->plot_calibrated_acc_z->width(),ui->plot_calibrated_acc_z->height());

    // give the axes some labels:
    //X.customPlot_gyro->yAxis->setLabel("X AXIS");
    X.customPlot_gyro->xAxis->setLabel("TIME (s)");
    Y.customPlot_gyro->xAxis->setLabel("TIME (s)");
    Z.customPlot_gyro->xAxis->setLabel("TIME (s)");
    X.customPlot_acc->xAxis->setLabel("TIME (s)");
    Y.customPlot_acc->xAxis->setLabel("TIME (s)");
    Z.customPlot_acc->xAxis->setLabel("TIME (s)");
    X.customPlot_mag->xAxis->setLabel("TIME (s)");
    Y.customPlot_mag->xAxis->setLabel("TIME (s)");
    Z.customPlot_mag->xAxis->setLabel("TIME (s)");
    X.customPlot_calibrated_acc->xAxis->setLabel("TIME (s)");
    Y.customPlot_calibrated_acc->xAxis->setLabel("TIME (s)");
    Z.customPlot_calibrated_acc->xAxis->setLabel("TIME (s)");

}
void MainWindow::plot_graph(void){
    static bool first_in = false;
    static unsigned int counter = 0;
    double x_axis;

    if(first_in == false){
        first_in = true;
        graph_time.start();
        counter = 0;
    }
    x_axis = (double)graph_time.elapsed() / 1000;

    if(x_axis < 10){
        X.customPlot_gyro->xAxis->setRange(0,x_axis + 1);
        Y.customPlot_gyro->xAxis->setRange(0,x_axis + 1);
        Z.customPlot_gyro->xAxis->setRange(0,x_axis + 1);
        X.customPlot_acc->xAxis->setRange(0,x_axis + 1);
        Y.customPlot_acc->xAxis->setRange(0,x_axis + 1);
        Z.customPlot_acc->xAxis->setRange(0,x_axis + 1);
        X.customPlot_mag->xAxis->setRange(0,x_axis + 1);
        Y.customPlot_mag->xAxis->setRange(0,x_axis + 1);
        Z.customPlot_mag->xAxis->setRange(0,x_axis + 1);
        X.customPlot_calibrated_acc->xAxis->setRange(0,x_axis + 1);
        Y.customPlot_calibrated_acc->xAxis->setRange(0,x_axis + 1);
        Z.customPlot_calibrated_acc->xAxis->setRange(0,x_axis + 1);
    }
    else{
        X.customPlot_gyro->xAxis->setRange(x_axis - 10,x_axis + 1);
        Y.customPlot_gyro->xAxis->setRange(x_axis - 10,x_axis + 1);
        Z.customPlot_gyro->xAxis->setRange(x_axis - 10,x_axis + 1);
        X.customPlot_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
        Y.customPlot_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
        Z.customPlot_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
        X.customPlot_mag->xAxis->setRange(x_axis - 10,x_axis + 1);
        Y.customPlot_mag->xAxis->setRange(x_axis - 10,x_axis + 1);
        Z.customPlot_mag->xAxis->setRange(x_axis - 10,x_axis + 1);
        X.customPlot_calibrated_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
        Y.customPlot_calibrated_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
        Z.customPlot_calibrated_acc->xAxis->setRange(x_axis - 10,x_axis + 1);
    }

    X.customPlot_gyro->graph(0)->addData(x_axis,X.GYRO);
    Y.customPlot_gyro->graph(0)->addData(x_axis,Y.GYRO);
    Z.customPlot_gyro->graph(0)->addData(x_axis,Z.GYRO);
    X.customPlot_acc->graph(0)->addData(x_axis,X.ACC);
    Y.customPlot_acc->graph(0)->addData(x_axis,Y.ACC);
    Z.customPlot_acc->graph(0)->addData(x_axis,Z.ACC);
    X.customPlot_mag->graph(0)->addData(x_axis,X.MAG);
    Y.customPlot_mag->graph(0)->addData(x_axis,Y.MAG);
    Z.customPlot_mag->graph(0)->addData(x_axis,Z.MAG);
    X.customPlot_calibrated_acc->graph(0)->addData(x_axis,X.calibrated_ACC);
    Y.customPlot_calibrated_acc->graph(0)->addData(x_axis,Y.calibrated_ACC);
    Z.customPlot_calibrated_acc->graph(0)->addData(x_axis,Z.calibrated_ACC);

    X.customPlot_calibrated_acc->graph(1)->addData(x_axis,X.filtered_calibrated_ACC);
    Y.customPlot_calibrated_acc->graph(1)->addData(x_axis,Y.filtered_calibrated_ACC);
    Z.customPlot_calibrated_acc->graph(1)->addData(x_axis,Z.filtered_calibrated_ACC);
    counter++;

    X.customPlot_gyro->graph(0)->rescaleValueAxis(false,true);
    Y.customPlot_gyro->graph(0)->rescaleValueAxis(false,true);
    Z.customPlot_gyro->graph(0)->rescaleValueAxis(false,true);
    X.customPlot_acc->graph(0)->rescaleValueAxis(false,true);
    Y.customPlot_acc->graph(0)->rescaleValueAxis(false,true);
    Z.customPlot_acc->graph(0)->rescaleValueAxis(false,true);
    X.customPlot_mag->graph(0)->rescaleValueAxis(false,true);
    Y.customPlot_mag->graph(0)->rescaleValueAxis(false,true);
    Z.customPlot_mag->graph(0)->rescaleValueAxis(false,true);
    X.customPlot_calibrated_acc->graph(0)->rescaleValueAxis(false,true);
    Y.customPlot_calibrated_acc->graph(0)->rescaleValueAxis(false,true);
    Z.customPlot_calibrated_acc->graph(0)->rescaleValueAxis(false,true);

    X.customPlot_gyro->replot();
    Y.customPlot_gyro->replot();
    Z.customPlot_gyro->replot();
    X.customPlot_acc->replot();
    Y.customPlot_acc->replot();
    Z.customPlot_acc->replot();
    X.customPlot_mag->replot();
    Y.customPlot_mag->replot();
    Z.customPlot_mag->replot();
    X.customPlot_calibrated_acc->replot();
    Y.customPlot_calibrated_acc->replot();
    Z.customPlot_calibrated_acc->replot();

}


