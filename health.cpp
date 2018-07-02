#include "health.h"

Health::Health(QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setPen(Qt::NoPen);
    setBrush(Qt::green);
}

void Health::setHealth(int hp)
{
    health = hp;
    setRect(0,0,health,10);
}
