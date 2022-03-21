#include "leaderboardwindow.h"
#include "ui_leaderboardwindow.h"

LeaderboardWindow::LeaderboardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderboardWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon.ico"));
    this->setWindowTitle("Таблица рекордов");
    ui->label->setText("Режим 4х4");
    ui->label->setFont(QFont( "Arial", 16 , QFont::Bold));
    ui->label_2->setText("Режим 3х3");
    ui->label_2->setFont(QFont( "Arial", 16 , QFont::Bold));
    ui->label_3->setText("Режим 5х5");
    ui->label_3->setFont(QFont( "Arial", 16 , QFont::Bold));
    ui->label_4->setText("Режим 6х6");
    ui->label_4->setFont(QFont( "Arial", 16 , QFont::Bold));
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_3->setColumnCount(2);
    ui->tableWidget_4->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 112);
    ui->tableWidget_2->setColumnWidth(0, 200);
    ui->tableWidget_2->setColumnWidth(1, 112);
    ui->tableWidget_3->setColumnWidth(0, 200);
    ui->tableWidget_3->setColumnWidth(1, 112);
    ui->tableWidget_4->setColumnWidth(0, 200);
    ui->tableWidget_4->setColumnWidth(1, 112);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QList<QString> labels;
    labels.append("Имя игрока");
    labels.append("Количество ходов");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget_2->setHorizontalHeaderLabels(labels);
    ui->tableWidget_3->setHorizontalHeaderLabels(labels);
    ui->tableWidget_4->setHorizontalHeaderLabels(labels);
    QFile fileGame(QDir::currentPath() + "/fileGame_9.txt");
    fileGame.open(QIODevice::ReadOnly);
    QTextStream in(&fileGame);
    QVector<int> moveCounter;
    QVector<QString> nameCounter;
    while(!(in.atEnd())){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString line = in.readLine();
        int move = line.toInt();
        moveCounter.append(move);
        line = in.readLine();
        nameCounter.append(line);
    }
    for (int i = 0; i < moveCounter.size(); i++) {
        for (int j = 0; j < moveCounter.size() - i - 1; j++) {
            if (moveCounter[j] > moveCounter[j + 1]) {
                int temp = moveCounter[j];
                moveCounter[j] = moveCounter[j + 1];
                moveCounter[j + 1] = temp;
                QString line = nameCounter[j];
                nameCounter[j] = nameCounter[j + 1];
                nameCounter[j + 1] = line;
             }
        }
    }
    for(int i = 0; i < moveCounter.size(); i++){
        QTableWidgetItem* itemMove = new QTableWidgetItem(QString :: number(moveCounter[i]));
        QTableWidgetItem* itemName = new QTableWidgetItem(nameCounter[i]);
        ui->tableWidget->setItem(i, 0, itemName);
        ui->tableWidget->setItem(i, 1, itemMove);
    }
    fileGame.close();
    QFile fileGame_2(QDir::currentPath() + "/fileGame_16.txt");
    fileGame_2.open(QIODevice::ReadOnly);
    QTextStream in_2(&fileGame_2);
    QVector<int> moveCounter_2;
    QVector<QString> nameCounter_2;
    while(!(in_2.atEnd())){
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        QString line = in_2.readLine();
        int move = line.toInt();
        moveCounter_2.append(move);
        line = in_2.readLine();
        nameCounter_2.append(line);
    }
    for (int i = 0; i < moveCounter_2.size(); i++) {
        for (int j = 0; j < moveCounter_2.size() - i - 1; j++) {
            if (moveCounter_2[j] > moveCounter_2[j + 1]) {
                // меняем элементы местами
                int temp = moveCounter_2[j];
                moveCounter_2[j] = moveCounter_2[j + 1];
                moveCounter_2[j + 1] = temp;
                QString line = nameCounter_2[j];
                nameCounter_2[j] = nameCounter_2[j + 1];
                nameCounter_2[j + 1] = line;
             }
        }
    }
    for(int i = 0; i < moveCounter_2.size(); i++){
        QTableWidgetItem* itemMove = new QTableWidgetItem(QString :: number(moveCounter_2[i]));
        QTableWidgetItem* itemName = new QTableWidgetItem(nameCounter_2[i]);
        ui->tableWidget_2->setItem(i, 0, itemName);
        ui->tableWidget_2->setItem(i, 1, itemMove);
    }
    fileGame_2.close();
    QFile fileGame_3(QDir::currentPath() + "fileGame_25.txt");
    fileGame_3.open(QIODevice::ReadOnly);
    QTextStream in_3(&fileGame_3);
    QVector<int> moveCounter_3;
    QVector<QString> nameCounter_3;
    while(!(in_3.atEnd())){
        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
        QString line = in_3.readLine();
        int move = line.toInt();
        moveCounter_3.append(move);
        line = in_3.readLine();
        nameCounter_3.append(line);
    }
    for (int i = 0; i < moveCounter_3.size(); i++) {
        for (int j = 0; j < moveCounter_3.size() - i - 1; j++) {
            if (moveCounter_3[j] > moveCounter_3[j + 1]) {
                // меняем элементы местами
                int temp = moveCounter_3[j];
                moveCounter_3[j] = moveCounter_3[j + 1];
                moveCounter_3[j + 1] = temp;
                QString line = nameCounter_3[j];
                nameCounter_3[j] = nameCounter_3[j + 1];
                nameCounter_3[j + 1] = line;
             }
        }
    }
    for(int i = 0; i < moveCounter_3.size(); i++){
        QTableWidgetItem* itemMove = new QTableWidgetItem(QString :: number(moveCounter_3[i]));
        QTableWidgetItem* itemName = new QTableWidgetItem(nameCounter_3[i]);
        ui->tableWidget_3->setItem(i, 0, itemName);
        ui->tableWidget_3->setItem(i, 1, itemMove);
    }
    fileGame_3.close();
    QFile fileGame_4(QDir::currentPath() + "fileGame_36.txt");
    fileGame_4.open(QIODevice::ReadOnly);
    QTextStream in_4(&fileGame_4);
    QVector<int> moveCounter_4;
    QVector<QString> nameCounter_4;
    while(!(in_4.atEnd())){
        ui->tableWidget_4->insertRow(ui->tableWidget_4->rowCount());
        QString line = in_4.readLine();
        int move = line.toInt();
        moveCounter_4.append(move);
        line = in_4.readLine();
        nameCounter_4.append(line);
    }
    for (int i = 0; i < moveCounter_4.size(); i++) {
        for (int j = 0; j < moveCounter_4.size() - i - 1; j++) {
            if (moveCounter_4[j] > moveCounter_4[j + 1]) {
                // меняем элементы местами
                int temp = moveCounter[j];
                moveCounter_4[j] = moveCounter_4[j + 1];
                moveCounter_4[j + 1] = temp;
                QString line = nameCounter_4[j];
                nameCounter_4[j] = nameCounter_4[j + 1];
                nameCounter_4[j + 1] = line;
             }
        }
    }
    for(int i = 0; i < moveCounter_4.size(); i++){
        QTableWidgetItem* itemMove = new QTableWidgetItem(QString :: number(moveCounter_4[i]));
        QTableWidgetItem* itemName = new QTableWidgetItem(nameCounter_4[i]);
        ui->tableWidget_4->setItem(i, 0, itemName);
        ui->tableWidget_4->setItem(i, 1, itemMove);
    }
    fileGame_4.close();
    ui->stackedWidget->setCurrentWidget(ui->page);

}

LeaderboardWindow::~LeaderboardWindow()
{
    delete ui;
}

void LeaderboardWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void LeaderboardWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void LeaderboardWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}

void LeaderboardWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}

void LeaderboardWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);

}

void LeaderboardWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void LeaderboardWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void LeaderboardWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void LeaderboardWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void LeaderboardWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void LeaderboardWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void LeaderboardWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void LeaderboardWindow::on_pushButton_13_clicked()
{
    QFile fileGame("C:/Users/HP/Documents/_15_/fileGame_9.txt");
    fileGame.open(QIODevice::WriteOnly);
    ui->tableWidget->setRowCount(0);
}

void LeaderboardWindow::on_pushButton_14_clicked()
{
    QFile fileGame("C:/Users/HP/Documents/_15_/fileGame_16.txt");
    fileGame.open(QIODevice::WriteOnly);
    ui->tableWidget_2->setRowCount(0);
}

void LeaderboardWindow::on_pushButton_15_clicked()
{
    QFile fileGame("C:/Users/HP/Documents/_15_/fileGame_25.txt");
    fileGame.open(QIODevice::WriteOnly);
    ui->tableWidget_3->setRowCount(0);
}

void LeaderboardWindow::on_pushButton_16_clicked()
{
    QFile fileGame("C:/Users/HP/Documents/_15_/fileGame_36.txt");
    fileGame.open(QIODevice::WriteOnly);
    ui->tableWidget_4->setRowCount(0);
}
