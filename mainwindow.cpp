#include "mainwindow.h"
#include "sudoku.h"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QCoreApplication>

#include <map>
#include <vector>

using namespace std;

Sudoku board = Sudoku("G:/1204_Advanced_Programming/P7_Sudoku GUI/Sudoku2/empty.txt");
   // SpinBox *boxes[81];

void MainWindow::openSudoku()
{
    QString file = QFileDialog::getOpenFileName(this,
                tr("Open Sudoku Text File"),
                "/1204_Advanced_Programming/P7_Sudoku GUI/Sudoku",
                tr("Text Files (*.txt)"));
    board = Sudoku(file);
}

bool MainWindow::solveSudoku(int *board, int boardPos)
{
    int row = boardPos / 9;
    int col = boardPos % 9;

    //is the sudoku complete
    if (row == 9)
    {
        return true;
    }

    //is it the end of the row
    if (col == 9)
    {
        row++;
        col = 0;
    }

    //is the value greater than zero
    if (board[boardPos] > 0)
    {
        if (solveSudoku(board, boardPos + 1))
        {
            return true;
        }
    }

    //check if new value is valid
    for (int number = 1; number <= 9; number++)
    {
        if (validNumber(board, row, col, number))
        {
            board[boardPos] = number;
            if (solveSudoku(board, boardPos + 1))
            {
                return true;
            }
        }
    }

    board[boardPos] = 0;
    return false;
}

bool MainWindow::validNumber(int *board, int row, int col, int num)
{
    //check if row is valid
    for (int i = 0; i < 9; i++)
    {
        if (board[(9 * row) + i] == num)
        {
            return false;
        }
    }

    //check if column is valid
    for (int i = 0; i < 9; i++)
    {
        if (board[(9 * i) + col] == num)
        {
            return false;
        }
    }

    //check if sub-board is valid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[(startRow + i) * 9 + startCol + j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPixmap openpix(QDir::currentPath() + "/open.png");
    QPixmap solvepix(QDir::currentPath() + "/solve.png");
    QPixmap quitpix(QDir::currentPath() + "/quit.png");

    auto *open = new QAction(openpix, "&Open", this);
    auto *solve = new QAction(solvepix, "&Solve", this);
    auto *quit = new QAction(quitpix, "&Quit", this);

    open->setShortcut(tr("CTRL+O"));
    solve->setShortcut(tr("CTRL+G"));
    quit->setShortcut(tr("CTRL+Q"));

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(open);
    file->addAction(solve);
    file->addSeparator();
    file->addAction(quit);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);


    connect(open, SIGNAL(triggered()), this, SLOT(openSudoku()));
    connect(solve, SIGNAL(triggered()), this, SLOT(solveSudoku()));
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);



    // set form size
    resize(550,550);
    setWindowTitle("Sudoku GUI");

    int inc = std::min(height(), width());
    int step = inc/11;

  /*  for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
                boxes[9*i+j] = new SpinBox(this);
            if (board.value(i, j) > 0)
            {
                boxes[9*i+j]->setSolved(true);
                boxes[9*i+j]->setValue(board.value(i, j));
            }
            if (board.value(i, j) == 0)
            {
                boxes[9*i+j]->show();
                boxes[9*i+j]->move(i*step +step, j*step +step);

            }
        }}*/
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    int inc = std::min(height(), width());
    int step = inc/11;

    QPen pen;
    QFont font;
    font.setPixelSize(30);
    painter.setFont(font);

    for(int i = 0, j = step; i < 10; i++, j+= step)
    {
        if((j-step)%(3*step) == 0)
        {
            pen.setWidth(4);
            painter.setPen(pen);
        }
        else
        {
            pen.setWidth(2);
            painter.setPen(pen);
        }

        QPoint xtop(j,step), xbottom(j,10*step);
        painter.drawLine(xtop, xbottom);

        QPoint ytop(step, j), ybottom(10*step, j);
        painter.drawLine(ytop, ybottom);
    }


    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            font.setPointSize(step*1/2);
            painter.setFont(font);
            painter.drawText(step*4/3+step*i, step*7/4+step*j, board.valuePrint(j, i));
           /* if (board.value(i, j) == 0)
            {
                boxes[9*i+j]->show();
                boxes[9*i+j]->move(i*step +step, j*step +step);

            }*/
        }
    }
}
