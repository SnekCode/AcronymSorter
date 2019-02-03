#pragma once
#include <algorithm>
#include <QMainWindow>
#include "Acronyms.h"
#include "verifyacro.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include <QString>
#include <QTextFormat>
#include <QFont>
//varibles for handling verification window for Acronyms with more than 1 def.

namespace Ui {
class Sorter;
}

class Sorter : public QMainWindow
{
    Q_OBJECT

private:
//defaults
QString DoDList = ":/Data/Classes.txt";
QString _15WGList = ":/Data/15WingClasses.txt";
QString defaultfile = _15WGList;
QString config = "config.dat";
QString Diag_File = "Diag.csv";
int defaultfontsize = 8;

//properties

bool debug = false;
bool _15WG = true;
bool isDoDList;
bool is15WgList;
bool highlight;
int windowWidth = 1500;
int windowHeight = 400;
int w_xpos = 0;
int w_ypos = 0;
int fontsize = 8;

public:
//Class Varibles
bool repeatedAcronyms = false; //set to true if repeated acronyms are found then notifies user.
QString DataBaseFile = defaultfile;
bool filesave = false;
QString Filehistory;
static std::vector <Acronyms*> Class_all;
// used to save the single charecter test cases
bool isEndofList;
std::vector <QStringList> savedArg;

//For load List and Search_for functions, these will be given vaule from the functions
QString input_qtxt = "";
//Used to store the findings of the REGEX functions
QString KnownList; //used to save printed Known Acronyms
int totalCount{0};
int userDefinedCount{0};
int approvedCount{0};
QString Unknown_txt = "";

static QString list_all_f1;
static QString list_approved_f1;
static QString list_user_defined_f1;
static QString list_all_f2;
static QString list_approved_f2;
static QString list_user_defined_f2;
static QString statusBar;
static int OutputFormatBoxIndex;
static int SortModeBoxIndex;
static size_t iteration;

    explicit Sorter(QWidget *parent = nullptr);
    ~Sorter();

public slots:
    void Load_List();
    void on_SortBtn_clicked();
    void UnkClassPhrase(QString arg);
    void ClassPhrase(QStringList &arg);
    void UnknownLoop (QStringList CapList);
    QString print (class Acronyms a);
    bool RegEx_Search(QString arg, QString &input);
    void Save_Config();
    void AcroVerification(std::vector<Acronyms*> arg);


public:
    Ui::Sorter *ui;



private slots:
    void Load_Config();
    void Search_for(QStringList arg);
    void Find_User_Defined();
    void ClearClassVector(std::vector<Acronyms *> &a);
    void on_OutputFormatBox_currentIndexChanged();
    void on_action_Open_triggered();
    void on_actionExport_triggered();
    void on_actionClear_triggered();
    void on_actionDebug_triggered();
    void on_pushButton_clicked();
    void on_Version_triggered();
    void on_actionExit_triggered();
    void on_actionReset_Window_triggered();
    void on_actionReset_Window_toggled();
    void on_SortModeBox_currentIndexChanged();
    void on_actionRestore_DataBase_File_triggered();
    void on_actionChoose_Custom_DataBase_triggered();
    void on_actionAll_triggered();
    void on_actionRun_Logic_Diagnostic_triggered();
    void Logic_Diagnostic();
    void on_InputBox_textChanged();
    void on__15WGRule_toggled(bool checked);
    void blankHighlight();
    void statusBarUpdate();



    friend class Acronyms;
    friend class VerifyAcro;

};

      /////////////////////////////////////////////
     ///////////////////ARCHIVE//////////////////
    ///////////////////////////////////////////
    //bool SingleCase(QString arg, QString &input);
