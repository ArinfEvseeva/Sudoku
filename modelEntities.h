#ifndef SUDOKULEVEL_H
#define SUDOKULEVEL_H

#include <QString>
#include <QVector>

//model entities

//уровень игры
class SudokuLevel
{
public:
    SudokuLevel(const QString& name, int difficultValue) : m_name{name},
                                                           m_difficultValue{difficultValue},
                                                           m_columnsCnt{difficultValue},
                                                           m_rowsCnt{difficultValue}
    {
        Init();
    }

    QString GetName() const{return m_name;}
    int GetDifficultValue() const{return m_difficultValue;}
    int GetRowsCnt() const{return m_rowsCnt;}
    int GetColumnsCnt() const{return m_columnsCnt;}

    bool GetItemValue(int nRow, int nCol, uint& outValue) const
    {
        if( nRow < m_table.size() && nCol < m_table[nRow].size() )
        {
            outValue = m_table[nRow][nCol];
            return true;
        }

        return false;
    }



    void SetItemValue(int nRow, int nCol, const uint& value)
    {
        if( nRow < m_table.size() && nCol < m_table[nRow].size() )
            m_table[nRow][nCol] = value;
    }



    bool operator == (const QString& lvlName) const
    {
        return m_name.toUpper() == lvlName.toUpper();
    }

    void Init()
    {
        for(int nRow = 0; nRow < m_rowsCnt; ++ nRow)
        {
            m_table.push_back(QVector<uint>());
            for(int nCol = 0; nCol < m_columnsCnt; ++ nCol)
            {
                m_table[nRow].push_back(0);

            }
        }

    }

private:
    QString m_name; //имя уровня
    int m_difficultValue = 0;//сложность уровня
    int m_columnsCnt = 0; //количество столбцов
    int m_rowsCnt = 0;//количество строк
    QVector<QVector<uint>> m_table; //матрица игры

};

#endif // SUDOKULEVEL_H
