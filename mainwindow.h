#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSplitter>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QPushButton>

#include "ocr.h"
#include "houghtransformation.h"

namespace Ui {
class MyMainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onListClick(QListWidgetItem *item);

private:
    Ui::MyMainWindow *ui;

    QSplitter *splitter;
    QLabel *label;
    QPushButton *button;

    Ocr *ocr;
    HoughTransformation *hough;
};

#endif // MAINWINDOW_H
