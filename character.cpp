#include "character.h"

Character::Character()
{

}

int Character::getHp() const
{
    return hp;
}

void Character::setHp(int value)
{
    hp = value;
}

int Character::getSp() const
{
    return sp;
}

void Character::setSp(int value)
{
    sp = value;
}

QString Character::getPic() const
{
    return pic;
}

void Character::setPic(QString pic)
{
    this->pic = pic;
}
