#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;
#include <QPainter>
#include <cmath>
#define PI 3.141592653589793
#define FILTERSIZE 9

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window_width=1500;window_height=1300;
    setFixedSize(window_width,window_height);
    raw_x=200;raw_y=100;raw_width=450;raw_height=450;
    project_btn_width=150;
    project_btn_height=50;
    margin=20;

    /*** hline,vline ***/
    ui->vline->setGeometry(raw_x-margin,raw_y-margin,3,window_height);
    ui->hline->setGeometry(0,raw_y-margin,window_width-raw_x,3);

    /*** project switch button ***/
    QPushButton* switchProject1Btn=ui->project1_btn;
    switchProject1Btn->setGeometry(margin,margin,project_btn_width,project_btn_height);
    connect(switchProject1Btn,SIGNAL(clicked()),this,SLOT(switchProject1()));

    QPushButton* switchProject2Btn=ui->project2_btn;
    switchProject2Btn->setGeometry(2*margin+project_btn_width,margin,project_btn_width,project_btn_height);
    connect(switchProject2Btn,SIGNAL(clicked()),this,SLOT(switchProject2()));

    QPushButton* switchProject3Btn=ui->project3_btn;
    switchProject3Btn->setGeometry(3*margin+2*project_btn_width,margin,project_btn_width,project_btn_height);
    connect(switchProject3Btn,SIGNAL(clicked()),this,SLOT(switchProject3()));

    QPushButton* switchProject4Btn=ui->project4_btn;
    switchProject4Btn->setGeometry(4*margin+3*project_btn_width,margin,project_btn_width,project_btn_height);
    connect(switchProject4Btn,SIGNAL(clicked()),this,SLOT(switchProject4()));

    /*** file uploader ***/
    QString iconPath="myImages/images/fileopen.png";
    uploadBtn2 =new QPushButton("&Upload",this);
    uploadBtn2->setText("choose file");
    uploadBtn2->setIcon(QIcon(QPixmap(iconPath)));
    uploadBtn2->setGeometry(margin,margin+100,150,30);
    connect(uploadBtn2,SIGNAL(clicked()),this,SLOT(openFileDialog2()));

    uploadBtn3 =new QPushButton("&Upload",this);
    uploadBtn3->setText("choose file");
    uploadBtn3->setIcon(QIcon(QPixmap(iconPath)));
    uploadBtn3->setGeometry(margin,margin+100,150,30);
    connect(uploadBtn3,SIGNAL(clicked()),this,SLOT(openFileDialog3()));

    uploadBtn4 =new QPushButton("&Upload",this);
    uploadBtn4->setText("choose file");
    uploadBtn4->setIcon(QIcon(QPixmap(iconPath)));
    uploadBtn4->setGeometry(margin,margin+100,150,30);
    connect(uploadBtn4,SIGNAL(clicked()),this,SLOT(openFileDialog4()));

    /*** convolution filters ***/
    robertsOperator=new QPushButton("robert",this);
    robertsOperator->setText("Roberts Operator");
    robertsOperator->setGeometry(margin,margin+100*2,150,30);
    connect(robertsOperator,SIGNAL(clicked()),this,SLOT(processRobertsConv()));

    prewittOperator=new QPushButton("prewitt",this);
    prewittOperator->setText("Prewitt Operator");
    prewittOperator->setGeometry(margin,margin+100*3,150,30);
    connect(prewittOperator,SIGNAL(clicked()),this,SLOT(processPrewittConv()));

    sobelOperator=new QPushButton("sobel",this);
    sobelOperator->setText("Sobel Operator");
    sobelOperator->setGeometry(margin,margin+100*4,150,30);
    connect(sobelOperator,SIGNAL(clicked()),this,SLOT(processSobelConv()));

    gaussianOperator=new QPushButton("gaussian",this);
    gaussianOperator->setText("Gaussian Filter");
    gaussianOperator->setGeometry(margin,margin+100*5,150,30);
    connect(gaussianOperator,SIGNAL(clicked()),this,SLOT(processGaussianConv()));

    medianOperator=new QPushButton("median",this);
    medianOperator->setText("Median Filter");
    medianOperator->setGeometry(margin,margin+100*6,150,30);
    connect(medianOperator,SIGNAL(clicked()),this,SLOT(processMedianConv()));

    /*** morphology: structure element's height and width input widget ***/
    seWidthEdit=new QLineEdit(this);
    seWidthEdit->setPlaceholderText("SE's width...");
    seWidthEdit->setGeometry(margin,margin+100*2,150,30);

    seHeightEdit=new QLineEdit(this);
    seHeightEdit->setPlaceholderText("SE's height...");
    seHeightEdit->setGeometry(margin,margin+100*3,150,30);

     seRadiusEdit=new QLineEdit(this);
     seRadiusEdit->setPlaceholderText("SE's radius...");
     seRadiusEdit->setGeometry(margin,margin+100*4,150,30);

    /*** morphology operators: dilation, erosion, opening and closing***/
    ersionAndDilationOperator=new QPushButton("erosionDilation",this);
    ersionAndDilationOperator->setText("Erosion&Dilation");
    ersionAndDilationOperator->setGeometry(margin,margin+100*5,150,30);
    connect(ersionAndDilationOperator,SIGNAL(clicked()),this,SLOT(processErosionAndDilation()));

    openAndCloseOperator=new QPushButton("openClose",this);
    openAndCloseOperator->setText("Opening&Closing");
    openAndCloseOperator->setGeometry(margin,margin+100*6,150,30);
    connect(openAndCloseOperator,SIGNAL(clicked()),this,SLOT(processOpeningAndClosing()));

    /*** morphology operators: distance transform, skeleton and skeleton restoration***/
    distanceTransform=new QPushButton("Distance Transform",this);
    distanceTransform->setText("Distance\nTransform");
    distanceTransform->setGeometry(margin,margin+100*5,150,60);
    connect(distanceTransform,SIGNAL(clicked()),this,SLOT(processDistanceTransform()));

    skeleton=new QPushButton("Skeleton",this);
    skeleton->setText("Skeleton and\nRestoration");
    skeleton->setGeometry(margin,margin+100*6,150,60);
    connect(skeleton,SIGNAL(clicked()),this,SLOT(processSkeleton()));


    /*** assign project 1 as the default project ***/
    label1=ui->thImg1;
    label2=ui->thImg2;
    label3=ui->thImg3;
    switchProject1();


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::switchProject4(){
    img=new QImage;
    filename="..\\imgs\\square.PNG";
    if(!(img->load(filename))){
        delete img;
        return;
    }
    /*** show raw img ***/
    ui->rawImg->setGeometry(raw_x,raw_y,raw_width,raw_height);
    ui->rawImgInfo->setGeometry(raw_x,raw_y+raw_height,raw_width,100);
    showRawImg(img);
    /*** show processed img: default is the distance transform ***/
    processDistanceTransform();

    project4VisibleSetting();
}
void MainWindow::switchProject3(){
    img=new QImage;
    filename="..\\imgs\\closing.PNG";
    if(!(img->load(filename))){
        delete img;
        return ;
    }
    /*** Show Raw Img***/
    ui->rawImg->setGeometry(raw_x,raw_y,raw_width,raw_height);
    ui->rawImgInfo->setGeometry(raw_x,raw_y+raw_height,raw_width,100);
    showRawImg(img);

    /*** Show Erosion and Dilation ***/
    processErosionAndDilation();

    project3VisibleSetting();
}
void MainWindow::copyImage(QImage *img1, QImage *img2){
    for(int i=0;i<img1->width();i++){
        for(int j=0;j<img1->height();j++){
            img2->setPixel(i,j,img1->pixel(i,j));
        }
    }
}
void MainWindow::findSkeletonPosition(QImage *inImage, int position){
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int graySkeleton=qGray(skeletonPositions->pixel(i,j));
            int grayInImage=qGray(inImage->pixel(i,j));
            if (graySkeleton==position || grayInImage==255){
                QRgb newPixel=qRgb(255,255,255);
                inImage->setPixel(i,j,newPixel);
            }else{
                QRgb newPixel=qRgb(0,0,0);
                inImage->setPixel(i,j,newPixel);
            }
        }
    }
}
void MainWindow::skeletonRestorationProcudure(QImage *outImage){
    QImage* tmp=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    int cnt=maxSkeleton;

    while(cnt>=1){
        findSkeletonPosition(tmp,cnt);
        dilationDisk(tmp,outImage);
        copyImage(outImage,tmp);
        cnt-=1;
    }
    /**closing**/
    QImage* tmp2=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    dilationDisk(tmp,tmp2);
    erosionDisk(tmp2,outImage);

}
void MainWindow::skeletonProcedure(QImage *inImage, QImage *outImage){
    /**erosion***/
    QImage* tmp=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    QImage* tmp4=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    copyImage(inImage,tmp4);
    bool flag=true;
    int cnt=1;
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            QRgb newPixel=qRgb(0,0,0);
            skeletonPositions->setPixel(i,j,newPixel);
        }
    }
    while(flag){
        erosionDisk(tmp4,tmp);
        copyImage(tmp,tmp4);
        flag=false;
        for(int i=0;i<inImage->width();i++){
            for(int j=0;j<inImage->height();j++){
                int tmpGray=qGray(tmp4->pixel(i,j));
                if(tmpGray==255){flag=true;break;}
            }
            if(flag)break;
        }
        /**opening**/
        QImage* tmp2=new QImage(img->width(),img->height(),QImage::Format_RGB32);
        QImage* tmp3=new QImage(img->width(),img->height(),QImage::Format_RGB32);
        erosionDisk(tmp,tmp2);
        dilationDisk(tmp2,tmp3);

        for(int i=0;i<inImage->width();i++){
            for(int j=0;j<inImage->height();j++){
                int tmp3Gray=qGray(tmp3->pixel(i,j));
                int tmpGray=qGray(tmp->pixel(i,j));
                int minus=tmpGray-tmp3Gray;

                if (minus!=0){
                    QRgb positionPixel=qRgb(cnt,cnt,cnt);
                    skeletonPositions->setPixel(i,j,positionPixel);
                    maxSkeleton=cnt;
                    minus=255;
                }
                int outGray=qGray(outImage->pixel(i,j));
                if (outGray==255)continue;
                QRgb newPixel=qRgb(minus,minus,minus);
                outImage->setPixel(i,j,newPixel);
            }
        }
        cnt+=1;
    }


}
void MainWindow::distanceTransformProcedure(   int seHeight, int seWidth, QImage *inImage, QImage *outImage){
    int padRow=(seWidth-1)/2;
    int padCol=(seHeight-1)/2;
    int erosionCnter=1;
    bool haveWhiteFlag=true;
    QImage tmpImg=inImage->copy();
    QImage tmpImg2=inImage->copy();
    for(int i=0;i<outImage->width();i++){
        for(int j=0;j<outImage->height();j++){
            outImage->setPixel(i,j,0);
        }
    }
    while(haveWhiteFlag){
        for(int i=0;i<inImage->width();i++){
            for(int j=0;j<inImage->height();j++){
                int minValue=9999;
                for(int k=-padRow;k<=padRow;k++){
                    for(int m=-padCol;m<=padCol;m++){
                        int v=-1;
                        if (i+k<0||i+k>=inImage->width()||j+m<0||j+m>=inImage->height())v=255;
                        else v=qGray(tmpImg.pixel(i+k,j+m));
                        if (v<minValue)minValue=v;
                    }
                }
                QRgb newPixel=qRgb(minValue,minValue,minValue);
                tmpImg2.setPixel(i,j,newPixel);
            }
        }
        /**记录erosion的位置**/
        for(int i=0;i<inImage->width();i++){
            for(int j=0;j<inImage->height();j++){
                int grayOld=qGray(tmpImg.pixel(i,j));
                int grayNew=qGray(tmpImg2.pixel(i,j));
                if (grayOld-grayNew!=0){
                    QRgb newPixel=qRgb(erosionCnter,erosionCnter,erosionCnter);
                    outImage->setPixel(i,j,newPixel);
                }
            }
        }
        tmpImg=tmpImg2.copy();
        erosionCnter+=1;
        haveWhiteFlag=false;
        cout<<"erosion counter: "<<erosionCnter<<endl;
        for(int i=0;i<tmpImg.width();i++){
            for(int j=0;j<tmpImg.height();j++){
                int v=qGray(tmpImg.pixel(i,j));
                if (v==255){
                    haveWhiteFlag=true;
                    break;
                }
            }
        }
    }
    int scale=int(255/(erosionCnter-1));
    for(int i=0;i<tmpImg.width();i++){
        for(int j=0;j<tmpImg.height();j++){
            int v=qGray(outImage->pixel(i,j))*scale;
            QRgb newPixel=qRgb(v,v,v);
            outImage->setPixel(i,j,newPixel);
        }
    }
}
void MainWindow::processSkeleton(){
    seRadius=1;
    /*** Show dilated Img***/
    QImage* skeleton=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    QImage* skeletonRestoration=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    skeletonPositions=new QImage(img->width(),img->height(),QImage::Format_RGB32);

    skeletonProcedure(img,skeleton);
    skeletonRestorationProcudure(skeletonRestoration);


    QImage* displayOutImg=new QImage;
    *displayOutImg=skeleton->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);
    ui->histInfo->setText("Skeleton: SE radius("+QString::number(seRadius)+")");
    label1->setPixmap(QPixmap::fromImage(*displayOutImg));
    label1->setGeometry(hist_x,hist_y,hist_width,hist_height);

    QImage* displayOutImg2=new QImage;
    *displayOutImg2=skeletonPositions->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int scale=255/maxSkeleton;
    for(int i=0;i<displayOutImg2->width();i++){
        for(int j=0;j<displayOutImg2->height();j++){
            int gray=qGray(displayOutImg2->pixel(i,j))*scale;
            if (gray!=0){
                QRgb newPixel=qRgb(gray,gray,gray);
                displayOutImg2->setPixel(i,j,newPixel);
            }
        }
    }
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    ui->th1ImgInfo->setGeometry(th1_x,th1_y+th1_height,th1_width,100);
    ui->th1ImgInfo->setText("Skeleton positions: SE radius("+QString::number(seRadius)+")");
    label2->setPixmap(QPixmap::fromImage(*displayOutImg2));
    label2->setGeometry(th1_x,th1_y,th1_width,th1_height);

    QImage* displayOutImg3=new QImage;
    *displayOutImg3=skeletonRestoration->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int th2_x=raw_x+raw_width+margin;int th2_y=raw_y+raw_height+10+100+margin;int th2_width=450;int th2_height=450;
    ui->th2ImgInfo->setGeometry(th2_x,th2_y+th2_height,th2_width,100);
    ui->th2ImgInfo->setText("Skeleton restoration: SE radius("+QString::number(seRadius)+")");
    label3->setPixmap(QPixmap::fromImage(*displayOutImg3));
    label3->setGeometry(th2_x,th2_y,th2_width,th2_height);

    ui->th1ImgInfo->setVisible(true);
    label2->setVisible(true);
    ui->th2ImgInfo->setVisible(true);
    label3->setVisible(true);
}
void MainWindow::processDistanceTransform(){
    seHeight=seHeightEdit->text().toInt();
    seWidth=seWidthEdit->text().toInt();
    seRadius=seRadiusEdit->text().toInt();
    if(seHeight==0 && seWidth==0 && seRadius==0){
        seHeight=3;seWidth=3;seRadius=0;
    }
    if(seHeight<3)seHeight=3;
    if(seWidth<3)seWidth=3;
    /*** Show dilated Img***/
    QImage* outImage=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    distanceTransformProcedure(   seHeight,seWidth,img,outImage);

    QImage* displayOutImg=new QImage;
    *displayOutImg=outImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);
    ui->histInfo->setText("Distance transform: SE ("+QString::number(seWidth)+","+QString::number(seHeight)+")");
    label1->setPixmap(QPixmap::fromImage(*displayOutImg));
    label1->setGeometry(hist_x,hist_y,hist_width,hist_height);

    ui->th1ImgInfo->setVisible(false);
    label2->setVisible(false);
    ui->th2ImgInfo->setVisible(false);
    label3->setVisible(false);

}
void MainWindow::processErosionAndDilation(){
    seHeight=seHeightEdit->text().toInt();
    seWidth=seWidthEdit->text().toInt();
    seRadius=seRadiusEdit->text().toInt();
    if(seHeight==0 && seWidth==0 && seRadius==0){
        seHeight=3;seWidth=3;seRadius=0;
    }
    if(seHeight<3)seHeight=3;
    if(seWidth<3)seWidth=3;

    /*** Show dilated Img***/
    QImage* outImage=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    processDilationImg(outImage);


    /*** Show ersioned Img***/
    QImage* outImage2=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    processErosionImg(outImage2);


}
void MainWindow::processOpeningAndClosing(){
    seHeight=seHeightEdit->text().toInt();
    seWidth=seWidthEdit->text().toInt();
    seRadius=seRadiusEdit->text().toInt();
    if(seHeight==0 && seWidth==0 && seRadius==0){
        seHeight=3;seWidth=3;seRadius=0;
    }
    if(seHeight<3)seHeight=3;
    if(seWidth<3)seWidth=3;
    /*** Show opening Img***/
    QImage* outImage=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    processOpeningImg(outImage);

    /*** Show closing Img***/
    QImage* outImage2=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    processClosingImg(outImage2);
}
void MainWindow::processClosingImg(QImage *outImage){
    QImage* tmp=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    if(seRadius==0){
        dilation(img,tmp);
        ersion(tmp,outImage);
        ui->histInfo->setText("Closing: Sqaure SE ("+QString::number(seWidth)+","+QString::number(seHeight)+")");

    }else{
        dilationDisk(img,tmp);
        erosionDisk(tmp,outImage);
        ui->histInfo->setText("Closing: Circle SE ("+QString::number(seRadius)+")");

    }


    QImage* displayOutImg=new QImage;
    *displayOutImg=outImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);
    label1->setPixmap(QPixmap::fromImage(*displayOutImg));
    label1->setGeometry(hist_x,hist_y,hist_width,hist_height);
}
void MainWindow::processOpeningImg( QImage *outImage){
    QImage* tmp=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    if(seRadius==0){
        ersion(img,tmp);
        dilation(tmp,outImage);
        ui->th1ImgInfo->setText("Opening: Square SE ("+QString::number(seWidth)+","+QString::number(seHeight)+")");
    }else{
        erosionDisk(img,tmp);
        dilationDisk(tmp,outImage);
        ui->th1ImgInfo->setText("Opening: Circle SE ("+QString::number(seRadius)+")");
    }


    QImage* displayOutImg=new QImage;
    *displayOutImg=outImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    ui->th1ImgInfo->setGeometry(th1_x,th1_y+th1_height,th1_width,100);
    label2->setPixmap(QPixmap::fromImage(*displayOutImg));
    label2->setGeometry(th1_x,th1_y,th1_width,th1_height);
}
void MainWindow:: processDilationImg(QImage* outImage){
    if(seRadius==0){
        dilation(img,outImage);
        ui->histInfo->setText("Dilation: Sqaure SE ("+QString::number(seWidth)+","+QString::number(seHeight)+")");
    }else{
        dilationDisk(img,outImage);
        ui->histInfo->setText("Dilation: Circle SE ("+QString::number(seRadius)+")");

    }
    QImage* displayOutImg=new QImage;
    *displayOutImg=outImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);

    label1->setPixmap(QPixmap::fromImage(*displayOutImg));
    label1->setGeometry(hist_x,hist_y,hist_width,hist_height);
}
void MainWindow:: processErosionImg(QImage* outImage){
    if(seRadius==0){
        ersion(img,outImage);
        ui->th1ImgInfo->setText("Erosion: Square SE ("+QString::number(seWidth)+","+QString::number(seHeight)+")");

    }else{
        erosionDisk(img,outImage);
        ui->th1ImgInfo->setText("Erosion: Circle SE ("+QString::number(seWidth)+")");

    }

    QImage* displayOutImg=new QImage;
    *displayOutImg=outImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    ui->th1ImgInfo->setGeometry(th1_x,th1_y+th1_height,th1_width,100);
    label2->setPixmap(QPixmap::fromImage(*displayOutImg));
    label2->setGeometry(th1_x,th1_y,th1_width,th1_height);
}
void MainWindow::switchProject1(){
    img=new QImage;
    filename="..\\imgs\\monkey.bmp";
    if(!(img->load(filename))){
        delete img;
        return;
    }

    /*** Show Raw Image ***/
    ui->rawImg->setGeometry(raw_x,raw_y,raw_width,raw_height);
    ui->rawImgInfo->setGeometry(raw_x,raw_y+raw_height,raw_width,100);

    showRawImg(img);

    /*** Plot histogram ***/
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    ui->widget->setGeometry(hist_x,hist_y,hist_width,hist_height);
    plot=ui->widget;
    Imhist(plot,img);
    ui->histInfo->setGeometry(hist_x,hist_y+hist_height,hist_width,100);
    ui->histInfo->setText("Histogram");

    /*** thresholding one ***/
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    ui->thImg1->setGeometry(th1_x,th1_y,th1_width,th1_height);
    int th1= OTSUThresholding();
    ui->th1ImgInfo->setGeometry(th1_x,th1_y+th1_height,th1_width,100);
    ui->th1ImgInfo->setText("OTSU thresholding: "+QString::number(th1));
     randomThresholding(img,label1,th1);


    /*** thresholding two ***/
    int th2_x=raw_x+raw_width+margin;int th2_y=raw_y+raw_height+10+100+margin;int th2_width=450;int th2_height=450;
    ui->thImg2->setGeometry(th2_x,th2_y,th2_width,th2_height);
    int th2= EntropyThresholding();
    ui->th2ImgInfo->setGeometry(th2_x,th2_y+th2_height,th2_width,100);
    ui->th2ImgInfo->setText("Entropy thresholding: "+QString::number(th2));
    cout<<"entropy thresholding:"<<th2<<endl;
     randomThresholding(img,label2,th2);

    /*** slider bar ***/
    QSlider *slider=ui->thSlider;
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setValue(th1);
    ui->sliderMin->setText("0");
    ui->sliderMax->setText("255");
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderChanged()));
    int slide_x=margin;int slide_y=100+margin;int slide_width=150;int slide_height=10;

    slider->setGeometry(slide_x,slide_y,slide_width,slide_height);
    ui->sliderMin->setGeometry(slide_x,slide_y+10,100,20);
    ui->sliderMax->setGeometry(slide_x+slide_width-30,slide_y+10,100,20);



    project1VisibleSetting();


}
void MainWindow::switchProject2(){

    // 卷积核显示   //
    float filterPixels[3][3]={{0,0,0},
                                                   {0,1,0},
                                                   {0,0,0}};
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showConvolutedImage(filterPixels,true);

    project2VisibleSetting();

}
void MainWindow::processSobelConv(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);

    // 卷积核显示   //
    float filterPixels[3][3]={{-1,-2,-1},
                                                   {0,0,0},
                                                   {1,2,1}};
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showConvolutedImage(filterPixels,false);

}
void MainWindow::processGaussianConv(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);

    // 卷积核显示   //
    float filterPixels[3][3]={{-1,-2,-1},
                                                   {0,0,0},
                                                   {1,2,1}};
    float sigma=1.;
    float samePart=1/(2*PI*sigma*sigma);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            float diffPart=-((i-1)*(i-1)+(j-1)*(j-1))/(2*sigma*sigma);
            float g=samePart*exp(diffPart);
            filterPixels[i][j]=g;
        }
    }
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showConvolutedImage(filterPixels,true);

}
void MainWindow::processMedianConv(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);

    // 卷积核显示   //
    float filterPixels[3][3]={{1,1,1},{1,1,1},{1,1,1}};
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showMedianImage();

}
void MainWindow::processPrewittConv(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);

    // 卷积核显示   //
    float filterPixels[3][3]={{-1,-1,-1},
                                                   {0,0,0},
                                                   {1,1,1}};
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showConvolutedImage(filterPixels,false);

}
void MainWindow::processRobertsConv(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);

    // 卷积核显示   //
    float filterPixels[3][3]={{0,0,0},
                                                   {0,-1,0},
                                                   {0,0,1}};
    showConvolutionFilter(filterPixels);

    //卷积并显示卷积后的图像//
    showConvolutedImage(filterPixels,false);

}
void MainWindow::project1VisibleSetting(){
    ui->project1_btn->setEnabled(false);
    ui->project2_btn->setEnabled(true);
    ui->project3_btn->setEnabled(true);
    ui->project4_btn->setEnabled(true);

    ui->thSlider->setVisible(true);
    ui->sliderMin->setVisible(true);
    ui->sliderMax->setVisible(true);
    ui->th2ImgInfo->setVisible(true);
    robertsOperator->setVisible(false);
    prewittOperator->setVisible(false);
    sobelOperator->setVisible(false);
    gaussianOperator->setVisible(false);
    medianOperator->setVisible(false);
    uploadBtn2->setVisible(false);
    uploadBtn3->setVisible(false);
    uploadBtn4->setVisible(false);
    plot->setVisible(true);

    ersionAndDilationOperator->setVisible(false);
    openAndCloseOperator->setVisible(false);
    seWidthEdit->setVisible(false);
    seHeightEdit->setVisible(false);
    distanceTransform->setVisible(false);
    skeleton->setVisible(false);
     seRadiusEdit->setVisible(false);

    ui->th1ImgInfo->setVisible(true);
    ui->th2ImgInfo->setVisible(true);
    label2->setVisible(true);

    label3->setVisible(false);
}
void MainWindow::project2VisibleSetting(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(false);
    ui->project3_btn->setEnabled(true);
    ui->project4_btn->setEnabled(true);

    ui->thSlider->setVisible(false);
    ui->sliderMax->setVisible(false);
    ui->sliderMin->setVisible(false);
    ui->th2ImgInfo->setVisible(false);
    uploadBtn2->setVisible(true);
    uploadBtn3->setVisible(false);
    uploadBtn4->setVisible(false);
    robertsOperator->setVisible(true);
    prewittOperator->setVisible(true);
    sobelOperator->setVisible(true);
    gaussianOperator->setVisible(true);
    medianOperator->setVisible(true);
    plot->setVisible(false);

    ersionAndDilationOperator->setVisible(false);
    openAndCloseOperator->setVisible(false);
    seWidthEdit->setVisible(false);
    seHeightEdit->setVisible(false);
    distanceTransform->setVisible(false);
    skeleton->setVisible(false);
     seRadiusEdit->setVisible(false);

    ui->th1ImgInfo->setVisible(true);
    ui->th2ImgInfo->setVisible(false);
    label2->setVisible(true);

    label3->setVisible(false);

}
void MainWindow::project3VisibleSetting(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(true);
    ui->project3_btn->setEnabled(false);
    ui->project4_btn->setEnabled(true);

    ui->thSlider->setVisible(false);
    ui->sliderMax->setVisible(false);
    ui->sliderMin->setVisible(false);
    ui->th2ImgInfo->setVisible(false);
    uploadBtn2->setVisible(false);
    uploadBtn3->setVisible(true);
    uploadBtn4->setVisible(false);
    robertsOperator->setVisible(false);
    prewittOperator->setVisible(false);
    sobelOperator->setVisible(false);
    gaussianOperator->setVisible(false);
    medianOperator->setVisible(false);
    plot->setVisible(false);

   ersionAndDilationOperator->setVisible(true);
   openAndCloseOperator->setVisible(true);
   seWidthEdit->setVisible(true);
   seHeightEdit->setVisible(true);
   distanceTransform->setVisible(false);
   skeleton->setVisible(false);
    seRadiusEdit->setVisible(true);

   ui->th1ImgInfo->setVisible(true);
   ui->th2ImgInfo->setVisible(false);
   label2->setVisible(true);
   label3->setVisible(false);

}
void MainWindow::project4VisibleSetting(){
    ui->project1_btn->setEnabled(true);
    ui->project2_btn->setEnabled(true);
    ui->project3_btn->setEnabled(true);
    ui->project4_btn->setEnabled(false);

    ui->thSlider->setVisible(false);
    ui->sliderMax->setVisible(false);
    ui->sliderMin->setVisible(false);
    ui->th2ImgInfo->setVisible(false);
    uploadBtn2->setVisible(false);
    uploadBtn3->setVisible(false);
    uploadBtn4->setVisible(true);
    robertsOperator->setVisible(false);
    prewittOperator->setVisible(false);
    sobelOperator->setVisible(false);
    gaussianOperator->setVisible(false);
    medianOperator->setVisible(false);
    plot->setVisible(false);

   ersionAndDilationOperator->setVisible(false);
   openAndCloseOperator->setVisible(false);
   seWidthEdit->setVisible(true);
   seHeightEdit->setVisible(true);
    seRadiusEdit->setVisible(true);
   distanceTransform->setVisible(true);
   skeleton->setVisible(true);

   ui->th1ImgInfo->setVisible(false);
   ui->th2ImgInfo->setVisible(false);
   label2->setVisible(false);
   label3->setVisible(false);

}
void MainWindow::showConvolutedImage(float filterPixels[3][3],bool normalized){
    int validLength=(filterSize-1)/2;
    QImage* convImage=new QImage(img->width()-validLength*2,img->height()-validLength*2,QImage::Format_RGB32);
     convolution(filterPixels,img,convImage,normalized);
    QImage* displayConvImg=new QImage;
    *displayConvImg=convImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    label2->setPixmap(QPixmap::fromImage(*displayConvImg));
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    label2->setGeometry(th1_x,th1_y,th1_width,th1_height);
    ui->th1ImgInfo->setText("Convolved Image");
}
void MainWindow::showMedianImage(){
    int validLength=(filterSize-1)/2;
    QImage* convImage=new QImage(img->width()-validLength*2,img->height()-validLength*2,QImage::Format_RGB32);
    medianFilter(img,convImage);
    QImage* displayConvImg=new QImage;
    *displayConvImg=convImage->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    label2->setPixmap(QPixmap::fromImage(*displayConvImg));
    int th1_x=raw_x;int th1_y=raw_y+raw_height+10+100+margin;int th1_width=450;int th1_height=450;
    label2->setGeometry(th1_x,th1_y,th1_width,th1_height);
    ui->th1ImgInfo->setText("Convolved Image");
}
void MainWindow::showConvolutionFilter(float filterPixels[3][3]){
    QImage* smallKernel=new QImage(filterSize,filterSize,QImage::Format_RGB32);
    for(int w=0;w<filterSize;w++){
        for(int h=0;h<filterSize;h++){
            smallKernel->setPixel(w,h,simpleGray2RGB(filterPixels[w][h]));
        }
    }
    QImage* displayKernel=new QImage;
    *displayKernel=smallKernel->scaled(raw_width,raw_height,Qt::KeepAspectRatio);
    label1->setPixmap(QPixmap::fromImage(*displayKernel));
    int hist_x=raw_x+raw_width+margin;int hist_y=raw_y;int hist_width=450;int hist_height=450;
    label1->setGeometry(hist_x,hist_y,hist_width,hist_height);
    ui->histInfo->setText("Convolution kernel size : "+QString::number(filterSize));
}
QRgb MainWindow::simpleGray2RGB(float gray){
    QRgb value;
    int simpleItensity=int(gray*255);
    value=qRgb(simpleItensity,simpleItensity,simpleItensity );
    return value;
}

//中位数操作 padding=valid 无插值：前提是输入图像和卷积核都是正方形的
void MainWindow::medianFilter(QImage *inImage, QImage *outImage){
    int filterWidth=3;
    int validLength=(filterWidth-1)/2;
    int start=validLength;
    int end=inImage->width()-start;


    for(int w=start;w<end;w++){
        for(int h=start;h<end;h++){
            int *tmpGray=new int[9];
            for(int a=-validLength;a<=validLength;a++){
                for(int b=-validLength;b<=validLength;b++){
                    QRgb pixel=inImage->pixel(w+a,h+b);
                    int gray=qGray(pixel);
                    tmpGray[(a+validLength)*filterWidth+(b+validLength)]=gray;
                }
            }
            int medianValue= getMedianValue(tmpGray);
            QRgb newPixel=qRgb(medianValue,medianValue,medianValue);
            outImage->setPixel(w-validLength,h-validLength,newPixel);
        }
    }
}
void MainWindow::openFileDialog4(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames){

        qDebug()<<tmp<<endl;
        filename=tmp;
        if(!(img->load(filename))){
            delete img;
            return;
        }
        showRawImg(img);

        processDistanceTransform();
    }
}
void MainWindow::openFileDialog3(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames){

        qDebug()<<tmp<<endl;
        filename=tmp;
        if(!(img->load(filename))){
            delete img;
            return;
        }
        showRawImg(img);

        processErosionAndDilation();
    }
}
void MainWindow::openFileDialog2(){
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("Open Image"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames){

        qDebug()<<tmp<<endl;
        filename=tmp;
        if(!(img->load(filename))){
            delete img;
            return;
        }
        showRawImg(img);
//        Imhist(plot,img);
        switchProject2();

    }
}
void MainWindow::sliderChanged(){
        int pos=ui->thSlider->value();
        QString str=QString::number(pos);
        //ui->sliderInfo->setText("Slide thresholding: "+str);
        ui->th1ImgInfo->setText("Slide thresholding: "+QString::number(pos));
         randomThresholding(img,label1,pos);
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
    //bars->moveAbove();

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

int MainWindow::getMedianValue(int *a){

    quickSort(a,0,FILTERSIZE-1);
    int medianValue=a[(FILTERSIZE-1)/2];
    return medianValue;
}
int MainWindow::quickSortOnce(int *a, int low, int high){
    int pivot=a[low];
    int i=low;
    int j=high;
    while(i<j){
        while(a[j]>=pivot && i<j){
            j--;
        }
        a[i]=a[j];
        while(a[i]<=pivot && i<j){
            i++;
        }
        a[j]=a[i];
    }
    a[i]=pivot;
    return i;
}
void MainWindow::quickSort(int *a, int low, int high){
    if(low>=high){
        return;
    }
    int i=quickSortOnce(a,low,high);
    quickSort(a,low,i-1);
    quickSort(a,i+1,high);
}
//膨胀操作 padding=same 快速膨胀操作
void MainWindow::dilation(QImage *inImage, QImage *outImage){
    QImage *tmpImg=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    int padRow=(seWidth-1)/2;
    int padCol=(seHeight-1)/2;
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int maxValue=0;
            for(int k=-padRow;k<=padRow;k++){
                int v=-1;
                if (i+k<0||i+k>=inImage->width())v=0;
                else v=qGray(inImage->pixel(i+k,j));
                if (v>maxValue)maxValue=v;
                }
            QRgb newPixel=qRgb(maxValue,maxValue,maxValue);
            tmpImg->setPixel(i,j,newPixel);
        }
    }
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int maxValue=0;
            for(int m=-padCol;m<=padCol;m++){
                int v=-1;
                if (j+m<0|| j+m>=inImage->height())v=0;
                else v=qGray(tmpImg->pixel(i,j+m));
                if (v>maxValue)maxValue=v;
            }
            QRgb newPixel=qRgb(maxValue,maxValue,maxValue);
            outImage->setPixel(i,j,newPixel);
        }
    }

}
void MainWindow::dilationDisk(QImage *inImage, QImage *outImage){
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int maxValue=0;
            for(int x=-seRadius;x<=seRadius;x++){
                int y=seRadius*seRadius-x*x;
                int yPlus=int(sqrt(y));
                int yMinus=-yPlus;
                int qgrayPlus=-1;
                int qgrayMinus=-1;
                if(i+x<0|| i+x>=inImage->width()|| j+yMinus<0){
                    continue;
                }else{
                    qgrayMinus=qGray(inImage->pixel(i+x,j+yMinus));
                    if (maxValue<qgrayMinus){maxValue=qgrayMinus;}
                }
                if(i+x<0|| i+x>=inImage->width()|| j+yPlus>=inImage->height()){
                    continue;
                }else{
                    qgrayPlus=qGray(inImage->pixel(i+x,j+yPlus));
                    if (maxValue<qgrayPlus){maxValue=qgrayPlus;}
                }
            }
            QRgb newPixel=qRgb(maxValue,maxValue,maxValue);
            outImage->setPixel(i,j,newPixel);
        }
    }
}
void MainWindow::erosionDisk(QImage *inImage, QImage *outImage){
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int minValue=999;
            for(int x=-seRadius;x<=seRadius;x++){
                int y=seRadius*seRadius-x*x;
                int yPlus=int(sqrt(y));
                int yMinus=-yPlus;
                int qgrayPlus=-1;
                int qgrayMinus=-1;
                if(i+x<0|| i+x>=inImage->width()|| j+yMinus<0){
                    continue;
                }else{
                    qgrayMinus=qGray(inImage->pixel(i+x,j+yMinus));
                    if (minValue>qgrayMinus){minValue=qgrayMinus;}
                }
                if(i+x<0|| i+x>=inImage->width()|| j+yPlus>=inImage->height()){
                    continue;
                }else{
                    qgrayPlus=qGray(inImage->pixel(i+x,j+yPlus));
                    if (minValue>qgrayPlus){minValue=qgrayPlus;}
                }
            }
            QRgb newPixel=qRgb(minValue,minValue,minValue);
            outImage->setPixel(i,j,newPixel);
        }
    }
}
//快速腐蚀操作，只针对square形状的structure element。 padding=same
void MainWindow::ersion(QImage *inImage, QImage *outImage){
    QImage *tmpImg=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    int padRow=(seWidth-1)/2;
    int padCol=(seHeight-1)/2;
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int minValue=9999;
            for(int k=-padRow;k<=padRow;k++){
                    int v=-1;
                    if (i+k<0||i+k>=inImage->width())v=255;
                    else v=qGray(inImage->pixel(i+k,j));
                    if (v<minValue)minValue=v;
            }
            QRgb newPixel=qRgb(minValue,minValue,minValue);
            tmpImg->setPixel(i,j,newPixel);
        }
    }
    for(int i=0;i<inImage->width();i++){
        for(int j=0;j<inImage->height();j++){
            int minValue=9999;
                for(int m=-padCol;m<=padCol;m++){
                    int v=-1;
                    if (j+m<0||j+m>=inImage->height())v=255;
                    else v=qGray(tmpImg->pixel(i,j+m));
                    if (v<minValue)minValue=v;
                }
            QRgb newPixel=qRgb(minValue,minValue,minValue);
            outImage->setPixel(i,j,newPixel);
        }
    }
}
//卷积操作 padding=valid 无插值：前提是输入图像和卷积核都是正方形的
void MainWindow::convolution(float filter[3][3], QImage *inImage, QImage *outImage,bool normalized){
    int filterWidth=3;
    int validLength=(filterWidth-1)/2;
    int start=validLength;
    int end=inImage->width()-start;

    float sumFilter=0.;
    if (normalized){
        for(int i=0;i<filterWidth;i++){
            for(int j=0;j<filterWidth;j++){
                sumFilter+=filter[i][j];
            }
        }
    }else{
        sumFilter=1.;
    }

    for(int w=start;w<end;w++){
        for(int h=start;h<end;h++){
            float sumR=0.;float sumG=0.;float sumB=0.;
            for(int a=-validLength;a<=validLength;a++){
                for(int b=-validLength;b<=validLength;b++){
                    QRgb pixel=inImage->pixel(w+a,h+b);
                    int gray=qGray(pixel);
                    float f=filter[a+validLength][b+validLength];
                    f=f/(sumFilter);
                    float tmpGray=f*gray;
                    sumR+=tmpGray;sumG+=tmpGray;sumB+=tmpGray;

                }
            }
            if (sumR>255){sumR=255;} if(sumR<0){sumR=0;}
            if (sumG>255){sumG=255;} if(sumG<0){sumG=0;}
            if (sumB>255){sumB=255;} if(sumB<0){sumB=0;}
            QRgb newPixel=qRgb(sumR,sumG,sumB);
            outImage->setPixel(w-validLength,h-validLength,newPixel);
        }
    }
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
