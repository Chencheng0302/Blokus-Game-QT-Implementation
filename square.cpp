#include "square.h"

square::square(int givenX, int givenY)
{
    x=givenX;
    y=givenY;
    owner=0;
    occupier=0;
    size=30;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(1);
}

square::square(int givenX, int givenY, qreal givenSize)
{
    x=givenX;
    y=givenY;
    owner=0;
    occupier=0;
    size=givenSize;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(1);
}

QRectF square::boundingRect() const
{
    return QRectF (y*size,x*size,size,size);
}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    pen.setWidthF(1.5);
    switch (owner) {
        case 0:
        brush->setColor(QColor(0xFF,0xFF,0xFF));
        pen.setWidth(1);
        break;
        case 1:
        brush->setColor(QColor(0x4E,0xC0,0xFC));
        break;
        case 2:
        brush->setColor(QColor(0xFF,0xF1,0x66));
        break;
        case 3:
        brush->setColor(QColor(0xFF,0x64,0x51));
        break;
        case 4:
        brush->setColor(QColor(0x57,0xD9,0x48));
        break;
        case 5:
        brush->setColor(QColor(0x97,0xCB,0xFF));
        break;
        case 6:
        brush->setColor(QColor(0xFF,0xFF,0xAA));
        break;
        case 7:
        brush->setColor(QColor(0xFF,0x75,0x75));
        break;
        case 8:
        brush->setColor(QColor(0x93,0xFF,0x93));
        break;
        case 9:
        brush->setColor(QColor(0x00,0x00,0x00));
        break;
    }
    painter->setPen(pen);
    painter->setBrush(*brush);
    painter->drawRect(boundingRect());
}

void square::setTile(tile *target)
{
    owner = target->getOwner();
    occupier = target->getID();
}

void square::setOwner(int givenOwner)
{
    owner=givenOwner;
}

void square::setOccupier(int givenOccupier)
{
    occupier=givenOccupier;
}

bool square::equals(square *target)
{
    if(x=target->getX()&&y==target->getY())
        return true;
    return false;
}

int square::type() const
{
    return Type;
}

int square::getX()
{
    return x;
}

int square::getY()
{
    return y;
}

int square::getOwner()
{
    return owner;
}

int square::getOccupier()
{
    return occupier;
}
