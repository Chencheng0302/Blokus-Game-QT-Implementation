#ifndef PLAYER_H
#define PLAYER_H

#include<QString>
#include<QVector>
#include<QLabel>

#include"square.h"
#include"tile.h"
#include"plan.h"
struct dataset{
    int origin_x;
    int origin_y;
    int kx;
    int ky;
};
class player
{
private:
    QString playerName;
    QLabel *ownLabel=nullptr;
    QGraphicsRectItem *ownRect=nullptr;
    bool isPassed,isPerfectlyPlaced, tileStatus[21],isHuman;
    int playerID;
    QVector<tile*> ownTiles;
    QVector<square*> availableSquares;
    QVector<square*> predictions;
    QVector<plan*> plans;
    dataset parameters;
public:
    player(int id, QString name);
    QVector<square*> getAvailableSquares();
    QVector<square*> getAvailableSquares(int topleftX, int topleftY, int width, int height);
    QVector<square*> getPredictions();
    QVector<tile*> getRemainingTiles();
    QVector<plan*> getPlans();
    tile *getTile(int id);
    void setAvailableSquare(square* target);
    void cleanSquaresRecord();
    void cleanPredictions();
    void perfectlyPlaced();
    void passed();
    void push_back(tile* target);
    void setHuman();
    void setLabel(QLabel* label);
    void setRect(QGraphicsRectItem* rect);
    void putTile(tile* target);
    void addPlan(plan* givenPlan);
    void clearPlans();
    void setTilesSelectable(bool isSelectable);
    void addPrediction(square* pos);
    bool isHumanPlayer();
    bool hasBeenPassed();
    bool isPefectlyPlaced();
    QString getName();
    QLabel *getLabel();
    QGraphicsRectItem *getRect();
    int getID();
    int getNumOfRemainingTiles();
    dataset getParameters();

};

#endif // PLAYER_H
