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

typedef char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void EOL(char *base_array, u8 i);
    void serial_port_setup(void);
    u32 crc_chk(u8* data, u8 length);
    void initilize_plot(void);
    void plot_graph(void);

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

    QElapsedTimer graph_time;
    int GYRO_x,GYRO_y,GYRO_z;
    int ACC_x,ACC_y,ACC_z;
    int MAG_x,MAG_y,MAG_z;

public slots:
    void serial_request_sender(void);
    void serial_response_handler(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
