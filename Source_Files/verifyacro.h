#pragma once
//#include "sorter.h"
#include <QDialog>
#include <vector>

namespace Ui {
class VerifyAcro;
}

class VerifyAcro : public QDialog
{
    Q_OBJECT
public:
    VerifyAcro(QWidget *parent = nullptr);
    ~VerifyAcro();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::VerifyAcro *ui;

    friend class Sorter;
    friend class Acronyms;
};

