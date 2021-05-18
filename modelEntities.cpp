#include "modelEntities.h"
#include "sudokumodel.h"



void DifficultLvlBase::CreateNewGame(LevelBuilder* pBuilder)
{
    Init();
    pBuilder->MakeLevel(this);
}

void DifficultLvlBase::Init()
{
    for(int nRow = 0; nRow < GetRowsCnt(); ++ nRow)
    {
        for(int nCol = 0; nCol < GetColumnsCnt(); ++ nCol)
        {
            //Todo write generator
            Cell newCell(nRow, nCol,false);
            newCell.SetValue("0");
            m_table.push_back(newCell);
        }
    }
}

std::unique_ptr<DifficultLvlBase> DifficultLvl_4_4::Clone() const{return std::make_unique<DifficultLvl_4_4>();}

std::unique_ptr<DifficultLvlBase> DifficultLvl_9_9::Clone() const{return std::make_unique<DifficultLvl_9_9>();}

std::unique_ptr<DifficultLvlBase> DifficultLvl_16_16::Clone() const{return std::make_unique<DifficultLvl_16_16>();}

Cell *GameTable::getCell(int nRow, int nCol) {

    Cell proxyCell(nRow, nCol);

    for(int n = 0; n < size(); ++n)
    {
        auto& data = operator[](n);


        if( data == proxyCell)
        {
            return &data;
        }
    }
    return nullptr;
}
