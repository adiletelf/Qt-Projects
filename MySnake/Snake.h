#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>

class Snake: public QWidget
{
    Q_OBJECT
public:
    Snake(QWidget *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    QImage dot;
    QImage head;
    QImage apple;

    //QPushButton* restart;

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int ALL_DOTS = 900;
    static const int DOT_SIZE = 10;
    static const int RAND_POS = 29;
    static const int DELAY = 140;

    int dots;
    int score;
    int timerId;
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool inGame;
    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;

    void initGame();
    void move();

    void locateApple();
    void checkApple();
    void checkCollision();


};

#endif // SNAKE_H
