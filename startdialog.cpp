#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    square* unitSquare=nullptr;
    difficulty=selectedID=0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
        {
            unitSquare = new square(i, j,25);
            board[i][j] = unitSquare;
            previewBoard->addToGroup(unitSquare);
        }
    scene->addItem(previewBoard);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    unitSquare=nullptr;
    delete unitSquare;
}

startDialog::~startDialog()
{
    delete ui;
    delete previewBoard;
    delete scene;
}

void startDialog::clear()
{
    board[0][0]->setOwner(0);
    board[5][0]->setOwner(0);
    board[0][5]->setOwner(0);
    board[5][5]->setOwner(0);
}

void startDialog::dataValidation()
{
    if(!ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled()){
        if(selectedID!=0&&difficulty!=0)
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void startDialog::on_buttonBox_accepted()
{
    if(ui->playerNameEdit->displayText().isEmpty()) playerName.append("Human");
    else playerName.append(ui->playerNameEdit->displayText());
}

void startDialog::on_buttonBox_rejected()
{
    selectedID=0;
}

void startDialog::on_blueRadio_clicked()
{
    selectedID=1;
    clear();
    board[0][0]->setOwner(1);
    scene->update();
    dataValidation();
//    if(!ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled())
//    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void startDialog::on_yellowRadio_clicked()
{
    selectedID=2;
    clear();
    board[0][5]->setOwner(2);
    scene->update();
    dataValidation();
}

void startDialog::on_redRadio_clicked()
{
    selectedID=3;
    clear();
    board[5][0]->setOwner(3);
    scene->update();
    dataValidation();
}

void startDialog::on_greenRadio_clicked()
{
    selectedID=4;
    clear();
    board[5][5]->setOwner(4);
    scene->update();
    dataValidation();
}

void startDialog::on_easy_clicked()
{
    difficulty=1;
    dataValidation();
}

void startDialog::on_normal_clicked()
{
    difficulty=2;
    dataValidation();
}
