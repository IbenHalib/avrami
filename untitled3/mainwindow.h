#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwt_plot_grid.h"
#include "qwtchartzoom.h"
#include "qwheelzoomsvc.h"
#include "qaxiszoomsvc.h"
#include "math.h"
#include "qwt_plot_curve.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    double frequency, l, dp, dx, dy, dt, r, t, Nnew, speed,  *timeNucleus;
    int **array, **arrayNucleus;
    int NNucleus, n;
    void init();
    double my_rand();
    void addNucleus(int i, int j);
    void getMemory();
    void setConfiguration();
    void initView();

    QVector<QPointF> *vector;
    QwtPlotCurve *curve;

    QwtChartZoom *zoom;
    QWheelZoomSvc *whlzmsvc;
    QAxisZoomSvc *axzmsvc;
    QwtPlotGrid *grid;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
