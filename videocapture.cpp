#include "videocapture.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

VideoCapture::VideoCapture():
    _pause(false)

{
    _video_src = "http://admin:12345@192.168.31.14:8081";
}

VideoCapture::VideoCapture(QString video_src):
    _video_src(video_src),_pause(false)
{
}

VideoCapture::~VideoCapture()
{

}

void VideoCapture::video_capture_run()
{

    cv::Mat frame;
    cap.open(_video_src.toStdString());

    for(;;)
    {
        sync.lock();
        if(_pause)
        {
            pauseCond.wait(&sync);
        }else if(cap.isOpened()){
            cap >> frame;
            if(!frame.empty())
            {
                emit video_display(frame);
                if(cv::waitKey(33) > 0) break;
            }
        }
        sync.unlock();
    }

    emit video_finished();
}

void VideoCapture::pause()
{
    sync.lock();
    _pause = true;
    sync.unlock();
}

void VideoCapture::resume()
{
    sync.lock();
    _pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void VideoCapture::change_video_source(QString src)
{

    pause();

    if(cap.isOpened())
    {
        sync.lock();
        cap.release();
        sync.unlock();
    }

    cap.open(src.toStdString());

    if(cap.isOpened())
        resume();
}
