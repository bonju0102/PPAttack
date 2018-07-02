#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Health : public QGraphicsRectItem
{
public:
    Health(QGraphicsItem * parent = 0);
    void setHealth(int hp);

private:
    int health;
};

#endif // HEALTH_H
