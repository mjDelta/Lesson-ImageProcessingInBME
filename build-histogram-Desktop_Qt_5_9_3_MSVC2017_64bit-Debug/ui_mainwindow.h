/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *rawImg;
    QCustomPlot *widget;
    QLabel *rawImgInfo;
    QLabel *thImg1;
    QLabel *thImg2;
    QLabel *th1ImgInfo;
    QLabel *th2ImgInfo;
    QLabel *histInfo;
    QSlider *thSlider;
    QLabel *sliderMin;
    QLabel *sliderMax;
    QFrame *hline;
    QFrame *vline;
    QPushButton *project1_btn;
    QPushButton *project2_btn;
    QPushButton *project3_btn;
    QPushButton *project4_btn;
    QLabel *thImg3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(501, 326);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        rawImg = new QLabel(centralWidget);
        rawImg->setObjectName(QStringLiteral("rawImg"));
        rawImg->setGeometry(QRect(50, 20, 141, 61));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 170, 291, 91));
        rawImgInfo = new QLabel(centralWidget);
        rawImgInfo->setObjectName(QStringLiteral("rawImgInfo"));
        rawImgInfo->setGeometry(QRect(50, 90, 41, 9));
        thImg1 = new QLabel(centralWidget);
        thImg1->setObjectName(QStringLiteral("thImg1"));
        thImg1->setGeometry(QRect(280, 30, 141, 61));
        thImg2 = new QLabel(centralWidget);
        thImg2->setObjectName(QStringLiteral("thImg2"));
        thImg2->setGeometry(QRect(140, 80, 141, 61));
        th1ImgInfo = new QLabel(centralWidget);
        th1ImgInfo->setObjectName(QStringLiteral("th1ImgInfo"));
        th1ImgInfo->setGeometry(QRect(50, 140, 41, 9));
        th2ImgInfo = new QLabel(centralWidget);
        th2ImgInfo->setObjectName(QStringLiteral("th2ImgInfo"));
        th2ImgInfo->setGeometry(QRect(270, 140, 41, 9));
        histInfo = new QLabel(centralWidget);
        histInfo->setObjectName(QStringLiteral("histInfo"));
        histInfo->setGeometry(QRect(410, 150, 41, 9));
        thSlider = new QSlider(centralWidget);
        thSlider->setObjectName(QStringLiteral("thSlider"));
        thSlider->setGeometry(QRect(330, 40, 160, 16));
        thSlider->setOrientation(Qt::Horizontal);
        sliderMin = new QLabel(centralWidget);
        sliderMin->setObjectName(QStringLiteral("sliderMin"));
        sliderMin->setGeometry(QRect(400, 60, 41, 9));
        sliderMax = new QLabel(centralWidget);
        sliderMax->setObjectName(QStringLiteral("sliderMax"));
        sliderMax->setGeometry(QRect(410, 60, 41, 9));
        hline = new QFrame(centralWidget);
        hline->setObjectName(QStringLiteral("hline"));
        hline->setGeometry(QRect(50, 30, 118, 3));
        hline->setFrameShape(QFrame::HLine);
        hline->setFrameShadow(QFrame::Sunken);
        vline = new QFrame(centralWidget);
        vline->setObjectName(QStringLiteral("vline"));
        vline->setGeometry(QRect(30, 200, 3, 61));
        vline->setFrameShape(QFrame::VLine);
        vline->setFrameShadow(QFrame::Sunken);
        project1_btn = new QPushButton(centralWidget);
        project1_btn->setObjectName(QStringLiteral("project1_btn"));
        project1_btn->setGeometry(QRect(140, 280, 80, 15));
        project2_btn = new QPushButton(centralWidget);
        project2_btn->setObjectName(QStringLiteral("project2_btn"));
        project2_btn->setGeometry(QRect(230, 280, 80, 15));
        project3_btn = new QPushButton(centralWidget);
        project3_btn->setObjectName(QStringLiteral("project3_btn"));
        project3_btn->setGeometry(QRect(340, 280, 80, 15));
        project4_btn = new QPushButton(centralWidget);
        project4_btn->setObjectName(QStringLiteral("project4_btn"));
        project4_btn->setGeometry(QRect(400, 220, 80, 15));
        thImg3 = new QLabel(centralWidget);
        thImg3->setObjectName(QStringLiteral("thImg3"));
        thImg3->setGeometry(QRect(10, 250, 141, 61));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        rawImg->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        rawImgInfo->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        thImg1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        thImg2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        th1ImgInfo->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        th2ImgInfo->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        histInfo->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        sliderMin->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        sliderMax->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        project1_btn->setText(QApplication::translate("MainWindow", "Project 1", Q_NULLPTR));
        project2_btn->setText(QApplication::translate("MainWindow", "Project 2", Q_NULLPTR));
        project3_btn->setText(QApplication::translate("MainWindow", "Project 3", Q_NULLPTR));
        project4_btn->setText(QApplication::translate("MainWindow", "Project 4", Q_NULLPTR));
        thImg3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
