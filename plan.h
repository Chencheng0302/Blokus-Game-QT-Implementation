#ifndef PLAN_H
#define PLAN_H

#include <QObject>
#include "tile.h"
#include "square.h"

class plan: public QObject
{
    Q_OBJECT
public:
    plan();
    plan(square* pos);
    plan(int plan_x, int plan_y, tile* givenTile);
    plan(int plan_x, int plan_y, int givenID,int timesRotated,bool reversed);
    plan(int plan_x,int plan_y,int exp_payoff, tile* givenTile,int timesRotated,bool reversed);
    square* getPosition();
    void setPosition(square* pos);
    void setTile(tile* givenTile);
    void clear();
    void foundSamePlan();
    tile *getTile();
    int getPayoff();
    int getNumOfSamePlan();
    int getTimesOfRotation();
    int getID();
    bool hasBeenReversed();
    bool equaulsTo(plan* thePlan);
private:
    int payoff, numOfSamePlan,timesOfRotation,id;
    tile* pTile;
    square* position=new square(0,0);
    bool isReversed;
};

#endif // PLAN_H
