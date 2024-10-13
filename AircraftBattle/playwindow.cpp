#include "playwindow.h"
#include <QApplication>
#include <QScreen>
#include <QGraphicsView>
#include <mypushbutton.h>
PlayWindow::PlayWindow(QMainWindow *parent) : QMainWindow(parent) {
    initScene();

}

void PlayWindow::initScene(){

    //游戏界面大小
    this->setFixedSize(scene_width,scene_height);

    //移动到屏幕中央
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2-40;
    this->move(x, y);

    //设置窗口标题
    this->setWindowTitle("AircraftBattle");

    //创建场景
    scene = new QGraphicsScene(this);

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(scene_width,scene_height);

    setCentralWidget(view);

    // 加载背景图片
    backgroundPixmap = QPixmap(":/res/background.jpg");
    backgroundheight = backgroundPixmap.height();
    offset = -backgroundheight/2;
    // 创建背景项
    backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setZValue(0);
    // 添加背景项到场景
    scene->setSceneRect(0, 0, scene_width, backgroundheight);
    scene->addItem(backgroundItem);
    backgroundItem->setPos(0, 0);

    // 返回按钮
    backButton();


    timer = new QTimer(this);
    timer->start(1000/Fps);
    qDebug()<<backgroundPixmap.height();
    connect(timer, &QTimer::timeout, this, &PlayWindow::updateBackground);

    myplane = new Myplane(QPixmap(":/res/hitpoint.png"),QPixmap(":/res/myplane0.png"),5,8,SELF,QPointF(300,600),QSize(80,80));
    myplane->setZValue(1);
    scene->addItem(myplane);
    scene->addItem(myplane->hitPoint);
}


void PlayWindow::backButton()
{
    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/back.png",QPoint(60,60));
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() - 5, 20);
    //点击返回
    connect(backBtn,&MyPushButton::clicked,this,[=](){

        //特效
        backBtn->zoom_down();
        backBtn->zoom_up();

        //返回
        QTimer::singleShot(100,this,[=](){
            emit this->Back();
        });
    });
}



void PlayWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case(Qt::Key_W):
        //TODO
        myplane->move(0,-1);
        break;
    case(Qt::Key_A):
        //TODO
        myplane->move(-1,0);
        break;
    case(Qt::Key_S):
        //TODO
        myplane->move(0,1);
        break;
    case(Qt::Key_D):
        //TODO
        myplane->move(1,0);
        break;
    }
}

void PlayWindow::wheelEvent(QWheelEvent *event) {
    event->ignore(); // 接受事件，但不处理它
}

void PlayWindow::updateBackground(){
    // 更新背景项的位置
    backgroundItem->setPos(0, offset);

    // 更新偏移量，循环平铺
    offset += 5; // 每次移动5个像素
    if (offset >= 0) {
        offset = -backgroundheight/2; // 重置偏移量以实现循环
    }
}
