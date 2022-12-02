#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>

namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = 0);
    ~History();

private:
    Ui::History *ui;
};

#endif // HISTORY_H
