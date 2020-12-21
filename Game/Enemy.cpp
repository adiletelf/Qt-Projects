#include "Enemy.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib>

extern Game * game;

Enemy::Enemy(QGraphicsItem * parent):
    QObject(), QGraphicsPixmapItem(parent)
{
    int random_number = rand() % 700;
    setPos(random_number, 0);

    // setPixmap(QPixmap(":/images/enemy.png"));

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Enemy::move()
{
    setPos(x(),
           y() + 5);

    if (pos().y() > scene()->height())
    {
        game->health->decrease();
        scene()->removeItem(this);
        delete this;
    }
}
