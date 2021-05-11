#include "mainwindow.h"
#include <QApplication>

//sudoku::matrix mat();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
