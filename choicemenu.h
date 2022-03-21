#ifndef CHOICEMENU_H
#define CHOICEMENU_H

#include <QDialog>
#include <QPushButton>
#include <QStyleFactory>
#include "gamewindow.h"

namespace Ui {
class choiceMenu;
}

class choiceMenu : public QDialog
{
    Q_OBJECT

public:
    explicit choiceMenu(QWidget *parent = nullptr);
    ~choiceMenu();
private slots:
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();


private:
    Ui::choiceMenu *ui;
    QPushButton *buttonMode3;
    gameWindow* game;
};

#endif // CHOICEMENU_H
