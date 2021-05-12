#include "mainwindowrefactor.h"
#include <QGridLayout>
#include <QHeaderView>

#include <QPainter>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QTableView>


MainWindowRefactor::MainWindowRefactor(QWidget *parent) : QMainWindow(parent)
{
    CreateControls();
}

void MainWindowRefactor::CreateControls()
{
    setWindowTitle("Sudoku");
    resize(QSize(800,600));

    //создание виджета для отрисовки (главный виджет)
    QWidget* pCentralWidget = new QWidget;
    setCentralWidget(pCentralWidget);

    //создание компоновочного контейнера
    QGridLayout* pMainLayout = new QGridLayout();
    pCentralWidget->setLayout(pMainLayout);

    //создание игрового поля
    CreatePlayArea();

    //создание кнопок управления
    CreatePlayButtons();
}

void MainWindowRefactor::CreatePlayArea()
{
    //создание игрового поля и привязка к компоновочному
    //контейнеру
    QTableView*  pPlayArea = new QTableView();
    pPlayArea->setModel(&m_sudokuModel);
    QGridLayout* pMainLayout = GetMainLayout();
    pMainLayout->addWidget(pPlayArea,0,0);


    //скрытие вертикальной нумерации
    QHeaderView* pVerticalHeader = new QHeaderView(Qt::Orientation::Vertical,pPlayArea);
    pVerticalHeader->hide();
    pPlayArea->setVerticalHeader(pVerticalHeader);

    //скрытие горизонтальной нумерации
    QHeaderView* pHorizHeader = new QHeaderView(Qt::Orientation::Horizontal, pPlayArea);
    pHorizHeader->hide();
    pPlayArea->setHorizontalHeader(pHorizHeader);
    pPlayArea->setObjectName(QString::fromUtf8("tableView"));
    pPlayArea->setFrameShape(QFrame::StyledPanel);
    pPlayArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //установка ширины ячейки
    const int nCellSizeVertical = pPlayArea->height() / m_sudokuModel.columnCount();
    for(int nRow = 0; nRow < m_sudokuModel.rowCount(); ++nRow)
        pPlayArea->setRowHeight(nRow,nCellSizeVertical);


    //установка высоты ячейки
    const int nCellSizeHorizontal = pPlayArea->width() / m_sudokuModel.rowCount();
    for(int nColumn = 0; nColumn < m_sudokuModel.columnCount(); ++nColumn)
       pPlayArea->setColumnWidth(nColumn,nCellSizeHorizontal);


    //шрифт в ячейке
    QFont font("Arial",21,1);
    pPlayArea->setFont(font);
}

void MainWindowRefactor::CreatePlayButtons()
{
    QVBoxLayout* pMainButtonLayout = new QVBoxLayout();

    QPushButton* pNewGameButton = new QPushButton("new game");
    pMainButtonLayout->addWidget(pNewGameButton);


    QGridLayout* pButtonsNumberLayout = new QGridLayout;
    pMainButtonLayout->addLayout(pButtonsNumberLayout, 1);

    const int nButtonsInRowCnt = 4;
    for (int nRow = 0, nCounter = 0, splitCouner = 0; nRow < m_sudokuModel.getDifficultLvl(); ++nRow,++splitCouner)
    {
        QPushButton* pNumberButton = new QPushButton(QString::number( ++nCounter));
        pNumberButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //TODO: connect signal and slots
        //QObject::connect(pNumberButton,&QPushButton::clicked,this,&MainWindowRefactor::OnCustiomAction);


        if(splitCouner == nButtonsInRowCnt)
            splitCouner = 0;


        pButtonsNumberLayout->addWidget(pNumberButton,nRow/nButtonsInRowCnt, splitCouner);

    }

    QGridLayout* pMainLayout = GetMainLayout();
    pMainLayout->addLayout(pMainButtonLayout,0,1);
}

QGridLayout *MainWindowRefactor::GetMainLayout() const
{
    QWidget *pCentralWidget = centralWidget();
    QGridLayout* pMainLayout = static_cast<QGridLayout*>(pCentralWidget->layout());
    return pMainLayout;
}
