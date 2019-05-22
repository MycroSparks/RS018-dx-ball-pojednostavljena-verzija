#include "powerup.h"
#include "paddle.h"
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QGraphicsScene>
#include <gamecontroller.h>
#include <QMediaPlayer>

extern GameController * gc;

Powerup::Powerup()
{
    int rNumb = rand() % 5 + 1;

    pickup = new QMediaPlayer();
    pickup->setMedia(QUrl("qrc:/sounds/Resources/pickup.wav"));
    pickup->setVolume(30);

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);

    setZValue(0);

    switch (rNumb) {
    case 1:
        pType = Slow;
        break;
    case 2:
        pType = ExtraBall;
        break;
    case 3:
        pType = Extend;
        break;
    case 4:
        pType = Fast;
        break;
    case 5:
        pType = SpeedUp;
        break;
    default:
        break;
    }

    switch (pType) {
    case Slow:
        setPixmap(QPixmap(":/images/Resources/slow.png"));
        break;
    case ExtraBall:
        setPixmap(QPixmap(":/images/Resources/extraBall.png"));
        break;
    case Extend:
        setPixmap(QPixmap(":/images/Resources/extend.png"));
        break;
    case Fast:
        setPixmap(QPixmap(":/images/Resources/fast.png"));
    case SpeedUp:
        setPixmap(QPixmap(":/images/Resources/speedUp.png"));
    default:
        break;
    }
}

void Powerup::move()
{
    // List of pointers of all the items colliding with the ball in the current "frame"
    QList<QGraphicsItem*> cItems = collidingItems();

    // Check for collision with Paddle or Bricks
    for(int i = 0, n = cItems.size(); i < n; i++)
    {
        // Collision with the paddle
        if(typeid(*(cItems[i])) == typeid(Paddle))
        {
            pickup->play();

            switch (pType) {
            case Slow:
                if(gc->getBallSpeeds() >= 1.5f)
                    gc->setBallSpeeds(gc->getBallSpeeds() - 0.2f);
                break;
            case ExtraBall:
                gc->createBall();
                break;
            case Extend:
                gc->paddle->extend();
                break;
            case Fast:
                gc->setBallSpeeds(gc->getBallSpeeds() + 0.2f);
            case SpeedUp:
                gc->paddle->setSpeed(gc->paddle->getSpeed() + 0.5f);
                break;
            default:
                break;
            }
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x(), y()+1);
}

