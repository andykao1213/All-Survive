#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "getready.h"
#include "gg.h"
#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QPushButton>
#include <role.h>
#include <obstacle.h>
#include "easymusic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);    //繪製背景圖
    //void mousePressEvent(QMouseEvent *event);	//滑鼠點下事件
    void keyPressEvent(QKeyEvent *event);	//鍵盤事件

private slots:
    void birdAction();			//鳥的動作
    void pipeAction();			//綠色管子的動作
    void collisDete();			//碰撞偵測
    void gameStart();			 //遊戲開始
private:

    void birdup(int);              // 設定鳥飛行速度參數
    void createPipe();			// 產生水管
    void createBird();          // 產生角色 - 鳥
    void gameLose();			 //遊戲結束

    void gameRedy();             //遊戲預備
    int isstop;
    int isjump[3];
    getready *get;
    gg *g;
    int nbirds;

    ROLE *birds[3];			// 建立一隻角色 - 鳥
    double birdV[3];			// 鳥的速度
    QTimer *birdTimer;
    QPushButton *btn;
    double timedata;			// birdTimer interval
    double birdV_array[15];
    double index_birdV[3];
    enum{lose=0,start=1,redy=2};  // Enum三個參數, 代表遊戲狀態
    int gamemod;		//目前遊戲狀態, 0=lose, 1=start, 2=redy
    // 遊戲狀態預設流程： redy -> start -> lose -> redy -> start .... 不斷循環
    enum{pipeCount=5};		//  pipe 數量
    OBSTACLE *pipe[3];	// 建立水管
    QTimer *pipeTimer;
    int pipeTValue;     // pipeTimer interval
    int pipeXgap;		// 管子間距
    int lastPipe;		// the flag of rightest pipe

    int win_width;      // 視窗寬度
    int win_height;     // 視窗高度
    easyMusic *bgm;
    easyMusic *fgm;
    easyMusic *ko;
    easyMusic *pau;
    QPushButton* creatBtn(QString pic, QString str);
    QPushButton* Start;
    QPushButton* Lose;
    QPushButton* Pause;

};

#endif // MAINWINDOW_H
