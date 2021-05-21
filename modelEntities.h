#ifndef SUDOKULEVEL_H
#define SUDOKULEVEL_H

#include <QString>
#include <QVector>
#include "constants.h"
#include <memory>

//model entities
//ячейка игры
class Cell
{
public:
    Cell(int nRow, int nCol, CellState state = CellState::eUndef) : m_nRow(nRow),
                                                                    m_nCol(nCol),
                                                                    m_state(state){}

    bool operator == (const Cell& other) const{
        return m_nRow == other.m_nRow && m_nCol == other.m_nCol;
    }

    Cell& operator = (const Cell& other)
    {
        if(this == &other)
            return *this;

        m_value = other.m_value;
        m_state = other.m_state;

        return *this;
    }

    int GetRow() const {return m_nRow;}
    int GetColumn() const {return m_nCol;}

    void SetValue(QString value) {m_value = value; }
    QString GetValue() const {return m_value; }

    void Swap(Cell& other);

    CellState GetState() const {return m_state;}
    void SetState(const CellState& state) {m_state = state;}

private:
    int m_nRow = NOT_FOUND;
    int m_nCol = NOT_FOUND;
    CellState m_state;
    QString m_value = 0;
};


//класс таблицы игры
class GameTable
{
public:

    Cell* GetCell(int nRow, int nCol) const;

    void push_back(const Cell& cell)
    {
        m_table.push_back(cell);
    }

    GameTable& operator =(const GameTable& other)
    {
       if(this == &other)
            return *this;

       m_table.clear();

       for(const Cell& currCell : other.m_table)
            m_table.push_back(currCell);

       return *this;
    }


private:
    mutable QVector<Cell> m_table;
};

class LevelBuilder;


//базовый класс уровня сложности
class DifficultLvlBase {

public:

  void CreateNewGame(LevelBuilder* pBuilder);
  QString GetName() const {return QString::number(GetRowsCnt()) + " x " + QString::number(GetColumnsCnt());}

  GameTable& GetOriginalTable() {return  m_originalTable;}
  const GameTable& GetOriginalTable() const {return  m_originalTable;}

  GameTable& GetPlayingTable() {return  m_playingTable;}
  const GameTable& GetPlayingTable() const {return  m_playingTable;}

  void CopyOriginalToPlayingTable(){ m_playingTable = m_originalTable;}


  virtual int GetCellCountingRowAndColumnForRegion() const = 0;
  virtual int GetDifficultValue() const = 0;
  virtual int GetRowsCnt() const = 0;
  virtual int GetColumnsCnt() const = 0;
  virtual int GetMaxValue() const = 0;
  virtual int GetMaxInvisibleCells() const = 0;

  virtual std::unique_ptr<DifficultLvlBase> Clone() const = 0;

  virtual ~DifficultLvlBase(){}

private:
   void Init();

   GameTable m_originalTable; //матрица игры (сгенерированнная). решенная
   GameTable m_playingTable; //матрица игры (игровая)
};


//игра 4x4
class DifficultLvl_4_4 : public DifficultLvlBase {

public:
    int GetCellCountingRowAndColumnForRegion() const override {return 2;}
    int GetDifficultValue() const override {return 4;}
    int GetRowsCnt() const override {return 4;}
    int GetColumnsCnt() const override {return 4;}
    int GetMaxValue() const override {return 4;}
    int GetMaxInvisibleCells() const override {return 12;}
    std::unique_ptr<DifficultLvlBase> Clone() const override;
};

//игра 9x9
class DifficultLvl_9_9 : public DifficultLvlBase {

public:
    int GetCellCountingRowAndColumnForRegion() const override {return 3;}
    int GetDifficultValue() const override {return 9;}
    int GetRowsCnt() const override {return 9;}
    int GetColumnsCnt() const override {return 9;}
    int GetMaxValue() const override {return 9;}
    int GetMaxInvisibleCells() const override {return 50;}
    std::unique_ptr<DifficultLvlBase> Clone() const override;
};

//игра 16x16
class DifficultLvl_16_16 : public DifficultLvlBase {

public:
    int GetCellCountingRowAndColumnForRegion() const override {return 4;}
    int GetDifficultValue() const override{return 16;}
    int GetRowsCnt() const override{return 16;}
    int GetColumnsCnt() const override{return 16;}
    int GetMaxValue() const override {return 16;}
    int GetMaxInvisibleCells() const override {return 130;}
    std::unique_ptr<DifficultLvlBase> Clone() const override;
};









#endif // SUDOKULEVEL_H
