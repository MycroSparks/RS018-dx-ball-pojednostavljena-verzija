#ifndef BRICK_H
#define BRICK_H

#include "gamecontroller.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsItem>
#include "powerup.h"
#include "ball.h"

class Brick : public QGraphicsRectItem
{
public:
    Brick(int);
    int getHp();
    void getHit();
    void setHp(int);
    void spawnPowerup();
private:
    int hp;
};

#endif // BRICK_H
