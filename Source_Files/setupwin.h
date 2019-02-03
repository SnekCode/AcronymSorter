#pragma once
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

public slots:


private:
    Ui::SetupWin *ui;
};

