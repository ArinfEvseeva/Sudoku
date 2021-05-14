#include "mainwindowrefactor.h"
#include <QGridLayout>
#include <QHeaderView>

#include <QMenuBar>
#include <QPainter>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QSizePolicy>

MainWindowRefactor::MainWindowRefactor(QWidget *parent) : QMainWindow(parent)
{
    CreateControls();
}

void MainWindowRefactor::CreateControls()
{
    setWindowTitle("Sudoku");
    resize(QSize(800,600));


    //создание виджета для отрисовки (главный виджет)
    QWidget* pCentralWidget = new QWidget(this);
    setCentralWidget(pCentralWidget);

    //создание компоновочного контейнера
    QGridLayout* pMainLayout = new QGridLayout();
    pCentralWidget->setLayout(pMainLayout);

    //создание игрового поля
    CreatePlayArea();

    //создание кнопок управления
    CreatePlayButtons();

    //создание меню с уровнями сложности
    CreateLvlsMenu();
}

void MainWindowRefactor::CreatePlayArea()
{
    //создание игрового поля и привязка к компоновочному
    //контейнеру
    QTableView*  pPlayArea = new QTableView();
    pPlayArea->setModel(&m_sudokuModel);
    pPlayArea->setObjectName(QString::fromUtf8("play_area"));
    pPlayArea->setFrameShape(QFrame::StyledPanel);
    pPlayArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pPlayArea->setSelectionBehavior(QAbstractItemView::SelectItems);
    pPlayArea->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    QGridLayout* pMainLayout = GetMainLayout();

    //pMainLayout.set
    pMainLayout->addWidget(pPlayArea,0,0);


    //скрытие вертикальной нумерации
    QHeaderView* pVerticalHeader = new QHeaderView(Qt::Orientation::Vertical,pPlayArea);
    pVerticalHeader->hide();
    pPlayArea->setVerticalHeader(pVerticalHeader);

    //скрытие горизонтальной нумерации
    QHeaderView* pHorizHeader = new QHeaderView(Qt::Orientation::Horizontal, pPlayArea);
    pHorizHeader->hide();
    pPlayArea->setHorizontalHeader(pHorizHeader);

    //шрифт в ячейке
    QFont font("Arial",20,1);
    pPlayArea->setFont(font);

    pPlayArea->resizeRowsToContents();
    pPlayArea->resizeColumnsToContents();

}

void MainWindowRefactor::CreatePlayButtons()
{


    QVBoxLayout* pMainButtonLayout = new QVBoxLayout();
    pMainButtonLayout->setObjectName(QString::fromUtf8("play_buttons"));
    QPushButton* pNewGameButton = new QPushButton("new game");

    pMainButtonLayout->addWidget(pNewGameButton);

    pNewGameButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QGridLayout* pButtonsNumberLayout = new QGridLayout;
    pButtonsNumberLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

    pMainButtonLayout->addLayout(pButtonsNumberLayout, 1);
    pMainButtonLayout->addStretch(100);

    const int nButtonsInRowCnt = 4;
    for (int nRow = 0, nCounter = 0, splitCouner = 0; nRow < m_sudokuModel.getDifficultLvl().GetDifficultValue(); ++nRow,++splitCouner)
    {
        QPushButton* pNumberButton = new QPushButton(QString::number( ++nCounter));

        pNumberButton->setMaximumSize(50,50);
        pNumberButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        //connect signal and slots
        QObject::connect(pNumberButton,&QPushButton::clicked,this,&MainWindowRefactor::OnButtonClicked);


        if(splitCouner == nButtonsInRowCnt)
            splitCouner = 0;

        pButtonsNumberLayout->addWidget(pNumberButton,nRow/nButtonsInRowCnt, splitCouner);
    }



    QGridLayout* pMainLayout = GetMainLayout();
    pMainLayout->addLayout(pMainButtonLayout,0,1);

}

void MainWindowRefactor::CreateLvlsMenu()
{
    QMenuBar* pLvlMenuBar = new QMenuBar(this);
    setMenuBar(pLvlMenuBar);
    QMenu* pLvlMenu = new QMenu("Levels",pLvlMenuBar);
    pLvlMenuBar->addMenu(pLvlMenu);



    const QVector<QString>& createdGameLvls = LevelsFactory::GetLevelsName();
    for(const QString& lvl : createdGameLvls)
    {
        QAction* pGameLvl = new QAction(lvl,pLvlMenu);
        pGameLvl->setData(lvl);
        //connect signal and slots
        QObject::connect(pGameLvl,&QAction::triggered,this,&MainWindowRefactor::OnLvlSelected);
        pLvlMenu->addAction(pGameLvl);
    }
}

void MainWindowRefactor::DestroyPlayArea()
{
    QGridLayout* pMainLayout = GetMainLayout();
    QTableView*  pPlayArea = findChild<QTableView*>("play_area");
    pMainLayout->removeWidget(pPlayArea);
    pPlayArea->deleteLater();
}

void remove ( QLayout* layout )
{
    QLayoutItem* child;
    while ( layout->count() != 0 ) {
        child = layout->takeAt ( 0 );
        if ( child->layout() != 0 ) {
            remove ( child->layout() );
        } else if ( child->widget() != 0 ) {
            delete child->widget();
        }
        delete child;
    }
}

void MainWindowRefactor::DestroyPlayButtons()
{
    QGridLayout* pMainLayout = GetMainLayout();
    QVBoxLayout*  pMainButtonLayout = findChild<QVBoxLayout*>("play_buttons");
    remove(pMainButtonLayout);
    pMainLayout->removeItem(pMainButtonLayout);
    pMainButtonLayout->deleteLater();
}

QGridLayout *MainWindowRefactor::GetMainLayout() const
{
    QWidget *pCentralWidget = centralWidget();
    QGridLayout* pMainLayout = static_cast<QGridLayout*>(pCentralWidget->layout());
    return pMainLayout;
}

void MainWindowRefactor::OnButtonClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) // this is the type we expect
     {
         const QString& buttonText = pButton->text();

         QTableView*  pPlayArea = findChild<QTableView*>("play_area");
         if(pPlayArea)
         {
            QModelIndex index = pPlayArea->selectionModel()->currentIndex();
            m_sudokuModel.setData(index,buttonText,Qt::EditRole);
            pPlayArea->setFocus();
         }
    }
}

void MainWindowRefactor::OnLvlSelected()
{
    QAction* pCheckedLvl = qobject_cast<QAction*>(sender());
    if (pCheckedLvl)
    {
        DestroyPlayArea();
        DestroyPlayButtons();
        const QString&  lvlLabel = pCheckedLvl->data().toString();
        m_sudokuModel.SetDifficult(lvlLabel);
        CreatePlayArea();
        CreatePlayButtons();
    }

}
