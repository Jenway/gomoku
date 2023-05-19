#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QLabel>
#include <QMovie>

namespace Ui {
class gameover;
}

class gameover : public QDialog {
    Q_OBJECT

public:
    explicit gameover(QWidget* parent = 0);
    ~gameover();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::gameover* ui;
    QLabel* label;
    QMovie* movie;
};

#endif // GAMEOVER_H
