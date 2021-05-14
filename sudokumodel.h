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

    SudokuLevel& getDifficultLvl();
    const SudokuLevel& getDifficultLvl() const;
    void SetDifficult(const QString& strDifficultName);

private:

    SudokuLevel m_activeLvl;
};


class LevelsFactory
{
public:

    static SudokuLevel CreateDefault();
    static SudokuLevel Create(const QString& strDifficultName);
    static QVector<QString> GetLevelsName();

private:

    static QVector<SudokuLevel> m_availableLevels;
};




#endif // SUDOKUMODEL_H
