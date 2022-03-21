#include "gamewindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "endwindow.h"


gameWindow::gameWindow(QWidget *parent , int gameMode, int saveMode)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon.ico"));
    this->setWindowTitle("Пятнашки");
    field = new fieldView(0, gameMode, saveMode);
    ui->gridLayout_2->addWidget(field);
    connect(field, SIGNAL(gameIsOver()), this, SLOT(closeWindow()));
}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::closeWindow()
{
    this->close();
}


tileItem::tileItem(puzzle game, int i, int j) : QGraphicsRectItem(0)
{

    int fieldSize = game.getSize();
    vector<int> gameState = game.getState();
    QString num = QString::number(gameState[i * fieldSize + j]);
    this->setX(480 / fieldSize);
    this->setY(480 / fieldSize);

    QGraphicsTextItem *text = new QGraphicsTextItem(num, 0);
    QPointF pos;
    if(gameState[i * fieldSize + j] <= 9){
        pos.setX((480 / fieldSize) / 3);
        pos.setY((480 / fieldSize) / 4);
    }
    else{
        pos.setX((480 / fieldSize) / 4);
        pos.setY((480 / fieldSize) / 4);
    }
    text->setParentItem(this);
    text->setPos(pos);
    QFont f( "Arial",50 * 3/ fieldSize , QFont::Bold);
    text->setFont(f);
    QColor color= QColor(103, 207, 196);
    this->setBrush(color);
    this->setRect(0, 0, 480 / fieldSize, 480 / fieldSize);
    this->setPos(j * (480 / fieldSize),i * (480 / fieldSize));
}



fieldView::fieldView(QWidget *parent, int gameMode, int saveMode) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,480,480,this);
    this->setScene(scene);
    scene->addRect(scene->sceneRect());
    if(saveMode){
        QFile fileGame(QDir::currentPath() + "/fileGame.txt");
        fileGame.open(QIODevice::ReadOnly);
        QTextStream in(&fileGame);
        QString line = in.readLine();
        int size = line.toInt();
        game = new puzzle(size);
        line = in.readLine();
        moveCounter = line.toInt();
        vector<int> state(size);
        for(int i = 0; i < size; i++){
            line = in.readLine();
            state[i] = line.toInt();
        }
        game->setState(state);
    }
    else{
        game = new puzzle(gameMode*gameMode);
        game->shuffle();
    }
    int fieldSize = game->getSize();
    int emptyPlace = game->getEmpty();
    for(int i = 0; i < fieldSize; i++)
        for(int j = 0; j < fieldSize; j++){
            if(emptyPlace/fieldSize == i && emptyPlace % fieldSize == j)
                    continue;
            tileItem *tile = new tileItem(*game, i, j);
            scene->addItem(tile);
        }
    moveCounterText = new QGraphicsTextItem("Количество ходов: " + QString :: number(moveCounter));
    moveCounterText->setFont(QFont( "Arial", 25 , QFont::Bold));
    moveCounterText->setPos(50, - 50);
    scene->addItem(moveCounterText);
    buttonSolve = new QPushButton("Решить\nавтоматически", this);
    buttonSolve->setGeometry(35, 74, 120, 100);
    buttonSolve->setFont(QFont( "Arial", 11 , QFont::Bold));
    connect(buttonSolve, SIGNAL(released()), SLOT(pushButtonSolve()));
    buttonSave = new QPushButton("Сохранить и\nвыйти", this);
    buttonSave->setGeometry(665, 74, 120, 100);
    buttonSave->setFont(QFont( "Arial", 11 , QFont::Bold));
    connect(buttonSave, SIGNAL(released()), SLOT(pushButtonSave()));

}

void fieldView::gameOver()
{
    if(solveMode)
    {
        QMessageBox endMsg;
        endMsg.setWindowIcon(QIcon(":/icon.ico"));
        endMsg.setWindowTitle("Пятнашки");
        endMsg.setText("Головоломка решена!\nКоличество ходов: " + QString :: number(moveCounter));
        endMsg.exec();
        MainMenu *menu = new MainMenu;
        menu->show();
        this->gameIsOver();
        return;
    }

    endWindow* window = new endWindow(0, moveCounter, game->getSize());
    window->exec();
    MainMenu *menu = new MainMenu;
    menu->show();
    this->gameIsOver();

}

void fieldView::moveCounterUpdate()
{
   moveCounterText->setPlainText("Количество ходов: " + QString :: number(moveCounter));
}

void fieldView::moveItem()
{
    for(int i = 0; i < current.size(); i++)
        current[i]->moveBy(2*moveDirection_x ,2* moveDirection_y);
    counter+=2;
    if(counter == 480/(game->getSize())){
        timer->deleteLater();
        counter = 0;
        current.clear();
    }
}

void fieldView::pushButtonSolve()
{
   if(solveMode)
       return;
   solvePath = game->solve();
   moveTimer = new QTimer(this);
   moveTimer->start(200);
   connect(moveTimer, SIGNAL(timeout()), this, SLOT(printSolve()));
}

void fieldView::pushButtonSave()
{
    if(solveMode)
        return;
    QFile fileGame(QDir::currentPath() + "/fileGame.txt");
    fileGame.open(QIODevice::WriteOnly);
    QTextStream out(&fileGame);
    out << game->getSize() * game->getSize()<< "\n";
    out << moveCounter << "\n";
    for(int i = 0; i < game->getSize() * game->getSize(); i++)
        out << game->getState()[i] <<"\n";
    fileGame.close();
    QMessageBox endMsg;
    endMsg.setWindowIcon(QIcon(":/icon.ico"));
    endMsg.setWindowTitle("Пятнашки");
    endMsg.setText("Вы успешно сохранили игру!");
    endMsg.exec();
    MainMenu *menu = new MainMenu;
    menu->show();
    this->gameIsOver();
}

void fieldView::printSolve()
{
    if(counter){
        counter = 0;
        return;
    }
    int fieldSize = game->getSize();
    solveMode = 1;
    if(solvePath.size() == solveCounter){
        gameOver();
        moveTimer->deleteLater();
        return;
    }
    int currentZero = 0, pastZero = 0;
    vector<int> currentState = solvePath[solveCounter];
    QGraphicsItem  *q;
    for(int i = 0; i < fieldSize * fieldSize; i++){
        if(!(currentState[i]))
                currentZero = i;
        if(!(solvePath[solveCounter - 1][i]))
                pastZero = i;
    }
    timer = new QTimer(this);
    timer->start(1);
    int diff = currentZero - pastZero;
    if(abs(diff) == 1){
        q = scene->itemAt((currentZero % fieldSize) * (480 / fieldSize) + 1, (currentZero / fieldSize) * (480 / fieldSize) + 1, QTransform());
        current.push_back(q);
        moveCounter++;
        moveDirection_x = -diff/abs(diff);
        moveDirection_y = 0;
        connect(timer, SIGNAL(timeout()), this, SLOT(moveItem()));
        moveCounterUpdate();
    }
    if(abs(diff) == fieldSize){
        q = scene->itemAt((currentZero % fieldSize) * (480 / fieldSize) + 1, (currentZero / fieldSize) * (480 / fieldSize) + 1, QTransform());
        current.push_back(q);
        moveCounter++;
        moveDirection_x = 0;
        moveDirection_y = -diff/abs(diff);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveItem()));
        moveCounterUpdate();
    }
    solveCounter++;

}

void fieldView::mousePressEvent(QMouseEvent *event)
{
     if(counter || solveMode)
         return;
     int fieldSize = game->getSize();
     const QPointF eventPos = mapToScene(event->pos());
     if(eventPos.x() < 0 || eventPos.y() < 0 || eventPos.x() > 480 || eventPos.y() > 480)
         return;
     int pos_j = (eventPos.y() / (480 / fieldSize));
     int pos_i = (eventPos.x() / (480 / fieldSize));
     QGraphicsItem  *q;
     int emptyPlace = game->getEmpty();
     if(pos_j * fieldSize + pos_i == emptyPlace)
         return;
     int turn = (pos_j) * fieldSize + pos_i, i;
     int diff = turn - emptyPlace;
     int emptyI = emptyPlace % fieldSize;
     int emptyJ = emptyPlace / fieldSize;
     if (pos_j == emptyJ){
         timer = new QTimer(this);
         timer->start(1);
        for (i = emptyI; i != pos_i; i += diff / abs(diff)){
            q = scene->itemAt((i + diff / abs(diff)) * (480 / fieldSize) + 1, pos_j * (480 / fieldSize) + 1, QTransform());
            current.push_back(q);
            moveCounter++;
        }
        moveDirection_x = -diff/abs(diff);
        moveDirection_y = 0;
        connect(timer, SIGNAL(timeout()), this, SLOT(moveItem()));
        moveCounterUpdate();
     }
     if (pos_i == emptyI){
         timer = new QTimer(this);
         timer->start(1);
         for (i = emptyJ; i != pos_j; i += diff / abs(diff)){
             q = scene->itemAt(pos_i * (480 / fieldSize) + 1, (i + diff / abs(diff)) * (480 / fieldSize) + 1, QTransform());
             current.push_back(q);
             moveCounter++;
         }
         moveDirection_x = 0;
         moveDirection_y = -diff/abs(diff);
         connect(timer, SIGNAL(timeout()), this, SLOT(moveItem()));
         moveCounterUpdate();
     }
     game->move(pos_j + 1, pos_i + 1);
     if(!(game->status()))
         gameOver();

}


void gameWindow::on_action_triggered()
{
    MainMenu *menu = new MainMenu;
    menu->show();
    this->closeWindow();
}

void gameWindow::on_action_2_triggered()
{
    LeaderboardWindow* leaderboard = new LeaderboardWindow;
    leaderboard->exec();
}

void gameWindow::on_action_3_triggered()
{
    QMessageBox endMsg;
    endMsg.setWindowIcon(QIcon(":/icon.ico"));
    endMsg.setWindowTitle("Об авторе");
    endMsg.setText("Автор приложения: Заболоцкий Артём\nУчебная группа: М8О-111Б-20");
    endMsg.exec();
}

void gameWindow::on_action_4_triggered()
{
    this->closeWindow();
}
