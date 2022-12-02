#ifndef START_H
#define START_H

#include <QDialog>
#include "mainwindow.h"
#include "QMessageBox"
namespace Ui {
class start;
}

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();
    static GAMETYPE gametype;
    void readCSV();

private slots:

    void on_AcceptButton_accepted();

    void on_AcceptButton_rejected();

    void on_PVP_BUTTON_toggled(bool checked);

    void on_PVE_BUTTON_toggled(bool checked);

    void on_EVE_BUTTON_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::start *ui;


};

#endif // START_H
