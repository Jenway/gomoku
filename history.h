#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QTreeWidget>
#include <QCheckBox>
#include "historyboard.h"
#include "gameset.h"
#include "QPushButton"

//extern  int RESTART_SEEK;

class restart     //新建一个类存放全局变量
{
public:
     static int RESTART_SEEK;

};

namespace Ui {
class History;
}

class History : public QWidget
{

    Q_OBJECT

public:


    explicit History(QWidget *parent = 0);
    ~History();



protected:



private slots:

    void on_Button_clicked();
private:
    Ui::History *ui;
};

#endif // HISTORY_H
