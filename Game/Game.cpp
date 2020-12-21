#include "Game.h"
#include "Enemy.h"
#include <QFont>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QImage>


Game::Game(QWidget *parent):
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    // setBackgroundBrush(QBrush(QImage(":/images/bg.jpg")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    player = new Player();
    // player->setRect(0, 0, 100, 100);
    player->setPos(this->scene->width() / 2,
                   this->scene->height());

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);


    // play background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgmusic.mp3"));
    music->play();


    show();
}
