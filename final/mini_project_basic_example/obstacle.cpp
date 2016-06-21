#include "obstacle.h"

OBSTACLE::OBSTACLE(QWidget *parent) : QWidget(parent)
{

    Gap=200;
    this->setFixedSize(35,Gap+600);

}

OBSTACLE::~OBSTACLE()
{

}

void OBSTACLE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    /*pix.load(":/Image/pipe1.png");
    painter.drawPixmap(0,0,70,300,pix);*/
    pix.load(":/Image/pipe2.png");
    painter.drawPixmap(0,550-height-lay*150,width,height,pix);
}

/*int OBSTACLE::getH1() //水管長度
{
    return 300;
}

int OBSTACLE::getH2() //水管長度
{
    return 300;
}

int OBSTACLE::getGap() // 上下水管間隔
{
    return Gap;
}*/

