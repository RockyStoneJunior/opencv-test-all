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
    ocr = new Ocr();

    splitter->addWidget(listwidget1);
    splitter->addWidget(ocr->getSplitter());

    listwidget1->addItem("Optical Character Recognization");
    listwidget1->addItem("Face Detection");
    listwidget1->addItem("Pattern Classification");
    listwidget1->addItem("Distance Measurement");
    listwidget1->addItem("Camera Calibration");
    listwidget1->addItem("3D Reconstruction");
    listwidget1->addItem("Defect Detection");
    listwidget1->addItem("Robotics Arm Positioning");
    listwidget1->addItem("QR Code Scan");

    splitter->setSizes(QList<int>{100,800});

    setCentralWidget(splitter);

    connect(listwidget1, SIGNAL(itemActivated(QListWidgetItem *)), this ,SLOT(onListClick(QListWidgetItem *)));
}

void MainWindow::onListClick(QListWidgetItem *item)
{
    QString str = item->text();
    qDebug(str.toLatin1());

    if(str == "Face Detection")
    {
        splitter->replaceWidget(1, label);
    }else if(str == "Optical Character Recognization")
    {
        splitter->replaceWidget(1, ocr->getSplitter());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
