#include "gameover.h"
#include "gameset.h"
#include "mainwindow.h"
#include "ui_gameover.h"

gameover::gameover(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::gameover)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    label = new QLabel(this);
    movie = new QMovie(":image/icon/miku1.gif");
    label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画

    label->show();
}

gameover::~gameover()
{
    delete ui;
    delete label;
    delete movie;
}

void gameover::on_buttonBox_rejected()
{
    QApplication::quit();
}

void gameover::on_buttonBox_accepted()
{
    this->deleteLater();
}
