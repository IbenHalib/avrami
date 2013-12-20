#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    this->l = 1e1;
    this->n = 1000;
    frequency = 1e-1;
    speed = 1e3;
    dx = 1e-1;
//    dx = l /double(n);
    dy = dx;
//    l = dx * n;

    dt =  1e-3;
    t = 0;


    Nnew = 0;
    NNucleus = 6;

    getMemory();
//    setConfigurationHomogeneous();
    setConfigurationHeterogeneous();
    initView();

}

double MainWindow::my_rand()
{
    return rand()/(double)RAND_MAX;
}
void MainWindow::addNucleus(int i, int j)
{
    array[i][j] = NNucleus;

    arrayNucleus[NNucleus][0] = i;
    arrayNucleus[NNucleus][1] = j;

    timeNucleus[NNucleus] = t;
    Nnew++;
    NNucleus++;

}


void MainWindow::on_pushButton_clicked()
{
    this->init();
    int nMax = pow (n, 2);
    int q=0;
    plot();
    plotArray();
    while (Nnew < nMax) {
//    vector->clear();

        QApplication::processEvents();
//        if (++q/3.0 == 1) {
//         plotArray();
//        } else {
//            q = 0;
//        }
        plotArray();
        plot();


    for (int k = 0; k < NNucleus; ++k) {

        r = speed * (t - timeNucleus[k]);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((( pow(i - arrayNucleus[k][0], 2) + pow(j - arrayNucleus[k][1], 2)) < pow(r, 2))
                       && (array[i][j] == 0)) {
                    array[i][j] = -1;
                    Nnew++;
                }
            }
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((array[i][j] == 0) && (my_rand() < frequency*dx*dy*dt)) {
                 addNucleus(i, j);
            }
        }
     }

    t += dt;



    }

}

void MainWindow::plot()
{
    double a = double(Nnew)/double(n*n);
    vector->append(QPointF(t, a));
    curve->setSamples(*vector);
    ui->qwtPlot->replot();
}

void MainWindow::plotArray()
{
    vectorNew->clear();
    vectorOld->clear();


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (array[i][j]==0) {
                vectorOld->append(QPointF(i, j));

            } else {
                vectorNew->append(QPointF(i, j));
            }
        }


    }
    curveNew->setSamples(*vectorNew);
    curveOld->setSamples(*vectorOld);
    ui->qwtPlot_2->replot();

}

void MainWindow::getMemory()
{
    int maxN = pow(n, 2);

    array = new int*[n];

    for (int i = 0; i < n; i++){
        array[i] = new int[n];
    }

    timeNucleus = new double[maxN];
    arrayNucleus = new int*[maxN];
    for (int i = 0; i < maxN; ++i) {
        arrayNucleus[i] = new int[2];
    }
}

void MainWindow::setConfigurationHomogeneous()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            array[i][j] = 0;
        }

    }
}

void MainWindow::setConfigurationHeterogeneous()
{
    setConfigurationHomogeneous();
    int NN = NNucleus;
    int iTemp, jTemp;
    NNucleus = 0;
    for (int i = 0; i < NN ; i++) {
        do {
            iTemp = rand() % n;
            jTemp = rand() % n;

        } while (array[iTemp][jTemp] != 0);

        addNucleus( iTemp, jTemp);
    }
}

void MainWindow::initView()
{
        curve = new QwtPlotCurve;

        vector = new  QVector<QPointF>;
        curve->attach(ui->qwtPlot);



//        curve->setPen(QPen(QColor(255, 0, 0)));


        grid = new QwtPlotGrid;
        grid->enableXMin(true);
        grid->setMajPen(QPen(Qt::black,0,Qt::DotLine));
        grid->setMinPen(QPen(Qt::gray,0,Qt::DotLine));
        grid->attach(ui->qwtPlot);

        zoom = new QwtChartZoom(ui->qwtPlot);
        zoom->setRubberBandColor(Qt::white);

        whlzmsvc = new QWheelZoomSvc();
        whlzmsvc->attach(zoom);

        axzmsvc = new QAxisZoomSvc();
        axzmsvc->attach(zoom);


        curveNew = new QwtPlotCurve;
        curveOld = new QwtPlotCurve;

        vectorNew = new  QVector<QPointF>;
        vectorOld = new  QVector<QPointF>;

        curveNew->attach(ui->qwtPlot_2);
        curveOld->attach(ui->qwtPlot_2);

        symbolNew = new QwtSymbol;
        symbolNew->setStyle(QwtSymbol::Ellipse);

        symbolNew->setPen(QColor(Qt::red));
        symbolNew->setSize(1);

        curveNew->setSymbol(symbolNew);
        curveNew->setStyle(QwtPlotCurve::Dots);
        curveNew->setPen(QPen(QColor(Qt::red)));

//     QwtChartZoom *zoom2 = new QwtChartZoom(ui->qwtPlot_2);
//        zoom2->setRubberBandColor(Qt::white);

        symbolOld = new QwtSymbol;
        symbolOld->setStyle(QwtSymbol::Ellipse);
        symbolOld->setPen(QColor(Qt::black));
         curveNew->setPen(QPen(QColor(Qt::black)));
        symbolOld->setSize(1);

//        curveOld->setPen(QPen(QColor(Qt::red)));
        curveOld->setSymbol(symbolOld);
        curveOld->setStyle(QwtPlotCurve::Dots);

}

