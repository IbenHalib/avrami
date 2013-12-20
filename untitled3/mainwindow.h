#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwt_plot_grid.h"
#include "qwtchartzoom.h"
#include "qwheelzoomsvc.h"
#include "qaxiszoomsvc.h"
#include "math.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"

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
    void setConfigurationHomogeneous();
    void setConfigurationHeterogeneous();
    void initView();
    void plot();
    void plotArray();

    QVector<QPointF> *vector, *vectorNew, *vectorOld;
    QwtPlotCurve *curve, *curveNew, *curveOld;

    QwtChartZoom *zoom;
    QWheelZoomSvc *whlzmsvc;
    QAxisZoomSvc *axzmsvc;
    QwtPlotGrid *grid;
    QwtSymbol *symbolOld, *symbolNew;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
