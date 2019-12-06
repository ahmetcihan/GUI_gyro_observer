#include "mainwindow.h"

void MainWindow::butterworth_lpf_coeffs(double *a, double *b){
    double OmegaC = 0.1;
    double A = 1, B = M_SQRT2, C = 1, D = 0, E = 0, F = 1, T, Arg;

    T = 2.0 * qTan(OmegaC * M_PI_2);

    Arg = (4.0*A + 2.0*B*T + C*T*T);
    a[2] = (4.0*A - 2.0*B*T + C*T*T) / Arg;
    a[1] = (2.0*C*T*T - 8.0*A) / Arg;
    a[0] = 1.0;

    // With all pole filters, our LPF numerator is (z+1)^2, so all our Z Plane zeros are at -1
    b[2] = (4.0*D - 2.0*E*T + F*T*T) / Arg * C/F;
    b[1] = (2.0*F*T*T - 8.0*D) / Arg * C/F;
    b[0] = (4*D + F*T*T + 2.0*E*T) / Arg * C/F;

}
void MainWindow::butterworth_hpf_coeffs(double *a, double *b){
    double OmegaC = 0.05;
    double A = 1, B = M_SQRT2, C = 1, D = 0, E = 0, F = 1, T, Arg;

    T = 2.0 * qTan(OmegaC * M_PI_2);

    Arg = A*T*T + 4.0*C + 2.0*B*T;
    a[2] = (A*T*T + 4.0*C - 2.0*B*T) / Arg;
    a[1] = (2.0*A*T*T - 8.0*C) / Arg;
    a[0] = 1.0;

    // With all pole filters, our HPF numerator is (z-1)^2, so all our Z Plane zeros are at 1
    b[2] = (D*T*T - 2.0*E*T + 4.0*F) / Arg * C/F;
    b[1] = (2.0*D*T*T - 8.0*F) / Arg * C/F;
    b[0] = (D*T*T + 4.0*F + 2.0*E*T) / Arg * C/F;

}
double MainWindow::butterworth_filter(double input, double *a, double *b, double *x, double *y){
    double output, CenterTap;

    CenterTap = input * b[0] + b[1] * x[0] + b[2] * x[1];
    output = a[0] * CenterTap - a[1] * y[0] - a[2] * y[1];

    x[1] = x[0];
    x[0] = input;
    y[1] = y[0];
    y[0] = output;

    return output;
}
double MainWindow::classic_MA(double raw_signal,u8 filter_coefficient, double running_average[64]){
    double processed_value = 0;
    uint16_t j;

    for (j = 0; j < (filter_coefficient-1); j++){
        running_average[j] = running_average[j+1];
        processed_value += running_average[j];
    }
    running_average[filter_coefficient-1] = raw_signal;
    processed_value += raw_signal;

    processed_value = (processed_value)/(filter_coefficient);

    return processed_value;
}
double MainWindow::definite_integral(double raw_signal,u8 integral_size, double int_array[400]){
    double processed_value;
    uint16_t j;

    int_array[integral_size-1] = raw_signal;
    processed_value = raw_signal;
    for (j = 0; j < (integral_size-1); j++){
        processed_value += int_array[j];
        int_array[j] = int_array[j+1];
    }

    return processed_value;
}
