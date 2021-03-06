#pragma once
#include <iostream>
#include <string>
#include <QString>

class Acronyms
{
public:
    friend class VerifyAcro;
    QString *name{};
    QString sourceList{};
    QString *def1{};
    QString *def2{};
    QString *def3{};
    QString *def4{};
    QString *def5{};
    QString *def6{};
    QString *def7{};
    QString SelectedDef{};
    QString format1{};
    QString format2{};

    int *def_num{nullptr};
    int *sort_num = nullptr;
    // Constructor will take args with defaults
    Acronyms(QString name, QString def1, QString def2, QString def3, QString def4, QString def5, QString def6, QString def7, int def_num);
    Acronyms(QString name);
    //copy constructor
    Acronyms(const Acronyms &source);
    //move constructor
    //Acronyms(Acronyms &&source);
    ~Acronyms();

    //methods

    int get_num();
    void set_num(int a);
    void set_sourceList(QString l);
    void set_def(QString d);
    void set_f1(QString f);
    void set_f2(QString f);
    QString get_name();
 };







