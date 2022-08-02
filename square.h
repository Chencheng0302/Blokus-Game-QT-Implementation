#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>


#include "tile.h"
class square : public QGraphicsItem
{
private:
    int x,y,owner,occupier, size;
    QPen pen;
    QBrush *brush = new QBrush(QColor(0xFF,0xFF,0xFF),Qt::SolidPattern);

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
public:
    enum{ Type = UserType+1};
    //square();
    square(int givenX, int givenY);
    square(int givenX, int givenY, qreal size);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setTile(tile *target);
    void setOwner(int givenOwner);
    void setOccupier(int givenOccupier);
    bool equals(square* target);
    int type() const override;
    int getX();
    int getY();
    int getOwner();
    int getOccupier();

};

#endif // SQUARE_H
