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
    int  OTSUThresholding();
    int EntropyThresholding();

    double OTSUBetweenClassVariance(int th);
    double EntropyConpute(int th);

    void initWindow();
    void showConvolutionFilter(float filterPixels[3][3]);
    void showConvolutedImage(float filterPixels[3][3],bool normalized);
    void showMedianImage();
    void convolution(float filter[3][3],QImage* inImage,QImage* outImage,bool normalized);
    void dilation(QImage* inImage,QImage* outImage);
    void ersion(QImage* inImage,QImage* outImage);
    void erosionDisk(QImage* inImage,QImage* outImage);
    void dilationDisk(QImage* inImage,QImage* outImage);
    void distanceTransformProcedure( int seHeight,int seWidth,QImage* inImage,QImage* outImage);
    void skeletonProcedure(QImage* inImage,QImage* outImage);
    void skeletonRestorationProcudure(QImage* outImage);
    void findSkeletonPosition(QImage* inImage,int position);

    QRgb simpleGray2RGB(float gray);
    void processDilationImg(QImage* outImage);
    void processErosionImg(QImage* outImage);
    void processOpeningImg(QImage* outImage);
    void processClosingImg(QImage* outImage);

    void project1VisibleSetting();
    void project2VisibleSetting();
    void project3VisibleSetting();
    void project4VisibleSetting();

    int quickSortOnce(int *a,int low,int high);
    void quickSort(int *a,int low,int high);

    int getMedianValue(int *a);
    void copyImage(QImage* img1,QImage* img2);

    void standardEdge(QImage* outImage);
    void internalEdge(QImage* outImage);
    void externalEdge(QImage* outImage);

    void conditionalDilation(QImage* outImage);
    bool judgeTwoImgsTheSame(QImage* img1,QImage* img2);
    void unionTwoImgs(QImage* img1,QImage* img2);
    void reconstructionOpening(QImage* outImage1,QImage* outImage2);
    void reconstructionClosing(QImage* outImage1,QImage* outImage2);
public slots:
    //void sliderChanged(int raw_width,int raw_height,QLabel* label);
    void sliderChanged();
    void openFileDialog2();
    void openFileDialog3();
    void openFileDialog4();
    void switchProject1();
    void switchProject2();
    void switchProject3();
    void switchProject4();
    void processSobelConv();
    void processRobertsConv();
    void processPrewittConv();
    void processGaussianConv();
    void medianFilter(QImage *inImage, QImage *outImage);
    void processMedianConv();

    void processErosionAndDilation();
    void processOpeningAndClosing();
    void processDistanceTransform();
    void processSkeleton();
    void processEdgeDetetion();

    void processConditionalDilation();
    void processReconstruction();

private:
    Ui::MainWindow *ui;
    QImage* img;
    QImage* skeletonPositions;
    int maxSkeleton;

    QVector<double> hist;
    int sumPixels;

    QVector<double> hist_normed;
    int raw_width;
    int raw_height;

    int window_width;
    int window_height;
    int raw_x;int raw_y;
    int project_btn_width;
    int project_btn_height;
    int margin;
    const int filterSize=3;

    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QString filename;


    QPushButton *uploadBtn2;
    QPushButton *uploadBtn3;
    QPushButton *uploadBtn4;
    QPushButton *robertsOperator;
    QPushButton *prewittOperator;
    QPushButton *sobelOperator;
    QPushButton *gaussianOperator;
    QPushButton *medianOperator;
    QPushButton *ersionAndDilationOperator;
    QPushButton *openAndCloseOperator;
    QCustomPlot *plot;

    QLineEdit *seWidthEdit;
    QLineEdit *seHeightEdit;
    QLineEdit *seRadiusEdit;

    QPushButton *distanceTransformBtn;
    QPushButton *skeletonBtn;
    QPushButton *edgeDetectionBtn;
    QPushButton *conditionDilationBtn;
    QPushButton *reconstructionBtn;

    int seWidth;
    int seHeight;
    int seRadius;


};

#endif // MAINWINDOW_H
