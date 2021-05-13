#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T22:10:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwindowrefactor.cpp \
    matrix.cc \
    modelEntities.cpp \
    rdarray.cc \
    sudokumodel.cpp

HEADERS  += mainwindow.h \
    include.h \
    mainwindowrefactor.h \
    matrix.h \
    modelEntities.h \
    rdarray.h \
    sudokumodel.h

FORMS    += mainwindow.ui
