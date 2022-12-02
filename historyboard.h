#ifndef HISTORYBOARD_H
#define HISTORYBOARD_H

#include <QWidget>
#include "gameset.h"

namespace Ui {
class HistoryBoard;
}

class HistoryBoard : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryBoard(QWidget *parent = 0);
    ~HistoryBoard();
    void initboard();
    int RESTART_SEEK=0;


private:
    Ui::HistoryBoard *ui;
    int i =RESTART_SEEK;
    int TEMPCOUNT=4;
    int tempCount=TEMPCOUNT;
    int count =0;

private slots:
    void readCSV();

    void on_pushButton_clicked();

protected:
    void paintEvent(QPaintEvent*);
    int board[COL+8][COL+8];
    int orderBoard[COL+8][COL+8];
    QTimer *Timer;
    int RECORD_X=0,RECORD_Y=0,RECORD_PLAYER=0;
//    RECORDS *HEAD;
//    RECORDS *record;

};

#endif // HISTORYBOARD_H
