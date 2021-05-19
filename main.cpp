#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>

//sudoku::matrix mat();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow test;
    test.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
