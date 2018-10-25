#include <houghtransformation.h>

#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QWindow>
#include <QMouseEvent>
#include <QString>
#include <QDialog>

#include "label.h"

HoughTransformation::HoughTransformation()
{
    QPixmap image("1.png");
    QSize label_size(640, 480);

    Label *label_left = new Label("Test Hough", this);
    label_left->setStyleSheet("border: 1px solid gray");
    label_left->setFixedSize(label_size);
    label_left->setPixmap(image.scaled(label_size, Qt::KeepAspectRatio));
    connect(label_left, SIGNAL(clicked(QPoint)), this, SLOT(open_image_window()));

    Label *label_right = new Label("Test Hough", this);
    label_right->setStyleSheet("border: 1px solid gray");
    label_right->setFixedSize(label_size);
    label_right->setPixmap(image.scaled(label_size, Qt::KeepAspectRatio));

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(label_left);
    mainlayout->addWidget(label_right);
}

HoughTransformation::~HoughTransformation()
{

}

void HoughTransformation::open_image_window()
{
    QPixmap image("1.png");
    Label *label_left = new Label("Test Hough", this);
    label_left->setPixmap(image);

    QDialog *image_window = new QDialog(this);

    QHBoxLayout *mainlayout = new QHBoxLayout(image_window);
    mainlayout->addWidget(label_left);

    image_window->showMaximized();
}
