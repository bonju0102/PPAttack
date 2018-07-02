#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QList>
#include <QTime>

#include "player.h"
#include "enemy.h"

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    bullet(QString type, QString pic, int damage);
    void setType(QString type);
    QString getType();
    void setPic(QString pic);
    QString getPic();
    void setDamage(int damage);
    int getDamage();

public slots:
    void flyToEnemy();
    void flyToPlayer1();
    void flyToPlayer2();
    void flyToPlayer3();
    void update();

//signals:
//    void hitEnemy(int damage);
//    void hitPlayer(int damage);

private:
    QString type;
    QString pic;
    int damage;

};

#endif // BULLET_H
