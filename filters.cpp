#include "mainwindow.h"

void MainWindow::butterworth_lpf_coeffs(double *by_1,double *by_0,double *ax_0,double *ax_1,double *ax_2){
    double samplerate = 200;
    double cutoff = 1;
    double w_d  = (2.0 * M_PI * cutoff)/(samplerate);
    double alpha = qTan(w_d/2);
    double k = (alpha*alpha) / (1.0 + M_SQRT2*alpha + alpha*alpha);

    *by_1 = 2.0;
    *by_0 = 1.0;
    *ax_0 = k;
    *ax_1 = 2.0 * k - 2*k/(alpha*alpha);
    *ax_2 = (1.0 - M_SQRT2*alpha + alpha*alpha)/(1.0 + M_SQRT2*alpha + alpha*alpha);
}
double MainWindow::butterworth_lpf(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]){

    xv[2] = xv[1];
    xv[1] = xv[0];
    xv[0] = input;
    yv[2] = yv[1];
    yv[1] = yv[0];
    yv[0] =  ax_0*(xv[0] + by_0*xv[1] + by_1*xv[2]) - (ax_1*yv[1] + ax_2*yv[2]);

    return yv[0];
}
void MainWindow::butterworth_hpf_coeffs(double *by_1,double *by_0,double *ax_0,double *ax_1,double *ax_2){
    double samplerate = 200;
    double cutoff = 1;
    double w_d  = (M_PI * cutoff)/(samplerate);
    double alpha = qTan(w_d/2);
    double k = (alpha*alpha) / (1.0 + M_SQRT2*alpha + alpha*alpha);

    *by_1 = 2.0;
    *by_0 = -1.0;
    *ax_0 = k;
    *ax_1 = -2.0 * k + 2*k/(alpha*alpha);
    *ax_2 = (1.0 - M_SQRT2*alpha + alpha*alpha)/(1.0 + M_SQRT2*alpha + alpha*alpha);
}
double MainWindow::butterworth_hpf(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]){

    xv[2] = xv[1];
    xv[1] = xv[0];
    xv[0] = input;
    yv[2] = yv[1];
    yv[1] = yv[0];
    yv[0] =  ax_0*(xv[0] + by_0*xv[1] + by_1*xv[2]) - (ax_1*yv[1] + ax_2*yv[2]);

    return yv[0];
}
double MainWindow::classic_MA(double raw_signal,u8 filter_coefficient, double running_average[64]){
    double processed_value;
    u8 j;

    running_average[filter_coefficient-1] = raw_signal;
    processed_value = raw_signal;
    for (j = 0; j < (filter_coefficient-1); j++){
        processed_value += running_average[j];
        running_average[j] = running_average[j+1];
    }
    processed_value = (processed_value)/(filter_coefficient);

    return processed_value;
}
