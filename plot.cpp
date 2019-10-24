#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_graphs.h"

void MainWindow::initilize_plot(void){
    customPlot_gyro_x = new QCustomPlot(this->ui->plot_gyro_x);
    customPlot_gyro_y = new QCustomPlot(this->ui->plot_gyro_y);
    customPlot_gyro_z = new QCustomPlot(this->ui->plot_gyro_z);
    customPlot_acc_x = new QCustomPlot(this->ui->plot_acc_x);
    customPlot_acc_y = new QCustomPlot(this->ui->plot_acc_y);
    customPlot_acc_z = new QCustomPlot(this->ui->plot_acc_z);
    customPlot_mag_x = new QCustomPlot(this->ui->plot_mag_x);
    customPlot_mag_y = new QCustomPlot(this->ui->plot_mag_y);
    customPlot_mag_z = new QCustomPlot(this->ui->plot_mag_z);
    customPlot_filtered_acc_x = new QCustomPlot(this->ui->plot_filtered_acc_x);
    customPlot_filtered_acc_y = new QCustomPlot(this->ui->plot_filtered_acc_y);
    customPlot_filtered_acc_z = new QCustomPlot(this->ui->plot_filtered_acc_z);

    // create graph and assign data to it:
    customPlot_gyro_x->addGraph();
    customPlot_gyro_y->addGraph();
    customPlot_gyro_z->addGraph();
    customPlot_acc_x->addGraph();
    customPlot_acc_y->addGraph();
    customPlot_acc_z->addGraph();
    customPlot_mag_x->addGraph();
    customPlot_mag_y->addGraph();
    customPlot_mag_z->addGraph();
    customPlot_filtered_acc_x->addGraph();
    customPlot_filtered_acc_y->addGraph();
    customPlot_filtered_acc_z->addGraph();

    customPlot_gyro_x->setGeometry(0,0,ui->plot_gyro_x->width(),ui->plot_gyro_x->height());
    customPlot_gyro_y->setGeometry(0,0,ui->plot_gyro_y->width(),ui->plot_gyro_y->height());
    customPlot_gyro_z->setGeometry(0,0,ui->plot_gyro_z->width(),ui->plot_gyro_z->height());
    customPlot_acc_x->setGeometry(0,0,ui->plot_acc_x->width(),ui->plot_acc_x->height());
    customPlot_acc_y->setGeometry(0,0,ui->plot_acc_y->width(),ui->plot_acc_y->height());
    customPlot_acc_z->setGeometry(0,0,ui->plot_acc_z->width(),ui->plot_acc_z->height());
    customPlot_mag_x->setGeometry(0,0,ui->plot_mag_x->width(),ui->plot_mag_x->height());
    customPlot_mag_y->setGeometry(0,0,ui->plot_mag_y->width(),ui->plot_mag_y->height());
    customPlot_mag_z->setGeometry(0,0,ui->plot_mag_z->width(),ui->plot_mag_z->height());
    customPlot_filtered_acc_x->setGeometry(0,0,ui->plot_filtered_acc_x->width(),ui->plot_filtered_acc_x->height());
    customPlot_filtered_acc_y->setGeometry(0,0,ui->plot_filtered_acc_y->width(),ui->plot_filtered_acc_y->height());
    customPlot_filtered_acc_z->setGeometry(0,0,ui->plot_filtered_acc_z->width(),ui->plot_filtered_acc_z->height());

    // give the axes some labels:
    //customPlot_gyro_x->yAxis->setLabel("X AXIS");
    customPlot_gyro_x->xAxis->setLabel("TIME (s)");
    customPlot_gyro_y->xAxis->setLabel("TIME (s)");
    customPlot_gyro_z->xAxis->setLabel("TIME (s)");
    customPlot_acc_x->xAxis->setLabel("TIME (s)");
    customPlot_acc_y->xAxis->setLabel("TIME (s)");
    customPlot_acc_z->xAxis->setLabel("TIME (s)");
    customPlot_mag_x->xAxis->setLabel("TIME (s)");
    customPlot_mag_y->xAxis->setLabel("TIME (s)");
    customPlot_mag_z->xAxis->setLabel("TIME (s)");
    customPlot_filtered_acc_x->xAxis->setLabel("TIME (s)");
    customPlot_filtered_acc_y->xAxis->setLabel("TIME (s)");
    customPlot_filtered_acc_z->xAxis->setLabel("TIME (s)");

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
        customPlot_gyro_x->xAxis->setRange(0,GX.x + 1);
        customPlot_gyro_y->xAxis->setRange(0,GY.x + 1);
        customPlot_gyro_z->xAxis->setRange(0,GZ.x + 1);
        customPlot_acc_x->xAxis->setRange(0,AX.x + 1);
        customPlot_acc_y->xAxis->setRange(0,AY.x + 1);
        customPlot_acc_z->xAxis->setRange(0,AZ.x + 1);
        customPlot_mag_x->xAxis->setRange(0,MX.x + 1);
        customPlot_mag_y->xAxis->setRange(0,MY.x + 1);
        customPlot_mag_z->xAxis->setRange(0,MZ.x + 1);
        customPlot_filtered_acc_x->xAxis->setRange(0,FAX.x + 1);
        customPlot_filtered_acc_y->xAxis->setRange(0,FAY.x + 1);
        customPlot_filtered_acc_z->xAxis->setRange(0,FAZ.x + 1);
    }
    else{
        customPlot_gyro_x->xAxis->setRange(GX.x - 10,GX.x + 1);
        customPlot_gyro_y->xAxis->setRange(GY.x - 10,GY.x + 1);
        customPlot_gyro_z->xAxis->setRange(GZ.x - 10,GZ.x + 1);
        customPlot_acc_x->xAxis->setRange(AX.x - 10,AX.x + 1);
        customPlot_acc_y->xAxis->setRange(AY.x - 10,AY.x + 1);
        customPlot_acc_z->xAxis->setRange(AZ.x - 10,AZ.x + 1);
        customPlot_mag_x->xAxis->setRange(MX.x - 10,MX.x + 1);
        customPlot_mag_y->xAxis->setRange(MY.x - 10,MY.x + 1);
        customPlot_mag_z->xAxis->setRange(MZ.x - 10,MZ.x + 1);
        customPlot_filtered_acc_x->xAxis->setRange(FAX.x - 10,FAX.x + 1);
        customPlot_filtered_acc_y->xAxis->setRange(FAY.x - 10,FAY.x + 1);
        customPlot_filtered_acc_z->xAxis->setRange(FAZ.x - 10,FAZ.x + 1);
    }

    GX.y = GYRO_x;
    GY.y = GYRO_y;
    GZ.y = GYRO_z;
    AX.y = ACC_x;
    AY.y = ACC_y;
    AZ.y = ACC_z;
    MX.y = MAG_x;
    MY.y = MAG_y;
    MZ.y = MAG_z;
    FAX.y = filtered_ACC_x;
    FAY.y = filtered_ACC_y;
    FAZ.y = filtered_ACC_z;

    //customPlot_gyro_x->yAxis->setRange(GX.min_y - 1,GX.max_y + 1);

    customPlot_gyro_x->graph(0)->addData(GX.x,GX.y);
    customPlot_gyro_y->graph(0)->addData(GY.x,GY.y);
    customPlot_gyro_z->graph(0)->addData(GZ.x,GZ.y);
    customPlot_acc_x->graph(0)->addData(AX.x,AX.y);
    customPlot_acc_y->graph(0)->addData(AY.x,AY.y);
    customPlot_acc_z->graph(0)->addData(AZ.x,AZ.y);
    customPlot_mag_x->graph(0)->addData(MX.x,MX.y);
    customPlot_mag_y->graph(0)->addData(MY.x,MY.y);
    customPlot_mag_z->graph(0)->addData(MZ.x,MZ.y);
    customPlot_filtered_acc_x->graph(0)->addData(FAX.x,FAX.y);
    customPlot_filtered_acc_y->graph(0)->addData(FAY.x,FAY.y);
    customPlot_filtered_acc_z->graph(0)->addData(FAZ.x,FAZ.y);
    counter++;

    customPlot_gyro_x->graph(0)->rescaleValueAxis(false,true);
    customPlot_gyro_y->graph(0)->rescaleValueAxis(false,true);
    customPlot_gyro_z->graph(0)->rescaleValueAxis(false,true);
    customPlot_acc_x->graph(0)->rescaleValueAxis(false,true);
    customPlot_acc_y->graph(0)->rescaleValueAxis(false,true);
    customPlot_acc_z->graph(0)->rescaleValueAxis(false,true);
    customPlot_mag_x->graph(0)->rescaleValueAxis(false,true);
    customPlot_mag_y->graph(0)->rescaleValueAxis(false,true);
    customPlot_mag_z->graph(0)->rescaleValueAxis(false,true);
    customPlot_filtered_acc_x->graph(0)->rescaleValueAxis(false,true);
    customPlot_filtered_acc_y->graph(0)->rescaleValueAxis(false,true);
    customPlot_filtered_acc_z->graph(0)->rescaleValueAxis(false,true);

    customPlot_gyro_x->replot();
    customPlot_gyro_y->replot();
    customPlot_gyro_z->replot();
    customPlot_acc_x->replot();
    customPlot_acc_y->replot();
    customPlot_acc_z->replot();
    customPlot_mag_x->replot();
    customPlot_mag_y->replot();
    customPlot_mag_z->replot();
    customPlot_filtered_acc_x->replot();
    customPlot_filtered_acc_y->replot();
    customPlot_filtered_acc_z->replot();


}


