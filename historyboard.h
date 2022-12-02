#ifndef HISTORYBOARD_H
#define HISTORYBOARD_H

#include <QWidget>

namespace Ui {
class HistoryBoard;
}

class HistoryBoard : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryBoard(QWidget *parent = 0);
    ~HistoryBoard();

private:
    Ui::HistoryBoard *ui;
};

#endif // HISTORYBOARD_H
