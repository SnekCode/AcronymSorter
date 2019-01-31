#include "Acronyms.h"
#include "sorter.h"
#include "ui_sorter.h"
#include "changelog.h"
#include "verifyacro.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include <QRegularExpressionMatchIterator>
#include <QStandardPaths>

std::vector <Acronyms*> Sorter::Class_all;
std::vector <Acronyms*> Sorter::Class_Approved;
std::vector <Acronyms*> Sorter::Class_DoD;
std::vector <Acronyms*> Sorter::Class_User_Defined;
QString Sorter::Class_list_approved_f0;
QString Sorter::Class_list_all_f0;
QString Sorter::Class_list_user_defined_f0;
QString Sorter::Class_list_approved_f1;
QString Sorter::Class_list_all_f1;
QString Sorter::Class_list_user_defined_f1;
size_t Sorter::iteration;
int Sorter::SortModeBoxIndex;
int Sorter::OutputFormatBoxIndex;


Sorter::Sorter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sorter)
{
    ui->setupUi(this);
    QIcon *ico = new QIcon();
        ico->addPixmap(QPixmap(":/images/Acronym.png"),QIcon::Active,QIcon::On);
        this->setWindowIcon(*ico);
    Load_Config();
    ui->statusBar->showMessage("Config Init Successful... Previous State Loaded!",4000);


}

Sorter::~Sorter()
{
    if(DataBaseFile != defaultfile && QMessageBox::question(this, "Save Database", "Do You Want to Save User Defined Database Prior to Closing Application?"))
        filesave = true;
    Save_Config();

    delete ui;
}


void Sorter::Load_Config()
{
    int debugload = 0;
    int filesaveload = 0;

    QFile config_file(config);
    if(!config_file.exists()) //Initization of Config file
    {
        Save_Config();
    }
    else {
        config_file.open(QIODevice::ReadWrite | QIODevice::Text);
        while (!config_file.atEnd()) {
                   QTextStream load (&config_file);
                   QString v =nullptr;
                   load >> v >> OutputFormatBoxIndex
                        >> v >> SortModeBoxIndex
                        >> v >> filesaveload
                        >> v >> Filehistory
                        >> v >> debugload
                        >> v >> windowWidth
                        >> v >> windowHeight
                        >> v >> w_xpos
                        >> v >> w_ypos
                       ;



    }//while
       //ui->OutputFormatBox->setCurrentIndex(OutputFormatBoxIndex);
       //ui->SortModeBox->setCurrentIndex(SortModeBoxIndex);
       filesave = filesaveload;
       if(filesave){
       DataBaseFile = Filehistory;
       ui->File_Dir->setText(Filehistory);
       }
       else{ui->File_Dir->setText("Program Default Database");}
       debug = debugload;
       this->setGeometry(w_xpos, w_ypos, windowWidth, windowHeight);



}//else
    if(debug){
        this->setWindowTitle("Sorter :: DEBUG MODE");
        QIcon *ico = new QIcon();
            ico->addPixmap(QPixmap(":/img/debug active.jpg"),QIcon::Active,QIcon::On);
            ui->actionDebug->setIcon(*ico);
        }
       config_file.close();
}//slot

void Sorter::Save_Config(){
    QFile config_file(config);
        config_file.open(QIODevice::ReadWrite | QIODevice::Text);
        qDebug() << config_file.isOpen();
        QTextStream save (&config_file);
        save << "OutputFormatBoxIndex\t" << OutputFormatBoxIndex << "\n"
             << "SorterModeBoxIndex\t"   << SortModeBoxIndex <<"\n"
             << "filesave\t"        << filesave << "\n"
             << "PreviousDatabase\t" << DataBaseFile << "\n"
             << "Debug\t"       << debug << "\n"
             << "WindowWidth\t" << this->width() <<"\n"
             << "windowHeight\t"<< this->height() <<"\n"
             << "windowXpos\t" << this->x() <<"\n"
             << "windowYpos\t" << this->y() << "\n"
             << "FontSize\t"  << fontsize << "\n"
            ;


}

void Sorter::Logic_Diagnostic()
{

    QString Diag_List;
    int databasecount=0;
    QFile file(DataBaseFile);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QMessageBox::warning(this, "Warning", "Data File Not Found");
        return;
    }
    file.close();
    file.open(QIODevice::ReadOnly);
    QTextStream FileStream(&file);
    QStringList arg;
    while (!file.atEnd()) {
         QString line = file.readLine();
         for (QString item : line.split("\t"))
          {
             if (item != "\r\n")
             {
                  arg.push_back(item);
             }//if

              else if (item == "\r\n")
             {
                 QString temp = arg[0];
                 Acronyms* acronym = new Acronyms(temp);

                 Diag_List.append(Sorter::print(*acronym));
                 //if(iteration == 2)
             //        Diag_List.replace(Diag_List.length(),1," ");
                 delete acronym;
                 arg.clear();
                 databasecount++;
             }
        }
    }//while
            ui->InputBox->setPlainText(Diag_List);
            Load_List();
            QString output_str = ui->OutputBox->toPlainText();
            QStringList output_list;
            QString input_str = Diag_List;
            QStringList input_list;
            QString combo_str;
            int count = 0;
                for (auto &&item : output_str.split("\n"))
                {
                    output_list.push_back(item);
                 }

                for (auto &&item : input_str.split("\n"))
                {
                    input_list.push_back(item);
                 }
            combo_str = "======================================\n"
                        ":::::::Diagnostic Logic Results:::::::\n"
                        "======================================\n\n";

            QFile Diag(Diag_File);
                Diag.open(QIODevice::ReadWrite | QIODevice::Text);
                qDebug() << Diag.isOpen();
                QTextStream save (&Diag);

                save << "===========================\n"
                        " Diagnosis Results v1.1.2\n"
                        "===========================\n"
                        " Number of Acronyms: ??\n"
                        " Number Found:       ??\n\n\n\n";

                while (count < output_list.count()){

                    save << input_list.at(count) << ","
                         << output_list.at(count) << ","
                         << endl;
                    count++;
                }
                QString qdatabasecount = QString::fromStdString(std::to_string(databasecount));
                QString qcount = QString::fromStdString(std::to_string(count));
                Diag.close();
                Diag.open(QIODevice::ReadWrite | QIODevice::Text);
                        save << "===========================\n"
                                " Diagnosis Results v1.1.2\n"
                                "===========================\n"
                                " Number of Acronyms: "+ qcount+"\n"
                                " Number Found:       "+ qdatabasecount+ "\n\n\n";
                debug = false;
                QFileInfo dir(Diag);
                QString path = QString::fromStdString(dir.absoluteFilePath().toStdString());
                QString msg = ":::Diagnosic Finished:::\n"
                              " Number of Acronyms: "+ qcount+"\n"
                              " Number of Found:    "+ qdatabasecount+ "\n"
                              " Diagnostic File Located: \n"
                              + path;
                QMessageBox::information(this, "Logic Diagnostic", msg);
}


void Sorter::Load_List(){
    Class_list_all_f0.clear();
    Class_list_all_f1.clear();
    Class_list_approved_f0.clear();
    Class_list_approved_f1.clear();
    Class_list_user_defined_f0.clear();
    Class_list_user_defined_f1.clear();
    iteration = 0;
    input_qtxt = ui->InputBox->toPlainText();
    Unknown_txt = input_qtxt;
    if(input_qtxt.size() == 0)
        return;
    ui->OutputBox->clear();

    //temp bool

    QFile file((_15WG) ? _15WGList : DoDList);
    file.close();


    for(int i{0}; i == 2; i++)
{
        if(i == 1 && file.fileName() ==_15WGList)
        {
            file.close();
            file.setFileName(DoDList);
            _15WG = false;
        }
        else if (i == 1 && file.fileName() == DoDList)
            file.setFileName(_15WGList);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QMessageBox::warning(this, "Warning", "Data File Not Found");
        return;
    }

    if(debug){
       qDebug() << "exists?              " << file.exists();
       qDebug() << "writable?            " << file.isWritable();
       qDebug() << "permissions before?  " << file.permissions();
       qDebug() << "permissions set?     " << file.setPermissions(QFileDevice::WriteOther | QFileDevice::ReadOther);
       qDebug() << "permissions after?   " << file.permissions();
       qDebug() << "Filename:            " << file.fileName();
       qDebug() << "opened?              " << file.open(QIODevice::Append);
       qDebug() << "errors?              " << file.errorString();
       qDebug() << "errnum?              " << file.error();
        }
        file.close();
        file.open(QIODevice::ReadOnly);
        QTextStream FileStream(&file);
        QStringList arg; // var used to store lines from the database file read
        QString demen = "\t";

          while (!file.atEnd()) {
               QString line = file.readLine();
               for (QString item : line.split(demen))
                {
                   if (item != "\r\n")
                   {
                        arg.push_back(item);
                   }//if

                    else if (item == "\r\n")
                   {
                       Search_for(arg, file.fileName());
                   }//else
                       //Function call to split up Load list function, called test case; pass arg varible;
                    }//for
                    arg.clear();
                    }//while
          file.close();
}//for loop
    Find_User_Defined();
}//Load_List end;

void Sorter::Search_for(QStringList arg, QString filename)
{
//          bool is15Wg = true;
//          if(filename == DoDList)
//              is15Wg = false;

          std::string input_txt = input_qtxt.toStdString();
          QString qtest_case = arg[0];
          std::string test_case = qtest_case.toStdString();
          std::size_t found_pos = input_txt.find(test_case);
          std::size_t test_length = test_case.length();
           if (found_pos != input_txt.npos)
           {
           if (test_length == 1)
        {

              if(SingleCase(qtest_case, Unknown_txt))
              {
              ClassPhrase(arg);
              //Known_count++;
             // i = 0;
             // arg.clear();
              }
           }

          if (test_length > 1)
          {

              if(MultiCase(qtest_case, Unknown_txt))
              {
                  ClassPhrase(arg);
                 // Known_count++;
                //  i = 0;
                //  arg.clear();
              }
          }
       }//nested if for searching
                    //   i = 0;
                       arg.clear();
                   }//Search_for end;

          //compare KnownList to Unknown List here

void Sorter::Find_User_Defined(){
          if(debug)
            {
              qDebug() <<"String Before: " << Unknown_txt;
              qDebug() << "String After: " << input_qtxt;
            }

          //Unknown Class Build
          QString UnknownList;
          QStringList CapList;
          std::string Unk_Str_count;
          std::string Known_Str_count;
          QRegExp CAPS  ("[A-Z]{2,}(?=\\W)");
          QRegExp CAPS2 ("[A-Z]{2,}(?=$)");


//R2D2 R2  REGEX Search

          QStringList patterns {"[A-Z]{2,}(?=\\W)","[A-Z]{2,}(?=$)",
                                "(^|\\s[A-Z](?=\\s|$)", "([A-Z]+[^a-z\\s])+(?=\\s|$)"};

                                /*),"(\\s\\d*([A-Z])(?=\\s)"
                                "(^\\d*([A-Z])(?=\\s)", "(\\s([A-Z])(?=$)"
                                "(\\s\\d*([A-Z])(?=$)","(^\\d*([A-Z])(?=$)"};*/


          {//for some scope
          int unk_count=0;

          for (auto i{0}; i < patterns.length(); i++)
          {
              QRegularExpression rx(patterns[i]);
              QRegularExpressionMatch match;
              match = rx.match(Unknown_txt);
              while(match.hasMatch())
                  {
                      CapList.push_back(match.captured());
                      Unknown_txt.remove(match.captured());
                      match = rx.match(Unknown_txt);
                      unk_count++;
                  }
                  //Unknown_txt.replace(CAPS, " ");
              }//for
          Unk_Str_count = std::to_string(unk_count);
          Known_Str_count = std::to_string(Known_count);
          UnknownLoop(CapList);
          }//scope

          //All Classes Alpha Bet Sorter
          size_t total = (Class_User_Defined.size() + Class_Approved.size() + Class_DoD.size());

          if(Class_User_Defined.size() != 0)
          {
          for (size_t i = 0; i < Class_User_Defined.size(); i++)
          {
              Class_all.push_back(Class_User_Defined[i]);
          }
          }
          if(Class_Approved.size() != 0)
          {
          for (size_t i = 0; i < Class_Approved.size(); i++)
          {
              Class_all.push_back(Class_Approved[i]);
          }
          for (size_t i = 0; i < Class_DoD.size(); i++)
          {
              Class_all.push_back(Class_DoD[i]);
          }
          }
          //Sort logic works 0.1.3_uI_update.0
          std::sort(Class_all.begin(),
                    Class_all.end(),
                    [](const Acronyms* lhs, const Acronyms* rhs)
          {
              return *lhs->name < *rhs->name;
          });


        // set font and size constant: v0.1.3 -UI branch.0 removed user option to control font.

          ui->OutputBox->setFontFamily("Calibri");
          ui->OutputBox->setFontPointSize(11);
          ui->InputBox->setFontFamily("Calibri");
          ui->InputBox->setFontPointSize(11);

        //call to open verifyAcro window allowing user to talior the results and to enter Definitions for the unknown acronyms
          QString test1 = "Nodef";
          QString test2 = "???";

          while (iteration < total)
          {
          if (*Class_all[iteration]->def1 == test2)
          {
          VerifyAcro verify;
          verify.setModal(true);
          verify.exec();
          iteration ++;
          continue;
          }
          else if (*Class_all[iteration]->def2 != test1)
              {
              VerifyAcro verify;
              verify.setModal(true);
              verify.exec();
              iteration ++;
              continue;
              }
              else {

                  Class_all[iteration]->set_num(1);
                  QString name  = *Class_all[iteration]->name;
                  QString def1 = *Class_all[iteration]->def1;
                  QString format0 = name + " (" + def1 +"); ";
                  QString format1 = def1 + " (" + name +"); ";


                      Sorter::Class_list_approved_f0.push_back(format0);
                      Sorter::Class_list_all_f0.push_back(format0);

                      Sorter::Class_list_approved_f1.push_back(format1);
                      Sorter::Class_list_all_f1.push_back(format1);

          }
                  iteration++;
              }


          //memory management deleting all saved Acronyms
          ClearClassVector(Class_Approved);
          ClearClassVector(Class_User_Defined);
          ClearClassVector(Class_DoD);
          Class_all.clear();
          //final semicolon removal
          Class_list_user_defined_f0.remove(Class_list_user_defined_f0.length(),1);



          if(OutputFormatBoxIndex == 0){
              if(Sorter::SortModeBoxIndex == 0)
                  ui->OutputBox->setPlainText(Class_list_approved_f0);
              if(Sorter::SortModeBoxIndex == 1)
                  ui->OutputBox->setPlainText(Class_list_all_f0);
              if(Sorter::SortModeBoxIndex == 2)
                  ui->OutputBox->setPlainText(Class_list_user_defined_f0);
            }
          if(OutputFormatBoxIndex == 1){
              if(Sorter::SortModeBoxIndex == 0)
                  ui->OutputBox->setPlainText(Class_list_all_f1);
              if(Sorter::SortModeBoxIndex == 1)
                  ui->OutputBox->setPlainText(Class_list_approved_f1);
              if(Sorter::SortModeBoxIndex == 2)
                  ui->OutputBox->setPlainText(Class_list_user_defined_f1);
          }

          if(repeatedAcronyms)
          {

          }

          //0.1.3 UI Update should obsolete this
       //sorter drop down logic
//          if(ui->SortModeBox->currentText() == "All")
//            {
//              QString all;
//              all.append(KnownList);
//              all.append(UnknownList);
//              ui->OutputBox->setPlainText(all);
//              ui->statusBar->showMessage(
//                          "Search Complete Known Acroynms: "
//                          + QString::fromStdString(Known_Str_count)
//                          + "\t|\tUnknown Acroynms: "
//                          + QString::fromStdString(Unk_Str_count), 5000);
//            }
//          if(ui->SortModeBox->currentText() == "Known")
//              ui->OutputBox->setText(KnownList);

//          if(ui->SortModeBox->currentText() == "Unknown")
//              ui->OutputBox->append(UnknownList);

          return;
   }

void Sorter::ClearClassVector(std::vector <Acronyms*> &a)
{
    for (size_t i = 0; i < a.size(); i++)
    delete a[i];

    a.clear();

}

void Sorter::UnknownLoop (QStringList CapList)
{

    QStringList::iterator it = CapList.begin();
    int i =0;
    while (it != CapList.end())
    {
        QString arg = CapList[i];
        UnkClassPhrase(arg);
        ++i;
        ++it;
    }

}

void Sorter::UnkClassPhrase(QString arg)
{
    Acronyms* acronym = new Acronyms(arg);
    Class_User_Defined.push_back(acronym);

    return;
}

void Sorter::ClassPhrase (QStringList &arg){

                   int def_num{0};
                   if(debug)
                           def_num=7;
                  else
                   {
                   if (arg[7] != "Nodef")
                       def_num = 7;

                   else if (arg[6] != "Nodef")
                       def_num = 6;

                   else if (arg[5] != "Nodef")
                       def_num = 5;

                   else if (arg[4] != "Nodef")
                       def_num = 4;

                   else if (arg[3] != "Nodef")
                       def_num = 3;

                   else if (arg[2] != "Nodef")
                       def_num = 2;

                   else
                       def_num = 1;
                   }

                   Acronyms* acronym = new Acronyms(arg[0],
                                                    arg[1],
                                                    arg[2],
                                                    arg[3],
                                                    arg[4],
                                                    arg[5],
                                                    arg[6],
                                                    arg[7],
                                                    def_num);

                   //ui->OutputBox->appendPlainText("class built");

                    //add global clas variable to 'save' class data for singlecase matches. this can be set based on a global bool set to true indicating singlecase match was found.
                   //if(singlematch)
                   //globalclass= *acronym.
                  if(_15WG)
                    {
                        Class_Approved.push_back(acronym);
                        return;
                    }
                  else
                        Class_DoD.push_back(acronym);

}

QString Sorter::print(class Acronyms a)
{
    if(debug)
    {
     return (*a.name + "\n");
    }

    if(ui->OutputFormatBox->currentIndex() == 0)
    return (*a.name + " (" + *a.def1 + "); ");

    if(ui->OutputFormatBox->currentIndex() == 1)
    return (*a.def1 + " (" + *a.name + "); ");




    //this sequence will be obsolete when the Verify Acro class is complete:  saving for now;
//    if (*a.def_num == 1) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//        return (*a.name + " (" + *a.def1 + "); ");

//        if(ui->OutputFormatBox->currentIndex() == 1)
//        return (*a.def1 + " (" + *a.name + "); ");

//    }if (*a.def_num == 2) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//        return                           (*a.name + " ("
//                                         + *a.def1 + " / "
//                                         + *a.def2 + "); ");

//        if(ui->OutputFormatBox->currentIndex() == 1)
//        return                           (*a.def1 + " / "
//                                         + *a.def2 + " ("
//                                         + *a.name + "); ");

//    }if (*a.def_num == 3) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//          return                         (*a.name
//                                         + " (" + *a.def1
//                                         + " / " + *a.def2
//                                         + " / " + *a.def3
//                                         + "); ");
//        if(ui->OutputFormatBox->currentIndex() == 1)
//        return                           (*a.def1
//                                          + " / " + *a.def2
//                                          + " / " + *a.def3
//                                          + " (" + *a.name + "); ");

//    }if (*a.def_num == 4) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//        return                         (*a.name
//                                       + " (" + *a.def1
//                                       + " / " + *a.def2
//                                       + " / " + *a.def3
//                                       + " / " + *a.def4
//                                       + "); ");

//        if(ui->OutputFormatBox->currentIndex() == 1)
//            return                           (*a.def1
//                                              + " / " + *a.def2
//                                              + " / " + *a.def3
//                                              + " / " + *a.def4
//                                              + " (" + *a.name + "); ");


//    }if (*a.def_num == 5) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//        return (*a.name
//                                       + " (" + *a.def1
//                                       + " / " + *a.def2
//                                       + " / " + *a.def3
//                                       + " / " + *a.def4
//                                       + " / " + *a.def5
//                                       + "); ");
//        if(ui->OutputFormatBox->currentIndex() == 1)
//        return                           (*a.def1
//                                         + " / " + *a.def2
//                                         + " / " + *a.def3
//                                         + " / " + *a.def4
//                                         + " / " + *a.def5
//                                         + " (" + *a.name + "); ");

//    }if (*a.def_num == 6) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//       return (*a.name
//                                       + " (" + *a.def1
//                                       + " / " + *a.def2
//                                       + " / " + *a.def3
//                                       + " / " + *a.def4
//                                       + " / " + *a.def5
//                                       + " / " + *a.def6
//                                       + "); ");
//        if(ui->OutputFormatBox->currentIndex() == 1)
//            return                           (*a.def1
//                                             + " / " + *a.def2
//                                             + " / " + *a.def3
//                                             + " / " + *a.def4
//                                             + " / " + *a.def5
//                                             + " / " + *a.def6
//                                             + " (" + *a.name + "); ");


//    }if (*a.def_num == 7) {
//        if(ui->OutputFormatBox->currentIndex() == 0)
//        return (*a.name
//                                       + " (" + *a.def1
//                                       + " / " + *a.def2
//                                       + " / " + *a.def3
//                                       + " / " + *a.def4
//                                       + " / " + *a.def5
//                                       + " / " + *a.def6
//                                       + " / " +*a.def7
//                                       + "); ");
//        if(ui->OutputFormatBox->currentIndex() == 1)
//            return                           (*a.def1
//                                             + " / " + *a.def2
//                                             + " / " + *a.def3
//                                             + " / " + *a.def4
//                                             + " / " + *a.def5
//                                             + " / " + *a.def6
//                                             + " / " + *a.def7
//                                             + " (" + *a.name + "); ");
//    }

    return "error";
}

bool Sorter::MultiCase(QString test_case, QString &Unknown_txt)
{
       // Multicase REGEX test works 1/1/2019 @ 1730

//        QRegExp PLSpace1   ("(\\s"     + test_case + ")(?=\\s)");   // Space with treiling space //tested
//        QRegExp PLSpace2   ("(\\s\\d*"   + test_case + ")(?=\\s)");   // Space & Digit with trailing space //tested
//        QRegExp PLSpace3   ("(^\\d*"   + test_case + ")(?=\\s)");   // Caret & Digit with trailing space //tested
//        QRegExp PLEndline1 ("(\\s"     + test_case + ")(?=$)");     // Space with trailing endline //tested
//        QRegExp PLEndline2 ("(\\s\\d*" + test_case + ")(?=$)");     // Space & Digit with trailing endline //tested
//        QRegExp PLEndline3 ("(^\\d*" + test_case + ")(?=$)");   // Caret with trailing endline//tested

        // TAC(A)
       QStringList patterns {"\\s("+ QRegularExpression::escape(test_case) + ")\\s", "\\s(" + QRegularExpression::escape(test_case) + ")$",
                             "^("  + QRegularExpression::escape(test_case) + ")\\s"  , "^(" + QRegularExpression::escape(test_case) + ")$"};
        QString input_box_txt = ui->InputBox->toPlainText();
        QRegularExpression nlrx("\\n");
        QRegularExpressionMatchIterator newline = nlrx.globalMatch(input_box_txt);
        bool patternFound = false;
        int deleteCount = 0;
        int lines = 2;
        while(newline.hasNext())
        {
            lines++;
            newline.next();
        }

        for (auto l{0}; l != lines; l++)
        {
        for (auto i{0}; i < patterns.length(); i++)
        {
            QRegularExpression rx(patterns[i]);
              QRegularExpressionMatch match;
            QRegularExpressionMatch match2;
            match = rx.match(input_box_txt);
            match2 = rx.match(Unknown_txt);

            if(test_case == 'F')
            {
                QRegularExpression rx2("R F");
                QRegularExpressionMatch match_F;
                match_F = rx2.match(input_box_txt);
                if (match_F.hasMatch())
                    return true;
                else {
                    return false;
                }
            }

            if(match.hasMatch())  //Need to build logic to check for repeated Acronyms.
            {
                if(match2.hasMatch())
                {
                if(match2.hasMatch()){
                    int j = match2.capturedStart();
                    int n = match2.capturedLength();
                    //j -= n;
                    Unknown_txt.replace(j,n," ");
                    patternFound = true;
                    deleteCount++;
                }


                }//if#2
                }//if#1
        }//for#2
        }//for#1

if(deleteCount > 1)
{
    repeatedAcronyms = true;
}
return patternFound;
}

//        0.1.1 Regex logic for history sake Also look at how bad I am at this haha!!!!
//        if(input_qtxt.contains(PLSpace1))
//        {
//            input.replace(PLSpace1, " ");
//            return true;
//        }
//        if(input_qtxt.contains(PLSpace2))
//        {
//            input.replace(PLSpace2, " ");
//            return true;
//        }

//        if(input_qtxt.contains(PLSpace3))
//        {
//            input.replace(PLSpace3, " ");
//            return true;
//        }

//        if(input_qtxt.contains(PLEndline1))
//        {
//            input.replace(PLEndline1, " ");
//            return true;
//        }

//        if(input_qtxt.contains(PLEndline2))
//        {
//            input.replace(PLEndline2, " ");
//            return true;
//        }

//        if(input_qtxt.contains(PLEndline3))
//        {
//            input.replace(PLEndline3, " ");
//            return true;
//        }


bool Sorter::SingleCase(QString test_case, QString &input){

    QString input_qtxt = ui->InputBox->toPlainText();
    std::string input_txt = input_qtxt.toStdString();
    //QString Symbols = "!@#$%^&*()_+-=:\";'<>?,./{}[]\\|~`";

    //A&P TEST P
//    QStringList patterns {"\\s(" + test_case + ")(?:\\s)",
//                          "\\d+(" + test_case + ")"};

//    for (auto i{0}; i < patterns.length(); i++)
//    {
//        QRegularExpression rx(patterns[i]);
//        QRegularExpressionMatch match;
//        match = rx.match(input_qtxt);
//        if(match.hasMatch())
//            {
//                input.remove(match.captured());
//                return true;
//            }

    //SingleCase RegEx test works 1/1/2019 @2000

    QRegExp PLSpace1   ("(\\s"     + test_case + ")(?=\\s)");   // Space with treiling space //tested
    QRegExp PLSpace2   ("(\\s\\d+"   + test_case + ")(?=\\s)");   // Space & Digit with trailing space //tested
    QRegExp PLSpace3   ("(^\\d+"   + test_case + ")(?=\\s)");   // Caret & Digit with trailing space //tested
    QRegExp PLEndline1 ("(\\s"     + test_case + ")(?=$)");     // Space with trailing endline //tested
    QRegExp PLEndline2 ("(\\s\\$?\\d+" + test_case + ")(?=$)");     // Space & Digit with trailing endline //tested
    QRegExp PLEndline3 ("(^" + test_case + ")(?=\\s)");
    QRegExp PLEndline4 ("(^" + test_case + ")($)");


    //need to a logic that if a singlecase match is made the class will be saved a global boolean set to true and the processing of the acronym section is continued.

    //additional: SingleCase slot's def needs to be updated to allow for a return vaule.  this will offer the option to have more than two possible return values.  currently set to be true or false.  the



    if(input_qtxt.contains(PLSpace1))
    {
        input.replace(PLSpace1, " ");

        return true;
    }

    if (input_qtxt.contains(PLSpace2))
    {
        input.replace(PLSpace2, " ");
        return true;
    }

    if (input_qtxt.contains(PLSpace3))
    {
        input.replace(PLSpace3, " ");
        return true;
    }

    if (input_qtxt.contains(PLEndline1))
    {
        input.replace(PLEndline1, " ");
        return true;
    }

    if (input_qtxt.contains(PLEndline2))
    {
        input.replace(PLEndline2, " ");
        return true;
    }
    if (input_qtxt.contains(PLEndline3))
    {
        input.replace(PLEndline3, " ");
        return true;
    }
    if (input_qtxt.contains(PLEndline4))
    {
        input.replace(PLEndline4, " ");
        return true;
    }

    return false;
}

void Sorter::on_SortBtn_clicked()
{
    Sorter::Load_List();
}

void Sorter::on_OutputFormatBox_currentIndexChanged()
{
    qDebug() << OutputFormatBoxIndex;
    OutputFormatBoxIndex = ui->OutputFormatBox->currentIndex();

    if(OutputFormatBoxIndex == 0){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(Class_list_approved_f0);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(Class_list_all_f0);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(Class_list_user_defined_f0);
      }
    if(OutputFormatBoxIndex == 1){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(Class_list_all_f1);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(Class_list_approved_f1);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(Class_list_user_defined_f1);
    }
}

void Sorter::on_action_Open_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this, "Select File to Open");
    QFile file(Filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
       QMessageBox::warning(this, "Warning", "Unable to Open File");
       return;
    }

    QTextStream in(&file);
    QString Text = in.readAll();
    ui->InputBox->setText(Text);
    file.close();
}

void Sorter::on_actionExport_triggered()
{
    QString path =
              QString("%1/SorterExport.txt").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    QString Filename = QFileDialog::getSaveFileName(this, "Save File as", path, tr("Text Files (*.txt)"));
    QFile file(Filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
       QMessageBox::warning(this, "Warning", "Unable to Save File");
       return;
    }
    QTextStream out (&file);
    QString Text = ui->OutputBox->toPlainText();
    out << Text;
    file.close();

}

void Sorter::on_actionClear_triggered()
{
    ui->InputBox->clear();
    ui->OutputBox->clear();
}

void Sorter::on_actionDebug_triggered()
{
    if(debug == false)
    {
        debug = true;
        this->setWindowTitle("Sorter :: DEBUG MODE");
        QIcon *ico = new QIcon();
            ico->addPixmap(QPixmap(":/images/debug active.jpg"),QIcon::Active,QIcon::On);
            ui->actionDebug->setIcon(*ico);

    }
    else {
        debug = false;
        this->setWindowTitle("Sorter");
                QIcon *ico = new QIcon();
                    ico->addPixmap(QPixmap(":/img/debug.png"),QIcon::Active,QIcon::On);
                    ui->actionDebug->setIcon(*ico);

    }
}

void Sorter::on_pushButton_clicked()
{
    VerifyAcro test;
    test.setModal(true);
    test.exec();
}

void Sorter::on_Version_triggered()
{
    ChangeLog version;
    version.setModal(true);
    version.exec();
}

void Sorter::on_actionExit_triggered()
{
    this->close();
}

void Sorter::on_actionReset_Window_triggered()
{
    this->setGeometry(530,388,1500,400);
}

void Sorter::on_actionReset_Window_toggled()
{
    this->setGeometry(530,388,1500,400);
}

void Sorter::on_SortModeBox_currentIndexChanged()
{
    SortModeBoxIndex = ui->SortModeBox->currentIndex();
    if(debug)
    qDebug() << ui->SortModeBox->currentIndex();

    if(OutputFormatBoxIndex == 0){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(Class_list_approved_f0);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(Class_list_all_f0);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(Class_list_user_defined_f0);
      }
    if(OutputFormatBoxIndex == 1){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(Class_list_approved_f1);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(Class_list_all_f1);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(Class_list_user_defined_f1);
    }
}

void Sorter::on_actionRestore_DataBase_File_triggered()
{
    DataBaseFile = defaultfile;
    filesave = false;
    ui->File_Dir->setText("Program Default DataBase");
}

void Sorter::on_actionChoose_Custom_DataBase_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this, "Select File to Open");
    if(debug)
    qDebug() << Filename;

    DataBaseFile = Filename;
    ui->File_Dir->setText(Filename);
}

void Sorter::on_actionAll_triggered()
{
    ui->OutputFormatBox->setCurrentIndex(0);
    ui->SortModeBox->setCurrentIndex(0);
    debug = false;
    this->setGeometry(530,388,1500,400);
    DataBaseFile = defaultfile;
    filesave = false;
    //ui->font_size->setValue(defaultfontsize);
    ui->File_Dir->setText("Program Default Database");
}



void Sorter::on_actionRun_Logic_Diagnostic_triggered()
{
    debug = true;
    if(QMessageBox::question(this,"Logic Diagnositic Mode",
   "This will run an Automatic Logic check of the database.\n\n "

   "The purpose of this diagnostic is to check RegEx Logic\n "
   "in hopes to identify errors after review of the diagnostic output files. "))
    {
        Logic_Diagnostic();
       // Logic_Diagnostic(2);

                debug = false;
    }
}

void Sorter::on_InputBox_textChanged()
{
   // QString txt = ui->InputBox->toPlainText();
    ui->InputBox->setFontFamily("Calibri");
    ui->InputBox->setFontPointSize(11);
    //ui->InputBox->setPlainText(txt);
}

