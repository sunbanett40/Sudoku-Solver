#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void openSudoku();
    bool solveSudoku(int *board, int boardPos);
    bool validNumber(int *board, int row, int col, int num);
};
#endif // MAINWINDOW_H
