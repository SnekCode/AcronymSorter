#include <iostream>
#include "Acronyms.h"
#include "sorter.h"
#include <vector>
#include <string>
#include <fstream>


void Sorter::Load_List(QString input)
{

	std::ifstream file;
    file.open("qrc:/data/Classes.txt", std::ios::in);
	if (!file)
	{

        //std::cout << "ERROR - DATA FILE NOT FOUND\n\n";
		return;
	}
	
			
        std::string arg;
        QString arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
		
        while (!file.eof())  // 0.0.2 -  created class build logic.  currently uses .txt file
		{
            std::getline(file, arg, '\t');
            arg1 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg2 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg3 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg4 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg5 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg6 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg7 = QString::fromStdString(arg);
            std::getline(file, arg, '\t');
            arg8 = QString::fromStdString(arg);
            file.ignore();

				{	Acronyms* acronym = new Acronyms(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);  //constructs the objects from the Classes.csv file
					acronym->test_def(input);
					delete acronym;
				}
			

		}//while

}
