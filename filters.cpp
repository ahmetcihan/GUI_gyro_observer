#include "mainwindow.h"

void MainWindow::butterworth_filter_coeffs(double *by_1,double *by_0,double *ax_0,double *ax_1,double *ax_2){
    double samplerate = 200;
    double cutoff = 5;

    double w_d  = (2.0 * M_PI * cutoff)/(samplerate);

    double alpha = qTan(w_d/2); // Warp cutoff frequency

    double k = (alpha*alpha) / (1.0 + M_SQRT2*alpha + alpha*alpha);

    *by_1 = 2.0;
    *by_0 = 1.0;
    *ax_0 = k;
    *ax_1 = 2.0 * k - 2*k/(alpha*alpha);
    *ax_2 = (1.0 - M_SQRT2*alpha + alpha*alpha)/(1.0 + M_SQRT2*alpha + alpha*alpha);
}
double MainWindow::butterworth_filter(double input,double by_1,double by_0,double ax_0,double ax_1,double ax_2,double xv[3],double yv[3]){
    //static double xv[3] = {0};
    //static double yv[3] = {0};

    xv[2] = xv[1];
    xv[1] = xv[0];
    xv[0] = input;
    yv[2] = yv[1];
    yv[1] = yv[0];

    yv[0] =  ax_0*(xv[0] + by_0*xv[1] + by_1*xv[2]) - (ax_1*yv[1] + ax_2*yv[2]);

    return yv[0];
}
