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

//void bk(int *i, int *j , int *k)
//{
//    if (*i < 0)
//    {
//        *j += N_x;
//        *k += N_x;
//        *i += N_x;
//    }
//    if (*i >= N_x )
//    {
//        *j -= N_x;
//        *k -= N_x;
//        *i -= N_x;
//    }

//    if (*j < 0)
//        *j += N_y;
//    if (*j >= N_y)
//        *j -= N_y;

//    if (*k < 0)
//        *k += N_z;
//    if (*k >= N_z)
//        *k -= N_z;
//}
