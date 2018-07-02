#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "player.h"
#include "enemy.h"

#include <QKeyEvent>
#include <QPoint>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void changeSize();
    void explode();
    int score = 0;
    void startAllTimer();
    void stopAllTimer();
    QTimer *timer;
    QLabel *nameLabel;
    ~MainWindow();

public slots:
    void keyPressEvent(QKeyEvent *e);
    void changePos(QPoint pos);
    void setBackground(QString pic);
    void hitPlayer(int damage);
    void hitEnemy(int damage);
    void increaseScore();
    void gameOver();
    void win();
    void lose();
    void inputName();
    void fire();
    void updateLabel();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Player *player;
    Enemy *enemy;
    QString name;
};

#endif // MAINWINDOW_H
