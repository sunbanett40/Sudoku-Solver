#ifndef SUDOKU_H
#define SUDOKU_H

#include <QTextStream>
#include <QFile>

class Sudoku
{
public:
    Sudoku() = default;
    Sudoku(QString location);

    int value(int i, int j);
    QString valuePrint(int i, int j);

private:
    int Sud[9][9];
};

#endif // SUDOKU_H
#ifndef SUDOKU_H
#define SUDOKU_H


class Sudoku
{
public:
    Sudoku();
};

#endif // SUDOKU_H
