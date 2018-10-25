#include "label.h"

#include <QMouseEvent>

Label::Label(QWidget *parent, Qt::WindowFlags f):
    QLabel (parent, f)
{

}

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f):
    QLabel (text, parent, f)
{

}

Label::~Label()
{

}

void Label::mousePressEvent(QMouseEvent *ev)
{
    emit clicked(ev->pos());
}
