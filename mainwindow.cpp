#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    scene(new QGraphicsScene(0,0,800,900))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    nameLabel = new QLabel;
    inputName();

    //create player & enemy
    player = new Player();
    enemy = new Enemy();
    player->setPos(scene->width()/2 - player->pixmap().width()/2, scene->height() - player->pixmap().height()-10);
    enemy->setPos(scene->width()/2 - enemy->pixmap().width()/2, 10);
    updateLabel();

    //Scene setting
    setBackground("background1.png");
    scene->addItem(player);
    scene->addItem(player->h);
    scene->addItem(enemy);
    scene->addItem(enemy->h);
    timer->start(1000);

    connect(ui->mouseBox, SIGNAL(toggled(bool)), ui->graphicsView, SLOT(toggleMouseTracking(bool)));
    connect(ui->graphicsView, SIGNAL(mouseMove(QPoint)), this, SLOT(changePos(QPoint)));
    connect(ui->graphicsView, SIGNAL(leftClicked()), this, SLOT(fire()));
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseScore()));

    connect(player, SIGNAL(die()), this, SLOT(lose()));
    connect(enemy, SIGNAL(die()), this, SLOT(win()));

    connect(player, SIGNAL(updateSp()), this, SLOT(updateLabel()));
    connect(enemy, SIGNAL(updateSp()), this, SLOT(updateLabel()));

    //Score setting
    ui->scoreNumber->setDigitCount(8);

}

void MainWindow::changeSize()
{
    if (!player->skill2) {
        if (player->getPic() == "PP.png") {
            player->setPixmap(QPixmap(":/resources/images/PP.png").scaled(50,35));
        } else {
            QTransform trans;
            trans.rotate(180);
            player->setPixmap(QPixmap(":/resources/images/GG.png").transformed(trans).scaled(50,58));
        }
        player->skill2 = true;
    } else {
        player->update();
        player->skill2 = false;
    }
}

void MainWindow::explode()
{
    if (!player->skill3) {
        player->hit(player->getHp());
        player->skill3 = true;
    } else {
        player->skill3 = false;
    }

}

void MainWindow::startAllTimer()
{
    timer->start(1000);
    player->bulletTimer->start(10);
    player->moveTimer->start(150);
    player->spTimer->start(1000);
    enemy->bulletTimer->start(500);
    enemy->moveTimer->start(100);
    enemy->shootTimer->start(1000);
    enemy->spTimer->start(1000);
}

void MainWindow::stopAllTimer()
{
    timer->stop();
    player->bulletTimer->stop();
    player->moveTimer->stop();
    player->spTimer->stop();
    enemy->bulletTimer->stop();
    enemy->moveTimer->stop();
    enemy->shootTimer->stop();
    enemy->spTimer->stop();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (player->y() + player->pixmap().height()/2 - 15 > 0) {
            player->setPos(player->x(), player->y() - 15);
            player->h->setPos(player->x(), player->y() - 10);
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if (player->y() + player->pixmap().height()/2 + 15 < 830) {
            player->setPos(player->x(), player->y() + 15);
            player->h->setPos(player->x(), player->y() - 10);
        }
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (player->x() + player->pixmap().width()/2 + 15 < 800) {
            player->setPos(player->x() + 15, player->y());
            player->h->setPos(player->x(), player->y() - 10);
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (player->x() + player->pixmap().width()/2 - 15 > 0) {
            player->setPos(player->x() - 15, player->y());
            player->h->setPos(player->x(), player->y() - 10);
        }
        break;
    case Qt::Key_Space:
        fire();
        break;
    case Qt::Key_P:
        break;
    case Qt::Key_C:
        if (player->getPic() == "PP.png") {
            player->setPic("GG.png");
            player->pee = true;
        } else {
            player->setPic("PP.png");
            player->pee = false;
        }
        player->update();
        break;
    case Qt::Key_T:
        ui->mouseBox->toggle();
        break;
    case Qt::Key_1:
        if (player->getSp() >= 2) {
            player->setSp(player->getSp() - 2);
            bullet *b = new bullet("player", "bullet1.png", 20);
            b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height() / 2);
            b->connect(player->bulletTimer, SIGNAL(timeout()), b, SLOT(flyToEnemy()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        }
        break;
    case Qt::Key_2:
        changeSize();
        break;
    case Qt::Key_3:
        explode();
        break;
    }
}

void MainWindow::changePos(QPoint pos)
{
    player->setPos(pos.x() - player->pixmap().width()/2, pos.y() - player->pixmap().height()/2);
    player->h->setPos(player->x(), player->y() - 10);
}

void MainWindow::setBackground(QString pic)
{
    QString path = ":/resources/images/" + pic;
    QRect rect(0,0,800,900);
    QPixmap org(path);
    QPixmap back = org.copy(rect);
    scene->addPixmap(back);
}

void MainWindow::hitPlayer(int damage)
{
    player->hit(damage);
    updateLabel();
}

void MainWindow::hitEnemy(int damage)
{
    enemy->hit(damage);
    updateLabel();
    score+=2173;
    ui->scoreNumber->display(score);
}

void MainWindow::increaseScore()
{
    score++;
    ui->scoreNumber->display(score);
}

void MainWindow::gameOver()
{
//    int result;
//    timer->stop();

//    if (info == "enemy") {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Toooooooo Sad~");
//        msgBox.setText("You fail this game.");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        result = msgBox.exec();
//    } else {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Congratulations!");
//        msgBox.setText("You get " + QString::number(score) + " in this game!!\n" + "\n" + "Congratulations! ");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        result = msgBox.exec();
//    }
//    switch (result){
//        case QMessageBox::Ok:
//            break;
//        default:
//            break;
    //    }
}

void MainWindow::win()
{
    updateLabel();
    stopAllTimer();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Congratulations!");
    msgBox.setText("You get " + QString::number(score) + " in this game!!\n" + "\n" + "Congratulations! " + name);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int result = msgBox.exec();
    switch (result){
        case QMessageBox::Ok:
            break;
        default:
            break;
    }
}

void MainWindow::lose()
{
    updateLabel();
    stopAllTimer();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Toooooooo sad~~");
    msgBox.setText("You fail in this game!\nYou're really suck :D");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int result = msgBox.exec();
    switch (result){
        case QMessageBox::Ok:
            player->setVisible(false);
            player->h->setVisible(false);
            break;
        default:
            break;
    }
}

void MainWindow::inputName()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Hello friend!!"),tr("Please Enter Your Name："),QLineEdit::Normal,nameLabel->text(),&ok);
    if (ok && !text.isEmpty()) {
        name = text;
    }
}

void MainWindow::fire()
{
    player->shoot();
}

void MainWindow::updateLabel()
{
    ui->enemyHP->setText(QString::number(enemy->getHp()));
    ui->enemySP->setText(QString::number(enemy->getSp()));
    ui->playerHP->setText(QString::number(player->getHp()));
    ui->playerSP->setText(QString::number(player->getSp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
