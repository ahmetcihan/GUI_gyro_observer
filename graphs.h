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

public slots:
    void get_zero(void);
    void get_cal(void);

private:
    Ui::graphs *ui;
    MainWindow *mainwin;
};

#endif // GRAPHS_H
