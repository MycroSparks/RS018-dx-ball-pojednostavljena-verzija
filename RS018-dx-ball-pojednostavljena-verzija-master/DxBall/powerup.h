#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QMediaPlayer>

class Powerup : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Powerup();
    enum PowerUpType { Slow, ExtraBall, Extend, Fast, SpeedUp };
public slots:
    void move();
private:
    PowerUpType pType;
    QMediaPlayer * pickup;
};

#endif // POWERUP_H
