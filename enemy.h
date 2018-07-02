#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "bullet.h"
#include "health.h"
#include <QTimer>

class Enemy : public Character
{
    Q_OBJECT
public:
    Enemy();
    Enemy(QString pic);
    QTimer *bulletTimer;
    QTimer *moveTimer;
    QTimer *shootTimer;
    QTimer *spTimer;
    Health *h;

public slots:
    void update();
    void move();
    void shoot();
    void addSp();
    void hit(int damage);
//    void gameOver();

private:
    bool moveRight;

signals:
    void die();
    void updateSp();
};

#endif // ENEMY_H
