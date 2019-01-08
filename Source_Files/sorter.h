#pragma once

#include <QMainWindow>
#include "Acronyms.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include <QString>
#include <QTextFormat>
#include <QFont>

namespace Ui {
class Sorter;
}

class Sorter : public QMainWindow
{
    Q_OBJECT
friend Acronyms;
private:
//defaults
QString defaultfile = ":/Data/Classes.txt";
QString config = "config.dat";
QString Diag_File = "Diag.csv";
int defaultfontsize = 8;

//properties
int OutputFormatBoxIndex = 0;
int SortModeBoxIndex = 0;
bool debug = false;
int windowWidth = 1500;
int windowHeight = 400;
int w_xpos = 0;
int w_ypos = 0;
int fontsize = 8;

public:
QString DataBaseFile = defaultfile;
bool filesave = false;
QString Filehistory;

    explicit Sorter(QWidget *parent = nullptr);
    ~Sorter();

public slots:
    void Load_List();
    void on_SortBtn_clicked();
    void UnkClassPhrase(QString arg, QString &UnkownList);
    void ClassPhrase(QStringList &arg, QString &printList);
    void UnknownLoop (QStringList CapList, QString &UnkownList);
    QString print (class Acronyms a);
    bool SingleCase(QString arg, QString &input);
    bool MultiCase(QString arg, QString &input);
    void Save_Config();

public:
    Ui::Sorter *ui;



private slots:
    void Load_Config();
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
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_font_size_valueChanged(int arg1);
    void on_actionRun_Logic_Diagnostic_triggered();
    void Logic_Diagnostic();
};

