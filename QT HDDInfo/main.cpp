#include "hddinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hddinfo w;
    w.show();

    return a.exec();
}
