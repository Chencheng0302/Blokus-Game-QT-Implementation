#include "resultsdialog.h"
#include "ui_resultsdialog.h"

resultsDialog::resultsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultsDialog)
{
    ui->setupUi(this);
    p1Basic=p2Basic=p3Basic=p4Basic=p1Bonus=p2Bonus=p3Bonus=p4Bonus=0;
}

resultsDialog::~resultsDialog()
{
    delete ui;
}

void resultsDialog::setValues(int Ba,int Bo, int id, QString name)
{
    switch (id) {
        case 1:
            p1Basic=Ba;
            p1Bonus=Bo;
            ui->p1->setText(name);
        break;
        case 2:
            p2Basic=Ba;
            p2Bonus=Bo;
            ui->p2->setText(name);
        break;
        case 3:
            p3Basic=Ba;
            p3Bonus=Bo;
            ui->p3->setText(name);
        break;
        case 4:
            p4Basic=Ba;
            p4Bonus=Bo;
            ui->p4->setText(name);
        break;
    }
}

void resultsDialog::display()
{
    ui->p1Basic->display(p1Basic);
    qDebug()<<p2Basic;
    ui->p2Basic->display(p2Basic);
    ui->p3Basic->display(p3Basic);
    ui->p4Basic->display(p4Basic);
    ui->p1Bonus->display(p1Bonus);
    ui->p2Bonus->display(p2Bonus);
    ui->p3Bonus->display(p3Bonus);
    ui->p4Bonus->display(p4Bonus);
    ui->p1Total->display(p1Basic+p1Bonus);
    ui->p2Total->display(p2Basic+p2Bonus);
    ui->p3Total->display(p3Basic+p3Bonus);
    ui->p4Total->display(p4Basic+p4Bonus);
}
