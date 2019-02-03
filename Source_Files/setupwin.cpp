#include "setupwin.h"
#include "ui_setupwin.h"

SetupWin::SetupWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetupWin)
{
    ui->setupUi(this);

}

SetupWin::~SetupWin()
{
    delete ui;
}

