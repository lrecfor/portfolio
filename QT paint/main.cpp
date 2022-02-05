#include "mainwindow.h"
#include <QPushButton>
#include <QApplication>
#include <QProgressBar>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    buttons w;
    w.setFixedSize(800, 600);
    w.setWindowTitle("Painter");
    w.show();
    return a.exec();
}
