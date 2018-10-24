#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoCapture : public QObject{
    Q_OBJECT

public:
    VideoCapture();
    VideoCapture(QString video_src);
    ~VideoCapture();

    void change_video_source(QString src);
    void pause();
    void resume();


public slots:
    void video_capture_run();

signals:
    void video_display(cv::Mat frame);
    void video_finished();

private:
    QString _video_src;
    cv::VideoCapture cap;

    QMutex sync;
    QWaitCondition pauseCond;
    bool _pause;
};

#endif // VIDEOCAPTURE_H
