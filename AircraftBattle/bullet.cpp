#include "bullet.h"



Bullet::Bullet(const int ty,const double dx,const double dy,QGraphicsPixmapItem *parent):QGraphicsPixmapItem{parent}{
    type = ty;
    bullet_speed = 15;
    state = 1;
    dir[0] = dx;
    dir[1] = dy;

    switch(type){
        //TODO 为子弹类型填写相应的图像，设置图像大小,填写size函数,同时更改速度
    case SLFBULLET:{
            camp = SELF;
            QPixmap p(":/res/selfbullet.png");
            p = p.scaled(QSize(30,30));
            size[0] = 30;
            size[1] = 30;
            this->setPixmap(p);
            break;
        }
    case EMYBULLET_FIRST:{
            camp = ENEMY;
            QPixmap p(":/res/enemy_bullet0.png");
            p = p.scaled(QSize(30,30));
            size[0]=30;
            size[1]=30;
            bullet_speed = 6;
            this->setPixmap(p);
            break;
        }
    case EMYBULLET_SECOND:{
            camp = ENEMY;
            QPixmap p(":/res/enemy_bullet_2.png");
            p = p.scaled(QSize(30,30));
            size[0]=30;
            size[1]=30;
            this->setPixmap(p);
            break;
        }
    case EMYBULLET_THIRD:{//精英子弹，加速
            camp = ENEMY;
            QPixmap p(":/res/enemy_bullet_3.png");
            p = p.scaled(QSize(10,60));
            size[0] = 10;
            size[1] = 60;
            this->setPixmap(p);
            bullet_speed = 5;
            a = 2;//加速度
            break;
        }
    case BOSSBULLET_FIRST:{
            camp = ENEMY;
            QPixmap p(":/res/boss_bullet0.png");
            p = p.scaled(QSize(20,80));
            size[0] = 20;
            size[1] = 80;
            this->setPixmap(p);
            bullet_speed = 10;
            a = 2;
            break;
        }
    case SLFBULLETLEVELUP:{
            camp = SELF;
            QPixmap p(":/res/selfbullet.png");
            p = p.scaled(QSize(30,30));
            size[0] = 30;
            size[1] = 30;
            this->setPixmap(p);
            bullet_speed = 20;
            break;
        }
    }
    this->setZValue(2);
    this->setShapeMode(QGraphicsPixmapItem::MaskShape);

};

void Bullet::move(const int screen_x,const int screen_y){
    if(state){//存活移动
        double nowX;
        double nowY;
        if(type==SLFBULLET||type==SLFBULLETLEVELUP){
            nowX = this->pos().x();
            nowY = this->pos().y()-bullet_speed;
            this->setPos(nowX,nowY);
        } else {
            if(type==EMYBULLET_THIRD||type==BOSSBULLET_FIRST){
                bullet_speed+=a;
            }
            nowX = this->pos().x() + dir[0]*bullet_speed;
            nowY = this->pos().y() + dir[1]*bullet_speed;
            this->setPos(nowX,nowY);
        }
        if(nowX<-size[0]||nowX>screen_x||nowY<-size[1]||nowY>screen_y){
            state = 0;//出界，删去子弹
        }
    }
};
