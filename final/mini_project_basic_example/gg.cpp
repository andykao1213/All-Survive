#include "gg.h"
#include <QPixmap>
#include <QPainter>

gg::gg(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(190,100);
}
void gg::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    QPainter painter(this);
    QPixmap bgImg;
    bgImg.load(":/Image/gg.png");
    painter.drawPixmap(0, 0, 190,100,bgImg);

}
gg::~gg()
{

}

