#include "Snake.h"
#include <QPainter>
#include <QAction>
#include <QRandomGenerator>
#include <QTime>

Snake::Snake(QWidget *parent):
    QWidget(parent)
{

    setStyleSheet("background-color: black;");
    setFixedSize(B_WIDTH, B_HEIGHT);
    dot.load("dot.png");
    head.load("head.png");
    apple.load("apple.png");

    setWindowIcon(QIcon("apple.png"));


    // It was a bad idea
    //restart = new QPushButton("New Game", this);
    //restart->setStyleSheet("background-color: white;");
    //connect(restart, &QPushButton::clicked, this, &Snake::initGame);
    //restart->hide();

    timerId = 0;
    initGame();
}


void Snake::initGame()
{
    inGame = true;
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    score = 0;


    dots = 3;
    for (int z = 0; z < dots; ++z) {
        x[z] = width()/2 - z * 10;
        y[z] = height()/2;
    }

    locateApple();


    if (timerId) {
        killTimer(timerId);
    }

    timerId = startTimer(DELAY);
}


void Snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    if (inGame) {
        checkApple();
        checkCollision();
        move();
    }

    repaint();
}


void Snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter qp(this);
    if (inGame) {
        qp.drawImage(apple_x, apple_y, apple);
        for (int z = 0; z < dots; ++z) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }
    } else {
        //restart->show();

        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int h = height();
        int w = width();

        QString message = "Game Over";
        int textWidth = fm.horizontalAdvance(message);
        qp.setPen(QColor(Qt::white));
        qp.setFont(font);
        qp.translate(QPoint(w/2, h/2)); // move painter to center
        qp.drawText(-textWidth/2, 0, message);

        QPainter scorePnt(this);
        QString num = QString("Your score: ") + QString::number(score);
        int numWidth = fm.horizontalAdvance(num);
        scorePnt.setPen(QColor(Qt::white));
        scorePnt.setFont(font);
        scorePnt.translate(w/2, h/2 + 30);
        scorePnt.drawText(-numWidth/2, 0, num);
    }
}


void Snake::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if (key == Qt::Key_Left && !rightDirection) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (key == Qt::Key_Right && !leftDirection) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (key == Qt::Key_Up && !downDirection) {
        leftDirection = false;
        rightDirection = false;
        upDirection = true;
    }

    if (key == Qt::Key_Down && !upDirection) {
        leftDirection = false;
        rightDirection = false;
        downDirection = true;
    }

    if (key == Qt::Key_Space) {
        initGame();
    }

    QWidget::keyPressEvent(e);
}


void Snake::move()
{
    for (int z = dots; z > 0; --z) {
        x[z] = x[z - 1];
        y[z] = y[z - 1];
    }

    if (leftDirection)
        x[0] -= DOT_SIZE;

    if (rightDirection)
        x[0] += DOT_SIZE;

    if (upDirection)
        y[0] -= DOT_SIZE;

    if (downDirection)
        y[0] += DOT_SIZE;
}


void Snake::locateApple()
{
    int r = QRandomGenerator::global()->generate() % RAND_POS;
    apple_x = r * DOT_SIZE;

    r = QRandomGenerator::global()->generate() % RAND_POS;
    apple_y = r * DOT_SIZE;

    for (int z = 0; z < dots; ++z) {
        if (apple_x == x[z] && apple_y == y[z]) {
            locateApple();
        }
    }
}


void Snake::checkApple()
{
    if (apple_x == x[0] && apple_y == y[0]) {
        dots++;
        score++;
        locateApple();
    }
}


void Snake::checkCollision()
{
    for (int z = 1; z < dots; ++z) {
        if (x[z] == x[0] && y[z] == y[0]) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT)
        inGame = false;

    if (x[0] >= B_WIDTH)
        inGame = false;

    if (x[0] < 0)
        inGame = false;

    if (y[0] < 0)
        inGame = false;
}

