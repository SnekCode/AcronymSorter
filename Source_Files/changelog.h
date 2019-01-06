#ifndef CHANGELOG_H
#define CHANGELOG_H

#include <QDialog>

namespace Ui {
class ChangeLog;
}

class ChangeLog : public QDialog
{
    Q_OBJECT

public:
    QString versionTitle = "Sorter ";

    explicit ChangeLog(QWidget *parent = nullptr);
    ~ChangeLog();

private slots:
    void on_pushButton_clicked();
    void Load();

private:
    Ui::ChangeLog *ui;
};

#endif // CHANGELOG_H
