#include "gameover.h"
#include "ui_gameover.h"
#include "gameset.h"
#include "mainwindow.h"

gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie(":image/icon/miku1.gif");
    label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画
    label->show();
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_buttonBox_rejected()
{
    QApplication *q;
    q->quit();
}


void gameover::on_buttonBox_accepted()
{
    this->hide();
}
