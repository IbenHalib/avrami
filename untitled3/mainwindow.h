#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
