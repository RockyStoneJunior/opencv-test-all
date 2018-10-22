#include <ocr.h>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>

Ocr::Ocr()
{
    splitter = new QSplitter(Qt::Vertical);
    original_video = new QLabel("Original Video");
    target_video = new QLabel("Target Video");

    original_video->setFixedWidth(640);
    original_video->setFixedHeight(480);

    target_video->setFixedWidth(640);
    target_video->setFixedHeight(480);

    //QGroupBox *group = new QGroupBox;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(original_video);
    layout->addWidget(new QPushButton("Click"));
    layout->addWidget(target_video);

    QGroupBox *group = new QGroupBox;
    group->setLayout(layout);

    editor = new QTextEdit;

    splitter->addWidget(group);
    splitter->addWidget(editor);
}

Ocr::~Ocr()
{

}
