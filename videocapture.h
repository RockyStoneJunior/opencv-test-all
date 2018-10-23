#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QObject>
#include <opencv2/core/core.hpp>

class VideoCapture : public QObject{
    Q_OBJECT

public:
    VideoCapture();
    VideoCapture(QString video_src);
    ~VideoCapture();

public slots:
    void video_capture();

signals:
    void video_display(cv::Mat frame);
    void video_finished();

private:
    QString _video_src;
};

#endif // VIDEOCAPTURE_H
