#include "brick.h"
#include <stdlib.h>

extern GameController * gc;

Brick::Brick(int _hp)
{
    // Init stats
    hp = _hp;

    // Draw brick
    setRect(0, 0, 48, 15);
    switch (hp) {
    case 1:
        setBrush(QBrush(Qt::darkGray));
        break;
    case 2:
        setBrush(QBrush(Qt::gray));
        break;
    case 3:
        setBrush(QBrush(Qt::lightGray));
        break;
    default:
        break;
    }
}

int Brick::getHp()
{
    return hp;
}

void Brick::getHit()
{
    hp--;
    switch (hp) {
    case 1:
        setBrush(QBrush(Qt::darkGray));
        break;
    case 2:
        setBrush(QBrush(Qt::gray));
        break;
    // Case 3 never happens in the current game, but better leave it, maybe in the future some feature will require this behavior
    case 3:
        setBrush(QBrush(Qt::lightGray));
        break;
    default:
        break;
    }
    if(hp <= 0)
    {
        int rNum = rand() % 100 + 1;
        scene()->removeItem(this);
        gc->brickDestroyed();
        if( rNum <= 15 && gc->getBrickCount() > 0)  // 15% chance
            spawnPowerup();
        delete this;
    }
}

void Brick::setHp(int value)
{
    hp = value;
}

void Brick::spawnPowerup()
{
    Powerup * p = new Powerup();
    p->setPos(x() + rect().width()/2 - p->pixmap().rect().width()/2, y() + rect().height()/2 - p->pixmap().rect().height()/2);
    gc->scene->addItem(p);
}
