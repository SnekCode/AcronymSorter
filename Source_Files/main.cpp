#include "sorter.h"
#include "setupwin.h"
#include <QApplication>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    SetupWin *setup = new SetupWin();
    Sorter *sortTool = new Sorter();
    sortTool->show();
    setup->show();

    QObject::connect(setup, SIGNAL(1), sortTool, SLOT(test()));

    return a.exec();
}
