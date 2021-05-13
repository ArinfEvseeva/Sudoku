#ifndef MAINWINDOWREFACTOR_H
#define MAINWINDOWREFACTOR_H

#include "sudokumodel.h"

#include <QMainWindow>
#include <QObject>


class QGridLayout;

class MainWindowRefactor : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowRefactor(QWidget *parent = nullptr);

private:
    void CreateControls();
    void CreatePlayArea();
    void CreatePlayButtons();
    void CreateLvlsMenu();

    void DestroyPlayArea();
    void DestroyPlayButtons();

    QGridLayout* GetMainLayout() const;

public slots:
    void OnButtonClicked();
    void OnLvlSelected();

signals:




private:
    SudokuModel m_sudokuModel;
};

#endif // MAINWINDOWREFACTOR_H
