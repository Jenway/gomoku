#include "history.h"
#include "ui_history.h"

History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    this->setWindowTitle("History");
}

History::~History()
{
    delete ui;
}





void History::on_pushButton_clicked()
{
    class HistoryBoard *w = new class HistoryBoard;
    QDesktopWidget dw;
//    int x= dw.width()*VIEW_VOL;
//    int y=dw.height()*VIEW_VOL;
    int x= 2600*VIEW_VOL;
    int y= 1800*VIEW_VOL;
    w->setFixedSize(x,y);
    w->RESTART_SEEK=0;
    w->show();
    this->hide();
}
