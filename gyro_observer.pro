#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T10:16:14
#
#-------------------------------------------------

QT       += core gui serialport network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gyro_observer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serial.cpp \
    plot.cpp \
    qcustomplot.cpp \
    graphs.cpp \
    filters.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    graphs.h

FORMS    += mainwindow.ui \
    graphs.ui

RESOURCES += \
    resource.qrc
