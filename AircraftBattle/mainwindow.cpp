#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //应用图片
    //this->setWindowIcon(QPixmap(":/res/shapez.png"));
    //标题
    this->setWindowTitle("少女折寿中……");
    //图标
    this->setWindowIcon(QIcon(":/res/icon2.png"));
    this->setFixedSize(this->width(),this->height());

    //play按钮
    MyPushButton * startBtn = new MyPushButton(":/res/play.png");
    startBtn->setParent(this);
    startBtn->setIconSize(QSize(275,88));
    startBtn->setFixedSize(275,88);
    startBtn->move((this->width()/2-startBtn->width())*2/3,350);

    //quit按钮
    MyPushButton * quitBtn = new MyPushButton(":/res/exit.png");
    quitBtn->setParent(this);
    quitBtn->setIconSize(QSize(275,88));
    quitBtn->setFixedSize(275,88);
    quitBtn->move((this->width()/2-quitBtn->width())/3 + this->width()/2 ,350);

    connect(startBtn,&MyPushButton::clicked,this,[=](){
        //做特效
        startBtn->zoom_down();
        startBtn->zoom_up();

        //做音效
        //todo

        //延时进入
        QTimer::singleShot(100,this,[=](){  
            //自身隐藏
            this->hide();
            //游戏界面
            playWindow = new PlayWindow(this);
            //监听返回信号
            connect(playWindow,&PlayWindow::Back,this,[=](){
                //重新显示开始界面
                delete playWindow;
                this->show();
            });
            //进入游戏界面
            playWindow->show();
        });
    });

    connect(quitBtn,&MyPushButton::clicked,this,[=](){

        //做特效
        quitBtn->zoom_down();
        quitBtn->zoom_up();

        //做音效
        //todo

        //延时退出
        QTimer::singleShot(100,this,[=](){
            //关闭
            this->close();
        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
