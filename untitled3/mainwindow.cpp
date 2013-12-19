#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    this->l = 1e1;
    this->n = 1000;
    frequency = 1e1;
    speed = 1e-5;
    dx = l /double(n);
    dy = dx;
//    l = dx * n;

    dt =  1e1;
    t = 0;


    Nnew = 0;
    NNucleus = 0;

    getMemory();
    setConfiguration();
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
    for (int var = 0; var < 10; ++var) {
    vector->clear();

   this->init();

    for (int k = 0; k < NNucleus; ++k) {

        r = speed * (t - timeNucleus[k]);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((( pow(i - arrayNucleus[k][0], 2) + pow(j - arrayNucleus[k][1], 2)) < pow(r, 2)) && (array[i][j] == 0)) {
                    array[i][j] = -1;
                    Nnew++;
                }
            }
        }
    }

    t += dt;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((array[i][j] == 0) && (my_rand() < frequency*dx*dy*dt)) {
                 addNucleus(i, j);
            }
        }
     }
      }

   vector->append(QPointF(t, Nnew/double(n)));
   curve->setSamples(vector);
   ui->qwtPlot->replot();
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

void MainWindow::setConfiguration()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            array[i][j] = 0;
        }

    }
}


void MainWindow::initView()
{
        curve = new QwtPlotCurve;
        vector = new  QVector<QPointF>;
        curve->attach(ui->qwtPlot);

        curve->setPen(QPen(QColor(255, 0, 0)));


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
}

