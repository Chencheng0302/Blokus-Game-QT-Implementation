#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QGraphicsItem>
#include <QPainter>
class playerInterface : public QGraphicsItem
{
public:
    playerInterface(int gx,int gy);
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    int x,y;
};

#endif // PLAYERINTERFACE_H
