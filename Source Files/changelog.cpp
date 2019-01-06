#include "changelog.h"
#include "ui_changelog.h"
#include <QString>
#include <QTextStream>
#include <QDebug>

void ChangeLog::Load()
{
    QString v ;
    QFile clog(":/data/ChangeLog.txt");
    clog.open(QIODevice::ReadWrite | QIODevice::Text);
    qDebug() << "exists?              " << clog.exists();
    qDebug() << "writable?            " << clog.isWritable();
    qDebug() << "permissions before?  " << clog.permissions();
    qDebug() << "permissions set?     " << clog.setPermissions(QFileDevice::WriteOther | QFileDevice::ReadOther);
    qDebug() << "permissions after?   " << clog.permissions();
    qDebug() << "Filename:            " << clog.fileName();
    qDebug() << "opened?              " << clog.open(QIODevice::Append);
    qDebug() << "errors?              " << clog.errorString();
    qDebug() << "errnum?              " << clog.error();
    clog.close();
    clog.open(QIODevice::ReadOnly);
    //QTextStream load (&clog);
    while (!clog.atEnd()) {
        QString line = clog.readLine();
        v.append(line);
    }
    ui->plainTextEdit->setPlainText(v);
}

ChangeLog::ChangeLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLog)
{
    ui->setupUi(this);
    this->setWindowTitle(versionTitle);
    Load();

}

ChangeLog::~ChangeLog()
{
    delete ui;
}

void ChangeLog::on_pushButton_clicked()
{
    this->close();
}
