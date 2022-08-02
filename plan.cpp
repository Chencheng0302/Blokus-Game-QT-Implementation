#include "plan.h"


plan::plan()
{
    position=nullptr;
    payoff=0;
    numOfSamePlan=0;
    isReversed=false;
    timesOfRotation=0;
}

plan::plan(square* pos)
{
    position=pos;
    payoff = 0;
    numOfSamePlan = 0;
    isReversed=false;
    timesOfRotation=0;
}

plan::plan(int plan_x, int plan_y, tile *givenTile)
{
    position=new square(plan_x,plan_y);
    payoff = 0;
    numOfSamePlan = 0;
    pTile = givenTile;
    isReversed=false;
    timesOfRotation=0;
}

plan::plan(int plan_x, int plan_y, int givenID, int timesRotated, bool reversed)
{
    position=new square(plan_x,plan_y);
    timesOfRotation=timesRotated;
    isReversed=reversed;
    id=givenID;
}

plan::plan(int plan_x, int plan_y, int exp_payoff, tile *givenTile,int timesRotated,bool reversed)
{
    position=new square(plan_x,plan_y);
    payoff = exp_payoff;
    numOfSamePlan = 0;
    pTile = givenTile;
    timesOfRotation=timesRotated;
    isReversed=reversed;
}

square* plan::getPosition()
{
    return position;
}

void plan::setPosition(square* pos)
{
    position=pos;
}

void plan::setTile(tile* givenTile)
{
    pTile=givenTile;
}

void plan::clear()
{
    position=nullptr;
}

void plan::foundSamePlan()
{
    numOfSamePlan++;
}

tile *plan::getTile()
{
    return pTile;
}

int plan::getPayoff()
{
    return payoff;
}

int plan::getNumOfSamePlan()
{
    return numOfSamePlan;
}

int plan::getTimesOfRotation()
{
    return timesOfRotation;
}

int plan::getID()
{
    return id;
}

bool plan::hasBeenReversed()
{
    return isReversed;
}

bool plan::equaulsTo(plan *thePlan)
{
    return position->getX()==thePlan->getPosition()->getX()&&position->getY()==thePlan->getPosition()->getY();
}
