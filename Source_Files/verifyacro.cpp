#include "verifyacro.h"
#include "sorter.h"
#include "Acronyms.h"
#include "ui_verifyacro.h"
#include <vector>


VerifyAcro::VerifyAcro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifyAcro)
{
    ui->setupUi(this);
    for(auto arg : Sorter::Class_Known)
    {

    QString name = *arg.name;
    ui->AcroLabel->setText(name);

    }
}

VerifyAcro::~VerifyAcro()
{
    delete ui;
}
