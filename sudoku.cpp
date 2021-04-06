
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QLabel>
#include <iostream>
#include <fstream>

#include "sudoku.h"

Sudoku::Sudoku(QString filename)
{
    std::ifstream inputStream;
    char input;
    int number;
    int row = 0;
    int col = 0;

    inputStream.open(filename.toUtf8().constData());

    while (!inputStream.eof())
    {
        inputStream >> input;

        //convert character into number
        number = input - 48;
        if (number < 0 || number > 9)
        {
            number = 0;
        }

        //update row position
        if (col == 9)
        {
            row++;
            col = 0;
        }

        //set position to number
        Sud[row][col] = number;
        col++;
    }
    inputStream.close();
}
int Sudoku::value(int i, int j)
{
    return Sud[i][j] = {0};
}

QString Sudoku::valuePrint(int i, int j)
{
    if(Sud[i][j] != 0)
    {
        return QString::number(Sud[i][j]);
    }
    else
    {
        return " ";
    }
}
