#include "enemy.h"
#include "mainwindow.h"

extern MainWindow *w;

Enemy::Enemy() : bulletTimer(new QTimer), moveTimer(new QTimer), shootTimer(new QTimer), spTimer(new QTimer)
{
    setPic("enemy1.png");
    update();
    setHp(200);
    h = new Health();
    h->setHealth(800);
    h->setPos(0,0);
    setSp(20);
    moveRight = true;
    bulletTimer->start(500);
    moveTimer->start(100);
    shootTimer->start(1000);
    spTimer->start(1000);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(spTimer, SIGNAL(timeout()), this, SLOT(addSp()));
}

Enemy::Enemy(QString pic) : bulletTimer(new QTimer), moveTimer(new QTimer), shootTimer(new QTimer), spTimer(new QTimer)
{
    setPic(pic);
    update();
    setHp(200);
    h->setHealth(800);
    h->setPos(0,0);
    setSp(20);
    moveRight = true;
    bulletTimer->start(500);
    moveTimer->start(100);
    shootTimer->start(1000);
    spTimer->start(1000);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(spTimer, SIGNAL(timeout()), this, SLOT(addSp()));
}

void Enemy::update()
{
    QString path = ":/resources/images/" + getPic();
    if (getPic() == "enemy1.png") {
        setPixmap(QPixmap(path).scaled(120,288));
    } else {
        setPixmap(QPixmap(path));
    }
}

void Enemy::move()
{
    if (this->pos().x() + 15 > 800 - pixmap().width())
        moveRight = false;
    if (this->pos().x() - 15 < 0)
        moveRight = true;
    if (moveRight) {
        setPos(x() + 15, y());
    } else {
        setPos(x() - 15, y());
    }
}

void Enemy::shoot()
{
    bullet *b1 = new bullet("enemy", "hammer.png", 10);
    bullet *b2 = new bullet("enemy", "hammer.png", 10);
    bullet *b3 = new bullet("enemy", "hammer.png", 10);
    b1->setPos(x() + pixmap().width() / 2 - b1->pixmap().width() / 2, y() + pixmap().height());
    b1->connect(moveTimer, SIGNAL(timeout()), b1, SLOT(flyToPlayer1()));
    b2->setPos(x() + pixmap().width() / 2 - b2->pixmap().width() / 2, y() + pixmap().height());
    b2->connect(moveTimer, SIGNAL(timeout()), b2, SLOT(flyToPlayer2()));
    b3->setPos(x() + pixmap().width() / 2 - b3->pixmap().width() / 2, y() + pixmap().height());
    b3->connect(moveTimer, SIGNAL(timeout()), b3, SLOT(flyToPlayer3()));
    scene()->addItem(static_cast<QGraphicsPixmapItem*>(b1));
    scene()->addItem(static_cast<QGraphicsPixmapItem*>(b2));
    scene()->addItem(static_cast<QGraphicsPixmapItem*>(b3));
}

void Enemy::addSp()
{
    if (getSp() < 10) {
        setSp(getSp() + 1);
    }
    emit updateSp();
}

void Enemy::hit(int damage)
{
    setHp(getHp() - damage);
    h->setHealth(getHp() * 4);
    if (getHp() <= 100) {
        h->setBrush(Qt::red);
    }
    if (getHp() <= 0) {
        h->setVisible(false);
        this->setVisible(false);
        disconnect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
        scene()->removeItem(h);
        scene()->removeItem(this);
        emit die();
    }
}

//void Enemy::gameOver()
//{
//    w->timer->stop();
//    moveTimer->stop();
//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Congratulations!");
//    msgBox.setText("You get " + QString::number(w->score) + " in this game!!\n" + "\n" + "Congratulations! ");
//    msgBox.setStandardButtons(QMessageBox::Ok);
//    msgBox.setDefaultButton(QMessageBox::Ok);
//    int result = msgBox.exec();
//    switch (result){
//        case QMessageBox::Ok:
//            break;
//        default:
//            break;
//    }
//}
