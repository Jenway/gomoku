#include "mainwindow.h"
#include "ui_mainwindow.h"

QTime globalTime;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QFont ft;
    this->setWindowTitle("Gomoku !");
    this->setWindowIcon(QIcon(":image/icon/favicon2.png"));
    timeClock();
    gametype = start::gametype;
//    qDebug() << start::gametype;
    initgame();

//    qDebug() << start::gametype;

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initgame(){

    globalTime.start();
    first_go_done = false;

    if(gametype == PVE2){
        PVE_ON_P=false;}
    else if(gametype==PVE) {
        PVE_ON_P=true;
    }
    else{}


    if(gametype==EVE){
        setMouseTracking(false);
    }
    else{
        setMouseTracking(true);
    }

    for(int i=0;i<COL+8;i++){
        for(int j=0;j<COL+8;j++){
            board[i][j]=0;
        }
    }

    step_count=0;
    this->ui->stepClock->display(step_count);
    this->ui->LastStep->setPlainText("");

        HEAD = (RECORDS*)malloc(sizeof(RECORDS));
        HEAD->x = -1;
        HEAD->y = -1;
        record = (RECORDS*)malloc(sizeof(RECORDS));
        HEAD->next = record;
        record_p = HEAD->next;
        record_p->next = NULL;


    gamemode = started;
    player = playerblack;
    update();
    if(gametype==EVE){
    Timer = new QTimer;
    // eveTimer
    Timer->setInterval(500);
    QObject::connect(Timer,&QTimer::timeout,this,&MainWindow::eveCpuGo);
        Timer->start();
    }
    else if(gametype==PVE2||gametype==PVE){
        Timer = new QTimer;
        // PVETimer
        Timer->setInterval(500);
        QObject::connect(Timer,&QTimer::timeout,this,&MainWindow::pveCpuGo);
        if(gametype==PVE2&&first_go_done==false){
            pveCpuGo();
        }else{}

    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

//    QPixmap pix;
//    pix.load(":image/icon/bak.png");
//    painter.drawPixmap(0, 0, 600, 400, pix);

    QPen pen;
    pen.setColor(QColor(100,149,237));

//    QBrush brush(QColor(0,155,125));
    QBrush brush(QColor(237,209,216));
    brush.setStyle(Qt::HorPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
//    painter.drawRect(50,50,200,100);


    for(int i = 0; i <= COL+1;i++){

    painter.drawLine(QPointF(EDGE,i*BLOCK_SIZE+EDGE),
                     QPointF(LENGTH+EDGE,i*BLOCK_SIZE+EDGE));
    painter.drawLine(QPointF(i*BLOCK_SIZE+EDGE,EDGE),
                     QPointF(i*BLOCK_SIZE+EDGE,EDGE+LENGTH));
    }


    QRectF rect(3*EDGE + COL*(BLOCK_SIZE+2),EDGE, 300, 200);
    painter.drawRect(rect);  //绘制个矩形
    painter.setPen(QColor(Qt::black));
    QFont font("宋体", 15, QFont::Bold, false);   //字体，大小，粗体，斜体
    font.setCapitalization(QFont::Capitalize);   //设置字母大小写
    painter.setFont(font);
    if(gamemode == started){
        QString str = (player == playerblack)?QString("\nproject\ngomoku\nBlack Go!"):QString("\nproject\ngomoku\nWhite Go!");
        painter.drawText(rect, Qt::AlignHCenter,str);
    }
    else {
        QFont font("Arial Black", 15, QFont::Bold, false);
        painter.setFont(font);
        if(player == playerwhite){painter.setPen(QColor(47,47,47));}
        else{painter.setPen(QColor(91,165,133));}
        QString str = (player == playerwhite)?QString("\nP-Black\nWin!"):QString("\nP-White\nWin!");
        painter.drawText(rect, Qt::AlignHCenter, str);
    }



    // 棋盘提示点

    painter.setPen(QColor(100,149,237));     //画提示点
    painter.setBrush(QColor(100,149,237));
    painter.drawEllipse(EDGE+5*BLOCK_SIZE-GO_SIZE/3,
                        EDGE +5*BLOCK_SIZE-GO_SIZE/3,
                        GO_SIZE/3*2,GO_SIZE/3*2);
    painter.drawEllipse(EDGE+11*BLOCK_SIZE-GO_SIZE/3,
                        EDGE +5*BLOCK_SIZE-GO_SIZE/3,
                        GO_SIZE/3*2,GO_SIZE/3*2);
    painter.drawEllipse(EDGE+5*BLOCK_SIZE-GO_SIZE/3,
                        EDGE +11*BLOCK_SIZE-GO_SIZE/3,
                        GO_SIZE/3*2,GO_SIZE/3*2);
    painter.drawEllipse(EDGE+11*BLOCK_SIZE-GO_SIZE/3,
                        EDGE +11*BLOCK_SIZE-GO_SIZE/3,
                        GO_SIZE/3*2,GO_SIZE/3*2);
    painter.drawEllipse(EDGE+8*BLOCK_SIZE-GO_SIZE/3,
                        EDGE +8*BLOCK_SIZE-GO_SIZE/3,
                        GO_SIZE/3*2,GO_SIZE/3*2);

//    QPixmap pix;
//    pix.load(":image/icon/bak.png");
//    painter.drawPixmap(3*EDGE + COL*(BLOCK_SIZE+2),EDGE, 600, 400, pix);


    for(int i =1; i <COL+1;i++){
        for(int j =1;j<COL+1;j++){
            if(board[i+3][j+3]==1){
                painter.setPen(QColor(82,149,120));     //画白点
                painter.setBrush(QColor(91,165,133));
                painter.drawEllipse(EDGE+i*BLOCK_SIZE-GO_SIZE,
                                    EDGE +j*BLOCK_SIZE-GO_SIZE,
                                    2*GO_SIZE,2*GO_SIZE);
            
            }
            else if(board[i+3][j+3]==2){
                painter.setPen(QColor(42,42,42));     //画黑点
                painter.setBrush(QColor(47,47,47));
                painter.drawEllipse(EDGE+i*BLOCK_SIZE-GO_SIZE,
                                    EDGE +j*BLOCK_SIZE-GO_SIZE,
                                    2*GO_SIZE,2*GO_SIZE);
            }
            else if (board[i+3][j+3]>=3) {// 胜利点

                if(board[i+3][j+3]==3){
                    painter.setPen(QColor(82,149,120));     //画白点
                    painter.setBrush(QColor(91,165,133));
                    painter.drawEllipse(EDGE+i*BLOCK_SIZE-GO_SIZE,
                                        EDGE +j*BLOCK_SIZE-GO_SIZE,
                                        2*GO_SIZE,2*GO_SIZE);
                }
                else{
                    painter.setPen(QColor(42,42,42));     //画黑点
                    painter.setBrush(QColor(47,47,47));
                    painter.drawEllipse(EDGE+i*BLOCK_SIZE-GO_SIZE,
                                        EDGE +j*BLOCK_SIZE-GO_SIZE,
                                        2*GO_SIZE,2*GO_SIZE);
                }
                // 胜利点 画星星(删掉) 太难了还是画方框吧
                // 方框太丑，还是画个叉号吧

                painter.setPen(QPen(Qt::white,5));
//                painter.setBrush(Qt::white);
//                brush.setStyle(Qt::SolidPattern);
//                QRectF rect(EDGE+i*BLOCK_SIZE-GO_SIZE/2,
//                           EDGE +j*BLOCK_SIZE-GO_SIZE/2,GO_SIZE,GO_SIZE);
//                painter.drawRect(rect);
//                painter.drawEllipse(EDGE+i*BLOCK_SIZE-GO_SIZE/2,
//                                    EDGE +j*BLOCK_SIZE-GO_SIZE/2,
//                                    GO_SIZE,GO_SIZE);
                //绘制左上线
                painter.drawLine(EDGE+i*BLOCK_SIZE-GO_SIZE/2,EDGE +j*BLOCK_SIZE-GO_SIZE/2,
                                 EDGE+i*BLOCK_SIZE+GO_SIZE/2,EDGE +j*BLOCK_SIZE+GO_SIZE/2);
                //绘制右下线
                painter.drawLine(EDGE+i*BLOCK_SIZE-GO_SIZE/2,EDGE +j*BLOCK_SIZE+GO_SIZE/2,
                                 EDGE+i*BLOCK_SIZE+GO_SIZE/2,EDGE +j*BLOCK_SIZE-GO_SIZE/2);

            }


        }    
    }

    if(player == playerblack){
        painter.setPen(QColor(42,42,42));     //画黑点
        painter.setBrush(QColor(47,47,47));}
    else{
            painter.setPen(QColor(82,149,120));     //画白点
            painter.setBrush(QColor(91,165,133));
        }

    if(board[mouseX+3][mouseY+3]==0){
    painter.drawEllipse(EDGE+mouseX*BLOCK_SIZE-GO_SIZE,
                        EDGE +mouseY*BLOCK_SIZE-GO_SIZE,
                        2*GO_SIZE,2*GO_SIZE);
    //绘制 十字准星
    pen.setColor(Qt::white);
    painter.setPen(pen);
    //绘制横向线
    painter.drawLine(EDGE+mouseX*BLOCK_SIZE-GO_SIZE/2,EDGE +mouseY*BLOCK_SIZE,EDGE+mouseX*BLOCK_SIZE+GO_SIZE/2,EDGE +mouseY*BLOCK_SIZE);
    //绘制纵向线
    painter.drawLine(EDGE+mouseX*BLOCK_SIZE,EDGE +mouseY*BLOCK_SIZE-GO_SIZE/2,EDGE+mouseX*BLOCK_SIZE,EDGE +mouseY*BLOCK_SIZE+GO_SIZE/2);

    }

}


void MainWindow::mouseMoveEvent(QMouseEvent *event)    //鼠标移动事件
{
//   setMouseTracking(true);
//    qDebug("121421");

   int x=event->x();   //鼠标移动时的坐标值
   int y=event->y();
   if(gamemode ==started&& x>=EDGE+BLOCK_SIZE&&x<=EDGE +(COL) * BLOCK_SIZE
           &&y>=EDGE+BLOCK_SIZE&&y<=(COL)* BLOCK_SIZE+EDGE)  //保证棋子落在棋盘内部，在外部的无效
   {
        mouseX = (x-EDGE/2)/BLOCK_SIZE;
        mouseY = (y-EDGE/2)/BLOCK_SIZE;
//        qDebug("move: %d %d , t: %d %d",mouseX,mouseY,event->x(),event->y());
//        qDebug("board: %d %d -> %d",mouseX,mouseY,board[mouseX+3][mouseY+3]);


    update();//更新整个界面，（为显示新的棋子的图像）

   }
   else
   {
       mouseX=-1;
       mouseY=-1;
   }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){

    if(gametype==EVE){
    }
    else{
        int x = event->x();
        int y = event->y();
        if(gamemode ==started&&PVE_ON_P==true&&x>=EDGE+BLOCK_SIZE &&x<=EDGE +(COL) * BLOCK_SIZE
                &&y>=EDGE+BLOCK_SIZE&&y<=(COL) * BLOCK_SIZE+EDGE)  //保证棋子落在棋盘内部，在外部的无效
        {
            int chessx =((x-EDGE/2)/BLOCK_SIZE)+3;
            int chessy =((y-EDGE/2)/BLOCK_SIZE)+3;
            if(board[chessx][chessy] == 0 // 判定位置是否为空
                    && chessx >=4
                    && chessx <= COL +4
                    && chessy >=4
                    && chessy <= COL+4)
            {
                if(player == playerblack){
                    board[chessx][chessy] = 2;
                }
                else{
                    board[chessx][chessy] = 1;
                }
                qDebug("release: %d %d , t: %d %d",chessx,chessy,event->x(),event->y());
                afterGo(chessx,chessy);
                first_go_done = true;
                player = (player==playerblack)?playerwhite:playerblack;

                if(gametype == PVE || gametype==PVE2){
                    PVE_ON_P=false;
                    setMouseTracking(false);
                    Timer->start();
                }
                else{
                }

            }
            else{}
        }
        else
        {
            mouseX=-1;
            mouseY=-1;
        }

    }
}


void MainWindow::afterGo(int chessX,int chessY){
    update();//更新整个界面，（为显示新的棋子的图像）
    step_count++; // 步数加一
    stepRecord(chessX,chessY);

//        qDebug("%d",HEAD->next->go_place);
    this->ui->LastStep->setPlainText("");
    QString onHands;
    while (record_p->next != NULL)
    {
        onHands=(record_p->player==1)?QString("Black"):QString("White");
        QString str = QString("step %1 %2:%3,%4")
                .arg((int)(record_p->count),0,10)
                .arg(onHands)
                .arg(record_p->x)
                .arg(record_p->y);
        this->ui->LastStep->appendPlainText(str);

//            qDebug("%d:%d,%d",record_p->count,(record_p->go_place)/COL,(record_p->go_place)%COL);
        record_p = record_p->next;
    }
    record_p = HEAD->next;


    this->ui->stepClock->display(step_count);

    if(judge(chessX,chessY)==0){
    }
    else {
        writeCSV();
        gameover *dlg = new gameover(this);
        connect(dlg,&gameover::accepted,this,&MainWindow::initgame);
        if(gametype==EVE){
            Timer->stop();
        }
        else {}



        dlg->setGeometry(this->x()+(this->width() - dlg->width()-GO_SIZE),
        this->y()+(this->height() - dlg->height())/2+8*GO_SIZE,dlg->width(),dlg->height());
        //            mainWindow.y()+(mainWindow.heigh()-dialog.height())/2, 200, 150);
        update();
        dlg->show();

    }



}



int MainWindow::judge(int x,int y){
        // 纵向
    int handOn;
    if(player == playerwhite){
    handOn =1;}
    else{
        handOn=2;
    }

        for (int i = x-4; i <= x+4; i++)
        {
            if (
                board[i][y] == handOn
                &&board[i+1][y]== handOn
                &&board[i+2][y]== handOn
                &&board[i+3][y]== handOn
                &&board[i+4][y]== handOn
                )
            {gamemode = unstarted;
                board[i][y] = handOn+2;
                board[i+1][y]= handOn+2;
                board[i+2][y]= handOn+2;
                board[i+3][y]= handOn+2;
                board[i+4][y]= handOn+2;
                return 1;}
        }

        // 横向
            for (int i = y-4; i <= y+4; i++)
        {
            if (
                board[x][i]== handOn
                &&board[x][i+1]== handOn
                &&board[x][i+2]== handOn
                &&board[x][i+3]== handOn
                &&board[x][i+4]== handOn
                )
            {gamemode = unstarted;
                board[x][i]= handOn+2;
                board[x][i+1]= handOn+2;
                board[x][i+2]= handOn+2;
                board[x][i+3]= handOn+2;
                board[x][i+4]= handOn+2;
                return 1;}
        }

        // 左斜
            for (int i = x-4,j=y+4; i <= x+4; i++,j--)
        {
            if (
                board[i][j]== handOn
                &&board[i+1][j-1]== handOn
                &&board[i+2][j-2]== handOn
                &&board[i+3][j-3]== handOn
                &&board[i+4][j-4]== handOn
                )
            {

                gamemode = unstarted;
                board[i][j]= handOn+2;
                board[i+1][j-1]= handOn+2;
                board[i+2][j-2]= handOn+2;
                board[i+3][j-3]= handOn+2;
                board[i+4][j-4]= handOn+2;
                return 1;}
        }

        //右斜
            for (int i = x-4,j = y-4; i <= x+4; i++,j++)
        {
            if (
                board[i][j]== handOn
                &&board[i+1][j+1]== handOn
                &&board[i+2][j+2]== handOn
                &&board[i+3][j+3]== handOn
                &&board[i+4][j+4]== handOn
                )
            {gamemode = unstarted;
                board[i][j]= handOn+2;
                board[i+1][j+1]= handOn+2;
                board[i+2][j+2]= handOn+2;
                board[i+3][j+3]= handOn+2;
                board[i+4][j+4]= handOn+2;
                return 1;}

        }


        return 0;

}

void MainWindow::cpuGo(){
    int handOn = (player==playerblack)?2:1;

    if(gamemode==started){
        if((gametype== PVE2||gametype== EVE)&&first_go_done == false){
            board[3+COL/2+1][3+COL/2+1] = handOn;
            afterGo(3+COL/2+1,3+COL/2+1);
            player = (player==playerblack)?playerwhite:playerblack;
        }
        else{
        GOS goMax,goP;
        goMax.score=0;
        for(int i =4;i<COL+4;i++){
            for(int j =4;j< COL+4;j++){
                goP.X = i;
                goP.Y = j;
                goP.score=score(i,j);
//                qDebug("goP:%d,%d,%d",goP.X-3,goP.Y-3,goP.score);
                goMax = (goP.score>goMax.score)?goP:goMax;
            }
        }
//        qDebug("goMax:%d,%d,%d",goMax.X,goMax.Y,goMax.score);

        board[goMax.X][goMax.Y] = handOn;
        afterGo(goMax.X,goMax.Y);

        player = (player==playerblack)?playerwhite:playerblack;

    }

    first_go_done = true;
    }
}

void MainWindow::cpuGo2(){
    int handOn = (player==playerblack)?2:1;

    if(gamemode==started){
        if((gametype== PVE2||gametype== EVE)&&first_go_done == false){
            board[3+COL/2+1][3+COL/2+1] = handOn;
            afterGo(3+COL/2+1,3+COL/2+1);
        }
        else{
            GOS Best_Attack;  // 最佳进攻位
            GOS Best_Defend;  // 最佳防守位
            Best_Attack.score = 0;  // 进攻策略 最高权重
            Best_Defend.score = 0;  // 防守策略 最高权重
            Best_Attack.X=0;Best_Attack.Y=0;Best_Defend.X=0;Best_Defend.Y=0;
            // 最佳进攻
            for (int i = 4; i < COL+4; i++){
                for (int j = 4; j < COL+4; j++){
                    if(board[i][j] != 0)
                        continue;
                    int value = score2(i,j,handOn);// 1 是 AI
                    Best_Attack.score = (Best_Attack.score>value)?Best_Attack.score:value;
                    Best_Attack.X = (Best_Attack.score>value)?Best_Attack.X:i;
                    Best_Attack.Y = (Best_Attack.score>value)?Best_Attack.Y:j;
                }
            }

            // 最佳防守
            for (int i = 4; i < COL+4; i++){
                for (int j = 4; j < COL+4; j++){
                    if(board[i][j] != 0)
                        continue;
                    int value = score2(i,j,3-handOn);// 1 是 AI
                    Best_Defend.score = (Best_Defend.score>value)?Best_Defend.score:value;
                    Best_Defend.X = (Best_Defend.score>value)?Best_Defend.X:i;
                    Best_Defend.Y = (Best_Defend.score>value)?Best_Defend.Y:j;
                }
            }
            // 选择 防守 || 进攻
            if(Best_Attack.score >= Best_Defend.score){  // 进攻 优先
                board[Best_Attack.X][Best_Attack.Y] = handOn;
                afterGo(Best_Attack.X,Best_Attack.Y);
            }
            else{ // 防守
                board[Best_Defend.X][Best_Defend.Y] = handOn;
                afterGo(Best_Defend.X,Best_Defend.Y);
            }


        }
        player = (player==playerblack)?playerwhite:playerblack;

    }



    first_go_done = true;
    }


int MainWindow::score2(int x,int y,int me) {
//        int me =(player==playerblack)?2:1;// me 作为参数是有必要的
        int value = 0;
        int rival = 3-me; // 对手

        int empty = 0;   // 无棋子
        int boundary = -1;// 边界

        int cnt_live_2 = 0;//活二的数量

        // 连五 > 活四 > 死四*3 > 活三*2 >
        // 活二*3 （略大于）死三*6 > 死二*4 > 其他棋型
        // 遍历 8 个方向
        for( int direct=1 ; direct <= 8 ; direct++ )  {
            // 活四 必胜
            // 1.活四  *22220
            if(getLine(x,y,direct, 1) == me
               && getLine(x,y,direct, 2) == me
               && getLine(x,y,direct, 3) == me
               && getLine(x,y,direct, 4) == me
               && getLine(x,y,direct, 5) == empty)
            {
                value += 300000;
                if(me == 1) value -= 500;// 人 不是当前棋手
                continue ;
            }

            // 死四 ： 如果是己方则下子获得胜利，对手的话要竭力去赌
            // 2. 死四A *22221
            if(getLine(x,y,direct, 1) == me
               && getLine(x,y,direct, 2) == me
               && getLine(x,y,direct, 3) == me
               && getLine(x,y,direct, 4) == me
               && (getLine(x,y,direct, 5) == rival || getLine(x,y,direct, 5) == boundary))
            {
                value += 250000;
                if(me == 1) value -= 500;
                continue ;
            }

            // 3. 死四B 2*222
            if(getLine(x,y,direct, -1) == me
               && getLine(x,y,direct, 1) == me
               && getLine(x,y,direct, 2) == me
               && getLine(x,y,direct, 3) == me)
            {
                value += 240000;
                if(me == 1) value -= 500;
                continue ;
            }

            // 4. 死四C 22*22
            if(getLine(x,y,direct, -2) == me
               && getLine(x,y,direct, -1) == me
               && getLine(x,y,direct, 1) == me
               && getLine(x,y,direct, 2) == me)
            {
                value += 230000;
                if(me == 1) value -= 500;
                continue ;
            }

            // 活三 ： 可直接一手变成活四，当敌方活三出现时，必须进行防守
            // 5. 活三A 222*0
            if(getLine(x,y,direct, -1) == me
               && getLine(x,y,direct, -2) == me
               && getLine(x,y,direct, -3) == me)
            {
                if(getLine(x,y,direct, 1) == empty)
                {
                    value += 750;
                    // 0222*0
                    if(getLine(x,y,direct, -4) == empty)
                    {
                        value += 3150;
                        if(me == 1)
                        {
                            value -= 500;
                        }
                    }
                }
                // 0222*1
                if(getLine(x,y,direct, -4) == empty
                   && (getLine(x,y,direct, 1) == rival || getLine(x,y,direct, 1) == boundary))
                    value += 500;
                continue ;
            }

            // 6. 活三B 2220*
            if(getLine(x,y,direct, -1) == empty
               && getLine(x,y,direct, -2) == me
               && getLine(x,y,direct, -3) == me
               && getLine(x,y,direct, -4) == me)
            {
                value += 350;
                continue ;
            }

            // 死三 ： 能够得到死四的三，即便不去防守，下一手也只能形成死四，仍然守的住
            // 7. 死三A 22*2
            if(getLine(x,y,direct, -1) == me
               && getLine(x,y,direct, -2) == me
               && getLine(x,y,direct, 1) == me)
            {
                value += 600;
                // 022*20
                if(getLine(x,y,direct, -3) == empty
                   && getLine(x,y,direct, 2) == empty)
                {
                    value += 3150;
                    continue ;
                }
                //122*21
                if((getLine(x,y,direct, -3) == rival || getLine(x,y,direct, -3) == boundary)
                    && (getLine(x,y,direct, 2) == rival || getLine(x,y,direct, 2) == boundary)){
                    continue ;
                }
                else {
                    value += 700;
                    continue ;
                }
            }

            // 活二 ： 能够形成活三的二，如果能够形成较多的活二棋型，对局势有利
            // 8. 活二数量 (!1)22*(!1)
            if(getLine(x,y,direct, -1) == me
               && getLine(x,y,direct, -2) == me
               && getLine(x,y,direct, -3) != rival
               && getLine(x,y,direct, 1) != rival)
                cnt_live_2++;

            // 周围如果已有我方棋子数目比较多的话，适当增加一下权值，越多机会越大
            int surround = 0;
            for (int k = -4; k <= 0; k++){
                int tmp = 0;
                for (int l = 0; l <= 4; l++){
                    if(getLine(x,y,direct, k+l) == me)
                        tmp++;
                    else if((getLine(x,y,direct, k+l) == rival || getLine(x,y,direct, k+l) == boundary)){
                        tmp = 0;
                        break;
                    }
                }
                surround += tmp;
            }
            value += surround * 15;
        }
        if(cnt_live_2 >= 2){
            value += 3000;
            if(me == 1) value -= 100;
        }
        return value;
    }

int MainWindow::score(int x, int y){
    
    int scoreSum=0;
    // playerwhite -》1
    int handOn= (player==playerblack)?2:1;
    
    if(board[x][y]!=0){
        return -1;
    }
    else{
        // ver 1
        int playerNum=0;//对方子个数
        int cpuNum=0; // 我方子个数
        int emptyNum=0;//空白位个数
        
        // 我方评估
        for(int direct =1;direct<=8;direct++){
            playerNum=0;
            cpuNum=0;
            emptyNum=0;
            for(int step = 1;step<=4;step++)
            {
//                qDebug("goP%d,%d:%d,%d,%d",x,y,goP.X,goP.Y,goP.score);
                if(getLine(x,y,direct,step)==handOn){
                    cpuNum++;
                }
                else if (getLine(x,y,direct,step)==0) {
                    emptyNum++;
                }
                else {
                    break;
                    }  
            }
            
            if(cpuNum==0){
                //normal
                scoreSum += 5;
            }
            else if (cpuNum==1) {
                //活二
                scoreSum += 10;
            }
            else if (cpuNum==2) {
                if(emptyNum==1){
                    //死三
                    scoreSum += 25;
                }
                else if(emptyNum==2){
                    // 活三
                    scoreSum += 50;
                }
            }
            else if(cpuNum==3){
                    if(emptyNum==1){
                        //死四
                        scoreSum += 55;
                    }
                    else if (emptyNum==2) {
                        // 活四
                        scoreSum += 300;
                    }
            }
            else if(cpuNum>=4){
                    scoreSum+=30000;
                    }
            
            emptyNum = 0;
            
            for(int step = 1;step<=4;step++)
            {
                
                if(getLine(x,y,direct,step)==3-handOn){
                    playerNum++;
                }
                else if (getLine(x,y,direct,step)==0) {
                    emptyNum++;
                }
                else {
                    break;
                    }  
            }
            
            if(playerNum==1){
                // 杀二
                scoreSum+=10;
            }
            else if (playerNum==2) {
                // 杀三
                if(emptyNum==1){
                    // 死三
                    scoreSum +=30;
                }
                else if(emptyNum==2){
                    // 活三
                    scoreSum += 40;
                }
            }
            else if (playerNum==3) {
                // 杀四
                if(emptyNum==1){
                    //死四
                    scoreSum +=60;
                }
                else if(emptyNum==2){
                    // 活四
                    scoreSum += 200;
                }
            }
            else if(playerNum==4){
                // 杀五
                    scoreSum += 20000;
            }

        }

    return scoreSum;
    }
}

int MainWindow::getLine(int x ,int y,int direction,int step){
    switch (direction)
    {
    case 1:
        x += step;// 向右
        break;
    case 2:
        x -= step; //向左
        break;
    case 3:
        x += step;
        y += step; // 右下
        break;
    case 4:
        x += step;
        y -= step; // 右上
        break;
    case 5:
        x -= step;
        y += step; // 左下
        break;
    case 6:
        x -= step;
        y -= step; // 左上
        break;
    case 7:
        y += step; // 向下
        break;
    case 8:
        y -= step; // 向上
    default:
        break;
    }
    if(x<4||x>=COL+4||y<4||y>=COL+4){
        return -1;
    }
    else{
//        qDebug("%d",board[x][y]);
    return board[x][y];
        }
}

void MainWindow::on_pushButton_clicked()
{
    writeCSV();
    initgame();


}

void MainWindow::timeClock(){

    onTimeOut();
    QTimer *pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    // 启动定时器
    pTimer->start();

}

void MainWindow::onTimeOut()
{
    // 获取系统当前时间
    QDateTime dateTime = QDateTime::currentDateTime();
    // 显示的内容
//    ui->timeClock->display(dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz"));
    ui->timeClock->display(dateTime.toString("HH:mm:ss"));
}

void MainWindow::eveCpuGo(){
    if(gamemode== started){
        if(player==playerblack){
            cpuGo();
        }
        else {
            cpuGo2();
        }
    }
    else {
         Timer->stop();
    }
}

void MainWindow::pveCpuGo(){
    if(gamemode== started){

            cpuGo2();
            Timer->stop();
            setMouseTracking(true);
            PVE_ON_P=true;
    }
    else {
         Timer->stop();
    }



}
void MainWindow::stepRecord(int chessX,int chessY){

    record->count =step_count;
    record->x = chessX-3;
    record->y= chessY-3;
    record->player = (player==playerblack)?1:2;
//    record->player = QString("Black");

    record->next = (RECORDS*)malloc(sizeof(RECORDS));
    record = record->next;
    record->next=NULL;

}


void MainWindow::on_homeButton_clicked()
{
    writeCSV();
    // ！！！这个地方会导致内存爆炸，可能与线程有关！！！
    if(gametype==EVE){
        Timer->stop();
    }else{}

    start *w = new start;
    w->show();
    w->gametype = PVE;

    this->hide();
}

void MainWindow::writeCSV(){

    int time = globalTime.elapsed()/1000.0;
    QFile goData("gameRecord.csv");
    int count =1;
   record_p = HEAD->next;
    if(goData.open(QIODevice::ReadOnly)){
        int fsize=goData.size();
        if(fsize==0){count=0;}
        else{
                int i = fsize-10;
                while (goData.read(1)!=QString('>')) {
                    i++;
                    goData.seek(i);
                }

                QString lastLine=goData.readLine();
                QStringList List = lastLine.split(',');
                QString counto = List[0];
                count = counto.toInt();
                qDebug()<<count;
            }

    }else {count=0;}
    goData.close();
    count+=1;
    QStringList lines;
    QString cGametype;
        if(gametype == PVE || gametype == PVE2){
            cGametype=QString("PVE");
        }
        else if (gametype == PVP) {
            cGametype=QString("PVP");
        }
        else {
            cGametype=QString("EVE");
        }
    QString cGamewinner;
    if(gamemode==started){
        cGamewinner =QString("Undone");
    }
    else {
        cGamewinner  = (player==playerwhite)?QString("white"):QString("black");
    }

    QString title= QString("Rec: %1,").arg(count);
    QString title2= QString("%1,").arg(cGametype);
    QString title3 = QString("%1,").arg(cGamewinner);
    QString title34 = QString("%1 s,").arg(QString::number(time));
    QString title4 = QString("%1\n").arg(step_count);
    QString endLine=QString("->%1,%2\n").arg(count).arg(step_count);

    QString tempData;
//    QString tempPlayer;
    int tempPlayer;
    while (record_p->next!=NULL) {
//        tempPlayer=(record_p->player==2)?QString("White"):QString("Black");
        tempPlayer=(record_p->player==2)?1:2;
        tempData =QString("%1,%2,%3,,%4,\n").arg(tempPlayer).arg(record_p->x).arg(record_p->y).arg(record_p->count);
        record_p = record_p->next;
        lines.append(tempData);
    }
//    lines << "black,5,13\n" << "white,11,12\n" << "20,21,22";

    if (goData.open(QIODevice::ReadWrite | QIODevice::Append))
    {
     goData.write(title.toStdString().c_str());
     goData.write(title2.toStdString().c_str());
     goData.write(title3.toStdString().c_str());
     goData.write(title34.toStdString().c_str());
     goData.write(title4.toStdString().c_str());

     for (int i = 0; i < lines.size(); i++)
     {
         goData.write(lines[i].toStdString().c_str());
     }
     goData.write(endLine.toStdString().c_str());
     goData.close();
    }

}

