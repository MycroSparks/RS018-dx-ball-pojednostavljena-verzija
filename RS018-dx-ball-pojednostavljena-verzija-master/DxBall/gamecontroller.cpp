#include "gamecontroller.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <QMediaPlayer>

GameController::GameController(int difficulty,QWidget * parent)
{
    srand(time(NULL));

    // Init stats
    ballSpeed = 2.0f + difficulty/3;
    brickCount = 0;
    gameWon = false;
    gamePaused = false;

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    gameover = new QMediaPlayer();
    gameover->setMedia(QUrl("qrc:/sounds/Resources/gameover.wav"));

    victorysound = new QMediaPlayer();
    victorysound->setMedia(QUrl("qrc:/sounds/Resources/victory.wav"));

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/Resources/music.mp3"));
    music->setVolume(10);

    setScene(scene);
    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::StrongFocus);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/images/Resources/wallpaper1.png"));
    item->setPos(scene->width()/2-item->boundingRect().width()/2,scene->height()/2-item->boundingRect().height()/2);
    QGraphicsTextItem * wText = new QGraphicsTextItem();
    scene->addItem(item);

    // Create paddle
    paddle = new Paddle();
    paddle->setFlag(QGraphicsItem::ItemIsFocusable);
    paddle->setFocus();

    // Create ball
    createBall();

    // Add created items into the scene
    scene->addItem(paddle);

    // Set created item positions
    paddle->setPos(width()/2 - paddle->rect().width()/2, height() - paddle->rect().height()-10);

    brickIt(difficulty);        // For some reason difficulty's value turns to -842150451 in brickIt(), but when we send it as an arg it works fine..??

    if(music->state() == QMediaPlayer::StoppedState){
        music->play();}

    show();
}

GameController::~GameController()
{
    qDeleteAll(balls); // The "balls" list will always be empty at this point so this doesn't do anything in this case, good practice though
    delete paddle;
    delete scene;
}

void GameController::brickIt(int diff)
{
    int hpFormula;

    if(diff % 3 == 1)
        hpFormula = 1;
    else if(diff % 3 == 2)
        hpFormula = 2;
    else
        hpFormula = 3;

    if(diff==1 || diff==2 || diff==3){
    // Basic layout
        for(int j = 0; j < 14; j=j+2)
        {
            for(int i = 0; i < 14; i=i+2)
            {
                // Instantiate brick
                Brick * brick = new Brick(hpFormula);
                scene->addItem(brick);
                brick->setPos( (i+1.5) * 50,50 + (j+1)*17);
                brickCount++;
            }
        }
    }
    else if (diff==4 || diff==5 || diff==6){
        for(int j = 0; j < 14; j++)
        {
            for(int i = 0; i < 14-j; i++)
            {
                // Instantiate brick
                Brick * brick = new Brick(hpFormula);
                scene->addItem(brick);
                brick->setPos( (i+1) * 50,50 + (j+1)*17);
                brickCount++;
            }
        }
    }
    else if (diff==7 || diff==8 || diff==9){
        for(int j = 0; j < 10; j++)
        {
            for(int i = 0; i < 14; i++)
            {
                // Instantiate brick
                Brick * brick = new Brick(hpFormula);
                scene->addItem(brick);
                brick->setPos( (i+1) * 50,50 + (j+1)*17);
                brickCount++;
            }
        }
    }


}

void GameController::focusInEvent()
{
    paddle->setFocus();
}

int GameController::getBrickCount()
{
    return brickCount;
}

bool GameController::isGameWon()
{
    return gameWon;
}

bool GameController::isPaused()
{
    return gamePaused;
}

void GameController::pause()
{
    if(gameWon == true)
        return;
    // Could pause the game by pausing QTimers for better optimization, but it's a small so this works.
    // ( In a bigger game you'd have 1 main QTimer for fps, pause() would only need to pause that timer in order to work. )
    gamePaused = !gamePaused;
}

void GameController::victory()
{
    gameWon = true;

    music->stop();
    victorysound->play();

    // TODO: victory screen or something

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/images/Resources/wallpaper.png"));
    item->setPos(scene->width()/2-item->boundingRect().width()/2,scene->height()/2-item->boundingRect().height()/2);
    QGraphicsTextItem * wText = new QGraphicsTextItem();
    scene->addItem(item);


    wText->setPlainText(QString("VICTORY"));
    wText->setDefaultTextColor(Qt::darkCyan);
    wText->setFont(QFont("times", 50,75));
    wText->setPos(scene->width()/2 - wText->boundingRect().width()/2, scene->height()/2 - wText->boundingRect().height()/2 - 50);
    wText->setZValue(2);
    scene->addItem(wText);

    QGraphicsTextItem * iText = new QGraphicsTextItem();

    iText->setPlainText(QString("press space to restart"));
    iText->setDefaultTextColor(Qt::darkCyan);
    iText->setFont(QFont("times", 34));
    iText->setPos(scene->width()/2 - iText->boundingRect().width()/2, scene->height()/2 - iText->boundingRect().height()/2 - 75 + wText->boundingRect().height());
    iText->setZValue(2);
    scene->addItem(iText);

    removeAllBalls();
}

void GameController::defeat()
{

    gameWon = true;

    music->stop();
    gameover->play();

    // TODO: victory screen or something

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/images/Resources/wallpaper2.png"));
    item->setPos(scene->width()/2-item->boundingRect().width()/2,scene->height()/2-item->boundingRect().height()/2);
    QGraphicsTextItem * wText = new QGraphicsTextItem();
    scene->addItem(item);


    wText->setPlainText(QString("GAME OVER"));
    wText->setDefaultTextColor(Qt::darkRed);
    wText->setFont(QFont("times", 50,75));
    wText->setPos(scene->width()/2 - wText->boundingRect().width()/2, scene->height()/2 - wText->boundingRect().height()/2 - 50);
    wText->setZValue(2);
    scene->addItem(wText);

    QGraphicsTextItem * iText = new QGraphicsTextItem();

    iText->setPlainText(QString("press space to restart"));
    iText->setDefaultTextColor(Qt::darkRed);
    iText->setFont(QFont("times", 34));
    iText->setPos(scene->width()/2 - iText->boundingRect().width()/2, scene->height()/2 - iText->boundingRect().height()/2 - 75 + wText->boundingRect().height());
    iText->setZValue(2);
    scene->addItem(iText);

    removeAllBalls();
}

void GameController::brickDestroyed()
{
    brickCount--;
}

int GameController::getDifficulty()
{
    return difficulty;
}

void GameController::setDifficulty(int value)
{
    difficulty = value;
}

void GameController::createBall()
{
    if(Ball::balls>0){
        Ball * b=new Ball();
        b->setSpeed(ballSpeed);
        scene->addItem(b);
        b->setPos(paddle->pos().rx()+paddle->rect().width()/2 - b->rect().width()/2, height()-paddle->rect().height()-25);
        balls.append(b);
        Ball::balls++;
    }
    else{
        Ball * b = new Ball();
        b->setSpeed(ballSpeed);
        scene->addItem(b);
        b->setPos(width()/2 - b->rect().width()/2, height()-paddle->rect().height()-25);
        balls.append(b);
        Ball::balls++;
    }
}

void GameController::removeAllBalls()
{
    for(auto x: balls)
    {
        scene->removeItem(x);
        delete x;
    }
}

void GameController::removeBall(Ball * b)
{
    int i = b->getID();
    for(auto &x: balls)
    {
        if(x->getID() > i)
            x->setID(x->getID()-1);
    }
    Ball::balls--;
    scene->removeItem(b);
    balls.removeAt(i);
}

float GameController::getBallSpeeds()
{
    return ballSpeed;
}

void GameController::setBallSpeeds(float value)
{
    ballSpeed = value;
    //qDebug() << ballSpeed;
    for(auto const& i : balls)
    {
        i->setSpeed(ballSpeed);
    }
}

void GameController::restartGame()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
