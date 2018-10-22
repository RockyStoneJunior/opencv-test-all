#ifndef OCR_H
#define OCR_H

#include <QWidget>
#include <QLabel>
#include <QSplitter>
#include <QTextEdit>

class Ocr : QObject{
    Q_OBJECT

public:
    Ocr();
    ~Ocr();

    QSplitter *getSplitter(){return splitter;}

private:
    QSplitter *splitter;
    QLabel *original_video;
    QLabel *target_video;

    QTextEdit *editor;
};

#endif // OCR_H
