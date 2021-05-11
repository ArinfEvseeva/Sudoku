#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyledItemDelegate>
#include <QPainter>
sudoku::matrix matx;

class DrawBorderDelegate : public QStyledItemDelegate
{
public:
     DrawBorderDelegate( QObject* parent = 0 ) : QStyledItemDelegate( parent ) {}
     void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override{
         const QRect rect( option.rect );
         QPen penHLines(QColor("#0e5a77"), 10, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
         painter->setPen(penHLines);
         painter->drawLine( rect.topLeft(), rect.topRight() );
         painter->drawLine( rect.bottomLeft(), rect.bottomRight() );

             // Draw left edge of left-most cell
            // if ( index.column() == 0 )
                 painter->drawLine( rect.topLeft(), rect.bottomLeft() );

             // Draw right edge of right-most cell
            // if ( index.column() == index.model()->columnCount() - 1 )
                 painter->drawLine( rect.topRight(), rect.bottomRight() );

         QStyledItemDelegate::paint( painter, option, index );



     }

}; // DrawBorderDelegate




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_sudokuModel);

//    matx.new_puzzle();
//    // ui->table->setItemDelegate(new DrawBorderDelegate());
//    for (int i = 0; i < 9; ++i)
//    {
//        for (int j = 0; j < 9; ++j)
//        {


//            QTableWidgetItem* Cell = ui->table->item(i, j);
//            QString str = "";
//            str += '0' + matx.read(i, j);
//            const QString cstr = str;
//            Cell->setText(cstr);
//            Cell->setTextAlignment(Qt::AlignCenter);
//            if (matx.read(i, j))
//            {
//                QColor c(122,122,235);
//                Cell->setBackground(c);
//            }

//        }
//    }
    ui->label->setText("sudoku!!");
    //QObject::connect(ui->pb00_1,&QPushButton::clicked,this,&MainWindow::OnCustiomAction);


}

MainWindow::~MainWindow()
{

}



void MainWindow::on_table_cellClicked(int row, int column)
{
    Row = row;
    Column = column;
    QString str = "";
    str += '0' + row;
    str += ',';
    str += '0' + column;
    const QString cstr = str;
    ui->label->setText(cstr);
}

void MainWindow::click__on_pb(int num)
{
    QTableWidgetItem* Cell = ui->table->item(Row, Column);
    matx.write(Row, Column, num);
    QString str = "";
    str += '0' + matx.read(Row, Column);
    const QString cstr = str;
    Cell->setText(cstr);
    if (matx.you_win())
    {
        ui->label->setText("you win!!");
    }
}

void MainWindow::on_pb00_1_clicked()
{
   click__on_pb(1);
}

void MainWindow::on_pb00_2_clicked()
{
    click__on_pb(2);
}

void MainWindow::on_pb00_3_clicked()
{
    click__on_pb(3);
}

void MainWindow::on_pb00_4_clicked()
{
    click__on_pb(4);
}

void MainWindow::on_pb00_5_clicked()
{
    click__on_pb(5);
}

void MainWindow::on_pb00_6_clicked()
{
    click__on_pb(6);
}

void MainWindow::on_pb00_7_clicked()
{
    click__on_pb(7);
}

void MainWindow::on_pb00_8_clicked()
{
    click__on_pb(8);
}

void MainWindow::on_pb00_9_clicked()
{
    click__on_pb(9);
}

void MainWindow::on_solve_clicked()
{
    matx.reset();
    matx.solve();
    for (int i = 0; i < 9; ++i)
	{
        for (int j = 0; j < 9; ++j)
		{
			QTableWidgetItem* Cell = ui->table->item(i, j);
			QString str = "";
            str += '0' + matx.read(i,j);
			const QString cstr = str;
			Cell->setText(cstr);
		}
	}
}

void MainWindow::on_actionNew_game_triggered()
{
    matx.new_puzzle();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            QTableWidgetItem* Cell = ui->table->item(i, j);
            QString str = "";
            str += '0' + matx.read(i, j);
            const QString cstr = str;
            Cell->setText(cstr);
            if (matx.read(i, j))
            {
                QColor c(122,122,235);
                Cell->setBackground(c);
            }
            else
            {
                QColor c(255,255,255);
                Cell->setBackground(c);
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    matx.reset();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            QTableWidgetItem* Cell = ui->table->item(i, j);
            QString str = "";
            str += '0' + matx.read(i, j);
            const QString cstr = str;
            Cell->setText(cstr);
        }
    }
}
