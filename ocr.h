#ifndef OCR_H
#define OCR_H

#include <QWidget>
#include <QLabel>
#include <QSplitter>
#include <QTextEdit>
#include <QLineEdit>
#include <QThread>

#include <opencv2/core/core.hpp>

#include "videocapture.h"

class Ocr : QObject{
    Q_OBJECT

public:
    Ocr();
    ~Ocr();

    QSplitter *getSplitter(){return splitter;}

public slots:
    void video_display(cv::Mat frame);
    void lineedit1_editing_finished();
    void open_video_file();

private:
    QSplitter *splitter;
    QLabel *original_video;
    QLabel *target_video;

    QTextEdit *editor;

    QLineEdit *linedit1;
    QLineEdit *linedit2;
    QLineEdit *linedit3;

    VideoCapture *video_capture;
    QThread *thread;
};

#endif // OCR_H
