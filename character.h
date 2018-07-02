#ifndef CHARACTER_H
#define CHARACTER_H

#include <QDebug>

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QMessageBox>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character();
    int getHp() const;
    void setHp(int value);
    int getSp() const;
    void setSp(int value);
    QString getPic() const;
    void setPic(QString pic);

public slots:
    virtual void update() = 0;
    virtual void move() = 0;
    virtual void shoot() = 0;
    virtual void addSp() = 0;
    virtual void hit(int damage) = 0;

private:
    QString pic;
    int hp;
    int sp;

};

#endif // CHARACTER_H
