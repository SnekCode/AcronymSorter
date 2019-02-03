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
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QStandardPaths>

std::vector <Acronyms*> Sorter::Class_all;
QString Sorter::list_approved_f1;
QString Sorter::list_all_f1;
QString Sorter::list_user_defined_f1;
QString Sorter::list_approved_f2;
QString Sorter::list_all_f2;
QString Sorter::list_user_defined_f2;
QString Sorter::statusBar;
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
    ui->dockWidget->hide();
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
    QTextCursor cursor(ui->InputBox->document());
    cursor.clearSelection();


    list_all_f1.clear();
    list_all_f2.clear();
    list_approved_f1.clear();
    list_approved_f2.clear();
    list_user_defined_f1.clear();
    list_user_defined_f2.clear();
    iteration = 0;
    repeatedAcronyms = false;
    input_qtxt = ui->InputBox->toPlainText();
    Unknown_txt = input_qtxt;
    if(input_qtxt.size() == 0)
        return;




    QFile file;



    for(int i{0}; i <= 1; i++)
{
        isDoDList = false;
        is15WgList = false;
        if(i == 0)
        {
            if(_15WG){
                file.setFileName(_15WGList);
                is15WgList = true;
            }
            else{
            file.setFileName(DoDList);
                isDoDList = true;
            }

        }
        if(i == 1)
        {
            if(file.fileName() == _15WGList){
                file.setFileName(DoDList);
                isDoDList = true;
            }
            else {
                file.setFileName(_15WGList);
                is15WgList = true;
            }
        }



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
                       Search_for(arg);
                   }//else
                       //Function call to split up Load list function, called test case; pass arg varible;
                    }//for
                    arg.clear();
                    }//while
                        isEndofList = true;
                        for (auto a : savedArg)
                        {
                            Search_for(a);
                        }
                        savedArg.clear();
                        isEndofList = false;
          file.close();
}//for loop
    Find_User_Defined();
}//Load_List end;

void Sorter::Search_for(QStringList arg)
{

    std::string input_txt = input_qtxt.toStdString();
    QString qtest_case = arg[0];
    std::string test_case = qtest_case.toStdString();
    std::size_t found_pos = input_txt.find(test_case);
    if(test_case.length() == 1 && !isEndofList)
    {
        savedArg.push_back(arg);
        arg.clear();
        return;
    }

    if (found_pos != input_txt.npos)
           {
              if(RegEx_Search(qtest_case, Unknown_txt))
              {
                  ClassPhrase(arg);
                 // Known_count++;
                //  i = 0;
                //  arg.clear();
              }
              arg.clear();
          }
       };

void Sorter::AcroVerification(std::vector <Acronyms*> arg)
{
    size_t total = (arg.size());
    iteration = 0;
    QString test1 = "Nodef";
    QString test2 = "???";

    while (iteration < total)
    {
    if (*arg[iteration]->def1 == test2)
    {
    VerifyAcro verify;
    verify.setModal(true);
    verify.exec();
    }
    else if (*arg[iteration]->def2 != test1)
        {
        VerifyAcro verify;
        verify.setModal(true);
        verify.exec();
        }
        else {
        arg[iteration]->set_def(*arg[iteration]->def1);
    }

            arg[iteration]->set_num(1);
            QString name  = *arg[iteration]->name;
            QString def = arg[iteration]->SelectedDef;
            QString format1 = name + " (" + def +"); ";
            QString format2 = def + " (" + name +"); ";

            arg[iteration]->set_f1(format1);
            arg[iteration]->set_f2(format2);

            iteration++;
        }

}

void Sorter::Find_User_Defined(){


          if(debug)
            {
              qDebug() <<"String Before: " << Unknown_txt;
              qDebug() << "String After: " << input_qtxt;
            }

          QString UnknownList;
          QStringList CapList;
          QRegExp CAPS  ("[A-Z]{2,}(?=\\W)");
          QRegExp CAPS2 ("[A-Z]{2,}(?=$)");


          QStringList patterns {"[A-Z]{2,}(?=\\W)","[A-Z]{2,}(?=$)",
                                "(^|\\s[A-Z](?=\\s|$)", "([A-Z]+[^a-z\\s])+(?=\\s|$)"};

                                /*),"(\\s\\d*([A-Z])(?=\\s)"
                                "(^\\d*([A-Z])(?=\\s)", "(\\s([A-Z])(?=$)"
                                "(\\s\\d*([A-Z])(?=$)","(^\\d*([A-Z])(?=$)"};*/


          {//for some scope
              int count = 0;
          for (auto i{0}; i < patterns.length(); i++)
          {
              QRegularExpression rx(patterns[i]);
              QRegularExpressionMatch match;
              match = rx.match(Unknown_txt);
              while(match.hasMatch())
                  {
                      CapList.push_back(match.captured());
                      //Unknown_txt.remove(match.captured());
                      int start = match.capturedStart();
                      int len = match.capturedLength();
                      Unknown_txt.remove(start, len);
                      match = rx.match(Unknown_txt);
                      count++;
                  }
                  //Unknown_txt.replace(CAPS, " ");
              }//for
          if(count > 1)
              repeatedAcronyms = true;

          UnknownLoop(CapList);
          }//scope

          //Sorts the Class_all into alphabetical order
          std::sort(Class_all.begin(),
                    Class_all.end(),
                    [](const Acronyms* lhs, const Acronyms* rhs)
          {
              return *lhs->name < *rhs->name;
          });


        // set font and size constant: v0.1.3 -UI branch.0 removed user option to control font.
          //BUG Text highlighted when program runs the sort cuases a crash

          //          ui->OutputBox->setFontFamily("Calibri");
          //          ui->OutputBox->setFontPointSize(11);
          //          ui->InputBox->setFontFamily("Calibri");
          //          ui->InputBox->setFontPointSize(11);

        //call to open verifyAcro window allowing user to talior the results and to enter Definitions for the unknown
          _15WG = ui->_15WGRule->isChecked();
          AcroVerification(Class_all);

                totalCount = 0;
                approvedCount = 0;
                userDefinedCount = 0;
          for (size_t i {0}; i < Class_all.size(); i++){

                 list_all_f1.push_back(Class_all[i]->format1);
                 list_all_f2.push_back(Class_all[i]->format2);
                 totalCount++;

             if(!_15WG && Class_all[i]->sourceList == DoDList){
                 list_approved_f1.push_back(Class_all[i]->format1);
                 list_approved_f2.push_back(Class_all[i]->format2);
                 approvedCount++;
            }
             if(_15WG && Class_all[i]->sourceList == DoDList){
                 list_user_defined_f1.push_back(Class_all[i]->format1);
                 list_user_defined_f2.push_back(Class_all[i]->format2);
                 userDefinedCount++;
            }
             if(Class_all[i]->sourceList == "user"){
                 list_user_defined_f1.push_back(Class_all[i]->format1);
                 list_user_defined_f2.push_back(Class_all[i]->format2);
                 userDefinedCount++;
             }


             if(Class_all[i]->sourceList == _15WGList && _15WG){
                 list_approved_f1.push_back(Class_all[i]->format1);
                 list_approved_f2.push_back(Class_all[i]->format2);
                 approvedCount++;
            }
            }

          ClearClassVector(Class_all);

          //final semicolon removal
          list_user_defined_f1.remove((list_user_defined_f1.length()-2),1);
          list_all_f1.remove((list_all_f1.length()-2),1);
          list_approved_f1.remove((list_approved_f1.length()-2),1);
          list_user_defined_f2.remove((list_user_defined_f2.length()-2),1);
          list_all_f2.remove((list_all_f2.length()-2),1);
          list_approved_f2.remove((list_approved_f2.length()-2),1);

          Sorter::SortModeBoxIndex = ui->SortModeBox->currentIndex();
          ui->OutputBox->clear();
          if(OutputFormatBoxIndex == 0){
              if(Sorter::SortModeBoxIndex == 0)
                  ui->OutputBox->setPlainText(list_user_defined_f1);
              if(Sorter::SortModeBoxIndex == 1)
                  ui->OutputBox->setPlainText(list_approved_f1);
              if(Sorter::SortModeBoxIndex == 2)
                  ui->OutputBox->setPlainText(list_all_f1);
            }
          if(OutputFormatBoxIndex == 1){
              if(Sorter::SortModeBoxIndex == 0)
                  ui->OutputBox->setPlainText(list_user_defined_f2);
              if(Sorter::SortModeBoxIndex == 1)
                  ui->OutputBox->setPlainText(list_approved_f2);
              if(Sorter::SortModeBoxIndex == 2)
                  ui->OutputBox->setPlainText(list_all_f2);
          }

          //Controls Notification label;
          //QString countTotal = &"Total: " +  totalCount + " ";

          blankHighlight();

          statusBarUpdate();

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

void Sorter::statusBarUpdate()
{
    QString blank = " Blank definitions found!   ";
    QString repeat = " Duplicate Acronyms found! Please double check your document!   ";
    QString Total = "Total Acronyms used: " + QString::number(totalCount) + "   ";
    QString userdefinedTotal = QString::number(userDefinedCount);
    //ui->statusBar->clearMessage();
    statusBar.clear();
    statusBar.push_back(Total);
    if(repeatedAcronyms)
        statusBar.push_back(repeat);
    if(highlight)
        statusBar.push_back(blank);

    if(userDefinedCount > 5 && _15WG && !repeatedAcronyms && !highlight)
        statusBar.push_back("Document exceeds 15th Wing Acronym rule by: " + QString::number(userDefinedCount - 5) );
    else if (_15WG && !highlight){
        statusBar.push_back("Document passes 15th Wing Acronym rule");
    }

    ui->statusBar->showMessage(statusBar);

}

void Sorter::blankHighlight()
{/////Finds blank user defines and highlights them
    int begin = 0;
    int end = 0;

    QTextCharFormat fmt;
    fmt.setBackground(Qt::yellow);
    QTextCursor cursor(ui->OutputBox->document());
    cursor.setCharFormat(fmt);
    QString string = ui->OutputBox->toPlainText();

    //Example blank ----  HJUI (); RBAA () //       ;       //

    QRegularExpression rx("\\w+ \\(\\)");
    QRegularExpressionMatch match;
    QRegularExpressionMatchIterator itrx = rx.globalMatch(string);
    if(!match.hasMatch())
        highlight = false;


    for(int i{0}; i < string.length(); i++)
    {
        match = rx.match(string);
        if(match.hasMatch()){
            highlight = true;
        begin = match.capturedStart();
        end = match.capturedEnd();
        cursor.beginEditBlock();
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.endEditBlock();
        cursor.setCharFormat(fmt);

        int len = match.capturedLength();
        QString strFill;
        for(int j {0}; j < len; j++)
            strFill.push_back(" ");
        string.replace(begin, len, strFill);
    }
    }




};

void Sorter::ClearClassVector(std::vector<Acronyms *> &a)
{
   // qDebug() << "clear";
    for(size_t i = 0; i < a.size(); i++)
    {
    a[i]->~Acronyms();
    }
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
    Class_all.push_back(acronym);

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

                   if(isDoDList)
                   {
                   acronym->set_sourceList(DoDList);
                   Class_all.push_back(acronym);
                   }
                   if(is15WgList)
                   {
                   acronym->set_sourceList(_15WGList);
                   Class_all.push_back(acronym);
                   }
                   return;
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

bool Sorter::RegEx_Search(QString test_case, QString &Unknown_txt)
{

        QStringList patterns;
        if(test_case.length() > 1) //multi letter test case
        {
             QStringList multi {  "\\s("+  QRegularExpression::escape(test_case) + ")\\s",
                                    "\\s(" + QRegularExpression::escape(test_case) + ")$",
                                    "^("  +  QRegularExpression::escape(test_case) + ")\\s"  ,
                                    "^(" +   QRegularExpression::escape(test_case) + ")$"};
             for(auto a : multi)
                 patterns.push_back(a);
        }

        //  A&P AAA A AAA AA AAAA AAAAAA A AC AA AA AC AAAA CA ACAC ACA CACA 2A 3A
        else{ //single letter test case

            QStringList single {"(\\s)" + QRegularExpression::escape(test_case) + "(\\s|$)",
                                "(\\d)" + QRegularExpression::escape(test_case) + "(\\d|$)",
                                "(^)" + QRegularExpression::escape(test_case) + "(\\s|$)",
                                "(^)" + QRegularExpression::escape(test_case) + "(\\d|$)"};

             for(auto a : single)
                 patterns.push_back(a);
        }

        QString input_box_txt = ui->InputBox->toPlainText();
        QRegularExpression nlrx("\\n");
        QRegularExpressionMatchIterator newline = nlrx.globalMatch(input_box_txt);
        bool patternFound = false;
        int deleteCount = 0;
        int lines = 1;
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
                    deleteCount++;//if this number is more than 1 repeated acro bool is true;
                    i--;
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
            ui->OutputBox->setPlainText(list_user_defined_f1);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(list_approved_f1);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(list_all_f1);
      }
    if(OutputFormatBoxIndex == 1){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(list_user_defined_f2);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(list_approved_f2);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(list_all_f2);
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
            ui->OutputBox->setPlainText(list_user_defined_f1);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(list_approved_f1);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(list_all_f1);
      }
    if(OutputFormatBoxIndex == 1){
        if(Sorter::SortModeBoxIndex == 0)
            ui->OutputBox->setPlainText(list_user_defined_f2);
        if(Sorter::SortModeBoxIndex == 1)
            ui->OutputBox->setPlainText(list_approved_f2);
        if(Sorter::SortModeBoxIndex == 2)
            ui->OutputBox->setPlainText(list_all_f2);
    }
    blankHighlight();
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

void Sorter::on__15WGRule_toggled(bool checked)
{
    if(checked)
    _15WG = true;
    else
    _15WG = false;

}
