#include "sudokumodel.h"

#include <QSize>

SudokuModel::SudokuModel()
{
FilltestData();
}

int SudokuModel::rowCount(const QModelIndex &parent) const
{
    return nRowLvl;
}

int SudokuModel::columnCount(const QModelIndex &parent) const
{
    return nColLvl;
}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{

    if ( role == Qt::TextAlignmentRole)
           return Qt::AlignCenter;



    if(!index.isValid() || (Qt::EditRole != role && Qt::DisplayRole !=role))
        return QVariant();

    int nRow = index.row();
    int nCol = index.column();

    return m_sudokuMatrix[nRow][nCol];
}

bool SudokuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != Qt::EditRole)
        return false;

    int nRow = index.row();
    int nCol= index.column();

    bool isConversionOk = false;
    unsigned int nSettingValue = value.toUInt(&isConversionOk);
    if(!isConversionOk)
        return false;

    m_sudokuMatrix[nRow][nCol] = nSettingValue;

    emit dataChanged(index,index);

    return true;
}
