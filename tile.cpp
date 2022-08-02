#include "tile.h"

tile::tile(QObject *parent) : QObject(parent)
{

}
tile::tile(int ID, int givenOwner)
{
    id=ID;
    owner = givenOwner;
    x = 0;
    y = 0;
    gx=0;
    gy=0;
    numOfSquares = 0;
    timesHaveBeenRotated=0;
    timesHaveBeenReversed=0;
    isPlaced = false;
    pen.setWidth(1);
    setAcceptHoverEvents(true);
    //setAcceptDrops(true);
//    this->setFlag(ItemIsMovable,true);
//    this->setEnabled(true);
//    this->setAcceptDrops(true);
    //this->setAcceptHoverEvents(true);
    //this->setCursor(Qt::SizeAllCursor);
    //this->setFlags(QGraphicsItem::ItemIsMovable);
    //setFlag(ItemIsSelectable,false);
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton|Qt::MiddleButton);
    //setFlag(ItemIsMovable);
    switch (id)
    {
    case 1://single sqaure
        numOfSquares = 1;
        x = 1;
        y = 1;
        symmetry = true;
        shape[0][0] = 1;
        break;
    case 2://2 units line
        numOfSquares = 2;
        x = 2;
        y = 1;
        symmetry = true;
        memset(shape[0],1,2);
        break;
    case 3://3 units line
        numOfSquares = 3;
        x = 3;
        y = 1;
        symmetry = true;
        memset(shape[0], 1, 3);
        break;
    case 4://right angle
        numOfSquares = 3;
        x = 2;
        y = 2;
        symmetry = true;
        shape[0][0] = 1;
        memset(shape[1], 1, 2);
        break;
    case 5://2 unit square
        numOfSquares = 4;
        x = 2;
        y = 2;
        symmetry = true;
        memset(shape[0],1,2);
        memset(shape[1], 1, 2);
        break;
    case 6://4 units line
        numOfSquares = 4;
        x = 4;
        y = 1;
        symmetry = true;
        memset(shape[0], 1, 4);
        break;
    case 7://long right angle
        numOfSquares = 4;
        x = 3;
        y = 2;
        symmetry = false;
        shape[0][0] =  1 ;
        memset(shape[1], 1, 3*sizeof(bool));
        break;
    case 8://fort
        numOfSquares = 4;
        x = 3;
        y = 2;
        symmetry = true;
        memset(shape[1], 1, 3);
        shape[0][1] = 1;
        break;
    case 9:	//step	**
            //		 **
        numOfSquares = 4;
        x = 3;
        y = 2;
        symmetry = false;
        memset(shape[0], 1, 2);
        shape[1][1] = 1;
        shape[1][2] = 1;
        break;
    case 10://5 units line
        numOfSquares = 5;
        x = 5;
        y = 1;
        symmetry = true;
        memset(shape[0], 1, 5);
        break;
    case 11://plus
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = true;
        memset(shape[1], 1, 3);
        shape[0][1] = 1;
        shape[2][1] = 1;
        break;
    case 12://long right angle	*
            //					****
        numOfSquares = 5;
        x = 4;
        y = 2;
        symmetry = false;
        shape[0][0] = 1;
        memset(shape[1], 1, 4);
        break;
    case 13://big right angle	*
            //					*
            //					***
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = false;
        memset(shape[2], 1, 3);
        shape[0][0] = 1;
        shape[1][0] = 1;
        break;
    case 14://long fort	 *
            //			****
        numOfSquares = 5;
        x = 4;
        y = 2;
        symmetry = false;
        memset(shape[1], 1, 4);
        shape[0][1] = 1;
        break;
    case 15://fortress	* *
            //			***
        numOfSquares = 5;
        x = 3;
        y = 2;
        symmetry = false;
        shape[0][0] = 1;
        shape[0][2] = 1;
        memset(shape[1], 1, 3);
        break;
    case 16://lie down six	**
            //				***
        numOfSquares = 5;
        x = 3;
        y = 2;
        symmetry = false;
        memset(shape[0], 1, 2);
        memset(shape[1], 1, 3);
        break;
    case 17://high fort		*
            //				*
            //			   ***
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = true;
        memset(shape[2], 1, 3);
        shape[0][1] = 1;
        shape[1][1] = 1;
        break;
    case 18://high step		**
            //				 *
            //				 **
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = false;
        memset(shape[0], 1, 2);
        shape[1][1] = 1;
        shape[2][1] = 1;
        shape[2][2] = 1;
        break;
    case 19://long step		**
            //				 ***
        numOfSquares = 5;
        x = 4;
        y = 2;
        symmetry = false;
        memset(shape[0], 1, 2);
        shape[1][1] = 1;
        shape[1][2] = 1;
        shape[1][3] = 1;
        break;
    case 20://big step		*
            //				**
            //				 **
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = false;
        memset(shape[1], 1, 2);
        shape[0][0] = 1;
        shape[2][1] = 1;
        shape[2][2] = 1;
        break;
    case 21://broken plus		*
            //					***
            //					 *
        numOfSquares = 5;
        x = 3;
        y = 3;
        symmetry = false;
        memset(shape[1], 1, 3);
        shape[0][0] = 1;
        shape[2][1] = 1;
        break;
    default:
        qDebug() << "Parameters Error in Tile initialization.";
        break;
    }
}

tile::~tile()
{
    delete origi_tile_position;
    delete brush;
}

QRectF tile::boundingRect() const
{
    return QRectF(0,0,x*10,y*10);
}

void tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //painter->drawRect(boundingRect());
    switch (owner) {
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
    }
    painter->setPen(pen);
    painter->setBrush(*brush);
    QVector<int> tile=getTile();
    int count=0,gxStorage=gx, gyStorage=gy;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {

            if (count == numOfSquares)break;
            else if (tile.front() != 0)
            {
                painter->drawRect(gx,gy,10,10);
                count++;
            }
            tile.pop_front();
            gx+=10;
        }
        gx=gxStorage;
        gy+=10;
    }
    gx=gxStorage;
    gy=gyStorage;
    painter->setPen(nomal_pen);
    painter->setBrush(nomalBrush);
}

QVector<int> tile::getTile()
{
    QVector<int> temp;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++) {
            if (shape[i][j] == 1) temp.push_back(owner);
            else temp.push_back(0);
        }
    }
    return temp;
}

void tile::rotate(bool rotateToLeft)
{
    int n = 5, temp = 0,lefttop_index_x,lefttop_index_y;
    if (rotateToLeft) {
        timesHaveBeenRotated++;
//        if(x==5) lefttop_index_x = 4;
//        else lefttop_index_x = n-x;
        lefttop_index_y = 0;
        lefttop_index_x = n-x;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n - i - 1; j++) {
                if (i == 1 && j == 0) continue;
                int temp = shape[i][j];
                shape[i][j] = shape[j][n - 1 - i];
                shape[j][n - 1 - i] = shape[n - 1 - i][n - 1 - j];
                shape[n - 1 - i][n - 1 - j] = shape[n - 1 - j][i];
                shape[n - 1 - j][i] = temp;
            }
        }
    }
    else
    {
        timesHaveBeenRotated--;
        lefttop_index_x = 0;
        lefttop_index_y = n - y;
//        if(y==5) lefttop_index_y = 4;
//        else lefttop_index_y = n - y;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n - i - 1; j++) {
                if (i == 1 && j == 0) continue;
                int temp = shape[i][j];
                shape[i][j] = shape[n - 1 - j][i];
                shape[n - 1 - j][i] = shape[n - 1 - i][n - 1 - j];
                shape[n - 1 - i][n - 1 - j] = shape[j][n - 1 - i];
                shape[j][n - 1 - i] = temp;
            }
        }
    }
    temp = x;
    x = y;
    y = temp;
//if (lefttop_index_x!=0&&lefttop_index_y!=0&&id==10)
    if (!(lefttop_index_x==0&&lefttop_index_y==0))
        replace(lefttop_index_x, lefttop_index_y);
    update();
//    QVector<int> test=getTile();
//    QString te;
//    for(int i=0;i<5;i++)
//        for(int j=0;j<5;j++)
//            te.append(QString("%1").arg(shape[i][j]));
    //    qDebug()<<te;
}

void tile::reverse()
{
    timesHaveBeenReversed++;
//    qDebug()<<getOwner()<<' '<<id<<" reversed";
    int n = 5;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < (n - 1) / 2; j++)
            {
                int temp = shape[i][j];
                shape[i][j] = shape[i][n - 1 - j];
                shape[i][n - 1 - j] = temp;
            }
        }
        replace(0, n-x);
}

void tile::replace(int lefttop_x, int lefttop_y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++) {
                shape[i][j] = shape[lefttop_x + i][lefttop_y + j];
                shape[lefttop_x + i][lefttop_y + j] = false;
        }
    }
}

void tile::setGraphicalX(int x)
{
    gx=x;
}

void tile::setGraphicalY(int y)
{
    gy=y;
}

void tile::placed()
{
    isPlaced=true;
}

void tile::setToTheOriginal()
{
    if(origi_tile_position!=nullptr)
        setPos(*origi_tile_position);
    if(this->scale()!=1)
        setScale(1);
    if(timesHaveBeenRotated!=0){
        int n=timesHaveBeenRotated%4;
        if(n>0){
            for(int i=0;i<n;i++)
                rotate(false);
        }
        else{
            for(int i=0;i>n;i--)
                rotate(true);
        }
//        qDebug()<<getOwner()<<' '<<id<<" setToTheOriginal";
        timesHaveBeenRotated=0;
    }
    if(timesHaveBeenReversed%2==1){
        reverse();
        timesHaveBeenReversed=0;
    }

}

int tile::type() const
{
    return Type;
}


int tile::getX()
{
    return x;
}

int tile::getY()
{
    return y;
}

int tile::getNum()
{
    return numOfSquares;
}

int tile::getID()
{
    return id;
}

int tile::getOwner()
{
    return owner;
}

bool tile::hasBeenPlaced()
{
    return isPlaced;
}

bool tile::getSymmetry()
{
    return symmetry;
}

bool tile::isUnstable()
{
    return (timesHaveBeenReversed!=0||timesHaveBeenRotated!=0);
}

void tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(flags().testFlag(ItemIsSelectable)){
        if(!isPlaced){
            setCursor(Qt::ClosedHandCursor);
            if(event->button()==0x00000001){
                if(!curr_inTheBoard){
                    origi_tile_position=new QPointF(this->pos().x(),this->pos().y());
//                    origi_tile_position->setX(this->pos().x());
//                    origi_tile_position->setY(this->pos().y());
                }
                setSelected(true);
                //qDebug()<<"Selected";
            }
            if(event->button()==0x00000002){
                if(isSelected()){
                    emit mouseStatu(this->pos(),this,false);
                    if(id!=10) reverse();
                    update();
                }
            }
        }
    }
}

void tile::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected()){
        setCursor(Qt::ClosedHandCursor);
        QPointF orig_cursor_position=event->lastScenePos();
        QPointF curr_cursor_position(event->scenePos());

        //setPos(curr_cursor_position);
        //update();

//        if((curr_cursor_position.x()>-5&&curr_cursor_position.x()<610&&curr_cursor_position.y()>-5&&curr_cursor_position.x()<610)){
//            curr_inTheBoard=true;
//        }
//        else
//            curr_inTheBoard=false;
//        if((orig_cursor_position.x()>-5&&orig_cursor_position.x()<610&&orig_cursor_position.y()>-5&&orig_cursor_position.x()<610))
//            orig_inTheBoard=true;
//        else
//            orig_inTheBoard=false;
        if((pos().x()>-5&&pos().x()<610&&pos().y()>-5&&pos().x()<610)){
            curr_inTheBoard=true;
            this->setScale(3);
            emit mouseStatu(this->pos(),this,true);
        }
        else{
            curr_inTheBoard=false;
            this->setScale(1);
            emit mouseStatu(this->pos(),this,false);
        }



//        if(curr_inTheBoard&&!orig_inTheBoard)
//            this->setScale(3);
//        else if(!curr_inTheBoard&&orig_inTheBoard){
//            this->setScale(1);
//        }
//        else if(curr_inTheBoard&&orig_inTheBoard){
//            emit mouseStatu(this->pos(),this,true);
//        }
//        else{
//            emit mouseStatu(this->pos(),this,false);
//        }
        QPointF orig_position=this->pos();
       int updated_x=curr_cursor_position.x()-orig_cursor_position.x()+orig_position.x();
        int updated_y=curr_cursor_position.y()-orig_cursor_position.y()+orig_position.y();
        setPos(updated_x,updated_y);

    }

    //update();
}

void tile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button()==0x00000001){
        if(isSelected()){
            setSelected(false);
            if(curr_inTheBoard){
                qDebug()<<"in the board";
                emit readyToPut(this->pos(),this);
            }
            else{
                qDebug()<<"not in the board";
                emit mouseStatu(this->pos(),this,false);
                //setPos(*origi_tile_position);
                setToTheOriginal();
            }
        }
    }
    setCursor(Qt::ArrowCursor);
}

void tile::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(isSelected()){
        emit mouseStatu(this->pos(),this,false);
        if(event->delta()>0)
            rotate(false);
        else if(event->delta()<0)
            rotate(true);
    }
    //emitSignal();
//    if(curr_inTheBoard&&orig_inTheBoard){
//                emit mouseStatu(this->pos(),this,true);
//            }
//            else{
//                emit mouseStatu(this->pos(),this,false);
//            }
    update();
}

void tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    if(flags().testFlag(ItemIsSelectable)) {
        //qDebug()<<id<<" "<<owner<<' '<<flags();
        setCursor(Qt::OpenHandCursor);
    }
    else{
        setCursor(Qt::ForbiddenCursor);
    }

}

void tile::keyPressEvent(QKeyEvent *event)
{
//    qDebug()<<"trrrr";
//    if(isSelected()){
//        if((event->key()==Qt::Key_W||event->key()==Qt::Key_S)){
//            reverse();
//        }
//        if(event->key()==Qt::Key_A){
//            rotate(true);
//        }
//        if(event->key()==Qt::Key_D){
//            rotate(false);
//        }
//    }
}
