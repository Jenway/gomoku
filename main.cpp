#include "start.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    start* w = new start;
    w->show();
    return a.exec();
}
