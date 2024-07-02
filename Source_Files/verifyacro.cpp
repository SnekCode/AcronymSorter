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
    std::vector <QLabel*> label;
    for (size_t i {0}; i < Sorter::Class_all.size(); i++)
    {
    QString name = *Sorter::Class_all[i]->name;
    QString def1 = *Sorter::Class_all[i]->def1;
    QString def2 = *Sorter::Class_all[i]->def2;
    QString def3 = *Sorter::Class_all[i]->def3;
    QString def4 = *Sorter::Class_all[i]->def4;
    QString def5 = *Sorter::Class_all[i]->def5;
    QString def6 = *Sorter::Class_all[i]->def6;
    QString def7 = *Sorter::Class_all[i]->def7;

    QLabel *lb = new QLabel;
    label.push_back(lb);

    //label[i]->setText(QString::number(i));
    QDialog::layout()->addWidget(label[i]);
    label[i]->show();

    //ui->AcroEdit->hide();
    ui->lb_def1->hide();
    ui->lb_def1->setText(def1);

        QString List{};

    ui->AcroLabel->setText(name);

    if (def7 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->addItem(def7);
        ui->AcroDef->addItem(def6);
        ui->AcroDef->addItem(def5);
        ui->AcroDef->addItem(def4);
        ui->AcroDef->addItem(def3);
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
        ui->AcroLabel->setText(name);

    }

    else if (def6 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->addItem(def6);
        ui->AcroDef->addItem(def5);
        ui->AcroDef->addItem(def4);
        ui->AcroDef->addItem(def3);
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else if (def5 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->addItem(def5);
        ui->AcroDef->addItem(def4);
        ui->AcroDef->addItem(def3);
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else if (def4 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->addItem(def4);
        ui->AcroDef->addItem(def3);
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else if (def3 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->addItem(def3);
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else if (def2 != "Nodef")
    {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->lb_note->setText("The Acronym " + name + " has multible definitions. Please choose below: ");
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else if (def1 == "???")
    {
            Sorter::Class_all[Sorter::iteration]->set_num(2);
            ui->AcroDef->hide();
            ui->AcroEdit->show();


     }
    else {
        Sorter::Class_all[Sorter::iteration]->set_num(1);
        ui->AcroDef->hide();
        ui->AcroLabel->setText(name + " (" + def1 + ")");

        ui->lb_note->setText("The Acronym: " + name + " has one definition. Press OK to countinue");


    }

}
    return;
}

VerifyAcro::~VerifyAcro()
{
    delete ui;
}

void VerifyAcro::on_pushButton_clicked()
{

}


// if a User defined database was to be made this is the section to call that function.
void VerifyAcro::on_buttonBox_accepted()
{
    if(ui->AcroDef->isVisible() && ui->AcroEdit->text().isEmpty())
    {
    QString Selection = ui->AcroDef->currentText();
    Sorter::Class_all[Sorter::iteration]->set_def(Selection);

    }
    else if (!ui->AcroEdit->text().isEmpty())
    {
        QString Selection = ui->AcroEdit->text();
        Sorter::Class_all[Sorter::iteration]->set_def(Selection);
        Sorter::Class_all[Sorter::iteration]->set_sourceList("user");

    }
    else {
            if(ui->AcroEdit->text().isEmpty() && ui->lb_def1->text() == "???")
         Sorter::Class_all[Sorter::iteration]->set_def("");
            else
            Sorter::Class_all[Sorter::iteration]->set_def(ui->lb_def1->text());
    }

    this->close();
}
