#include "mainwindow.h"
#include <QApplication>
#include "gamecontroller.h"

GameController * gc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(800,600);
    w.setWindowTitle("DxBall");
    w.show();
    w.setFocus();

    return a.exec();
}
