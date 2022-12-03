#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMovie>
#include <QLabel>

#include "gameset.h"
#include "gameover.h"
#include "start.h"
#include "QTime"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    PLAYER player;
    GAMEMODE gamemode;
    GAMETYPE gametype;
    RECORDS *HEAD;
    RECORDS *record;
    RECORDS *record_p;
    int step_count=0;
    QTimer *Timer;

    int board[COL+8][COL+8];

    void initgame();
    void stepRecord(int chessX,int chessY);


private:
    Ui::MainWindow *ui;
    QPainter *painter;
    int mouseX=-1,mouseY=-1;
    bool first_go_done;// 第一棋子
    bool PVE_ON_P = true;

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void timeClock();
    int judge(int x,int y);
    void cpuGo();
    void cpuGo2();
    int score(int chessx,int chessy);
    int score2(int chessx,int chessy,int me);

    void afterGo(int chessX,int chessY);

    int getLine(int x ,int y,int direction,int step);
    void writeCSV();
private slots:
    void on_pushButton_clicked();
    void onTimeOut();
    void eveCpuGo();
    void pveCpuGo();
    void on_homeButton_clicked();
};
#endif // MAINWINDOW_H
