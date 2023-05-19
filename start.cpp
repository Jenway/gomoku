#include "start.h"
#include "history.h"
#include "ui_start.h"

GAMETYPE start::gametype = PVE;

start::start(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::start)
{

    //    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    label = new QLabel(this);
    movie = new QMovie(":image/icon/miku2.gif");

    label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画
    label->show();
    ui->setupUi(this);

    label->setWindowTitle("Welcome !");
    this->setWindowIcon(QIcon(":image/icon/favicon2.png"));
    this->setWindowTitle("Welcome !");
}

start::~start()
{
    delete ui;
    delete label;
    delete movie;
}

void start::openMainWindow()
{

    MainWindow* mainwindow = new MainWindow;
    //    QObject::connect(mainwindow, &QWidget::destroyed, [mainwindow]() { delete mainwindow; });
    //    QDesktopWidget dw;
    //    int x= dw.width()*VIEW_VOL;
    //    int y=dw.height()*VIEW_VOL;
    int x = 2600 * VIEW_VOL;
    int y = 1800 * VIEW_VOL;
    mainwindow->setFixedSize(x, y);
    mainwindow->show();
    this->close();
    delete this;
}

void start::openHistoryPage()
{
    QFile goData("gameRecord.csv");
    if (goData.open(QIODevice::ReadOnly)) {
        History* h = new History();
        h->show();
        //        this->hide();
        goData.close();
    } else {
        QMessageBox msg;
        msg.critical(this, "错误", "Data Not Found!", msg.Yes);
    }
}

void start::on_AcceptButton_accepted()
{
    this->openMainWindow();
}

void start::on_AcceptButton_rejected()
{
    QApplication::quit();
}

void start::on_PVP_BUTTON_toggled(bool checked)
{
    if (checked) {
        this->gametype = PVP;
    }
}

void start::on_PVE_BUTTON_toggled(bool checked)
{
    if (checked) {
        this->gametype = PVE;
    }
}

void start::on_EVE_BUTTON_toggled(bool checked)
{
    if (checked) {
        this->gametype = EVE;
    }
}

void start::on_PVE2_BUTTON_toggled(bool checked)
{
    if (checked) {
        this->gametype = PVE2;
    }
}

void start::on_HISTORY_BUTTON_clicked()
{
    openHistoryPage();
}
