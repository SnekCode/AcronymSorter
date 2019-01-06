#pragma once
#include <iostream>
#include <string>
#include <QString>

class Acronyms
{
public:
    QString *name{};
    QString *def1{};
    QString *def2{};
    QString *def3{};
    QString *def4{};
    QString *def5{};
    QString *def6{};
    QString *def7{};  //highest counted number of definitions on JP1-02
    int *def_num{nullptr};
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
    QString get_name();
 };







