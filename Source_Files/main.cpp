#include "sorter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    Sorter w;

    w.show();


    return a.exec();
}
