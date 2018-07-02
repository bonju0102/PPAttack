#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "bullet.h"
#include "health.h"
#include <QTimer>
#include <QCursor>

class Player : public Character
{
    Q_OBJECT
public:
    Player();
    Player(QString pic);
    bool pee = false;
    QTimer *bulletTimer;
    QTimer *moveTimer;
    QTimer *spTimer;
    bool skill1;
    bool skill2;
    bool skill3;
    Health *h;

public slots:
    void update();
    void move();
    void shoot();
    void addSp();
    void hit(int damage);
//    void gameOver();

signals:
    void die();
    void updateSp();
};

#endif // PLAYER_H
