#ifndef GAMESET_H
#define GAMESET_H

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QFont>
#include <QMainWindow>
//#include <QDesktopWidget>
#include <QDebug>
#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QString>
//#include <QtMultimedia/

#define SIZE_VOL 2
#define VIEW_VOL 0.4

#define EDGE (75/SIZE_VOL)
#define BLOCK_SIZE (70/SIZE_VOL)
#define LENGTH (70 * 16/SIZE_VOL)
#define GO_SIZE (30/SIZE_VOL)
#define COL 15


enum PLAYER{
    playerwhite,
    playerblack
};

enum GAMEMODE{
    unstarted,
    started
};

enum GAMETYPE{
    PVP,
    PVE,
    PVE2,
    EVE
};



typedef struct RECORDS
{
    int x;
    int y;
    int count;
    int player;
    struct RECORDS *next;

}RECORDS;

typedef struct GOS
{
    int X;
    int Y;
    int score;
}GOS;

//int RESTART_SEEK=0;

#endif // GAMESET_H
