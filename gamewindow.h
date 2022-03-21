#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMouseEvent>
#include <QWidget>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QWindow>
#include <QDir>
#include <puzzle.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class tileItem : public QGraphicsRectItem
{


public:
    tileItem(puzzle game, int i,int j);

};

class fieldView : public QGraphicsView{
    Q_OBJECT
public:
    fieldView(QWidget *parent = 0, int gameMode = 0, int saveMode = 0);
    void gameOver();
    void moveCounterUpdate();
private:
    QGraphicsScene *scene;
    QList<QGraphicsItem*> current;
    QGraphicsTextItem* moveCounterText;
    vector<vector<int>> solvePath;
    int moveCounter = 0;
    int moveDirection_x;
    int moveDirection_y;
    puzzle *game;
    QTimer *timer;
    QTimer* moveTimer;
    int counter = 0;
    QPushButton *buttonSolve;
    QPushButton* buttonSave;
    int solveCounter = 1;
    int solveMode = 0;

private slots:
    void moveItem();
    void printSolve();
    void pushButtonSolve();
    void pushButtonSave();
signals:
    void gameIsOver();

protected:
    void mousePressEvent(QMouseEvent *event);
};

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    gameWindow(QWidget *parent = nullptr, int gameMode = 0, int saveMode = 0);
    ~gameWindow();

private:
    Ui::MainWindow *ui;
    puzzle *game;
    fieldView *field;
public slots:
    void closeWindow();
private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
};


#endif // GAMEWINDOW_H
