#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Imhist(QCustomPlot * plot, QImage *img);
    void showRawImg(QImage *img);
    void randomThresholding(QImage *img,QLabel *label,int th);
    int OTSUThresholding();
    int EntropyThresholding();

    double OTSUBetweenClassVariance(int th);
    double EntropyConpute(int th);

    void initWindow();

public slots:
    //void sliderChanged(int raw_width,int raw_height,QLabel* label);
    void sliderChanged();
    void openFileDialog();

private:
    Ui::MainWindow *ui;
    QImage* img;

    QVector<double> hist;
    int sumPixels;
    QVector<double> hist_normed;

    int raw_width;
    int raw_height;

    QLabel* label1;
    QLabel* label2;
    QString filename;



    QCustomPlot *plot;
};

#endif // MAINWINDOW_H
