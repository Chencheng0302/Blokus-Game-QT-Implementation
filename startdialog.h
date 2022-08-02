#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

#include "square.h"
#include "tile.h"

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = nullptr);
    ~startDialog();

    QString playerName;
    int selectedID,difficulty;
private slots:
    void on_buttonBox_accepted();

    void on_blueRadio_clicked();

    void on_yellowRadio_clicked();

    void on_redRadio_clicked();

    void on_greenRadio_clicked();

    void on_buttonBox_rejected();

    //void on_playerNameEdit_textChanged(const QString &arg1);

    void on_easy_clicked();

    void on_normal_clicked();

private:
    void clear();
    void dataValidation();
    Ui::startDialog *ui;
    QGraphicsScene *scene = new QGraphicsScene();
    square* board[8][8];
    QGraphicsItemGroup *previewBoard=new QGraphicsItemGroup();
    QMessageBox *status_report=new QMessageBox();
};

#endif // STARTDIALOG_H
