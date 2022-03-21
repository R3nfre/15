#include "choicemenu.h"
#include "ui_choicemenu.h"
#include "gamewindow.h"

choiceMenu::choiceMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choiceMenu)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon.ico"));
    this->setWindowTitle("Выбор режима игры");
    buttonMode3 = new QPushButton("Режим 3х3", this);
    QPushButton *buttonMode4 = new QPushButton("Режим 4х4", this);
    QPushButton *buttonMode5 = new QPushButton("Режим 5х5", this);
    QPushButton *buttonMode6 = new QPushButton("Режим 6х6", this);
    buttonMode3->setGeometry(200, 10, 220, 100);
    buttonMode3->setFont(QFont( "Arial", 11 , QFont::Bold));
    buttonMode4->setGeometry(200, 110, 220, 100);
    buttonMode4->setFont(QFont( "Arial", 11 , QFont::Bold));
    buttonMode5->setGeometry(200, 210, 220, 100);
    buttonMode5->setFont(QFont( "Arial", 11 , QFont::Bold));
    buttonMode6->setGeometry(200, 310, 220, 100);
    buttonMode6->setFont(QFont( "Arial", 11 , QFont::Bold));
    connect(buttonMode3, SIGNAL(released()),this, SLOT(button3Clicked()));
    connect(buttonMode4, SIGNAL(released()),this, SLOT(button4Clicked()));
    connect(buttonMode5, SIGNAL(released()),this, SLOT(button5Clicked()));
    connect(buttonMode6, SIGNAL(released()),this, SLOT(button6Clicked()));

}

choiceMenu::~choiceMenu()
{
    delete ui;
}

void choiceMenu::button3Clicked()
{
    game = new gameWindow(0, 3, 0);
    game->show();
    this->close();
}

void choiceMenu::button4Clicked()
{
    game = new gameWindow(0, 4, 0);
    game->show();
    this->close();
}

void choiceMenu::button5Clicked()
{
    game = new gameWindow(0, 5, 0);
    game->show();
    this->close();
}

void choiceMenu::button6Clicked()
{
    game = new gameWindow(0, 6, 0);
    game->show();
    this->close();
}
