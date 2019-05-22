#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QObject>
#include <QVector2D>
#include <QMediaPlayer>

class Ball : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ball();
    ~Ball();
    void setDir(float,float);
    void setSpeed(float);
    float getSpeed();
    int getID() const;
    void setID(int);
    static int balls;
    bool operator==(const Ball&) const;
public slots:
    void move();
private:
    bool sideHit;
    int id;
    float speed;
    QVector2D dir;
    bool collided;
    QMediaPlayer * jumpsound;
    QMediaPlayer * wallsound;
    QMediaPlayer * brickhit;
};

#endif // BALL_H
