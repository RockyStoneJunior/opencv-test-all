#include <ocr.h>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QFormLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QThread>
#include <QFont>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "videocapture.h"

using namespace std;

Ocr::Ocr()
{
    splitter = new QSplitter(Qt::Vertical);
    original_video = new QLabel;
    target_video = new QLabel;

    original_video->setFixedWidth(640);
    original_video->setFixedHeight(480);
    original_video->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //original_video->setStyleSheet("border: 1px solid gray;");

    target_video->setFixedWidth(640);
    target_video->setFixedHeight(480);
    target_video->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //target_video->setStyleSheet("border: 1px solid gray;");

    QPushButton *button = new QPushButton("Start Ocr");
    button->setFixedWidth(60);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(button);
    //button_layout->addSpacing(800);
    //button_layout->setContentsMargins(10,0,800,0);

    QGroupBox *button_group = new QGroupBox;
    button_group->setLayout(button_layout);
    button_group->setFixedHeight(60);

    QHBoxLayout *videolayout = new QHBoxLayout;
    videolayout->addWidget(original_video);
    videolayout->addWidget(target_video);

    QVBoxLayout *radiobuttonlayout = new QVBoxLayout;
    QRadioButton *radiobutton1 = new QRadioButton;
    QRadioButton *radiobutton2 = new QRadioButton;
    QRadioButton *radiobutton3 = new QRadioButton;

    radiobutton1->setAutoExclusive(true);
    radiobutton2->setAutoExclusive(true);

    radiobuttonlayout->addWidget(radiobutton1);
    radiobuttonlayout->addWidget(radiobutton2);
    radiobuttonlayout->addWidget(radiobutton3);

    QButtonGroup *buttongroup = new QButtonGroup;
    buttongroup->addButton(radiobutton1);
    buttongroup->addButton(radiobutton2);
    buttongroup->addButton(radiobutton3);

    QGridLayout *gridlayout = new QGridLayout;
    QLabel *videosource = new QLabel("Video Source");
    videosource->setStyleSheet("color: blue");
    videosource->setAlignment(Qt::AlignCenter);

    gridlayout->addWidget(videosource, 0, 0, 1, 4);
    gridlayout->addWidget(radiobutton1, 1, 0);
    gridlayout->addWidget(radiobutton2, 2, 0);
    gridlayout->addWidget(radiobutton3, 3, 0);
    gridlayout->addWidget(new QLabel("PC Camera"),1,1);
    gridlayout->addWidget(new QLabel("IP Camera"),2,1);
    gridlayout->addWidget(new QLabel("Local File"),3,1);

    linedit1 = new QLineEdit;
    connect(linedit1, SIGNAL(editingFinished()), this, SLOT(lineedit1_editing_finished()));
    linedit2 = new QLineEdit;
    linedit3 = new QLineEdit;
    //linedit1->setFixedWidth(200);
    //linedit2->setFixedWidth(200);
    gridlayout->addWidget(linedit1, 1, 2, 1, 2);
    gridlayout->addWidget(linedit2, 2, 2, 1, 2);
    gridlayout->addWidget(linedit3, 3, 2, 1, 1);
    gridlayout->addWidget(new QPushButton("Open File"), 3, 3, 1, 1);

    //QVBoxLayout *layout = new QVBoxLayout;
    //layout->addLayout(videolayout);
    //layout->addLayout(gridlayout);

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->addWidget(original_video, 0, 0);
    mainlayout->addWidget(target_video, 0, 1);

    QGroupBox *videosourcegroup = new QGroupBox;
    videosourcegroup->setLayout(gridlayout);
    videosourcegroup->setFixedWidth(640);
    videosourcegroup->setFixedHeight(120);

    mainlayout->addWidget(videosourcegroup, 1, 0);
    mainlayout->addWidget(new QGroupBox, 1, 1);


    QGroupBox *group = new QGroupBox;
    group->setLayout(mainlayout);

    editor = new QTextEdit;
    editor->setFont(QFont("Courier", 16));

    splitter->addWidget(group);
    splitter->addWidget(button_group);
    splitter->addWidget(editor);

    QThread *thread = new QThread;
    video_capture = new VideoCapture;
    video_capture->moveToThread(thread);

    connect(thread, SIGNAL(started()), video_capture, SLOT(video_capture()));
    connect(video_capture, SIGNAL(video_display(cv::Mat)), this, SLOT(video_display(cv::Mat)));

    thread->start();
}

void Ocr::video_display(cv::Mat frame)
{
    cv::Mat display_frame, trans_frame;

    //cv::cvtColor(frame, display_frame, CV_BGR2RGB);

//    original_video->setPixmap(QPixmap::fromImage(QImage(display_frame.data,
//    display_frame.cols, display_frame.rows, display_frame.step, QImage::Format_RGB888)));

    cv::cvtColor(frame, trans_frame, CV_BGR2GRAY);
    cv::GaussianBlur(trans_frame, trans_frame, cv::Size(9,9), 3, 3);

    vector<cv::Vec3f> circles;

    cv::HoughCircles(trans_frame, circles, CV_HOUGH_GRADIENT, 1, trans_frame.rows/8, 200, 100, 0, 1000);

    for(size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        cv::circle(frame, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        cv::circle(frame, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }

//    int low_threshold = 60;
//    cv::Canny(frame, trans_frame, low_threshold, low_threshold * 3, 3, false);

    cv::cvtColor(frame, display_frame, CV_BGR2RGB);
    original_video->setPixmap(QPixmap::fromImage(QImage(display_frame.data,
    display_frame.cols, display_frame.rows, display_frame.step, QImage::Format_RGB888)));


    target_video->setPixmap(QPixmap::fromImage(QImage(trans_frame.data,
    trans_frame.cols, trans_frame.rows, trans_frame.step, QImage::Format_Grayscale8)));
}

void Ocr::lineedit1_editing_finished()
{
    QString str = linedit1->text();
    qDebug(str.toLatin1());

    disconnect(video_capture, SIGNAL(video_display(cv::Mat)), this, SLOT(video_display(cv::Mat)));
    video_capture = new VideoCapture(str);
    connect(video_capture, SIGNAL(video_display(cv::Mat)), this, SLOT(video_display(cv::Mat)));
}

Ocr::~Ocr()
{

}
