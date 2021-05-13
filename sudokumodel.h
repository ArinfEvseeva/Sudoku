#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include "modelEntities.h"

#include <QObject>
#include <QAbstractTableModel >
#include <QVector>

//http://itnotesblog.ru/note.php?id=159


class SudokuModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SudokuModel();

    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    bool setData( const QModelIndex& index, const QVariant& value, int role ) override;


    SudokuLevel& getDifficultLvl()
    {
        return m_allLevels[m_nMenuIndex];
    }

    const SudokuLevel& getDifficultLvl() const
    {
        return m_allLevels[m_nMenuIndex];
    }

    void SetDifficult(const QString& strDifficultName);
    QVector<SudokuLevel> GetCreatedLvls() const;

private:
    void CreateLvls();

    void FilltestData()
    {
        m_sudokuMatrix[0][0] = 1;
        m_sudokuMatrix[0][1] = 2;
 m_sudokuMatrix[0][2] = 3;


        m_sudokuMatrix[1][0] = 10;
        m_sudokuMatrix[1][1] = 20;
         m_sudokuMatrix[1][2] = 30;


         m_sudokuMatrix[2][0] = 100;
         m_sudokuMatrix[2][1] = 200;
          m_sudokuMatrix[2][2] = 300;

    }


    static const int nDifcicult = 3;
    static const int nRowLvl = nDifcicult;
    static const int nColLvl = nDifcicult;



    unsigned int m_sudokuMatrix[nRowLvl][nColLvl];


    QVector<SudokuLevel> m_allLevels;
    uint m_nMenuIndex = 0;
};





#endif // SUDOKUMODEL_H
