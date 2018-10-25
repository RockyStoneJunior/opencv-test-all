#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    splitter = new QSplitter(Qt::Horizontal);
    QListWidget *listwidget1 = new QListWidget();
    label = new QLabel("Label");
    ocr = new Ocr(Qt::Vertical);
    hough = new HoughTransformation;

    splitter->addWidget(listwidget1);
    splitter->addWidget(ocr);

    listwidget1->addItem(tr("Optical Character Recognization"));
    listwidget1->addItem(tr("Face Detection"));
    listwidget1->addItem(tr("Hough Transformation"));
    listwidget1->addItem(tr("Pattern Classification"));
    listwidget1->addItem(tr("Distance Measurement"));
    listwidget1->addItem(tr("Camera Calibration"));
    listwidget1->addItem(tr("3D Reconstruction"));
    listwidget1->addItem(tr("Defect Detection"));
    listwidget1->addItem(tr("Robotics Arm Positioning"));
    listwidget1->addItem(tr("QR Code Scan"));
    listwidget1->addItem(tr("Optical Flow"));


    splitter->setSizes(QList<int>{200,Qt::MaximumSize});

    setCentralWidget(splitter);

    connect(listwidget1, SIGNAL(itemActivated(QListWidgetItem *)), this ,SLOT(onListClick(QListWidgetItem *)));
}

void MainWindow::onListClick(QListWidgetItem *item)
{
    QString str = item->text();
    //qDebug(str.toLatin1());

    if(str == "Face Detection")
    {
        splitter->replaceWidget(1, label);
    }else if(str == "Optical Character Recognization")
    {
        splitter->replaceWidget(1, ocr);
    }else if(str == "Hough Transformation")
    {
        splitter->replaceWidget(1, hough);
    }else if(str == "Pattern Classification")
    {

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
