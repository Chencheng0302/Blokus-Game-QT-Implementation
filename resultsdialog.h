#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class resultsDialog;
}

class resultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit resultsDialog(QWidget *parent = nullptr);
    ~resultsDialog();
    void setValues(int Ba,int Bo, int id, QString name);
    void display();
private:
    Ui::resultsDialog *ui;
    int p1Basic,p2Basic,p3Basic,p4Basic,p1Bonus,p2Bonus,p3Bonus,p4Bonus;
};

#endif // RESULTSDIALOG_H
