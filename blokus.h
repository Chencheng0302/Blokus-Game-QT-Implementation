#ifndef BLOKUS_H
#define BLOKUS_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <time.h>
#include <QList>
#include <QVector>
#include <QLabel>
#include <QEventLoop>
#include <QTimer>
#include <QMessageBox>

#include "square.h"
#include "player.h"
#include "tile.h"
#include "plan.h"
#include "startdialog.h"
#include "resultsdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Blokus; }
QT_END_NAMESPACE

class Blokus : public QMainWindow
{
    Q_OBJECT

public:
    Blokus(QWidget *parent = nullptr);
    void putTile(square* pos, tile* par, bool undo, bool preview);
    bool isPlaceable(tile *target, int posX, int posY, bool preview);

    void RecordAvailbleSquares(int x,int y, int width, int height, int skipedPlayer);
    void gameProcedure();
    void AI(player* aiPlayer);
    void normalPlacement(tile *pTile, player* player, int mode);
    QVector<square*> getRelativeLocation(int x, int y, tile* target);
    int checkPayoff(int paraX, int paraY, tile* par);
    void checkPayoff(int paraX, int paraY, tile* par, int timesRotated, bool isReversed, QVector<square*> interlopers);
    void previewClear();
    void closeEvent(QCloseEvent *event);
//    void keyPressEvent(QKeyEvent *event);

    //void wheelEvent(QWheelEvent *event);
    //void putTile(int paraX, int paraY, tile* par, bool undo);
    ~Blokus();

protected:
    //void paintEvent(QPaintEvent *event);


public slots:
    void tileReadyToPut(QPointF pos,tile *target);
    void tileHoverInTheBoard(QPointF pos,tile *target, bool inTheBoard);

private slots:
    void on_actionNew_Game_triggered();
    void on_scoreboard_triggered();
    void on_hintBtn_clicked();

private:
    Ui::Blokus *ui;
    int turn,humanID;
    QGraphicsScene *scene=new QGraphicsScene();
    QGraphicsItemGroup *gameboard=new QGraphicsItemGroup();
    //QGraphicsScene *p1Tiles=new QGraphicsScene();
    bool gameover,AvailableToHuman,advancedAI,hint_triggerd,allAiPassedInformed;
    square* board[20][20];
    tile* pHint=nullptr;
    plan *undoPlan = new plan();
    QVector<player*> playerSet;
    QVector<plan*> hint_storage;
    QLabel *statusBarLabel=new QLabel();
    QLabel *additionalInfo= new QLabel();
    QEventLoop *gameLoop= new QEventLoop();
//    QEventLoop *playerLoop=new QEventLoop();
    QEventLoop *playerLoop=nullptr;
//    QEventLoop playerLoop;
//    QEventLoop *aiPlayerLoop=new QEventLoop();
    QEventLoop *aiPlayerLoop=nullptr;
    QMessageBox *status_report=new QMessageBox();
    QTimer *timer=new QTimer();
    QTimer *pTimer=new QTimer();
    QPen pen;

//    void hint(bool triggered);
};
#endif // BLOKUS_H
