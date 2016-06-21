#include "getready.h"
#include <QPixmap>
#include <QPainter>

getready::getready(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(380,450);
}

void getready::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    QPainter painter(this);
    QPixmap bgImg;
    bgImg.load(":/Image/bg_start.png");
    painter.drawPixmap(0, 0, 380,450,bgImg);

}

getready::~getready()
{

}

