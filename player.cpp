#include "player.h"


player::player(int id, QString name)
{
    playerID = id;
    playerName = name;
    isPassed = false;
    isPerfectlyPlaced = false;
    isHuman=false;
    for (int i = 0; i < 21; i++)
    {
        tileStatus[i] = true;
    }
    switch (playerID)
    {
    case 1:
        parameters.origin_x = 0;
        parameters.origin_y = 0;
        parameters.kx = 1;
        parameters.ky = 1;
        break;
    case 2:
        parameters.origin_x = 0;
        parameters.origin_y = 19;
        parameters.kx = 1;
        parameters.ky = -1;
        break;
    case 3:
        parameters.origin_x = 19;
        parameters.origin_y = 0;
        parameters.kx = -1;
        parameters.ky = 1;
        break;
    case 4:
        parameters.origin_x = 19;
        parameters.origin_y = 19;
        parameters.kx = -1;
        parameters.ky = -1;
        break;
    default:
        break;
    }
}

QVector<square *> player::getAvailableSquares()
{
    return availableSquares;
}

QVector<square *> player::getAvailableSquares(int topleftX, int topleftY, int width, int height)
{
    QVector<square*> squares;
    for (auto it : availableSquares) {
        if ((it->getX() >= topleftX && it->getX() <= topleftX + height) && (it->getY() >= topleftY && it->getY() <= topleftY + width))
            squares.push_back(it);
    }
    return squares;
}

QVector<square *> player::getPredictions()
{
    return predictions;
}

QVector<tile *> player::getRemainingTiles()
{
    return ownTiles;
}

QVector<plan *> player::getPlans()
{
    return plans;
}

tile *player::getTile(int id)
{
    int diff=0;
    for(int i=id-1;i>=0;i--){
        if(!tileStatus[i]){
            diff++;
        }
    }
    return ownTiles.at(id-diff);
}

void player::setAvailableSquare(square *target)
{
    availableSquares.push_back(target);
    if (availableSquares.size() > 1) {
        for (int i = 0; i < availableSquares.size(); i++) {
            switch (playerID)
            {
            case 1:
                if (availableSquares[i]->getX() > availableSquares.back()->getX() && availableSquares[i]->getY() > availableSquares.back()->getY()) {
                    availableSquares.push_back(availableSquares[i]);
                    availableSquares.erase(availableSquares.begin()+i);
                }
                break;
            case 2:
                if (availableSquares[i]->getX() < availableSquares.back()->getX() && availableSquares[i]->getY() > availableSquares.back()->getY()) {
                    availableSquares.push_back(availableSquares[i]);
                    availableSquares.erase(availableSquares.begin() + i);
                }
                break;
            case 3:
                if (availableSquares[i]->getX() > availableSquares.back()->getX() && availableSquares[i]->getY() < availableSquares.back()->getY()) {
                    availableSquares.push_back(availableSquares[i]);
                    availableSquares.erase(availableSquares.begin() + i);
                }
                break;
            case 4:
                if (availableSquares[i]->getX() < availableSquares.back()->getX() && availableSquares[i]->getY() < availableSquares.back()->getY()) {
                    availableSquares.push_back(availableSquares[i]);
                    availableSquares.erase(availableSquares.begin() + i);
                }
                break;
            default:
                break;
            }
        }
    }
}

void player::cleanSquaresRecord()
{
    availableSquares.clear();
}

void player::cleanPredictions()
{
    predictions.clear();
}

void player::perfectlyPlaced()
{
    isPerfectlyPlaced=true;
}

void player::passed()
{
    isPassed=true;
}

void player::push_back(tile *target)
{
    ownTiles.push_back(target);
}

void player::setHuman()
{
    isHuman=true;
}

void player::setLabel(QLabel *label)
{
    ownLabel=label;
}

void player::setRect(QGraphicsRectItem *rect)
{
    ownRect=rect;
}

void player::putTile(tile* target)
{
//    if(isHuman){
//        int diff=0;
//        for(int i=pos;i>0;i--){
//            if(!tileStatus[i]){
//                diff++;
//            }
//        }
//        ownTiles.erase(ownTiles.begin()+pos-diff);
//    }
//    else{
//        ownTiles.erase(ownTiles.begin()+pos);
//    }
//    tileStatus[pos]=false;
    int id=target->getID(),index=0;
    for (int i = 0; i < ownTiles.size(); i++) {
        if (ownTiles.at(i)->getID() == id) {
            index = i;
        }
    }
    target->placed();
    tileStatus[index] = false;
    ownTiles.erase(ownTiles.begin() + index);

}

void player::addPlan(plan *givenPlan)
{
    plans.push_back(givenPlan);
}

void player::clearPlans()
{
    plans.clear();
}

void player::setTilesSelectable(bool isSelectable)
{
    for(auto it:ownTiles)
        it->setFlag(QGraphicsItem::ItemIsSelectable,isSelectable);
}

void player::addPrediction(square *pos)
{
    predictions.push_back(pos);
}

bool player::isHumanPlayer()
{
    return isHuman;
}

bool player::hasBeenPassed()
{
    return isPassed;
}

bool player::isPefectlyPlaced()
{
    return isPerfectlyPlaced;
}

QString player::getName()
{
    return playerName;
}

QLabel* player::getLabel()
{
    return ownLabel;
}

QGraphicsRectItem *player::getRect()
{
    return ownRect;
}

int player::getID()
{
    return playerID;
}

int player::getNumOfRemainingTiles()
{
    return ownTiles.size();
}

dataset player::getParameters()
{
    return parameters;
}
