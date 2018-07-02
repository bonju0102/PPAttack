#include "bullet.h"
#include "mainwindow.h"

extern MainWindow *w;

bullet::bullet()
{
    setType("player");
    setPic("shit.png");
    setDamage(5);
    update();
}

bullet::bullet(QString type, QString pic, int damage)
{
    setType(type);
    setPic(pic);
    setDamage(damage);
    update();
}

void bullet::setType(QString type)
{
    this->type = type;
}

QString bullet::getType()
{
    return type;
}

void bullet::setPic(QString pic)
{
    this->pic = pic;
}

QString bullet::getPic()
{
    return pic;
}

void bullet::setDamage(int damage)
{
    this->damage = damage;
}

int bullet::getDamage()
{
    return damage;
}

void bullet::flyToPlayer1()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            w->hitPlayer(getDamage());
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x(), y() + 3);
    if (y() > 900 || x() + pixmap().width() < 0 || x() > 800) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::flyToPlayer2()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            w->hitPlayer(getDamage());
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() - 3, y() + 3);
    if (y() > 900 || x() + pixmap().width() < 0 || x() > 800) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::flyToPlayer3()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            w->hitPlayer(getDamage());
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() + 3, y() + 3);
    if (y() > 900 || x() + pixmap().width() < 0 || x() > 800) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::flyToEnemy()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            w->hitEnemy(getDamage());
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x(), y() - 3);
    if (y() + pixmap().height() < 0 || x() + pixmap().width() < 0 || x() > 800) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::update()
{
    QString path = ":/resources/images/" + pic;
    if (pic == "hammer.png") {
        QTransform trans;
        trans.rotate(180);
        setPixmap(QPixmap(path).transformed(trans).scaled(50,80));
    } else if (pic == "bullet1.png") {
        setPixmap(QPixmap(path).scaled(40,40));
    } else {
        setPixmap(QPixmap(path).scaled(20,40));
    }
}
