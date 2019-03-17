#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;
#include <QPainter>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1500,1300);

    img=new QImage;
    QString filename("..\\imgs\\monkey.bmp");
    if(!(img->load(filename))){
        delete img;
        return;
    }
    int margin=20;

    /*** Show Raw Image ***/
    int raw_x=80;int raw_y=80;raw_width=450;raw_height=450;
    ui->rawImg->setGeometry(raw_x,raw_y,raw_width,raw_height);
    ui->rawImgInfo->setGeometry(raw_x,raw_y+raw_height,raw_width,100);

    showRawImg(img);

    /*** Plot histogram ***/
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->widget->setGeometry(hist_x,hist_y,hist_width,hist_height);
    QCustomPlot* plot=ui->widget;
    Imhist(plot,img);
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);
    ui->histInfo->setText("Histogram");

    /*** thresholding one ***/
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    ui->thImg1->setGeometry(th1_x,th1_y,th1_width,th1_height);
    QLabel* label1=ui->thImg1;
    int th1=OTSUThresholding();
    ui->th1ImgInfo->setGeometry(th1_x,th1_y+th1_height,th1_width,100);
    ui->th1ImgInfo->setText("OTSU thresholding: "+QString::number(th1));
    randomThresholding(img,label1,th1);

    slideLabel=label1;

    /*** thresholding two ***/
    int th2_x=raw_x+raw_width+margin;int th2_y=raw_y+raw_height+10+100+margin;int th2_width=450;int th2_height=450;
    ui->thImg2->setGeometry(th2_x,th2_y,th2_width,th2_height);
    QLabel* label2=ui->thImg2;
    int th2=EntropyThresholding();
    ui->th2ImgInfo->setGeometry(th2_x,th2_y+th2_height,th2_width,100);
    ui->th2ImgInfo->setText("Entropy thresholding: "+QString::number(th2));
    randomThresholding(img,label2,th2);

    /*** slider bar ***/
    QSlider *slider=ui->thSlider;
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setValue(th1);
    ui->sliderInfo->setText("Slide thresholding: "+QString::number(th1));
    //connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderChanged(int,int,QLabel*)));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderChanged()));
    int slide_x=raw_x+2*raw_width+2*margin;int slide_y=raw_y;int slide_width=300;int slide_height=10;
    slider->setGeometry(slide_x,slide_y,slide_width,slide_height);
    ui->sliderInfo->setGeometry(slide_x,slide_y+margin,300,50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//void MainWindow::sliderChanged(int raw_width,int raw_height,QLabel* label){
//    int pos=ui->thSlider->value();
//    QString str=QString::number(pos);
//    ui->sliderInfo->setText("Slide thresholding: "+str);
//    ui->th1ImgInfo->setText("OTSU thresholding: "+QString::number(pos));
//    randomThresholding(img,raw_width,raw_height,label,pos);
//}
void MainWindow::sliderChanged(){
        int pos=ui->thSlider->value();
        QString str=QString::number(pos);
        ui->sliderInfo->setText("Slide thresholding: "+str);
        ui->th1ImgInfo->setText("Slide thresholding: "+QString::number(pos));
        randomThresholding(img,slideLabel,pos);
}
int MainWindow::EntropyThresholding(){
    int best_th=-1;
    double max_entropy=-1;
    for(int th=0;th<256;th++){
        double entropy=EntropyConpute(th);
        if (entropy>max_entropy){
            max_entropy=entropy;
            best_th=th;
        }
    }
    cout<<"best th "<<best_th<<", max entropy "<<max_entropy<<endl;
    return best_th;
}
int MainWindow::OTSUThresholding(){
    int best_th=-1;
    double max_variance=-1;
    for(int th=0;th<256;th++){
        double variance=OTSUBetweenClassVariance(th);
        if (variance>max_variance){
            max_variance=variance;
            best_th=th;
        }
    }
    cout<<"best th "<<best_th<<", max variance "<<max_variance<<endl;
    return best_th;
}
double MainWindow::EntropyConpute(int th){
    double f1=0.;double f2=0.;
    for(int i=0;i<hist_normed.size();i++){
        if(i<=th){
            f1+=hist_normed.at(i);
        }else{
            f2+=hist_normed.at(i);
        }
    }
    double entropy_sum=0.;
    for(int i=0;i<hist_normed.size();i++){
        double p=0.;
        if(i<=th){
            p=hist_normed.at(i)/(f1+10e-9);
        }else{
            p=hist_normed.at(i)/(f2+10e-9);
        }

        double entropy=0.;
        if (p==0){
            entropy=0.;
        }else{
            entropy=-p*log(p);
        }
        entropy_sum+=entropy;
    }
    return entropy_sum;
}
double MainWindow::OTSUBetweenClassVariance(int th){
    double f1=0.;double f2=0.;
    for(int i=0;i<hist_normed.size();i++){
        if(i<=th){
            f1+=hist_normed.at(i);
        }else{
            f2+=hist_normed.at(i);
        }
    }
    double mean1=0.;double mean2=0.;
    for(int i=0;i<hist_normed.size();i++){
        if(i<=th){
            mean1+=(i*hist_normed.at(i)/(f1+10e-9));
        }else{
            mean2+=(i*hist_normed.at(i)/(f2+10e-9));
        }
    }
    double variance=f1*f2*(mean2-mean1)*(mean2-mean1);
    //cout<<"th:"<<th<<",mean1:"<<mean1<<",mean2:"<<mean2<<".variance:"<<variance<<endl;

    return variance;

}

void MainWindow::randomThresholding(QImage *img,QLabel *label,int th){
    QImage* scaledImg=new QImage;
    int pic_width=img->width(),pic_height=img->height();
    int ratio_width,ratio_height;
    float ratio;
    if(pic_width/(raw_width+0.)>=pic_height/(raw_height+0.))
        ratio=pic_width/(raw_width+0.);
    else
        ratio=pic_height/(raw_height+0.);
    ratio_width=pic_width/ratio;
    ratio_height=pic_height/ratio;
    QImage  grayimg = img->copy();
    QRgb white,black;
    white=qRgb(255,255,255);
    black=qRgb(0,0,0);

    for(int i = 0; i <pic_height; i++)
    {
        for(int j = 0; j < pic_width; j++)
        {
            QRgb value=grayimg.pixel(j,i);
            int red=qRed(value);
            int green=qGreen(value);
            int blue=qBlue(value);
            int intensity = (int)((red*30 + green*59 + blue*11 + 50.) / 100.);

            if (intensity>th){
                grayimg.setPixel(j,i,white);
            }else{
                grayimg.setPixel(j,i,black);
            }
        }
    }
    *scaledImg=grayimg.scaled(ratio_width,ratio_height,Qt::KeepAspectRatio);
    label->setPixmap(QPixmap::fromImage(*scaledImg));
}
void MainWindow::showRawImg(QImage *img){

    QImage* scaledImg=new QImage;
    int pic_width=img->width(),pic_height=img->height();
    sumPixels=pic_height*pic_width;
    int ratio_width,ratio_height;
    float ratio;
    if(pic_width/(raw_width+0.)>=pic_height/(raw_height+0.))
        ratio=pic_width/(raw_width+0.);
    else
        ratio=pic_height/(raw_height+0.);
    ratio_width=pic_width/ratio;
    ratio_height=pic_height/ratio;
    //QImage imgCopy=img->copy();
    *scaledImg=img->scaled(ratio_width,ratio_height,Qt::KeepAspectRatio);
    ui->rawImg->setPixmap(QPixmap::fromImage(*scaledImg));
    ui->rawImgInfo->setText("Raw image\nWidth: "+QString::number(pic_width)+", Height: "+QString::number(pic_height)+
                            "\nScaled width: "+QString::number(ratio_width)+", Scaled height: "+QString::number(ratio_height));
}
void MainWindow::Imhist(QCustomPlot * plot, QImage *img)
{
    double yrange = 0;
    QVector<double> datax;
    plot->clearGraphs();
    hist.resize(256);
    for(double i = 0; i < 256; i = i + 1)
       datax.append(i);
    QImage  grayimg = img->copy();
    cout<<"bytes per line:"<<grayimg.bytesPerLine()<<"\t bytes count:"<<grayimg.byteCount()<<endl;
    //  对直方图进行数据处理
    int width = img->width();
    int hight = img->height();

    for(int i = 0; i <hight; i++)
    {
        for(int j = 0; j < width; j++)
        {
            QRgb value=grayimg.pixel(j,i);
            int red=qRed(value);
            int green=qGreen(value);
            int blue=qBlue(value);
            int intensity = (int)((red*30 + green*59 + blue*11 + 50.) / 100.);
            //cout<<"height:"<<i<<",width:"<<j<<". rgb is ("<<red<<","<<green<<","<<blue<<"). The intensity is "<<intensity<<"." <<endl;

            hist.replace(intensity,hist.at(intensity)+1);
        }
    }

    QVector<double>::iterator it;
    for(it = hist.begin(); it != hist.end(); it++)
    {
        if(*it > yrange){
            yrange = *it;

        }
    }
    plot->xAxis->setRange(0,256);  //x轴范围
    plot->yAxis->setRange(0,(int)yrange);  //y轴范围
    QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
    bars->setData(datax, hist);
    bars->setPen(QColor(0, 0, 0));
    bars->setWidth(0.05);
    plot->setVisible(true);
    plot->replot();

    hist_normed.resize(256);
    double sum_hist=0.;
    for(int i=0; i<256; i++)
    {
        hist_normed.replace(i,hist.at(i)/sumPixels);
        sum_hist+=hist_normed.at(i)*i;
    }
    cout<<"sum hist norm "<<sum_hist<<endl;
}
