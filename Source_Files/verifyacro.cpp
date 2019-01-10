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
     QString name =*Sorter::Class_all[Sorter::iteration]->name;
     QString def1 = *Sorter::Class_all[Sorter::iteration]->def1;

     QString def2 = *Sorter::Class_all[Sorter::iteration]->def2;
     QString def3 = *Sorter::Class_all[Sorter::iteration]->def3;
     QString def4 = *Sorter::Class_all[Sorter::iteration]->def4;
     QString def5 = *Sorter::Class_all[Sorter::iteration]->def5;
     QString def6 = *Sorter::Class_all[Sorter::iteration]->def6;
     QString def7 = *Sorter::Class_all[Sorter::iteration]->def7;

     ui->AcroEdit->hide();

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
        ui->AcroDef->addItem(def2);
        ui->AcroDef->addItem(def1);
    }
    else
    {
        if(def1 == "???")
        {
            Sorter::Class_all[Sorter::iteration]->set_num(2);
            ui->AcroDef->hide();
            ui->AcroEdit->show();

        }


    }//else

    return;
}

VerifyAcro::~VerifyAcro()
{
    delete ui;
}

void VerifyAcro::on_pushButton_clicked()
{

}

void VerifyAcro::on_buttonBox_accepted()
{
    if(ui->AcroDef->isVisible())
    {
    QString def1 = ui->AcroDef->currentText();
    QString name = ui->AcroLabel->text();
    QString format0 = name + " (" + def1 +"); ";
    QString format1 = def1 + " (" + name +"); ";

         Sorter::Class_list_all_f0.push_back(format0);

         if(*Sorter::Class_all[Sorter::iteration]->sort_num == 1)
            Sorter::Class_list_Known_f0.push_back(format0);

         if(*Sorter::Class_all[Sorter::iteration]->sort_num == 2)
            Sorter::Class_list_Unk_f0.push_back(format0);


        Sorter::Class_list_all_f1.push_back(format1);

        if(*Sorter::Class_all[Sorter::iteration]->sort_num == 1)
           Sorter::Class_list_Known_f1.push_back(format1);

        if(*Sorter::Class_all[Sorter::iteration]->sort_num == 2)
           Sorter::Class_list_Unk_f1.push_back(format1);

    }

    else {
        QString def1 = ui->AcroEdit->text();
        QString name = ui->AcroLabel->text();
        QString format0 = name + " (" + def1 +"); ";
        QString format1 = def1 + " (" + name +"); ";

            if(Sorter::SortModeBoxIndex == 0)
            Sorter::Class_list_all_f0.push_back(format0);

            if(Sorter::SortModeBoxIndex == 1)
                Sorter::Class_list_Known_f0.push_back(format0);

            if(Sorter::SortModeBoxIndex == 2)
                Sorter::Class_list_Unk_f0.push_back(format0);


            if(Sorter::SortModeBoxIndex == 0)
            Sorter::Class_list_all_f1.push_back(format1);

            if(Sorter::SortModeBoxIndex == 1)
                Sorter::Class_list_Known_f1.push_back(format1);

            if(Sorter::SortModeBoxIndex == 2)
                Sorter::Class_list_Unk_f1.push_back(format1);
    }

    this->close();
}
