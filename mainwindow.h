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
    QElapsedTimer graph_time;

    struct _axes{
        QCustomPlot *customPlot_gyro;
        QCustomPlot *customPlot_acc;
        QCustomPlot *customPlot_mag;
        QCustomPlot *customPlot_calibrated_acc;
        int GYRO;
        int ACC;
        int MAG;
        double calibrated_ACC;
        double filtered_calibrated_ACC;
        double ax_0,ax_1,by_0,by_1,by_2,xv[3],yv[3];
    };
    _axes X,Y,Z;

public slots:
    void serial_request_sender(void);
    void serial_response_handler(void);

private:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
