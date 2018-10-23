#include "videocapture.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

VideoCapture::VideoCapture()
{
    _video_src = "http://admin:12345@192.168.31.14:8081";
}

VideoCapture::VideoCapture(QString video_src)
{
    _video_src = video_src;
}

VideoCapture::~VideoCapture()
{

}

void VideoCapture::video_capture()
{

    cv::Mat frame;
    cv::VideoCapture cap(_video_src.toStdString());

    for(;;)
    {
        cap >> frame;
        if(frame.empty()) break;

        emit video_display(frame);

        if(cv::waitKey(33) > 0) break;
    }

    emit video_finished();
}
