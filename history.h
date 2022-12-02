#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "historyboard.h"

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
    void on_pushButton_clicked();

private:
    Ui::History *ui;
};

#endif // HISTORY_H
