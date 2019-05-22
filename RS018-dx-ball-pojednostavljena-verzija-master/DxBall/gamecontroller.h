#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QProcess>
#include <QWidget>
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "powerup.h"
#include <QList>
#include <QGraphicsTextItem>
#include <QMediaPlayer>

class GameController : public QGraphicsView
{
public:
    // Member functions
    GameController(int difficulty,QWidget * parent = 0);
    ~GameController();
    int getBrickCount();
    bool isGameWon();
    bool isPaused();
    void pause();
    void victory();
    void defeat();
    void brickDestroyed();
    int getDifficulty();
    void setDifficulty(int);
    void createBall();
    void removeBall(Ball*);
    float getBallSpeeds();
    void setBallSpeeds(float);
    void restartGame();

    // Member attributes
    Paddle * paddle;
    QList<Ball*> balls;
    QGraphicsScene * scene;
private:
    void removeAllBalls();
    void brickIt(int);
    void focusOutEvent();
    void focusInEvent();
    float ballSpeed;
    int brickCount;
    int brickRows;
    int brickColumns;
    int difficulty;
    bool gameWon;
    bool gamePaused;
    QMediaPlayer * gameover;
    QMediaPlayer * victorysound;
    QMediaPlayer * music;
};

#endif // GAMECONTROLLER_H
