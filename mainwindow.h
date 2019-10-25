#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QElapsedTimer>
#include <QProcess>
#include <qcustomplot.h>
#include "ui_mainwindow.h"
#include "graphs.h"

typedef char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

    graphs *graph_page;

    void EOL(char *base_array, u8 i);
    void serial_port_setup(void);
    u32 crc_chk(u8* data, u8 length);
    void initilize_plot(void);
    void plot_graph(void);
    void butterworth_filter_coeffs(double *by_1, double *by_0, double *ax_0, double *ax_1, double *ax_2);
    static double butterworth_filter(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]);

    double (*filter_x)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*filter_y)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*filter_z)(double ,double ,double ,double ,double ,double,double* ,double*);

    QSerialPort *serial;
    QTimer *_100_msec_timer;
    QTimer *read_timer;

    QCustomPlot *customPlot_gyro_x;
    QCustomPlot *customPlot_gyro_y;
    QCustomPlot *customPlot_gyro_z;
    QCustomPlot *customPlot_acc_x;
    QCustomPlot *customPlot_acc_y;
    QCustomPlot *customPlot_acc_z;
    QCustomPlot *customPlot_mag_x;
    QCustomPlot *customPlot_mag_y;
    QCustomPlot *customPlot_mag_z;
    QCustomPlot *customPlot_filtered_acc_x;
    QCustomPlot *customPlot_filtered_acc_y;
    QCustomPlot *customPlot_filtered_acc_z;

    QElapsedTimer graph_time;

    struct _axes{
        int GYRO;
    };
    _axes X,Y,Z;

    //int GYRO_x,GYRO_y,GYRO_z;
    int ACC_x,ACC_y,ACC_z;
    int MAG_x,MAG_y,MAG_z;
    double filtered_ACC_x,filtered_ACC_y,filtered_ACC_z;
    double X_ax_0,X_ax_1,X_by_0,X_by_1,X_by_2,X_xv[3],X_yv[3];
    double Y_ax_0,Y_ax_1,Y_by_0,Y_by_1,Y_by_2,Y_xv[3],Y_yv[3];
    double Z_ax_0,Z_ax_1,Z_by_0,Z_by_1,Z_by_2,Z_xv[3],Z_yv[3];

public slots:
    void serial_request_sender(void);
    void serial_response_handler(void);

private:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
