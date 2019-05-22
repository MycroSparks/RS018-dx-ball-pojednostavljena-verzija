#include "ball.h"
#include "paddle.h"
#include "gamecontroller.h"
#include <cmath>
#include <QMediaPlayer>

extern GameController * gc; // There is an external global object gc of type GameController
int Ball::balls = 0;

Ball::Ball()
{
    // Init default ball stats
    speed = 2.0f;
    dir.setX(0.3f);
    dir.setY(1);
    dir.normalize();
    setZValue(1);
    id = balls;
    sideHit = false;

    //Init sounds
    jumpsound = new QMediaPlayer();
    jumpsound->setMedia(QUrl("qrc:/sounds/Resources/jumpsound.wav"));
    jumpsound->setVolume(70);

    wallsound = new QMediaPlayer();
    wallsound->setMedia(QUrl("qrc:/sounds/Resources/wallsound.wav"));
    wallsound->setVolume(20);

    brickhit = new QMediaPlayer();
    brickhit->setMedia(QUrl("qrc:/sounds/Resources/brickhit.wav"));
    brickhit->setVolume(30);

    // Draw the ball
    setRect(0,0,10,10);
    setBrush(QBrush(Qt::darkRed));

    // Connect
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Ball::move()
{
    // Could pause the game by pausing QTimers for better optimization, but it's a small so this works.
    // ( In a bigger game you'd have 1 main QTimer for fps, pause() would only need to pause that timer in order to work. )
    if(gc->isGameWon() || gc->isPaused())
        return;

    collided = false;
    // List of pointers of all the items colliding with the ball in the current "frame"
    QList<QGraphicsItem*> cItems = collidingItems();

    // Check for collision with Paddle or Bricks
    for(int i = 0, n = cItems.size(); i < n; i++)
    {
        // Ball hit SFX go here

        // Collision with the paddle
        if(typeid(*(cItems[i])) == typeid(Paddle))
        {


            // Change Vec2's y component based on player input

            // Check if the hit was from the side or front
            if(dir.y() < 0 && gc->paddle->y() < y()+rect().height()+speed*dir.y())
            {
                sideHit = true;
            }
            else
                sideHit = false;

            if(sideHit == false)
            {
                int p=pos().rx()+rect().width()/2-(gc->paddle->pos().rx()+gc->paddle->rect().width()/2);
                if(p<0)
                    setDir(- std::abs(dir.x())-0.05-std::abs(p)/50, - dir.y());
                else if(p>0)
                    setDir( std::abs(dir.x())+0.05+std::abs(p)/50, - dir.y());
                else if(p==(gc->paddle->rect().width()))
                    setDir(1.2f,-dir.y());
                else if(p==(- gc->paddle->rect().width()))
                    setDir(-1.2f,-dir.y());
                else if(p==0)
                    setDir(0, - dir.y());

                // Could get a reference via --Paddle * paddle = dynamic_cast<Paddle*>(cItems[i]);-- but we want gc to be global anyway, might as well use it
                /*
                switch(gc->paddle->getDir())
                {
                // Player's not pressing anything
                case 0:
                    setDir(dir.x(), - dir.y());
                    break;
                // Player's pressing/holding D
                case 1:
                    if(dir.x() == 0)
                    {
                        setDir(1, - dir.y());
                    }
                    else
                    {
                        setDir(std::abs(0.5f + gc->paddle->getTimeSpentMoving()), - dir.y());
                    }
                    break;
                // Player's pressing/holding A
                case -1:
                    if(dir.x() == 0)
                    {
                        setDir(-1, - dir.y());
                    }
                    else
                    {
                        setDir(- std::abs(0.5f + gc->paddle->getTimeSpentMoving()), - dir.y());
                    }
                    break;
                }*/

            }
            else
            {
                setDir(-dir.x(), dir.y());
            }

            setPos(x()+dir.x() * speed, y() - dir.y() * speed);

            jumpsound->play();
        }

        // Collision with a brick
        if(typeid(*(cItems[i])) == typeid(Brick))
        {

            if(brickhit->state() == QMediaPlayer::PlayingState){
                brickhit->setPosition(0);
            }
            else if(brickhit->state() == QMediaPlayer::StoppedState){
                brickhit->play();
            }

            Brick * bricky = dynamic_cast<Brick*>(cItems[i]);

            // Check if the hit was from the side or front
            if(dir.y() < 0 && bricky->y() < y()+rect().height()+speed*dir.y())
            {
                sideHit = true;
            }
            else if(dir.y() > 0 && bricky->y() + bricky->rect().height()-speed*dir.y() > y())
            {
                sideHit = true;
            }
            else
                sideHit = false;

            bricky->getHit();
            // Makes sure the ball changes direction only once even when colliding with multiple bricks.
            //(Without the if() check dir.y would be --dir.y <==> dir.y which would make it go through them)
            if(collided == false)
            {
                if(sideHit == false)
                {
                    setDir(dir.x(), - dir.y());
                }
                else
                {
                    setDir(-dir.x(), dir.y());
                }
            }

            if(gc->getBrickCount() <= 0 && gc->isGameWon() == false)
            {
                gc->victory();
                return;
            }
            collided = true;
            setPos(x()+dir.x() * speed, y() - dir.y() * speed);
        }
    }

    //*// Handle ball going out of bounds

    // Ball hits top of the screen
    if(y() <= 0)
    {
        setDir(dir.x(), - dir.y());
        wallsound->play();
    }
    // Ball hits left or right edge of the screen
    if(x() <= 0 || x() >= scene()->width() - rect().width())
    {
        setDir(-dir.x(), dir.y());
        wallsound->play();
    }
    // Ball goes through bottom of the screen
    if(y() >= scene()->height())
    {
        // Restart
        gc->removeBall(this);
        if(Ball::balls <= 0)
        {
            gc->defeat();
        }
        delete this;
        return;
    }

    setPos(x()+dir.x() * speed, y() - dir.y() * speed);
    //qDebug() << y();
}

void Ball::setDir(float x, float y)
{
    dir.setX(x);
    dir.setY(y);
    dir.normalize();
}

void Ball::setSpeed(float value)
{
    speed = value;
}

int Ball::getID() const
{
    return id;
}

void Ball::setID(int value)
{
    id = value;
}

bool Ball::operator==(const Ball& o) const
{
    if( id == o.getID() )
        return true;
    else
        return false;
}

Ball::~Ball()
{
    //delete this;
}
