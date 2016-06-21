#include "mainwindow.h"
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    win_width = 380;
    win_height = 450;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/bird1.png"));
    this->setWindowTitle("Allmighty");

    bgm = new easyMusic("/bgm.wav",100,1);
    fgm = new easyMusic("/fgm.mp3",50,0);
    ko = new easyMusic("/Game Over.mp3",100,0);
    pau = new easyMusic("/pause.mp3",100,0);
    //g = new gg(this);
    //創建水管
    pipe[0] = new OBSTACLE(this);
    pipe[1] = new OBSTACLE(this);
    pipe[2] = new OBSTACLE(this);

    //創建鳥
    nbirds = 3;
    for(int i=0; i<nbirds; i++) birds[i]=new ROLE(this);

    Lose = creatBtn(":/Image/gg.png", "press r restart");
    Pause = creatBtn(":/Image/pause.png", "pause");
    Pause->hide();
    //遊戲初始模式
    gameRedy();

    Start = creatBtn(":/Image/icon.png", "START");

    Start->move(5, 25);

    connect(Start, SIGNAL(clicked()), SLOT(gameStart()));

}
void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    QPainter painter(this);
    QPixmap bgImg;
    bgImg.load(":/Image/bg.png");
    painter.drawPixmap(0, 0, win_width,win_height,bgImg);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(gamemod != lose){
          if(event->key() == Qt::Key_P){
              if(!isstop){
                  birdTimer->stop();
                  pipeTimer->stop();
                  bgm->pause();
                  pau->play();
                  isstop = 1;
                  Pause->show();
              } else {
                  birdTimer->start(timedata);
                  pipeTimer->start(pipeTValue);
                  pau->stop();
                  pau->play();
                  bgm->play();
                  isstop = 0;
                  Pause->hide();
              }
          }
      } else if(event->key() == Qt::Key_R){
          gamemod=start;
          bgm->stop();
          gameRedy();
          //Lose->setEnabled(false);
          gameStart();
      }

    /*if(gamemod == redy){
        if(event->key() == Qt::Key_A)
            gameStart();
        if(event->key() == Qt::Key_S)
            gameStart();
        if(event->key() == Qt::Key_D)
            gameStart();

    }*/
    if(gamemod == start){
        if(event->key()==Qt::Key_A && isjump[0] == 0)
        {
            birdup(0);
            isjump[0] = 1;
            if(isstop == 0){
                fgm->stop();
                fgm->play();
            }

        }
        else if(event->key()==Qt::Key_S && isjump[1] == 0)
        {
            birdup(1);
            isjump[1] = 1;
            if(isstop == 0){
                fgm->stop();
                fgm->play();
            }

        }
        else if(event->key()==Qt::Key_D && isjump[2] == 0)
        {
            birdup(2);
            isjump[2] = 1;
            if(isstop == 0){
                fgm->stop();
                fgm->play();
            }

        }

    }
}
void MainWindow::createPipe()		//初始化水管，依序排在視窗外
{

    int startx=win_width+10;		//第一个水管的位置
    for(int i = 0; i < 3; i++){
        pipe[i]->move(startx,-100);
        pipe[i]->isprint = 0;
        pipe[i]->lay = i;
    }

    pipeTimer =new QTimer(this);	//pipeTimer 處理兩個動作
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(pipeAction()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(collisDete()));
    pipeTValue=8;

}
void MainWindow::createBird(){

    for(int i=0; i<nbirds; i++) birds[i]->move(60,450);
    //鳥的上下速度
    this->birdV_array[0]=-3;
    this->birdV_array[1]=-4;
    this->birdV_array[2]=-3;
    this->birdV_array[3]=-2;
    this->birdV_array[4]=-1;
    this->birdV_array[5]=-1;
    this->birdV_array[6]=-1;
    this->birdV_array[7]=0;
    this->birdV_array[8]=1;
    this->birdV_array[9]=1;
    this->birdV_array[10]=2;
    this->birdV_array[11]=2;
    this->birdV_array[12]=2;
    this->birdV_array[13]=3;
    this->birdV_array[14]=3;

    for(int i=0; i<3; i++)this->index_birdV[i]=0;


    for(int i=0; i<3; i++)birdV[i]=0;

    birdTimer=new QTimer(this);
    connect(birdTimer,SIGNAL(timeout()),this,SLOT(birdAction()));
    timedata=8;
}
void MainWindow::birdup(int k){
    index_birdV[k]=0.0;
    birdV[k]=birdV_array[int(index_birdV[k]*10)]*6;
}
void MainWindow::birdAction()
{
    //鳥的運動
    // 每次觸發這個function都會更改鳥的位置，x軸不變, y軸加上 birdV成為新的位置
    // XX->pos().x() and XX->pos().y() 是QWidget物件的函式，可以用來取得xy座標位置
    for(int i=0; i<nbirds; i++){
        birds[i]->move(birds[i]->pos().x(),birds[i]->pos().y()+birdV[i]);
        if(index_birdV[i]<14.0)
            index_birdV[i]+=0.2;
        else
            index_birdV[i]=14.0;
    }
    for(int i=0; i<3; i++)birdV[i]=birdV_array[int(index_birdV[i])];

    // 這邊做一個地板碰撞偵測
    for(int i=0; i<nbirds; i++){


    if(birds[i]->pos().y()+birds[i]->height()>=win_height/nbirds+win_height/nbirds*i+10)
    {
        birds[i]->move(birds[i]->pos().x(),win_height/nbirds+win_height/nbirds*i-birds[i]->height()+10); // XX->height可用來取得物件高度
        //birdTimer->stop();
        isjump[i] = 0;
   }

    if(birds[i]->pos().y()+birds[i]->height()<=-20)
            birds[i]->move(birds[i]->pos().x(),-20);
    }
}
void MainWindow::pipeAction()
{
    int pipew[4] ={10, 20, 40, 60};
    int pipeh[4] ={50, 30, 20, 10};

    // 每次觸發這個函式，水管都會向左移動，如果最左邊的水管離開地圖範圍則移動到最右邊

    qsrand(time(NULL));
    for(int i = 0; i < 3; i++){
        int a = rand()%4;
        int b = rand()%6;
        double s = rand()%3+3;
        if(pipe[i]->pos().x()<-100){
            pipe[i]->move(400,-100);
            pipe[i]->isprint = 0;
        } else if(pipe[i]->isprint){
            pipe[i]->move(pipe[i]->pos().x()-pipe[i]->speed,pipe[i]->pos().y());
        } else if(!pipe[i]->isprint){
            if(b>1){
                pipe[i]->isprint = 1;
                pipe[i]->width= pipew[a];
                pipe[i]->height= pipeh[a];
                pipe[i]->speed = s/2;
            }
        }
    }

}
void MainWindow::collisDete()
{
    for(int i = 0; i < 3; i++){
        int birdRx=birds[2-i]->pos().x()+30;
        int birdDy=birds[2-i]->pos().y()+25;
        if(birdRx>=pipe[i]->pos().x() && birds[2-i]->pos().x() < pipe[i]->pos().x()+pipe[i]->width-20)
        {
            if(birdDy >= 450-pipe[i]->height-i*150)
                gameLose();
        }
    }
}
void MainWindow::gameRedy()
{
    gamemod=redy;
    //Lose->hide();
    get = new getready(this);
    ko->stop();
    createBird();
    get->move(0,0);
    createPipe();

}
void MainWindow::gameLose()
{
    gamemod=lose;
    isstop = 1;
    birdTimer->stop();
    pipeTimer->stop();
    bgm->stop();
    ko->play();

    Lose->show();

    //connect(Start, SIGNAL(clicked()), SLOT(gameStart()));
}
void MainWindow::gameStart()
{
    Start->hide();
    Start->setEnabled(false);
    Lose->hide();
    get->move(380,450);
    gamemod=start;
    bgm->play();
    isstop = 0;
    birdTimer->start(timedata);
    pipeTimer->start(pipeTValue);

}
QPushButton* MainWindow::creatBtn(QString pic, QString str)
{
    QPushButton *btn = new QPushButton(this);

    btn->setGeometry(10, 10, 200, 200);
    btn->clearMask();
    btn->setBackgroundRole(QPalette::Base);

    QPixmap bg; bg.load(pic);

    btn->setFixedSize(bg.width(), bg.height());
    btn->setMask(bg.createHeuristicMask());
    btn->setIcon(bg);
    btn->setIconSize(QSize(bg.width(), bg.height()));
    btn->setToolTip(str);

    return btn;
}

