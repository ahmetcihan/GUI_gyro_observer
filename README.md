## Gyro Sensor Data Visualization with Qt

**Author:** Ahmet Cihan AKINCA (acihana@gmail.com)

A Qt application for visualizing gyroscope sensor data with real-time plotting and filtering options.

This project visualizes data from a gyroscope sensor connected via a serial port. It incorporates magnetometer and accelerometer data for a complete 3-axis orientation analysis.
Features

    Reads data from a gyroscope sensor with integrated magnetometer and accelerometer.
    Plots gyroscope data (X, Y, Z axes) in real-time.
    Implements Butterworth low-pass and high-pass filters to observe noise reduction and signal behavior.

Requirements

    C++ compiler
    QtCreator (latest stable version recommended)
    Qt version > 5.9.x (consider mentioning the latest stable version)
    QCustomPlot library
    QSerialPort library
