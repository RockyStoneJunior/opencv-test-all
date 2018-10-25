#ifndef LABEL_H
#define LABEL_H

#include <QObject>
#include <QLabel>
#include <QWidget>

class Label : public QLabel{
    Q_OBJECT

public:
    Label(QWidget *parent = 0, Qt::WindowFlags f = 0);
    Label(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~Label();

protected:
    void mousePressEvent(QMouseEvent *ev);

signals:
    void clicked(QPoint pos);
};

#endif // LABEL_H
