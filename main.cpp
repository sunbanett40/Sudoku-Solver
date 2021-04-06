#include "widget.h"
#include "mainwindow.h"
#include "sudoku.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;

    window.resize(550, 550);
    window.setWindowTitle("Sudoku");
    window.show();

    return a.exec();
}
