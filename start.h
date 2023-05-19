#ifndef START_H
#define START_H

#include "QMessageBox"
#include <QDialog>
#include <mainwindow.h>
namespace Ui {
class start;
}

class start : public QDialog {
    Q_OBJECT
public:
    explicit start(QWidget* parent = 0);
    ~start();
    static GAMETYPE gametype;
    void openHistoryPage();
    void openMainWindow();

private slots:

    void on_AcceptButton_accepted();

    void on_AcceptButton_rejected();

    void on_PVP_BUTTON_toggled(bool checked);

    void on_PVE_BUTTON_toggled(bool checked);

    void on_EVE_BUTTON_toggled(bool checked);

    void on_PVE2_BUTTON_toggled(bool checked);

    void on_HISTORY_BUTTON_clicked();

private:
    QLabel* label;
    QMovie* movie;
    Ui::start* ui;
};

#endif // START_H
