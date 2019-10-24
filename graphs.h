#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>

namespace Ui {
    class graphs;
}
class MainWindow;

class graphs : public QWidget
{
    Q_OBJECT

public:
    explicit graphs(MainWindow *master, QWidget *parent = 0);
    ~graphs();
    Ui::graphs *ui;

    double slope[9];
    double calibrated[9];

public slots:
    void get_zero(void);
    void get_cal(void);
    void calibrate();

private:
    MainWindow *mainwindow;
};

#endif // GRAPHS_H
