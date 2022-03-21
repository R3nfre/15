#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("Главное меню");
    this->setWindowIcon(QIcon(":/icon.ico"));
    QLabel* text = new QLabel("Игра \"Пятнашки\" ", this);
    text->setGeometry(200, 10, 230, 50);
    text->setFont(QFont( "Arial", 20 , QFont::Bold));
    buttonNewGame = new QPushButton("Новая игра", this);
    buttonNewGame->setGeometry(200, 110, 220, 60);
    buttonNewGame->setFont(QFont( "Arial", 11 , QFont::Bold));
    QPushButton *buttonContinueGame = new QPushButton("Продолжить игру", this);
    buttonContinueGame->setGeometry(200, 170, 220, 60);
    buttonContinueGame->setFont(QFont( "Arial", 11 , QFont::Bold));
    QPushButton *buttonLeaderboard = new QPushButton("Таблица рекордов", this);
    buttonLeaderboard->setGeometry(200, 230, 220, 60);
    buttonLeaderboard->setFont(QFont( "Arial", 11 , QFont::Bold));
    QPushButton *buttonInstruction = new QPushButton("Инструкция", this);
    buttonInstruction->setGeometry(200, 290, 220, 60);
    buttonInstruction->setFont(QFont( "Arial", 11 , QFont::Bold));
    QPushButton *buttonAuthor = new QPushButton("Об авторе", this);
    buttonAuthor->setGeometry(200, 350, 220, 60);
    buttonAuthor->setFont(QFont( "Arial", 11 , QFont::Bold));
    QPushButton *buttonExit = new QPushButton("Выход из игры", this);
    buttonExit->setGeometry(200, 410, 220, 60);
    buttonExit->setFont(QFont( "Arial", 11 , QFont::Bold));
    connect(buttonNewGame, SIGNAL(released()),this, SLOT(buttonNewGameClicked()));
    connect(buttonContinueGame, SIGNAL(released()),this, SLOT(buttonContinueClicked()));
    connect(buttonLeaderboard, SIGNAL(released()),this, SLOT(buttonLeaderboardClicked()));
    connect(buttonInstruction, SIGNAL(released()),this, SLOT(buttonInstructionClicked()));
    connect(buttonAuthor, SIGNAL(released()),this, SLOT(buttonAuthorClicked()));
    connect(buttonExit, SIGNAL(released()),this, SLOT(buttonExitClicked()));

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::buttonNewGameClicked()
{
    menu = new choiceMenu();
    menu->show();
    this->close();
}

void MainMenu::buttonContinueClicked()
{
    gameWindow *game = new gameWindow(0, 3, 1);
    game->show();
    this->close();
}

void MainMenu::buttonLeaderboardClicked()
{
    LeaderboardWindow* leaderboard = new LeaderboardWindow;
    leaderboard->exec();
}

void MainMenu::buttonInstructionClicked()
{
    QMessageBox endMsg;
    endMsg.setWindowIcon(QIcon(":/icon.ico"));
    endMsg.setWindowTitle("Инструкция");
    endMsg.setText("Пятнашки — головоломка, придуманная в 1878 году Ноем Чепмэном.\nИгра представляет одинаковых набор одинаковых квадратов с нанесёнными числами, эти квадраты расположены на квадратном поле.\nЦель игры — перемещая костяшки по полю, добиться упорядочивания их по номерам, желательно сделав как можно меньше перемещений.\nУправление: для того чтобы сделать ход, нужно нажать на квадратик, который вы хотите переместить, и он передвинется на свободное место на игровом поле. Также можно сделать длинный ход, переместив сразу ряд квадратиков, для этого нажмите на начало ряда, и он передвинется.\nКнопка \"Автоматическое решение\" - если на неё нажать, то будет показан полный путь решения головоломки из заданной позиции.\nКнопка \"Сохранить и выйти\" - если на неё нажать, то данная игра будет сохранена, вы сможете её продолжить, если нажмёте в главном меню кнопку \"Продолжить игру\"");
    endMsg.exec();
}


void MainMenu::buttonAuthorClicked()
{
    QMessageBox endMsg;
    endMsg.setWindowIcon(QIcon(":/icon.ico"));
    endMsg.setWindowTitle("Об авторе");
    endMsg.setText("Автор приложения: Заболоцкий Артём\nУчебная группа: М8О-111Б-20");
    endMsg.exec();
}

void MainMenu::buttonExitClicked()
{
    this->close();
}
