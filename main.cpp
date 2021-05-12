#include "mainwindow.h"
#include "mainwindowrefactor.h"
#include <QApplication>

//sudoku::matrix mat();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowRefactor test;
    test.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
