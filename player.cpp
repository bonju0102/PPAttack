#include "player.h"
#include "mainwindow.h"

extern MainWindow *w;

Player::Player() : bulletTimer(new QTimer), moveTimer(new QTimer), spTimer(new QTimer)
{
    setPic("PP.png");
    update();
    setHp(100);
    h = new Health();
    h->setHealth(getHp()*2);
    h->setPos(x(), y() - 10);
    setSp(10);
    skill1 = false;
    skill2 = false;
    skill3 = false;
    bulletTimer->start(10);
    moveTimer->start(150);
    spTimer->start(1000);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(spTimer, SIGNAL(timeout()), this, SLOT(addSp()));
}

Player::Player(QString pic) : bulletTimer(new QTimer), moveTimer(new QTimer), spTimer(new QTimer)
{
    setPic(pic);
    update();
    setHp(100);
    h = new Health();
    h->setHealth(getHp()*2);
    h->setPos(x(), y() - 10);
    setSp(10);
    skill1 = false;
    skill2 = false;
    skill3 = false;
    bulletTimer->start(10);
    moveTimer->start(150);
    spTimer->start(1000);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(spTimer, SIGNAL(timeout()), this, SLOT(addSp()));
}

void Player::update()
{
    QString path = ":/resources/images/" + getPic();
    if (getPic() == "PP.png") {
        setPixmap(QPixmap(path).scaled(200,140));
        pee = false;
    } else {
        QTransform trans;
        trans.rotate(180);
        setPixmap(QPixmap(path).transformed(trans).scaled(137,160));
        pee = true;
    }
}

void Player::move()
{

}

void Player::shoot()
{
    bullet *b = new bullet;
    if (pee) {
        b->setPic("pee.png");
        b->update();
    }
    b->setPos(x() + pixmap().width() / 2 - b->pixmap().width() / 2, y() - b->pixmap().height());
    b->connect(bulletTimer, SIGNAL(timeout()), b, SLOT(flyToEnemy()));
    scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
}

void Player::addSp()
{
    if (getSp() < 5) {
        setSp(getSp() + 1);
    }
    emit updateSp();
}

void Player::hit(int damage)
{
    setHp(getHp() - damage);
    h->setHealth(getHp() * 2);
    if (getHp() <= 50) {
        h->setBrush(Qt::red);
    }
    if (getHp() <= 0) {
        disconnect(moveTimer, SIGNAL(timeout()), this, SLOT(shoot()));
        h->setVisible(false);
        this->setVisible(false);
        emit die();
    }
}

//void Player::gameOver()
//{
//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Toooooooo sad~~");
//    msgBox.setText("You fail in this game!\nYou're really suck :D");
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
