#include "sudokumodel.h"

#include <QSize>

SudokuModel::SudokuModel()
{
    CreateLvls();
FilltestData();
}

int SudokuModel::rowCount(const QModelIndex &parent) const
{
    return getDifficultLvl().GetRowsCnt();
}

int SudokuModel::columnCount(const QModelIndex &parent) const
{
    return getDifficultLvl().GetColumnsCnt();
}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{

    if ( role == Qt::TextAlignmentRole)
           return Qt::AlignCenter;



    if(!index.isValid() || (Qt::EditRole != role && Qt::DisplayRole !=role))
        return QVariant();

    int nRow = index.row();
    int nCol = index.column();

    uint resValue = 0;
    if(!getDifficultLvl().GetItemValue(nRow, nCol,resValue))
        return QVariant();


    return resValue;
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

    getDifficultLvl().SetItemValue(nRow, nCol, nSettingValue);


    emit dataChanged(index,index);

    return true;
}

void SudokuModel::SetDifficult(const QString& strDifficultName)
{
    beginResetModel();
    int nMenuIndex = 0;
    for(; nMenuIndex < m_allLevels.count(); ++nMenuIndex)
    {
       if( m_allLevels[nMenuIndex] == strDifficultName)
           break;
    }

    m_nMenuIndex = nMenuIndex;

    endResetModel();
}

QVector<SudokuLevel> SudokuModel::GetCreatedLvls() const
{
    return m_allLevels;
}

void SudokuModel::CreateLvls()
{
    m_allLevels =
    {
        SudokuLevel("4x4",4),
        SudokuLevel("9x9",9),
        SudokuLevel("16x16",16)
    };
}
