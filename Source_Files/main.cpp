#include "sorter.h"
#include "setupwin.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    SetupWin *s = new SetupWin(w);
    s->show();

    return a.exec();
}
