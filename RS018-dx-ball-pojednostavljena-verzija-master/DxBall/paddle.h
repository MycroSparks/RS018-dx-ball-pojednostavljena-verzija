#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

class Paddle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    int getDir();
    void extend();
    void setSpeed(float);
    float getSpeed();
    float getTimeSpentMoving();
public slots:
    void move();
private:
    //int width,heigth;     Postoji rect().width() i rect().height()...
    int dir;
    float timeSpentMoving;
    float speed;
};

#endif // PADDLE_H
