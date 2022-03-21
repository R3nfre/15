#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class endWindow;
}

class endWindow : public QDialog
{
    Q_OBJECT

public:
    explicit endWindow(QWidget *parent = nullptr,  int moveCounter = 0, int size = 0);
    ~endWindow();
private slots:
    void buttonEndClicked();

private:
    QLineEdit* line;
    Ui::endWindow *ui;
    int moveCount = 0;
    int gameSize = 0;
};

#endif // ENDWINDOW_H
