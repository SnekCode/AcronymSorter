#ifndef SETUPWIN_H
#define SETUPWIN_H
#include "sorter.h"
#include <QMainWindow>

namespace Ui {
class SetupWin;
}

class SetupWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetupWin(QWidget *parent = nullptr);
    ~SetupWin();
    friend class Sorter;

private:
    Ui::SetupWin *ui;
};

#endif // SETUPWIN_H
