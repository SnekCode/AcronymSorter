#include <iostream>
#include "Acronyms.h"
#include "sorter.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <cstring>


//constructor
Acronyms::Acronyms(QString n, QString d1, QString d2, QString d3, QString d4, QString d5, QString d6, QString d7, int dnum)
{
    name = new QString;
	*name = n;
    def1 = new QString;
	*def1 = d1;
    def2 = new QString;
	*def2 = d2;
    def3 = new QString;
	*def3 = d3;
    def4 = new QString;
	*def4 = d4;
    def5 = new QString;
	*def5 = d5;
    def6 = new QString;
	*def6 = d6;
    def7 = new QString;
	*def7 = d7;
    def_num = new int;
    *def_num = dnum;
	//std::cout << "Constructed " << *name;
};

//single aurgument constructor
Acronyms::Acronyms(QString n)
{
    name = new QString;
    *name = n;
    def1 = new QString;
    *def1 = "???";
//    def2 = new QString;
//	*def2 = "Nodef";
//    def3 = new QString;
//	*def3 = "Nodef";
//    def4 = new QString;
//	*def4 = "Nodef";
//    def5 = new QString;
//	*def5 = "Nodef";
//    def6 = new QString;
//	*def6 = "Nodef";
//    def7 = new QString;
//	*def7 = "Nodef";
    def_num = new int;
    *def_num = 1;
    //std::cout << "Constructed " << *name;
};


//copy constructor
Acronyms::Acronyms(const Acronyms &source)
    : name(source.name),
      def1(source.def1),
      def2(source.def2),
      def3(source.def3),
      def4(source.def4),
      def5(source.def5),
      def6(source.def6),
      def7(source.def7),
      def_num(source.def_num)
{

}

//move constructor
//Acronyms:: Acronyms(Acronyms &&source)
//	: name( nullptr ), def1(nullptr), def2(nullptr), def3(nullptr), def4(nullptr), def5(nullptr), def6(nullptr), def7(nullptr)
//{
//	name = source.name;
//	def_num = source.def_num;
//	def1 = source.def1;
//	def2 = source.def2;
//	def3 = source.def3;
//	def4 = source.def4;
//	def5 = source.def5;
//	def6 = source.def6;
//	def7 = source.def7;

//source.name = nullptr;
//source.def_num = nullptr;
//source.def1 = nullptr;
//source.def2 = nullptr;
//source.def3 = nullptr;
//source.def4 = nullptr;
//source.def5 = nullptr;
//source.def6 = nullptr;
//source.def7 = nullptr;
//}

Acronyms::~Acronyms()
{
	//std::cout << "deleted " << name;

}

QString Acronyms::get_name()
{
	return *name;
}


