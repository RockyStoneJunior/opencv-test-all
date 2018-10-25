#ifndef HOUGHTRANSFORMATION_H
#define HOUGHTRANSFORMATION_H

#include <QObject>
#include <QWidget>

class HoughTransformation : public QWidget{
    Q_OBJECT

public:
    HoughTransformation();
    ~HoughTransformation();

private slots:
    void open_image_window();

};

#endif // HOUGHTRANSFORMATION_H
