#include <Qdebug>
#include "playwindow.h"
#include <QApplication>
#include <QScreen>
#include <QGraphicsView>
#include <mypushbutton.h>
#include <stdlib.h>
PlayWindow::PlayWindow(QMainWindow *parent)
    : QMainWindow(parent){
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
    this->setWindowTitle("打不过🐴？");

    //设置图标
    this->setWindowIcon(QIcon(":/res/icon.jpg"));

    //创建场景
    scene = new QGraphicsScene(this);

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setFixedSize(scene_width,scene_height);
    view->setSceneRect(rect());

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

    // 加载边栏图片
    barPixmap = QPixmap(":/res/bar.png");
    // 创建边栏项
    barItem = new QGraphicsPixmapItem(barPixmap.scaled(70,860));
    barItem->setZValue(3);
    // 添加边栏项到场景
    scene->addItem(barItem);
    barItem->setPos(670, 0);

    // 返回按钮
    backButton();

    createEnemy(shootenemy3,QPixmap(":/res/enemy_1.png"),110,1,QPointF(300,0),QSize(80,80),0,1);
    bullet_supporter = new Enemy(QPixmap(":/res/enemy_1.png"), 1, 1, QPointF(0, 900), QSize(1, 1), 0, 0);
    scene->addItem(bullet_supporter);

    timer = new QTimer(this);
    timer->start(1000/Fps);

    connect(timer, &QTimer::timeout, this, [=](){//全局定时器行为
        updateBackground();

        //自机移动
        myplane->setSpeed((myplane->low_speed == true) ? 3 : 8);
        for(int i = 0; i < 4; ++i)
        {
            double dx = 0, dy = 0;
            dx += (moving[i] ? di[i][0] : 0);
            dy += (moving[i] ? di[i][1] : 0);
            if(dx || dy)
            {
                double len = sqrt(dx * dx + dy * dy);
                myplane->move(dx / len, dy / len);
            }
        }

        // 自机处于无敌状态的处理
        if(myplane->nondead){
            ++myplane->time_after_death;
            if(myplane->time_after_death == myplane->nondead_time){
                myplane->nondead = false;
                myplane->time_after_death = 0;
            }
        }

        //子弹移动与删除
        myplane->bullet_move();
        myplane->bullet_dead();
        for(auto m : shootenemies){
            m->bullet_move();
            m->bullet_dead();
        }
        bullet_supporter->bullet_move();
        bullet_supporter->bullet_dead();

        //5帧产生一个子弹,不是很丝滑
        if(selfattacktimer%5==0){
            if(upgrade){
                int num = myplane->attack(SLFBULLETLEVELUP, 0, 0);
                int s = myplane->bullet_list.size()-1;//将最新产生的子弹加入scene
                for (int i = 0; i < num; ++i) {
                    scene->addItem(myplane->bullet_list[s-i]);
                }
            } else {
                myplane->attack(SLFBULLET, 0, 0);
                int s = myplane->bullet_list.size()-1;
                scene->addItem(myplane->bullet_list[s]);
            }
        }
        selfattacktimer = (selfattacktimer+1)%5;

        enemy_clock++;
        if(enemy_clock%(Fps * 60) == 0){
            qDebug()<<"enemy level up!";
            enemy_phase++;
            enemy_clock=0;
            if(enemy_phase>=3){
                enemy_phase=3;
                //产生一个boss
                a_wave_of_enemies(8);
            }
        }

        // 碰撞检测
        for(auto b:bullet_supporter->bullet_list)
        {
            if(myplane->hitPoint->collidesWithItem(b))
            {
                myplane->be_attacked();
                b->state = false;
            }
        }
        for(auto enemy:enemies)
        {
            if(enemy->collidesWithItem(myplane->hitPoint))
            {
                myplane->be_attacked();
                qDebug()<<myplane->life();
            }
            for(auto b:myplane->bullet_list)
            {
                if(enemy->collidesWithItem(b))
                {
                    enemy->be_attacked();
                    b->state = false;
                }
            }
        }
        for(auto senemy:shootenemies)
        {
            if(senemy->collidesWithItem(myplane->hitPoint))
            {
                myplane->be_attacked();
            }
            for(auto b:myplane->bullet_list)
            {
                if(senemy->collidesWithItem(b))
                {
                    senemy->be_attacked();
                    b->state = false;
                }
            }
            for(auto bu:senemy->bullet_list)
            {
                if(myplane->hitPoint->collidesWithItem(bu))
                {
                    myplane->be_attacked();
                    bu->state = false;
                }
            }
        }

        // 删除敌机
        for(auto it = enemies.begin(); it != enemies.end();)
        {
            if(!(*it)->is_alive())
            {
                delete (*it);
                it = enemies.erase(it);
            }
            else
            {
                ++it;
            }
        }
        for(auto it = shootenemies.begin(); it != shootenemies.end();)
        {
            if(!(*it)->is_alive())
            {
                for(auto b:(*it)->bullet_list)
                {
                    auto tmp = new Bullet(*b);
                    tmp->setPos(b->pos());
                    bullet_supporter->bullet_list.append(tmp);
                    scene->addItem(bullet_supporter->bullet_list[bullet_supporter->bullet_list.size() - 1]);
                    b->state = false;
                }
                (*it)->bullet_dead();
                delete (*it)->timer;
                delete (*it);
                it = shootenemies.erase(it);
            }
            else
            {
                ++it;
            }
        }
    });


    myplane = new Myplane(QPixmap(":/res/hitpoint.png"),QPixmap(":/res/myplane0.png"),5,8,SELF,QPointF(300,600),QSize(80,80));
    myplane->setZValue(1);
    for(auto h : myplane->hp){
        scene->addItem(h);
    }
    scene->addItem(myplane);
    scene->addItem(myplane->hitPoint);

    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    enemy_generate=new QTimer(this);
    enemy_generate->start(10000);
    connect(enemy_generate,&QTimer::timeout,this,[=](){
        qDebug()<<"enemy generate!";
        int n=rand()%3;
        switch(enemy_phase){
        case 1:{
            qDebug()<<"enemy_1 of "<<n;
            break;
        }//第一阶段的产怪
        case 2:{
            n+=2;
            qDebug()<<"enemy_2 of "<<n;
            break;
        }//第二阶段的产怪
        case 3:{
            n+=5;
            qDebug()<<"enemy_3 of "<<n<<"and Boss";
            break;
        }//第三及之后的产怪
        }
        a_wave_of_enemies(n);
    });
}


void PlayWindow::backButton()
{
    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/back.png",QPoint(60,60));
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() - 5, 780);
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

void PlayWindow::keyPressEvent(QKeyEvent *event)
{
    //gameStart = true;
    if (event->key() == Qt::Key_W) {
        moving[1] = true;
    } else if (event->key() == Qt::Key_S) {
        moving[3] = true;
    } else if (event->key() == Qt::Key_A) {
        moving[0] = true;
    } else if (event->key() == Qt::Key_D) {
        moving[2] = true;
    } else if (event->key() == Qt::Key_P) {
        myplane->low_speed = true;
    }
}

void PlayWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        moving[1] = false;
    } else if (event->key() == Qt::Key_S) {
        moving[3] = false;
    } else if (event->key() == Qt::Key_A) {
        moving[0] = false;
    } else if (event->key() == Qt::Key_D) {
        moving[2] = false;
    } else if (event->key() == Qt::Key_P) {
        myplane->low_speed = false;
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

void PlayWindow::createEnemy(EnemyType type,const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y){
    if(type == enemy1){
        Enemy *new_enemy = new Enemy(p,l,s,pos,scale,x,y);
        enemies.append(new_enemy);
        scene->addItem(new_enemy);
    }
    //修改射击模式
    if(type == shootenemy1){
        ShootEnemy *new_enemy = new ShootEnemy(p,l,s,pos,scale,x,y);
        connect(new_enemy->timer, &QTimer::timeout,this,[=](){
            int num = new_enemy->attack(EMYBULLET_FIRST,0,1);
            int s = new_enemy->bullet_list.size()-1;
            for (int i = 0; i < num; ++i) {
                scene->addItem(new_enemy->bullet_list[s-i]);
            }
        });
        shootenemies.append(new_enemy);
        scene->addItem(new_enemy);
    }
    if(type==shootenemy2){

    }
    //添加精英怪
    if(type==shootenemy3){
        ShootEnemy *new_enemy = new ShootEnemy(p,l,s,pos,scale,x,y);
        connect(new_enemy->timer,&QTimer::timeout,this,[=](){
            int tp = rand()%4;
            if(tp==0||tp==1){
                int num = new_enemy->attack(EMYBULLET_FIRST,0,1);
                int s = new_enemy->bullet_list.size()-1;
                for (int i = 0; i < num; ++i) {
                    scene->addItem(new_enemy->bullet_list[s-i]);
                }
            } else if(tp==2){

            } else if(tp==3){
                double dx,dy;
                dx = myplane->hitPoint->x()-new_enemy->x()-20;
                dy = myplane->hitPoint->y()-new_enemy->y()-65;
                double len = sqrt(dx*dx+dy*dy);
                int num = new_enemy->attack(EMYBULLET_THIRD,dx/len,dy/len);
                int s = new_enemy->bullet_list.size()-1;
                for (int i = 0; i < num; ++i) {
                    scene->addItem(new_enemy->bullet_list[s-i]);
                }
            }
        });
        shootenemies.append(new_enemy);
        scene->addItem(new_enemy);
    }
}

void PlayWindow::a_wave_of_enemies(int n){
    switch(n){
    case 0:{
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(0,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(140,90),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(280,180),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(420,90),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(560,0),QSize(80,80),0,1);
        break;
    };
    case 1:{
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(0,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(140,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(280,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(420,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(560,90),QSize(80,80),0,1);
        break;
    };
    case 2:{
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(0,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(140,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(280,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(420,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(560,0),QSize(80,80),0,1);
        break;
    };
    case 3:{
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(0,270),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(140,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(210,160),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(280,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(350,160),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(420,90),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(560,180),QSize(80,80),0,1);
        break;
    };
    case 4:{
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(0,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(140,90),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(280,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(280,90),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(280,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(420,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(560,180),QSize(80,80),0,1);
        break;
    };
    case 5:{
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(0,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(100,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(100,270),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(200,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(300,270),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(400,360),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(500,0),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(500,270),QSize(80,80),0,1);
        createEnemy(enemy1,QPixmap(":/res/enemy_1.png"),life_enemy_1,1,QPointF(600,90),QSize(80,80),0,1);
        break;
    };
    case 6:{
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(0,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(140,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(280,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(420,270),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(180,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(320,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(460,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(600,270),QSize(80,80),0,1);
        break;
    };
    case 7:{
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(0,0),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(100,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(200,180),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(300,90),QSize(80,80),0,1);
        createEnemy(shootenemy1,QPixmap(":/res/shootenemy_1.png"),life_enemy_1,1,QPointF(400,0),QSize(80,80),0,1);
        break;
    };
    case 8:{
        //产生boss
        break;
    };
    default:break;
    }
}
