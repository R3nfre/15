#include "endwindow.h"
#include "ui_endwindow.h"
#include "mainmenu.h"

endWindow::endWindow(QWidget *parent, int moveCounter, int size) :
    QDialog(parent),
    ui(new Ui::endWindow)
{
    ui->setupUi(this);
    moveCount = moveCounter;
    gameSize = size;
    this->setWindowIcon(QIcon(":/icon.ico"));
    this->setWindowTitle("Пятнашки");
    this->setGeometry(600, 300, 300, 120);
    QGridLayout* layout = new QGridLayout();
    this->setLayout(layout);
    QLabel* text = new QLabel("Поздравляю! Вы решили головоломку!\nВаше количество ходов: " + QString :: number(moveCounter) + "\nВведите ваше имя для записи в таблице рекордов:");
    layout->addWidget(text);
    text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    text->setFont(QFont( "Arial", 11 , QFont::Bold));
    line = new QLineEdit();
    line->setGeometry(0 ,0, 50, 100);
    layout->addWidget(line);
    QPushButton *buttonEnd = new QPushButton("Oк", this);
    layout->addWidget(buttonEnd);
    connect(buttonEnd, SIGNAL(released()),this, SLOT(buttonEndClicked()));
}

endWindow::~endWindow()
{
    delete ui;
}

void endWindow::buttonEndClicked()
{
     QString text = line->text();
     if(text == ""){
        QMessageBox message;
        message.setWindowIcon(QIcon(":/icon.ico"));
        message.setWindowTitle("Пятнашки");
        message.setText("Имя не введено!");
        message.setFont(QFont( "Arial", 11 , QFont::Bold));

        message.exec();
        return;
     }
     switch (gameSize) {
     case 3 :
     {
        QFile fileGame(QDir::currentPath() + "/fileGame_9.txt");
        fileGame.open(QIODevice::Append);
        QTextStream out(&fileGame);
        out<<QString :: number(moveCount) << "\n";
        out<<text<<"\n";
        break;
     }
     case 4 :
     {
        QFile fileGame(QDir::currentPath() + "/fileGame_16.txt");
        fileGame.open(QIODevice::Append);
        QTextStream out(&fileGame);
        out<<QString :: number(moveCount) << "\n";
        out<<text<<"\n";
        break;
     }
         break;
      case 5:
     {
        QFile fileGame(QDir::currentPath() +  "/fileGame_25.txt");
        fileGame.open(QIODevice::Append);
        QTextStream out(&fileGame);
        out<<QString :: number(moveCount) << "\n";
        out<<text<<"\n";
        break;
     }
      case 6:
     {
        QFile fileGame(QDir::currentPath() + "/fileGame_36.txt");
        fileGame.open(QIODevice::Append);
        QTextStream out(&fileGame);
        out<<QString :: number(moveCount) << "\n";
        out<<text<<"\n";
        break;
     }
     default:
         break;

     }
     this->close();

}
