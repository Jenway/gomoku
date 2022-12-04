#include "historyboard.h"
#include "ui_historyboard.h"

int RESTART_SEEK=restart::RESTART_SEEK;

HistoryBoard::HistoryBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryBoard)
{
    ui->setupUi(this);
    initboard();
//    i = RESTART_SEEK;
//    qDebug()<<restart::RESTART_SEEK;

    Timer = new QTimer(this);
    // 设置定时间隔
    Timer->setInterval(300);
    connect(Timer, SIGNAL(timeout()), this, SLOT(readCSV()));
    // 启动定时器
//    record = (RECORDS*)malloc(sizeof(RECORDS));
//    HEAD = record;


    Timer->start();

}

HistoryBoard::~HistoryBoard()
{
    delete ui;
}

void HistoryBoard::readCSV(){

    QFile goData("gameRecord.csv");
    goData.open(QIODevice::ReadOnly);
    goData.seek(i);
    line = goData.readLine();
    i+=line.length();
    QStringList lines =line.split(",");
    int temp;
    int tempNum=3;
            foreach (QString s, lines)
            {
                temp=s.toInt();
//                    qDebug() << temp;
                    if(tempNum == 3){
                        RECORD_PLAYER = temp;
                    }
                    else if(tempNum ==2){
                        RECORD_X = temp;
                    }
                    else if(tempNum==1){
                        RECORD_Y = temp;
                    }
                    tempNum -=1;
            }

    if (goData.read(2)==QString("->")){
            Timer->stop();
            qDebug("Oh!!!!");
        }

        board[RECORD_X+3][RECORD_Y+3]=RECORD_PLAYER;
        qDebug()<<RECORD_X<<RECORD_Y<<RECORD_PLAYER;
        orderBoard[RECORD_X+3][RECORD_Y+3]=count;
        count++;
        this->update();
    goData.close();
}

void HistoryBoard::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setColor(QColor(100,149,237));
    QBrush brush(QColor(237,209,216));
    brush.setStyle(Qt::HorPattern);
    painter.setPen(pen);
    painter.setBrush(brush);

    for(int i = 0; i <= COL+1;i++){

    painter.drawLine(QPointF(EDGE,i*BLOCK_SIZE+EDGE),
                     QPointF(LENGTH+EDGE,i*BLOCK_SIZE+EDGE));
    painter.drawLine(QPointF(i*BLOCK_SIZE+EDGE,EDGE),
                     QPointF(i*BLOCK_SIZE+EDGE,EDGE+LENGTH));
    }


    QRectF rect(3*EDGE + COL*(BLOCK_SIZE+2),EDGE, 300, 200);
    painter.drawRect(rect);  //绘制个矩形
//    if(gamemode == started){
//        QString str = (player == playerblack)?QString("\nproject\ngomoku\nBlack Go!"):QString("\nproject\ngomoku\nWhite Go!");
//        painter.drawText(rect, Qt::AlignHCenter,str);
//    }
//    else {
        QFont font=QFont("Arial Black", 15, QFont::Bold, false);
        painter.setFont(font);
//        if(player == playerwhite){painter.setPen(QColor(47,47,47));}
        /*else{*/painter.setPen(QColor(91,165,133));/*}*/
        QString str = /*(player == playerwhite)?*/QString("\nP-Black\nWin!")/*:QString("\nP-White\nWin!")*/;
        painter.drawText(rect, Qt::AlignHCenter, str);
//    }



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

    QString order;
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
            if(orderBoard[i+3][j+3]==0){}
            else {
                // 棋子的序号
                painter.setPen(QColor(Qt::white));
                QFont font2=QFont("Arial Black",8, QFont::Bold, false);
                painter.setFont(font2);
                order =QString("%1").arg(orderBoard[i+3][j+3]);
                QRectF rect2(EDGE+i*BLOCK_SIZE-3*GO_SIZE/2,
                             EDGE +j*BLOCK_SIZE-GO_SIZE,GO_SIZE*3,GO_SIZE*3);
                painter.drawText(rect2, Qt::AlignHCenter,order);
            }
        }
    }
}

void HistoryBoard::on_pushButton_clicked()
{
    initboard();
    Timer->start();
}

void HistoryBoard::initboard(){

    count =0;
    for(int i =0;i<COL+8;i++){
        for(int j=0;j<COL+8;j++){
            board[i][j]=0;
            orderBoard[i][j]=0;
        }
    }
    tempCount = TEMPCOUNT;
//    i = RESTART_SEEK;
//    qDebug()<<"ALAH"<<RESTART_SEEK;

    QFile goData("gameRecord.csv");
    goData.open(QIODevice::ReadOnly);
    goData.seek(i);
    line = goData.readLine();
    i+=line.length();
    goData.close();
}

void HistoryBoard::on_pushButton_2_clicked()
{
    emit siganal_hisboardToHistory();
    Timer->stop();
    this->hide();
}
