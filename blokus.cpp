#include "blokus.h"
#include "ui_blokus.h"

Blokus::Blokus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Blokus)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::TabFocus);
    this->setWindowFlag(Qt::Dialog);
    scene->setSceneRect(-175,-50,960,700);
    ui->statusBar->setSizeGripEnabled(false);
    ui->boardView->setScene(scene);
    ui->p1Statu->setVisible(false);
    ui->p2Statu->setVisible(false);
    ui->p3Statu->setVisible(false);
    ui->p4Statu->setVisible(false);
    ui->hintBtn->setVisible(false);
    srand(time(0));
    gameover=false;
    square* unitSquare = nullptr;
    turn=0;
    humanID=0;
    //currPlayer=-1;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            unitSquare = new square(i, j);
            board[i][j] = unitSquare;
            gameboard->addToGroup(unitSquare);
        }
    scene->addItem(gameboard);
    gameboard->setPos(0,0);
    QGraphicsRectItem *rect=new QGraphicsRectItem(QRect(-5,-5,610,610));
    scene->addItem(rect);
    tile* sigleTile= nullptr;

    sigleTile= new tile(14,1);
    sigleTile->rotate(false);
    putTile(board[8][0],sigleTile,false,false);

    sigleTile= new tile(10,1);
    sigleTile->rotate(false);
    putTile(board[7][12],sigleTile,false,false);

    sigleTile= new tile(9,1);
    sigleTile->reverse();
    putTile(board[7][13],sigleTile,false,false);

    sigleTile= new tile(20,1);
    putTile(board[9][13],sigleTile,false,false);

    sigleTile= new tile(18,2);
    putTile(board[7][1],sigleTile,false,false);

    sigleTile= new tile(15,2);
    sigleTile->rotate(false);
    sigleTile->rotate(false);
    putTile(board[9][8],sigleTile,false,false);

    sigleTile= new tile(3,2);
    putTile(board[11][8],sigleTile,false,false);

    sigleTile= new tile(1,3);
    putTile(board[7][0],sigleTile,false,false);

    sigleTile = new tile(12,3);
    sigleTile->rotate(true);
    sigleTile->reverse();
    putTile(board[8][5],sigleTile,false,false);

    sigleTile= new tile(7,4);
    sigleTile->reverse();
    putTile(board[10][1],sigleTile,false,false);
    sigleTile->rotate(false);
    sigleTile->rotate(false);
    putTile(board[7][17],sigleTile,false,false);

    sigleTile= new tile(2,4);
    putTile(board[9][17],sigleTile,false,false);

    sigleTile= new tile(13,4);
    sigleTile->reverse();
    putTile(board[9][17],sigleTile,false,false);
    sigleTile=nullptr;
    ui->statusBar->addWidget(statusBarLabel);
    ui->statusBar->addWidget(additionalInfo);
    statusBarLabel->setText("Ready");
}

void Blokus::gameProcedure()
{
    //on_scoreboard_triggered();
    playerLoop=new QEventLoop();
    aiPlayerLoop=new QEventLoop();
    connect(timer,SIGNAL(timeout()),aiPlayerLoop,SLOT(quit()));
    for(int i=0;i<4;i++){
        //currPlayer=i;
        if (!this->isVisible()) break;
        else if(playerSet.at(i)->hasBeenPassed()) {
            continue;
        }
        else{
            for(auto it: playerSet)
                it->getLabel()->setStyleSheet("*{border:1px outset black;background-color:#FFFFFF;color:black;border-radius:5px;}");

            switch (i) {
                    case 0:
                    ui->player1Label->setStyleSheet("*{border:1px outset white;border-color:black;background-color:#0080FF;color:white;border-radius:5px;}");
                    pen.setColor(QColor(0x4E,0xC0,0xFC));
                    break;
                    case 1:
                    ui->player2Label->setStyleSheet("*{border:1px outset white;border-color:black;background-color:#F9F900;color:black;border-radius:5px;}");
                    pen.setColor(QColor(0xFF,0xF1,0x66));
                    break;
                    case 2:
                    ui->player3Label->setStyleSheet("*{border:1px outset white;border-color:black;background-color:#FF0000;color:white;border-radius:5px;}");
                    pen.setColor(QColor(0xFF,0x64,0x51));
                    break;
                    case 3:
                    ui->player4Label->setStyleSheet("*{border:1px outset white;border-color:black;background-color:#00EC00;color:white;border-radius:5px;}");
                    pen.setColor(QColor(0x57,0xD9,0x48));
                    break;
                }
            pen.setWidth(3);
            playerSet.at(i)->getRect()->setPen(pen);
            statusBarLabel->setText(QString("Current Turn: %1 Current Player: "+playerSet.at(i)->getName()+" Number of Remaining Tiles: %2").arg(turn).arg(playerSet.at(i)->getNumOfRemainingTiles()));
            if(playerSet.at(i)->isHumanPlayer()) {
                playerSet.at(i)->setTilesSelectable(true);
                if(humanID==0) humanID=playerSet.at(i)->getID();
                if(turn>1){
                    ui->hintBtn->setEnabled(true);
                    playerSet.at(i)->clearPlans();
                    AI(playerSet.at(i));
                    hint_storage= playerSet.at(i)->getPlans();
                }

                if(!playerSet.at(i)->hasBeenPassed()) {
//                    if(turn>1){
//                        QVector<plan*> temp=playerSet.at(i)->getPlans();
//                        bool different;
//                        int randNum;
//                        while(hint_storage.size()<3){
//                            randNum=rand()%temp.size();
//                            different=true;
//                            for(auto it:hint_storage){
//                                if(it->equaulsTo(temp.at(randNum))){
//                                    different=false;
//                                }
//                            }
//                            if(different) hint_storage.push_back(temp.at(randNum));
//                        }
//                        hint_system_index=0;
//                    }
                    playerLoop->exec();
                    ui->hintBtn->setEnabled(false);
                }
                else{
                    ui->hintBtn->setVisible(false);
                    status_report->setWindowTitle("Status");
                    status_report->setIcon(QMessageBox::Information);
                    status_report->setText(QString("You are skiped!"));
                    status_report->exec();
                }
            }
            else {
                if(humanID==0){
                    for(auto it:playerSet)
                        if(it->isHumanPlayer())
                            it->setTilesSelectable(false);
                }
                else{
                    playerSet.at(humanID-1)->setTilesSelectable(false);
                    if(!playerSet.at(humanID-1)->hasBeenPassed()){
                        int randNum=rand()%20;
                        timer->start(400+randNum*70);
                        aiPlayerLoop->exec();
                    }
                }
                additionalInfo->setText(playerSet.at(i)->getName()+" is Thinking...");
                AI(playerSet.at(i));
                additionalInfo->clear();
            }

        }
        RecordAvailbleSquares(0, 0, 20, 20,0);
        if(playerSet.at(i)->hasBeenPassed()){
            ui->statusBar->showMessage(QString("Player: "+playerSet.at(i)->getName()+" is Passed"));
            switch (i) {
                case 0:
                if(!ui->p1Statu->isVisible()) ui->p1Statu->setVisible(true);
                break;
                case 1:
                if(!ui->p2Statu->isVisible()) ui->p2Statu->setVisible(true);
                break;
                case 2:
                if(!ui->p3Statu->isVisible()) ui->p3Statu->setVisible(true);
                break;
                case 3:
                if(!ui->p4Statu->isVisible()) ui->p4Statu->setVisible(true);
                break;
            }
        }
        pen.setColor(QColor(0x00,0x00,0x00));
        pen.setWidth(2);
        playerSet.at(i)->getRect()->setPen(pen);

    }
    gameover=true;
    bool allAIPassed=true;
    for(auto it: playerSet){
        if(!it->hasBeenPassed()&&it->getRemainingTiles().size()>0) {
            gameover=false;
            if(!it->isHumanPlayer()) allAIPassed=false;
        }
    }
    if(this->isVisible()){
        if(!gameover){
            turn++;
            previewClear();
            if(allAIPassed&&!allAiPassedInformed){
                status_report->setWindowTitle("Status");
                status_report->setIcon(QMessageBox::Information);
                status_report->setText(QString("All AI are skiped! Keep placing tiles to get a higher score."));
                status_report->exec();
                allAiPassedInformed=true;
            }
            gameProcedure();
        }
        else{
            status_report->setWindowTitle("Status");
            status_report->setIcon(QMessageBox::Information);
            status_report->setText(QString("Game Over! Press OK to view the scoreboard."));
            status_report->exec();
            on_scoreboard_triggered();
        }
    }
    else{
        qDebug()<<"closed";
    }
}

void Blokus::AI(player *pPlayer)
{
    int id = pPlayer->getID(), randNum = 0, x = 0, y = 0, owner=pPlayer->getID();
    QVector<tile*> tiles = pPlayer->getRemainingTiles();
    bool hasBeenPlaced = false;
    tile* pTempTile = nullptr;
    if (turn == 1) {
        while (randNum == 9 || randNum <= 4 || randNum == 10 || randNum < 6)
        {
            randNum = rand() % 20;
        }
        pTempTile = pPlayer->getTile(randNum);
        for (int i = 0; i < 8; i++)
        {
            switch (id)
            {
            case 1:
                x = y = 0;
                break;
            case 2:
                x = 0;
                y = 19 - (pTempTile->getX() - 1);
                break;
            case 3:
                x = 19 - (pTempTile->getY() - 1);
                y = 0;
                break;
            case 4:
                x = 19 - (pTempTile->getY() - 1);
                y = 19 - (pTempTile->getX() - 1);
                break;
            }
            if (isPlaceable(pTempTile,x,y,false)) {
                putTile(board[x][y], pTempTile,false,false);
                pPlayer->putTile(pTempTile);
                pTempTile = nullptr;
                break;
            }
            if (i == 4) pTempTile->reverse();
            pTempTile->rotate(true);
        }
    }
    else{
        QVector<square*> availableSquares = pPlayer->getAvailableSquares();
        if (availableSquares.empty()) {
            pPlayer->passed();
        }
        else {
            if(pPlayer->isHumanPlayer()){
                AvailableToHuman=false;
                        for (int i=tiles.size()-1;i>=0;i-- ) {
                            pTempTile=tiles.at(i);
                            normalPlacement(pTempTile,pPlayer,4);
                            if(AvailableToHuman) break;
                        }
                        if(!AvailableToHuman) pPlayer->passed();
                    }
            else{
                QVector<plan*> plans;
                    //interlopers determination
                    int terrX = availableSquares.back()->getX(), terrY = availableSquares.back()->getY(), minX = 19, minY = 19;
                    bool interlopers[4] = { false };
                    dataset paras = pPlayer->getParameters();
                    pPlayer->clearPlans();
                    pPlayer->cleanPredictions();
                    for (int i = paras.origin_x; i != terrX; i += paras.kx) {
                        for (int j = paras.origin_y; j != terrY; j += paras.ky) {
                            if (board[i][j]->getOwner() != owner && board[i][j]->getOwner() != 0) {
                                interlopers[board[i][j]->getOwner() - 1] = true;
                                if (board[i][j]->getX() < minX) minX = board[i][j]->getX();
                                if (board[i][j]->getY() < minY) minY = board[i][j]->getY();
                            }
                        }
                    }
                    x = fmin(paras.origin_x, terrX);
                    y = fmin(paras.origin_y, terrY);
                    QVector<square*> requiredIndex;
                    for (int i = 0; i < 4;i++) {
                        if (interlopers[i]) {
                            requiredIndex = playerSet.at(i)->getAvailableSquares(x,y,fabs(paras.origin_y-terrY),fabs(paras.origin_x - terrX));
                            for (auto it : requiredIndex) {
                                pPlayer->addPrediction(it);
                            }
                        }
                    }
                    if (pPlayer->getPredictions().empty()&&advancedAI) {
                            for (int i = 0; i < 4; i++) {
                                if (i == id - 1)continue;
                                requiredIndex = playerSet.at(i)->getAvailableSquares();
                                for (auto it : requiredIndex) {
                                    pPlayer->addPrediction(it);
                                }
                            }
                    }
                    if(!pPlayer->getPredictions().empty()){
                        for (int i = tiles.size() - 1; i >= 0; i--) {
                            pTempTile = pPlayer->getTile(i);
                            normalPlacement(pTempTile,pPlayer,1);
                        }
                    }
                    plans=pPlayer->getPlans();
                    if(!plans.empty()){
                        //select a set of better plans
                        int maxPayoff = 0;
                        for (int i = 0; i < plans.size();i++) {
                            if (plans.at(i)->getPayoff() > maxPayoff)
                                maxPayoff = plans.at(i)->getPayoff();
                            else if (plans.at(i)->getPayoff() < maxPayoff) {
                                plans.pop_front();
                            }
                        }
                        qDebug()<<pPlayer->getName()<<" plan size: "<<plans.size();
                        if(plans.size()>1){
                            QVector<plan*> buffer;
                            buffer.push_back(plans.front());
                            plans.pop_front();
                            //pPlan = plans.front();
                            for (int i = 0; i < plans.size();i++) {
                                bool isTheSamePlan = false;
                                int times=0;
                                for (int j = 0; j < buffer.size();j++) {
                                    if (plans.at(i)->equaulsTo(buffer.at(j))) {
                                        isTheSamePlan = true;
                                        buffer.at(j)->foundSamePlan();
                                    }
                                    if (j == buffer.size() - 1) {
                                        if (!isTheSamePlan) {
                                            buffer.push_back(plans.at(i));
                                        }
                                    }
                                    times++;
                                }
                            }
                            qDebug()<<pPlayer->getName()<<" buffer size: "<<buffer.size();
                            if(buffer.size()>1){
                                QVector<plan*> selectedPlans;
                                int maxPayoff = 0;
                                for (auto it : buffer)
                                    if (it->getPayoff() > maxPayoff) maxPayoff = it->getPayoff();
                                for (auto it : buffer)
                                    if (it->getPayoff() == maxPayoff) selectedPlans.push_back(it);
                                if(selectedPlans.size()>1){
                                    int maxNumOfSamePlan = 0;
                                    QVector<plan*> finalPlan;
                                    qDebug()<<pPlayer->getName()<<" selected plan size: "<<selectedPlans.size();
                                    for(auto it: selectedPlans){
                                        qDebug()<<pPlayer->getName()<<"payoff: "<< it->getPayoff() <<" numOfSamePlan:"<< it->getNumOfSamePlan();
                                        if(it->getNumOfSamePlan()>maxNumOfSamePlan) maxNumOfSamePlan=it->getNumOfSamePlan();
                                    }
                                    for(auto it: selectedPlans)
                                        if(it->getNumOfSamePlan()==maxNumOfSamePlan) finalPlan.push_back(it);
                                    qDebug()<<pPlayer->getName()<<" final plan size: "<<finalPlan.size();
                                    if(finalPlan.size()>1){
                                        int random_plan=rand()%(finalPlan.size()-1);
                                        plans.clear();
                                        plans.push_back(finalPlan.at(random_plan));
                                    }
                                    else{
                                        plans=finalPlan;
                                    }
                                }
                                else{
                                    plans=selectedPlans;
                                }
                            }
                            else{
                                plans=buffer;
                            }
                        }
                        pTempTile=plans.front()->getTile();
                        int n=plans.front()->getTimesOfRotation();
                        bool reversed=false;
                        if(n>4){
                            reversed=true;
                            n-=5;
                        }
                        if(reversed) pTempTile->reverse();
                        for(int i=0;i<n;i++)
                            pTempTile->rotate(true);
                        if(isPlaceable(pTempTile,plans.front()->getPosition()->getX(),plans.front()->getPosition()->getY(),false)){

                        putTile(plans.front()->getPosition(),pTempTile,false,false);
                            pPlayer->putTile(pTempTile);
                            qDebug()<<pPlayer->getName()<<"place with the plan ";
                            qDebug()<<pPlayer->getID()<<": X: "<<plans.front()->getPosition()->getX()<<" Y: "<<plans.front()->getPosition()->getY()<<" Times of Rotation: "<<plans.front()->getTimesOfRotation()<<' '<<pTempTile->getID();
                            hasBeenPlaced=true;
                            pTempTile=nullptr;
                        }
                        else{
                            qDebug()<<pPlayer->getName()<<"place withOUT the plan ";
                            qDebug()<<pPlayer->getID()<<": X: "<<plans.front()->getPosition()->getX()<<" Y: "<<plans.front()->getPosition()->getY()<<" Times of Rotation: "<<plans.front()->getTimesOfRotation()<<' '<<pTempTile->getID();
                            pTempTile->setToTheOriginal();
                        }
                    }
            //DIVIDE
                if(!hasBeenPlaced){
                        int tilesRecord[5]={0};
                        plan* pTempPlan=nullptr;
                        for(auto it:tiles)
                            tilesRecord[(it->getNum())-1]++;
                        int times=0;
                        for(int i=0;i<3;i++){
                            if(hasBeenPlaced) break;
                            pPlayer->clearPlans();
                            //plans.clear();
                            switch (i) {
                            case 0:
                                times=tilesRecord[3]+tilesRecord[4];
                                break;
                            case 1:
                                times=tilesRecord[2]+tilesRecord[1];
                                break;
                            case 2:
                                times=1;
                            }
                            for(int j=0;j<times;j++){
                                if(hasBeenPlaced) break;
                                switch (i) {
                                case 0:
                                    pTempTile=tiles.at(tiles.size()-j-1);
                                    break;
                                case 1:
                                    pTempTile=tiles.at(tiles.size()-j-(1+tilesRecord[3]+tilesRecord[4]));
                                    break;
                                case 2:
                                    pTempTile=tiles.front();
                                }

                                normalPlacement(pTempTile,pPlayer,2);
                            }

                            //qDebug()<<owner<<" size"<<plans.size();
                            plans=pPlayer->getPlans();
                            qDebug()<<"PLAN "<<owner<<" size"<<plans.size();
                            if(!plans.empty()){
                                if(plans.size()>1) randNum=rand()%(plans.size()-1);
                                else randNum=0;
                                pTempPlan=plans.at(randNum);
                                pTempTile=pTempPlan->getTile();
                                int n=pTempPlan->getTimesOfRotation();
    //                            bool reversed=pTempPlan->hasBeenReversed();
                                bool reversed=false;
                                if(n>4){
                                    reversed=true;
                                    n-=5;
                                }
                                if(reversed) {
                                    pTempTile->reverse();
                                }
                                for(int i=0;i<n;i++)
                                    pTempTile->rotate(true);
                                if(isPlaceable(pTempTile,pTempPlan->getPosition()->getX(),pTempPlan->getPosition()->getY(),false)){
                                    putTile(pTempPlan->getPosition(),pTempTile,false,false);
                                    pPlayer->putTile(pTempTile);
                                    qDebug()<<pPlayer->getID()<<" placed at "<<": X: "<<x<<" Y: "<<y<<" "<<pTempTile->getID();
                                    pTempPlan=nullptr;
                                    pTempTile=nullptr;
                                    hasBeenPlaced=true;
                                    break;
                                }
//                                else {
//                                    qDebug()<<pPlayer->getID()<<" cannot placed at "<<": X: "<<x<<" Y: "<<y<<" "<<pTempTile->getID();

//                                    for(int i=0;i<n;i++)
//                                        pTempTile->rotate(false);
//                                    if(reversed) pTempTile->reverse();
//                                    //pTempTile->setToTheOriginal();
//                                }
                            }
                        }

//                    else{
//                        qDebug()<<owner<<" triggerd ";
//                        for (QVector<tile*>::reverse_iterator rit=tiles.rbegin();rit!=tiles.rend();++rit) {
//                            normalPlacement(*rit,pPlayer,3);
//                            if((*rit)->hasBeenPlaced()){
//                                hasBeenPlaced=true;
//                                break;
//                            }
//                        }
//                    }
                }
                if (!hasBeenPlaced) {
                    qDebug() << "Player " << id << ", " << pPlayer->getName() << " is Passed" ;
                    pPlayer->passed();
                }
            }
        }
    }
}

void Blokus::normalPlacement(tile *pTile,player* player,int mode)
{
    QVector<square*> availableSquares=player->getAvailableSquares();
    int x,y;
    plan *pPlan=nullptr;
    for (QVector<square*>::reverse_iterator rit = availableSquares.rbegin(); rit != availableSquares.rend(); ++rit) {
        x = (*rit)->getX();
        y = (*rit)->getY();
        QVector<square*> temp;
        int count = 0;
        if (pTile->getSymmetry()) count = 5;
        else count = 10;
            bool isReversed=false;
            for (int k = 0; k < count; k++) {
                temp=getRelativeLocation(x,y,pTile);
                for(auto it:temp){
                    x=it->getX();
                    y=it->getY();
                    if (isPlaceable(pTile, x, y, false))
                    {
                            switch (mode) {
                                case 1://plan
                                checkPayoff(x, y, pTile, k,isReversed,player->getPredictions());
                                break;
                                case 2://intelligent decending
                                pPlan=new plan(x,y,0,pTile,k,isReversed);
                                player->addPlan(pPlan);
                                pPlan=nullptr;
                                break;
                                case 4://human availability test
                                AvailableToHuman=true;

                                    bool hasSamePlan=false;
                                    for(auto singlePlan:player->getPlans()){
                                        if(singlePlan->getPosition()->getX()==x&&singlePlan->getPosition()->getY()==y&&singlePlan->getTile()->getID()==pTile->getID()&&singlePlan->getTimesOfRotation()==k&&(singlePlan->hasBeenReversed()==isReversed)){
                                            hasSamePlan=true;
                                        }
                                    }
                                    if(!hasSamePlan){
                                        pPlan = new plan(x, y, 0,pTile,k,isReversed);
                                        player->addPlan(pPlan);
                                        pPlan=nullptr;
                                    }
                                    break;
                            }
                    }
                }
                if(k!=4&&k!=9)pTile->rotate(true);
                else
                {
                    if(count==10){
                        isReversed=true;
                        pTile->reverse();
                    }
                }

            }
    }
}


void Blokus::putTile(square* pos, tile *par, bool undo, bool preview)
{
    QVector<int> tempTransfer=par->getTile();
    int paraX=pos->getX(),paraY=pos->getY(),count = 0, total = par->getNum(), x = paraX, y = paraY, id=par->getID(), owner=par->getOwner();
    if(preview)
        owner+=4;
    for (int i = 0; i < par->getY(); i++)
    {
        for (int j = 0; j < par->getX(); j++)
        {

            if (count == total)break;
            else if (tempTransfer.front() != 0)
            {
                if(undo&&preview){
                    if(board[x][y]->getOwner()>4){
                        board[x][y]->setOwner(0);
                        board[x][y]->setOccupier(0);
                    }
                }
                else if(undo) {
                    board[x][y]->setOwner(0);
                    board[x][y]->setOccupier(0);
                }
                else {
                    if(board[x][y]->getOwner()==0){
                        board[x][y]->setOwner(owner);
                        board[x][y]->setOccupier(id);

                    }
                }
                count++;
            }
            tempTransfer.erase(tempTransfer.begin());
            y++;
        }
        y = paraY;
        x++;
    }
    if(!undo&&!preview){
        par->setPos(-50,-50);
        par->setScale(1);
        par->setVisible(false);
        par->setSelected(false);
        if(turn>0){
            if(playerSet.at(par->getOwner()-1)->isHumanPlayer()) {
                playerLoop->exit();
            }
            if(par->getID()==1&&playerSet.at(par->getOwner()-1)->getRemainingTiles().size()==1){
                playerSet.at(par->getOwner()-1)->perfectlyPlaced();
            }
            //RecordAvailbleSquares(0, 0, 20, 20,0);
        }
    }
    scene->update();
}

bool Blokus::isPlaceable(tile *target, int posX, int posY, bool preview)
{
    int count = 0, x = posX, y = posY, width = target->getX(), height = target->getY(), total = target->getNum(), owner = target->getOwner();
    bool isPlaceable = false;
    QVector<int> tempTransfer = target->getTile();

    if (x + height-1 > 19 || y + width-1 > 19 || x < 0 || y < 0) return false;
    else if(preview) return true;
    else if (turn == 1) {
        if ((x == 0 && y == 0 && tempTransfer.front() == 0) || (x == 0 && y + width - 1 == 19 && tempTransfer.at(width - 1) == 0) || (x + height - 1 == 19 && y == 0 && tempTransfer.at(width * height - width) == 0) || (x + height - 1 == 19 && y + width - 1 == 19 && tempTransfer.size() != width * height)) return false;
        else if ((x == 0 && y == 0 && tempTransfer.front() != 0) || (x == 0 && y + width - 1 == 19 && tempTransfer.at(width - 1) != 0) || (x + height - 1 == 19 && y == 0 && tempTransfer.at(width * height - width) != 0) || (x + height - 1 == 19 && y + width - 1 == 19 && tempTransfer.size() == width * height)) return true;
        else return false;
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (count == total)break;
                else if (tempTransfer.front() == 0) {
                    tempTransfer.pop_front();
                    y++;
                    continue;
                }
                else if (board[x][y]->getOwner() != 0 && tempTransfer.front() != 0) return false;
                else
                {
                    count++;
                    if (x != 0 && y != 0 && x != 19 && y != 19){
                        if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
                        else if (board[x - 1][y - 1]->getOwner() == owner || board[x - 1][y + 1]->getOwner() == owner || board[x + 1][y - 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
                    }
                    else {
                        if (x == 0) {
                            if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
                            else if (board[x + 1][y - 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
                        }
                        else if (y == 0) {
                            if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner)) return false;
                            else if (board[x - 1][y + 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
                        }
                        else if (x == 19) {
                            if ((board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
                            else if (board[x - 1][y - 1]->getOwner() == owner || board[x - 1][y + 1]->getOwner() == owner)isPlaceable = true;
                        }
                        else
                        {
                            if ((board[x + 1][y]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
                            else if (board[x - 1][y - 1]->getOwner() == owner || board[x + 1][y - 1]->getOwner() == owner)isPlaceable = true;
                        }
                    }
                }
                tempTransfer.pop_front();
                y++;
            }
            y = posY;
            x++;
        }
        return isPlaceable;
    }
}

void Blokus::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if(playerLoop!=nullptr)
        if(playerLoop->isRunning()) playerLoop->exit();
    previewClear();
    gameover=true;
}

//void Blokus::keyPressEvent(QKeyEvent *event)
//{
//    qDebug()<<playerSet.at(humanID-1)->getNumOfRemainingTiles();
//    QVector<square*> sqs;
//    if(event->key()==0x51){
//        previewClear();
//        sqs=playerSet.at(0)->getAvailableSquares();
//        for(auto it:sqs)
//            it->setOwner(playerSet.at(0)->getID()+4);
//    }
//    else if(event->key()==0x57){
//        previewClear();
//        sqs=playerSet.at(1)->getAvailableSquares();
//        for(auto it:sqs)
//            it->setOwner(playerSet.at(1)->getID()+4);
//    }
//    else if(event->key()==0x45){
//        previewClear();
//        sqs=playerSet.at(2)->getAvailableSquares();
//        for(auto it:sqs)
//            it->setOwner(playerSet.at(2)->getID()+4);
//    }
//    else if(event->key()==0x52){
//        previewClear();
//        sqs=playerSet.at(3)->getAvailableSquares();
//        for(auto it:sqs)
//            it->setOwner(playerSet.at(3)->getID()+4);
//    }
//    else{
//        previewClear();
//    }

//}

Blokus::~Blokus()
{
    delete ui;
    delete playerLoop;
    delete aiPlayerLoop;
    delete gameLoop;
    delete timer;
    delete scene;
}

void Blokus::tileReadyToPut(QPointF pos,tile *target)
{
    QList items=scene->items(pos,Qt::IntersectsItemShape,Qt::AscendingOrder,QTransform());
    for (auto it:items ) {
        if(it->type()==square::Type){
            if(undoPlan->getPosition()!=nullptr){
                putTile(undoPlan->getPosition(),undoPlan->getTile(),true,true);
                if(isPlaceable(target,undoPlan->getPosition()->getX(),undoPlan->getPosition()->getY(),false)){
                    putTile(undoPlan->getPosition(),target,false,false);
                    playerSet.at(target->getOwner()-1)->putTile(target);
                }

                else{
                    target->setToTheOriginal();
                    previewClear();
                }


                //qDebug()<<isPlaceable(undoPlan->getTile(),undoPlan->getPosition()->getX(),undoPlan->getPosition()->getY(),false);
            }
            else{
                if(isPlaceable(target,qgraphicsitem_cast<square*>(it)->getX(),qgraphicsitem_cast<square*>(it)->getY(),false)){
                    putTile(qgraphicsitem_cast<square*>(it),target,false,false);

                    playerSet.at(target->getOwner()-1)->putTile(target);

                }
                else{
                    target->setToTheOriginal();
                    undoPlan->clear();
                    previewClear();
                }
                //qDebug()<<isPlaceable(target,qgraphicsitem_cast<square*>(it)->getX(),qgraphicsitem_cast<square*>(it)->getY(),false);
            }
            undoPlan->clear();
            //previewClear();
        }
    }
}

void Blokus::tileHoverInTheBoard(QPointF pos, tile *target, bool inTheBoard)
{
    if(hint_triggerd) on_hintBtn_clicked();
    if(inTheBoard){
        QList items=scene->items(pos,Qt::IntersectsItemShape,Qt::AscendingOrder,QTransform());
        for (auto it:items ) {
            if(it->type()==square::Type){
                    if(isPlaceable(target,qgraphicsitem_cast<square*>(it)->getX(),qgraphicsitem_cast<square*>(it)->getY(),true)){
                        if(undoPlan->getPosition()==nullptr){
                            previewClear();
                            undoPlan->setPosition(qgraphicsitem_cast<square*>(it));
                            undoPlan->setTile(target);
                        }
                        else{
                            //undoPlan->setPosition()
                            putTile(undoPlan->getPosition(),undoPlan->getTile(),true,true);
                        }
                            undoPlan->setPosition(qgraphicsitem_cast<square*>(it));
                            putTile(qgraphicsitem_cast<square*>(it),target,false,true);
                    }
            }
        }
    }
    else{
            if(undoPlan->getPosition()!=nullptr){
                putTile(undoPlan->getPosition(),undoPlan->getTile(),true,true);
                undoPlan->clear();
        }
    }
}

void Blokus::RecordAvailbleSquares(int x, int y, int width, int height, int skipedPlayer)
{

    for (auto it : playerSet)it->cleanSquaresRecord();
    for (int i = x; i < height; i++)
    {
        for (int j = y; j < width; j++)
        {
            int owner;
            if ((i == 0 && j == 0) || (i == 0 && j == 19) || (i == 19 && j == 0) || (i == 19 && j == 19)) continue;
            else if (board[i][j]->getOwner() != 0)continue;
            else if (i == 0) {

                if (board[i + 1][j - 1]->getOwner() != 0){
                    owner=board[i + 1][j - 1]->getOwner() != 0;
                    if((board[i + 1][j]->getOwner() == owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
                if (board[i + 1][j + 1]->getOwner() != 0){
                    owner=board[i + 1][j + 1]->getOwner();
                    if((board[i + 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
//                if ((board[i + 1][j]->getOwner() == owner) || (board[i][j + 1]->getOwner() == owner) || (board[i][j - 1]->getOwner() == owner)) continue;
//                else
//                {
//                    if (board[i + 1][j - 1]->getOwner() != 0)playerSet.at(board[i + 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                    if (board[i + 1][j + 1]->getOwner() != 0)playerSet.at(board[i + 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                }
            }
            else if (j == 0) {
                if (board[i - 1][j + 1]->getOwner() != 0){
                    owner=board[i - 1][j + 1]->getOwner();
                    if((board[i + 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
                if (board[i + 1][j + 1]->getOwner() != 0){
                    owner=board[i + 1][j + 1]->getOwner();
                    if((board[i + 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
//                if ((board[i + 1][j]->getOwner() == owner) || (board[i][j + 1]->getOwner() == owner) || (board[i - 1][j]->getOwner() == owner)) continue;
//                else
//                {
//                    if (board[i - 1][j + 1]->getOwner() != 0)playerSet.at(board[i - 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                    else if (board[i + 1][j + 1]->getOwner() != 0)playerSet.at(board[i + 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                }
            }
            else if (i == 19) {
                if (board[i - 1][j + 1]->getOwner() != 0){
                    owner=board[i - 1][j + 1]->getOwner();
                    if((board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
                if (board[i - 1][j - 1]->getOwner() != 0){
                    owner=board[i - 1][j - 1]->getOwner();
                    if((board[i][j+1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
//                if ((board[i][j + 1]->getOwner() == owner) || (board[i - 1][j]->getOwner() == owner) || (board[i][j - 1]->getOwner() == owner)) continue;
//                else
//                {
//                    if (board[i - 1][j + 1]->getOwner() != 0)playerSet.at(board[i - 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                    else if (board[i - 1][j - 1]->getOwner() != 0)playerSet.at(board[i - 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                }
            }
            else if (j == 19) {
                if (board[i - 1][j - 1]->getOwner() != 0){
                    owner=board[i - 1][j - 1]->getOwner();
                    if((board[i+1][j]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner) && (board[i][j-1]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
                if (board[i + 1][j - 1]->getOwner() != 0){
                    owner=board[i + 1][j - 1]->getOwner();
                    if((board[i+1][j]->getOwner() != owner) && (board[i-1][j]->getOwner() != owner) && (board[i][j-1]->getOwner() != owner)) playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                }
//                if ((board[i + 1][j]->getOwner() == owner) || (board[i - 1][j]->getOwner() == owner) || (board[i][j-1]->getOwner() == owner)) continue;
//                else
//                {
//                    if (board[i - 1][j - 1]->getOwner() != 0)playerSet.at(board[i - 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                    else if (board[i + 1][j - 1]->getOwner() != 0)playerSet.at(board[i + 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
//                }
            }
            else {
                    owner = board[i - 1][j - 1]->getOwner();
                    if (owner != 0)
                        if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
                            playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                    owner = board[i - 1][j + 1]->getOwner();
                    if (owner != 0)
                        if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
                            playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                    owner = board[i + 1][j - 1]->getOwner();
                    if (owner != 0)
                        if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
                            playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
                    owner = board[i + 1][j + 1]->getOwner();
                    if (owner != 0)
                        if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
                            playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
            }
        }
    }
}




QVector<square*> Blokus::getRelativeLocation(int x, int y, tile *target)
{
    bool squaresDetected[4] = { 0 };
    int width = target->getX(), height = target->getY(), type = target->getID(), playerID = target->getOwner(), count = 0;
    Q_UNUSED(type);
    QVector<int> temp = target->getTile();
    QVector<square*> availableSquares;
    if (x == 0 || y == 0 || x == 19 || y == 19) count = 2;
    else {
//        if (board[x - 1][y - 1]!=nullptr)
            if (board[x - 1][y - 1]->getOwner() == playerID)squaresDetected[0] = true;
//        if (board[x - 1][y + 1]!=nullptr)
            if (board[x - 1][y + 1]->getOwner() == playerID)squaresDetected[1] = true;
//        if (board[x + 1][y + 1]!=nullptr)
            if (board[x + 1][y + 1]->getOwner() == playerID)squaresDetected[2] = true;
//        if (board[x - 1][y + 1]!=nullptr)
            if (board[x - 1][y + 1]->getOwner() == playerID)squaresDetected[3] = true;

        for (auto it : squaresDetected)
            if (it) count++;
    }
    if (!(count > 2 || (squaresDetected[0] && squaresDetected[2]) || (squaresDetected[1] && squaresDetected[3]))) {
        int index = 0;
        count=0;
        for (int i = 0; i < height; i++) {
            if (count == target->getNum())break;
            for (int j = 0; j < width; j++) {
                if (temp.at(index) != 0) {
                    count++;
                    if (isPlaceable(target, x - i,y - j, false)) availableSquares.push_back(board[x - i][y - j]);
                }
                index++;
            }
        }
    }
    if (availableSquares.size() > 0) return availableSquares;
    else return QVector<square*>{board[x][y]};
}

int Blokus::checkPayoff(int paraX, int paraY, tile *par)
{
    QVector<int> tempTransfer = par->getTile();
    int count = 0, total = par->getNum(), x = paraX, y = paraY, payoff = 0, owner = par->getOwner();
    for (int i = 0; i < par->getY(); i++)
    {
        for (int j = 0; j < par->getX(); j++)
        {

            if (count == total)break;
            else if (tempTransfer.front() != 0)
            {
                if (x > 0 && x < 19 && y>0 && y < 19) {
                    if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                    if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                    if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                    if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                }
                else {
                    if (x == 0) {
                        if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                        if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                    }
                    else if (y == 0) {
                        if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                        if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                    }
                    else if (x == 19) {
                        if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                        if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                    }
                    else {
                        if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                        if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                    }
                }
                count++;
            }
            tempTransfer.pop_front();
            y++;
        }
        y = paraY;
        x++;
    }
    return payoff;
}

void Blokus::checkPayoff(int paraX, int paraY, tile *par, int timesRotated, bool isReversed, QVector<square *> interlopers)
{
    QVector<int> tempTransfer = par->getTile();
    int count = 0, total = par->getNum(), x = paraX, y = paraY, payoff = 0, owner = par->getOwner();
    plan* newPlan = nullptr;
    for (int i = 0; i < par->getY(); i++)
    {
        for (int j = 0; j < par->getX(); j++)
        {
            if (count == total)break;

                if (tempTransfer.front() != 0)
                {
                    if(advancedAI){
                        for (auto it : interlopers)
                            if (x == it->getX() && y == it->getY())payoff++;
                    }
                    else{
                        if (x > 0 && x < 19 && y>0 && y < 19) {
                            if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                            if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                            if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                            if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                        }
                        else {
                            if (x == 0) {
                                if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                                if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                            }
                            else if (y == 0) {
                                if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                                if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
                            }
                            else if (x == 19) {
                                if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                                if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
                            }
                            else {
                                if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
                                if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
                            }
                        }
                    }
                    count++;
                }
            tempTransfer.pop_front();
            y++;
        }
        y = paraY;
        x++;
    }
    if (payoff > 0) {
        newPlan = new plan(paraX, paraY, payoff,par,timesRotated,isReversed);
        playerSet.at(owner - 1)->addPlan(newPlan);
    }
    newPlan = nullptr;
}

void Blokus::previewClear()
{
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            if(board[i][j]->getOwner()>4)
                board[i][j]->setOwner(0);
    gameboard->update();
}




void Blokus::on_actionNew_Game_triggered()
{
    startDialog *pStartDialog= new startDialog(this);
    statusBarLabel->setText("Game Setting");
    pStartDialog->exec();
    if(pStartDialog->selectedID!=0&&pStartDialog->difficulty!=0){
        ui->p1Statu->setVisible(false);
        ui->p2Statu->setVisible(false);
        ui->p3Statu->setVisible(false);
        ui->p4Statu->setVisible(false);
        ui->hintBtn->setVisible(true);
        ui->hintBtn->setEnabled(false);
        if(turn>0){
            playerLoop->deleteLater();
            aiPlayerLoop->deleteLater();
            for(auto it:playerSet)
                delete it;
            playerSet.clear();
        }
        if(pStartDialog->difficulty==1) advancedAI=false;
        else advancedAI=true;
        QList<QGraphicsItem*> items=scene->items();
        for(auto it:items){
            if(it->type()!=square::Type&&it->type()!=QGraphicsItemGroup::Type) delete it;
            else {
                if(qgraphicsitem_cast<square*>(it)!=nullptr) qgraphicsitem_cast<square*>(it)->setOwner(0);
            }
        }
        turn =1;
        humanID=0;
        hint_triggerd=false;
        allAiPassedInformed=false;
        tile *sigleTile= nullptr;
        QGraphicsRectItem *rect=nullptr;
        QVector<QGraphicsRectItem*> rects;
        rect=new QGraphicsRectItem(QRect(-5,-5,610,610));
        scene->addItem(rect);
        rect=new QGraphicsRectItem(QRect(-165,0,155,250));

//        pen.setColor(QColor(0x4E,0xC0,0xFC));
        pen.setWidth(2);
        pen.setColor(QColor(0x00,0x00,0x00));
        rect->setPen(pen);
        rects.push_back(rect);
        scene->addItem(rect);
        rect=new QGraphicsRectItem(QRect(610,0,155,250));
//        pen.setColor(QColor(0xFF,0xF1,0x66));
//        pen.setWidth(2);
        rect->setPen(pen);
        rects.push_back(rect);
        scene->addItem(rect);
        rect= new QGraphicsRectItem(QRect(-165,350,155,250));
//        pen.setColor(QColor(0x00,0x00,0x00));
//        pen.setWidth(2);
        rect->setPen(pen);
        rects.push_back(rect);
        scene->addItem(rect);
        rect=new QGraphicsRectItem(QRect(610,350,155,250));
        rect->setPen(pen);
        rects.push_back(rect);
        scene->addItem(rect);
        int posY, posX, minX, maxX, maxW=0, maxH=0;
        player* pPlayer;
        for (int h = 1; h <= 4; h++)
        {
            QString playerName;
            if(h==pStartDialog->selectedID){
                playerName.append(pStartDialog->playerName);
            }
            else{
                switch (h) {
                    case 1:
                    playerName.append("Sapphire");
                    break;
                    case 2:
                    playerName.append("Topaz");
                    break;
                    case 3:
                    playerName.append("Rubious");
                    break;
                    case 4:
                    playerName.append("Emerald");
                    break;
                }
            }

            pPlayer = new player(h, playerName);
            playerSet.push_back(pPlayer);
            pPlayer->setRect(rects.at(h-1));
            if(h==pStartDialog->selectedID){
                pPlayer->setHuman();
                humanID=pPlayer->getID();
                switch (humanID) {
                    case 1:
                    ui->hintBtn->move(108,53);
                    break;
                    case 2:
                    ui->hintBtn->move(883,53);
                    break;
                    case 3:
                    ui->hintBtn->move(108,403);
                    break;
                    case 4:
                    ui->hintBtn->move(883,403);
                    break;
                }
            }
            switch (h) {
                case 1:
                    minX=posX=-160;
                    maxX=-5;
                    posY=20;
                    ui->player1Label->setText(playerName);
                    pPlayer->setLabel(ui->player1Label);
                    //scene->addText(playerName)->setPos(-155,0);
                    break;
                case 2:
                    minX=posX=615;
                    posY=20;
                    maxX=770;
                    ui->player2Label->setText(playerName);
                    pPlayer->setLabel(ui->player2Label);
                    //scene->addText(playerName)->setPos(-155,350);
                    break;
                case 3:
                    minX=posX=-160;
                    posY=370;
                    maxX=-5;
                    ui->player3Label->setText(playerName);
                    pPlayer->setLabel(ui->player3Label);
                    //scene->addText(playerName)->setPos(620,0);
                    break;
                case 4:
                    minX=posX=615;
                    posY=370;
                    maxX=770;
                    ui->player4Label->setText(playerName);
                    pPlayer->setLabel(ui->player4Label);
                    //scene->addText(playerName)->setPos(620,350);
                    break;
            }
            for(int i=1;i<=21;i++){
                sigleTile=new tile(i,h);
                pPlayer->push_back(sigleTile);
                if(h==pStartDialog->selectedID){
                    sigleTile->setFlag(QGraphicsItem::ItemIsSelectable,true);
                }
                else{
                    sigleTile->setFlag(QGraphicsItem::ItemIsSelectable,false);
                }
                int w=sigleTile->getX(), h=sigleTile->getY();
                if(posX+w*10+5>maxX){
                    posX=minX;
                    posY=posY+maxH*10+10;
                    maxW=0;
                    maxH=0;
                }
                if(i==21) {
                    maxH=0;
                    maxW=0;
                }
                if(w>maxW) maxW=w;
                if(h>maxH) maxH=h;
                sigleTile->setPos(posX,posY);
                scene->addItem(sigleTile);
                posX+=w*10+8;
                connect(sigleTile,SIGNAL(readyToPut(QPointF,tile*)),this,SLOT(tileReadyToPut(QPointF,tile*)));
                connect(sigleTile,SIGNAL(mouseStatu(QPointF,tile*,bool)),this,SLOT(tileHoverInTheBoard(QPointF,tile*,bool)));
            }
        }
        gameProcedure();

    }
    statusBarLabel->setText("Ready");

}

void Blokus::on_scoreboard_triggered()
{
    resultsDialog *dlg=new resultsDialog(this);
    int basic,bonus;

    QVector<tile*> remainingTiles;
    for(int i=0;i<4;i++){
        basic=bonus=0;
        remainingTiles=playerSet.at(i)->getRemainingTiles();
        if(remainingTiles.isEmpty()){
            bonus+=15;
            if(playerSet.at(i)->isPefectlyPlaced()) bonus+=5;
        }
        else{
            for(auto it:remainingTiles)
                basic-=it->getNum();
        }
        dlg->setValues(basic,bonus,i+1,playerSet.at(i)->getName());
    }
    dlg->display();
    dlg->exec();
}

//void Blokus::hint(bool triggered)
//{
//    if(hint_system_index<hint_storage.size()){
//        previewClear();
//        int hint_system_index=0;
//        qDebug()<<hint_system_index;
//        int id=hint_storage.at(hint_system_index)->getTile()->getID();
//        //int owner=humanID;
//        tile*  temp= new tile(id,humanID);
//        int n=hint_storage.at(hint_system_index)->getTimesOfRotation();
//    //                            bool reversed=pTempPlan->hasBeenReversed();
//        bool reversed=false;
//        if(n>4){
//            reversed=true;
//            n-=5;
//        }
//        if(reversed) {
//           temp->reverse();
//        }
//        for(int i=0;i<n;i++)
//           temp->rotate(true);
//        putTile(hint_storage.at(hint_system_index)->getPosition(),temp,false,true);
//        //hint_system_index++;
//    }
//    else{
//        previewClear();
//        hint_system_index=0;
//    }
//}

void Blokus::on_hintBtn_clicked()
{
    if(hint_storage.size()>0){
        if(!hint_triggerd){
            qDebug()<<"tr";
            int randNum,id,n;
            randNum=rand()%hint_storage.size();
            id=hint_storage.at(randNum)->getTile()->getID();
            pHint=new tile(id,humanID);
            n=hint_storage.at(randNum)->getTimesOfRotation();
            if(n>4){
                n-=5;
                pHint->reverse();
            }
            for(int i=0;i<n;i++)
               pHint->rotate(true);
            putTile(hint_storage.at(randNum)->getPosition(),pHint,false,true);
            hint_triggerd=true;
        }
        else{
            qDebug()<<"tr22";
            previewClear();
            delete pHint;
            pHint=nullptr;
            hint_triggerd=false;
        }
    }
    else{
        ui->hintBtn->setEnabled(false);
    }
}
