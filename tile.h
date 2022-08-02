#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <cstring>
#include <QVector>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPointF>
#include <QCursor>
#include <QString>
#include <QKeyEvent>

class tile : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum {Type = UserType+2};
    explicit tile(QObject *parent = nullptr);
    tile(int ID, int givenOwner);
    ~tile();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVector<int> getTile();
    void rotate(bool rotateToLeft);
    void reverse();
    void replace(int lefttop_x,int lefttop_y);
    void setGraphicalX(int x);
    void setGraphicalY(int y);
    void placed();
    void setToTheOriginal();
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    //void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    int type() const override;
    int getX();
    int getY();
    int getNum();
    int getID();
    int getOwner();
    bool hasBeenPlaced();
    bool getSymmetry();
    bool isUnstable();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    int id, numOfSquares, x, y, owner,gx,gy, timesHaveBeenRotated, timesHaveBeenReversed;
    bool symmetry, isPlaced;
    bool curr_inTheBoard=false;
    bool shape[5][5] = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
    QBrush *brush = new QBrush(QColor(0xFF,0xFF,0xFF),Qt::SolidPattern);
    QPen pen;
    QPen nomal_pen;
    QBrush nomalBrush;
    QPointF *origi_tile_position =nullptr;
signals:
    void readyToPut(QPointF target, tile *selectedTile);
    void mouseStatu(QPointF target, tile *selectedTile, bool inTheBoard);
};

#endif // TILE_H
