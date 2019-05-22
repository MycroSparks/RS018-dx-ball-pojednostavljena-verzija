#include "paddle.h"
#include <QDebug>
#include <QGraphicsView>
#include <gamecontroller.h>

extern GameController * gc;

Paddle::Paddle()
{
    // Init paddle stats
    dir = 0;                // 0 = standing still, -1 = left, 1 = right
    speed = 4.0f;
    timeSpentMoving = 0;
    //width = 80;
    //heigth = 20;

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);

    // Draw paddle
    setRect(0,0,80,10);
    setBrush(QBrush(Qt::cyan));
}

void Paddle::keyReleaseEvent(QKeyEvent *event)
{
    // QKeyEvent::isAutoRepat() makes the event return true only when the button is releasted for real (keyReleaseEvent would activate every "frame" otherwise)
    if(event->isAutoRepeat() == false && event->key() == Qt::Key_A && dir == -1)
    {
        dir = 0;
        timeSpentMoving = 0;
    }
    if(event->isAutoRepeat() == false && event->key() == Qt::Key_D && dir == 1)
    {
        timeSpentMoving = 0;
        dir = 0;
    }
}

void Paddle::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        //setPos(x()-30, y());
        dir = -1;
    }
    else if(event->key() == Qt::Key_D && x() < (scene()->width() - rect().width()))
    {
        //setPos(x()+30, y());
        dir = 1;
    }

    if(gc->isGameWon() && event->key() == Qt::Key_Space)
    {
        gc->restartGame();
    }

    if(event->key() == Qt::Key_P && event->isAutoRepeat() == false)
    {
        gc->pause();
    }

    // Cheat code for debugging
    if(event->key() == Qt::Key_F1 && gc->isGameWon() == false)
    {
        gc->victory();
    }
}

int Paddle::getDir()
{
    return dir;
}

void Paddle::extend()
{
    setRect(0, 0, rect().width()+30, rect().height());
    setPos(x()-15,y());
}

void Paddle::setSpeed(float value)
{
    speed = value;
}

float Paddle::getSpeed()
{
    return speed;
}

float Paddle::getTimeSpentMoving()
{
    return timeSpentMoving;
}


// MOST RESPONSIVE MOVEMENT THAT WE COULD THINK OF ( with the basic move left on event->key() == A,D; the movement has a delay after the initial press and holding )
void Paddle::move()
{
    // Could pause the game by pausing QTimers for better optimization, but it's a small so this works.
    // ( In a bigger game you'd have 1 main QTimer for fps, pause() would only need to pause that timer in order to work. )
    if(gc->isPaused() == true)
        return;

    // If button pressed
    if(dir != 0)
    {
        bool move = false;

        // Check if paddle's out of bounds
        if(dir == -1 && x() > 0)
        {
            move = true;
        }
        else if(dir == 1 && x() < (scene()->width() - rect().width()))
        {
            move = true;
        }


        if(move)
        {
            timeSpentMoving += 0.01f;
            setPos(x() + speed * dir, y());
        }
        if(timeSpentMoving > 1)
            timeSpentMoving = 1;
    }

}
