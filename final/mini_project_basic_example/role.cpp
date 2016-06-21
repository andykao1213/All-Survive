#include "role.h"

ROLE::ROLE(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(35,35);
    src[0]=":/Image/bird1.png";
    src[1]=":/Image/bird2.png";
    src[2]=":/Image/bird3.png";
    roletimer = new QTimer(this);
    connect(roletimer, SIGNAL(timeout()), this, SLOT(update()));
    roletimer->start(100);
}

ROLE::~ROLE()
{

}

void ROLE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    if(i==1){
        pix.load(src[0]);
        painter.drawPixmap(0,0,35,35,pix);
        i++;
    }else if(i == 2){
        pix.load(src[1]);
        painter.drawPixmap(0,0,35,35,pix);
        i++;
    }else{
        pix.load(src[2]);
        painter.drawPixmap(0,0,35,35,pix);
        i++;
        i = 1;
    }
    painter.drawPixmap(0,0,35,35,pix);
}

