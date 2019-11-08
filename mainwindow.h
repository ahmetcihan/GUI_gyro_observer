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

    static double classic_MA(double raw_signal, u8 filter_coefficient, double running_average[]);
    void butterworth_lpf_coeffs(double *by_1, double *by_0, double *ax_0, double *ax_1, double *ax_2);
    static double butterworth_lpf(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]);
    void butterworth_hpf_coeffs(double *by_1, double *by_0, double *ax_0, double *ax_1, double *ax_2);
    static double butterworth_hpf(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]);

    double (*classic_MA_x)(double,u8,double*);
    double (*classic_MA_y)(double,u8,double*);
    double (*classic_MA_z)(double,u8,double*);

    double (*lpf_x)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*lpf_y)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*lpf_z)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*hpf_x)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*hpf_y)(double ,double ,double ,double ,double ,double,double* ,double*);
    double (*hpf_z)(double ,double ,double ,double ,double ,double,double* ,double*);

    QSerialPort *serial;
    QTimer *_100_msec_timer;
    QTimer *read_timer;
    QElapsedTimer graph_time;

    struct _filter{
        double GYRO;
        double ax_0,ax_1,by_0,by_1,by_2,xv[3],yv[3];
    };

    struct _axes{
        QCustomPlot *customPlot_gyro;
        QCustomPlot *customPlot_acc;
        QCustomPlot *customPlot_mag;
        QCustomPlot *customPlot_lpf_gyro;
        QCustomPlot *customPlot_hpf_gyro;
        QCustomPlot *customPlot_gyro_dps;
        QCustomPlot *customPlot_gyro_angle;
        int GYRO;
        int ACC;
        int MAG;
        double dps_gyro;
        double dps_angle;
        double running_average_array[64];
        int offset;
        bool offset_status;
        struct _filter lpf,hpf;
    };
    _axes X,Y,Z;

public slots:
    void serial_request_sender(void);
    void serial_response_handler(void);
    void take_offset_gyro_x(void);
    void take_offset_gyro_y(void);
    void take_offset_gyro_z(void);

private:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
