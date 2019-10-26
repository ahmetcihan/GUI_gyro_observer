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
    X.customPlot_filtered_acc = new QCustomPlot(this->ui->plot_filtered_acc_x);
    Y.customPlot_filtered_acc = new QCustomPlot(this->ui->plot_filtered_acc_y);
    Z.customPlot_filtered_acc = new QCustomPlot(this->ui->plot_filtered_acc_z);

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
    X.customPlot_filtered_acc->addGraph();
    Y.customPlot_filtered_acc->addGraph();
    Z.customPlot_filtered_acc->addGraph();

    X.customPlot_acc->addGraph();
    Y.customPlot_acc->addGraph();
    Z.customPlot_acc->addGraph();

    X.customPlot_acc->graph(0)->setPen(QPen(Qt::blue));
    Y.customPlot_acc->graph(0)->setPen(QPen(Qt::blue));
    Z.customPlot_acc->graph(0)->setPen(QPen(Qt::blue));
    X.customPlot_acc->graph(1)->setPen(QPen(Qt::red));
    Y.customPlot_acc->graph(1)->setPen(QPen(Qt::red));
    Z.customPlot_acc->graph(1)->setPen(QPen(Qt::red));

    X.customPlot_acc->graph(1)->setLineStyle(QCPGraph::lsLine);
    Y.customPlot_acc->graph(1)->setLineStyle(QCPGraph::lsLine);
    Z.customPlot_acc->graph(1)->setLineStyle(QCPGraph::lsLine);
    X.customPlot_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    Y.customPlot_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    Z.customPlot_acc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));


    X.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_x->width(),ui->plot_gyro_x->height());
    Y.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_y->width(),ui->plot_gyro_y->height());
    Z.customPlot_gyro->setGeometry(0,0,ui->plot_gyro_z->width(),ui->plot_gyro_z->height());
    X.customPlot_acc->setGeometry(0,0,ui->plot_acc_x->width(),ui->plot_acc_x->height());
    Y.customPlot_acc->setGeometry(0,0,ui->plot_acc_y->width(),ui->plot_acc_y->height());
    Z.customPlot_acc->setGeometry(0,0,ui->plot_acc_z->width(),ui->plot_acc_z->height());
    X.customPlot_mag->setGeometry(0,0,ui->plot_mag_x->width(),ui->plot_mag_x->height());
    Y.customPlot_mag->setGeometry(0,0,ui->plot_mag_y->width(),ui->plot_mag_y->height());
    Z.customPlot_mag->setGeometry(0,0,ui->plot_mag_z->width(),ui->plot_mag_z->height());
    X.customPlot_filtered_acc->setGeometry(0,0,ui->plot_filtered_acc_x->width(),ui->plot_filtered_acc_x->height());
    Y.customPlot_filtered_acc->setGeometry(0,0,ui->plot_filtered_acc_y->width(),ui->plot_filtered_acc_y->height());
    Z.customPlot_filtered_acc->setGeometry(0,0,ui->plot_filtered_acc_z->width(),ui->plot_filtered_acc_z->height());

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
    X.customPlot_filtered_acc->xAxis->setLabel("TIME (s)");
    Y.customPlot_filtered_acc->xAxis->setLabel("TIME (s)");
    Z.customPlot_filtered_acc->xAxis->setLabel("TIME (s)");

}
void MainWindow::plot_graph(void){
    static bool first_in = false;
    static unsigned int counter = 0;

    struct _axis{
        double x,y;
    };
    static struct _axis GX, GY, GZ, AX, AY, AZ, MX, MY, MZ, FAX, FAY, FAZ;

    if(first_in == false){
        first_in = true;
        graph_time.start();
        counter = 0;
    }
    GX.x = (double)graph_time.elapsed() / 1000;
    GY.x = GX.x;
    GZ.x = GX.x;
    AX.x = GX.x;
    AY.x = GX.x;
    AZ.x = GX.x;
    MX.x = GX.x;
    MY.x = GX.x;
    MZ.x = GX.x;
    FAX.x = GX.x;
    FAY.x = GX.x;
    FAZ.x = GX.x;

    if(GX.x < 10){
        X.customPlot_gyro->xAxis->setRange(0,GX.x + 1);
        Y.customPlot_gyro->xAxis->setRange(0,GY.x + 1);
        Z.customPlot_gyro->xAxis->setRange(0,GZ.x + 1);
        X.customPlot_acc->xAxis->setRange(0,AX.x + 1);
        Y.customPlot_acc->xAxis->setRange(0,AY.x + 1);
        Z.customPlot_acc->xAxis->setRange(0,AZ.x + 1);
        X.customPlot_mag->xAxis->setRange(0,MX.x + 1);
        Y.customPlot_mag->xAxis->setRange(0,MY.x + 1);
        Z.customPlot_mag->xAxis->setRange(0,MZ.x + 1);
        X.customPlot_filtered_acc->xAxis->setRange(0,FAX.x + 1);
        Y.customPlot_filtered_acc->xAxis->setRange(0,FAY.x + 1);
        Z.customPlot_filtered_acc->xAxis->setRange(0,FAZ.x + 1);
    }
    else{
        X.customPlot_gyro->xAxis->setRange(GX.x - 10,GX.x + 1);
        Y.customPlot_gyro->xAxis->setRange(GY.x - 10,GY.x + 1);
        Z.customPlot_gyro->xAxis->setRange(GZ.x - 10,GZ.x + 1);
        X.customPlot_acc->xAxis->setRange(AX.x - 10,AX.x + 1);
        Y.customPlot_acc->xAxis->setRange(AY.x - 10,AY.x + 1);
        Z.customPlot_acc->xAxis->setRange(AZ.x - 10,AZ.x + 1);
        X.customPlot_mag->xAxis->setRange(MX.x - 10,MX.x + 1);
        Y.customPlot_mag->xAxis->setRange(MY.x - 10,MY.x + 1);
        Z.customPlot_mag->xAxis->setRange(MZ.x - 10,MZ.x + 1);
        X.customPlot_filtered_acc->xAxis->setRange(FAX.x - 10,FAX.x + 1);
        Y.customPlot_filtered_acc->xAxis->setRange(FAY.x - 10,FAY.x + 1);
        Z.customPlot_filtered_acc->xAxis->setRange(FAZ.x - 10,FAZ.x + 1);
    }

    GX.y = X.GYRO;
    GY.y = Y.GYRO;
    GZ.y = Z.GYRO;
    AX.y = X.ACC;
    AY.y = Y.ACC;
    AZ.y = Z.ACC;
    MX.y = X.MAG;
    MY.y = Y.MAG;
    MZ.y = Z.MAG;
    FAX.y = X.filtered_ACC;
    FAY.y = Y.filtered_ACC;
    FAZ.y = Z.filtered_ACC;

    //X.customPlot_gyro->yAxis->setRange(GX.min_y - 1,GX.max_y + 1);

    X.customPlot_gyro->graph(0)->addData(GX.x,GX.y);
    Y.customPlot_gyro->graph(0)->addData(GY.x,GY.y);
    Z.customPlot_gyro->graph(0)->addData(GZ.x,GZ.y);
    X.customPlot_acc->graph(0)->addData(AX.x,AX.y);
    Y.customPlot_acc->graph(0)->addData(AY.x,AY.y);
    Z.customPlot_acc->graph(0)->addData(AZ.x,AZ.y);
    X.customPlot_mag->graph(0)->addData(MX.x,MX.y);
    Y.customPlot_mag->graph(0)->addData(MY.x,MY.y);
    Z.customPlot_mag->graph(0)->addData(MZ.x,MZ.y);
    X.customPlot_filtered_acc->graph(0)->addData(FAX.x,FAX.y);
    Y.customPlot_filtered_acc->graph(0)->addData(FAY.x,FAY.y);
    Z.customPlot_filtered_acc->graph(0)->addData(FAZ.x,FAZ.y);

    X.customPlot_acc->graph(1)->addData(FAX.x,FAX.y);
    Y.customPlot_acc->graph(1)->addData(FAY.x,FAY.y);
    Z.customPlot_acc->graph(1)->addData(FAZ.x,FAZ.y);
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
    X.customPlot_filtered_acc->graph(0)->rescaleValueAxis(false,true);
    Y.customPlot_filtered_acc->graph(0)->rescaleValueAxis(false,true);
    Z.customPlot_filtered_acc->graph(0)->rescaleValueAxis(false,true);

    X.customPlot_gyro->replot();
    Y.customPlot_gyro->replot();
    Z.customPlot_gyro->replot();
    X.customPlot_acc->replot();
    Y.customPlot_acc->replot();
    Z.customPlot_acc->replot();
    X.customPlot_mag->replot();
    Y.customPlot_mag->replot();
    Z.customPlot_mag->replot();
    X.customPlot_filtered_acc->replot();
    Y.customPlot_filtered_acc->replot();
    Z.customPlot_filtered_acc->replot();


}


