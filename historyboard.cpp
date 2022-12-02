#include "historyboard.h"
#include "ui_historyboard.h"

HistoryBoard::HistoryBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryBoard)
{
    ui->setupUi(this);
}

HistoryBoard::~HistoryBoard()
{
    delete ui;
}
