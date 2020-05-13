#include "ssp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ssp w;
    w.show();

    return a.exec();
}
