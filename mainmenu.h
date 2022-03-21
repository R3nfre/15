#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include "choicemenu.h"
#include "gamewindow.h"
#include "leaderboardwindow.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private slots:
    void buttonNewGameClicked();
    void buttonContinueClicked();
    void buttonLeaderboardClicked();
    void buttonInstructionClicked();
    void buttonAuthorClicked();
    void buttonExitClicked();

private:
    Ui::MainMenu *ui;
    QPushButton* buttonNewGame;
    choiceMenu* menu;
};

#endif // MAINMENU_H
