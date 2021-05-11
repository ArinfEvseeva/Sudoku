#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QObject>
#include <QAbstractTableModel >

//http://itnotesblog.ru/note.php?id=159


class SudokuModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SudokuModel();

    virtual int
    rowCount(const QModelIndex &parent = QModelIndex()) const  override;

    virtual int
    columnCount(const QModelIndex &parent = QModelIndex()) const  override;

    QVariant data( const QModelIndex& index, int role ) const override;

    bool setData( const QModelIndex& index, const QVariant& value, int role ) override;




private:
    void FilltestData()
    {
        m_sudokuMatrix[0][0] = 1;
        m_sudokuMatrix[0][1] = 2;



        m_sudokuMatrix[1][0] = 10;
        m_sudokuMatrix[1][1] = 20;



    }



    static const int nRowLvl = 2;
    static const int nColLvl = 2;

    unsigned int m_sudokuMatrix[nRowLvl][nColLvl];
};





#endif // SUDOKUMODEL_H
