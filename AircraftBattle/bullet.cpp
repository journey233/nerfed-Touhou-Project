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
            bullet_speed = 3;
            this->setPixmap(p);
            break;
        }
    case EMYBULLET_SECOND:{
            camp = ENEMY;
            bullet_speed = 5;
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
            p = p.scaled(QSize(20,150));
            size[0] = 20;
            size[1] = 150;
            this->setPixmap(p);
            if(dy){
                // this->setTransformOriginPoint(10,75);
                this->setRotation(-(atan(dx/dy)*(180.0/M_PI)));
            }
            bullet_speed = 0;
            a = 0.25;//加速度
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
            a = 0.5;
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
    case BOSSBULLET_SECOND:{
        camp = ENEMY;
        QPixmap p(":/res/enemy_bullet0.png");
        p = p.scaled(QSize(50,50));
        size[0] = 50;
        size[1] = 50;
        bullet_speed = 2;
        a = 0.05;
        this->setPixmap(p);
        for(int i=0;i<3;i++){
            Bullet* b = new Bullet(BOSSBULLET_SECOND_ORB,0,0);
            orb[i] = b;
        }
        angle = 0;
        break;
    }
    case BOSSBULLET_SECOND_ORB:{
        camp = ENEMY;
        QPixmap p(":/res/enemy_bullet_2.png");
        p = p.scaled(QSize(30,30));
        size[0]=30;
        size[1]=30;
        this->setPixmap(p);
        break;
    }
    case EMYBULLET_ATDEATH:{
            camp = ENEMY;
            QPixmap p(":/res/death_bullet.png");
            p = p.scaled(QSize(30,30));
            size[0]=30;
            size[1]=30;
            bullet_speed = 5;
            this->setPixmap(p);
            break;
        }
    }
    this->setZValue(2);
    this->setShapeMode(QGraphicsPixmapItem::MaskShape);

};

Bullet::Bullet(const Bullet &bul, QGraphicsPixmapItem *parent)
{
    this->type = bul.type;
    this->bullet_speed = bul.bullet_speed;
    this->state = 1;
    this->dir[0] = bul.dir[0];
    this->dir[1] = bul.dir[1];
    this->a = bul.a;

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
        p = p.scaled(QSize(20,150));
        size[0] = 20;
        size[1] = 150;
        this->setPixmap(p);
        if(dir[1]){
            this->setRotation(-atan(dir[0]/dir[1])*(180.0/M_PI));
        }
        a = 0.3;//加速度
        break;
    }
    case BOSSBULLET_FIRST:{
        camp = ENEMY;
        QPixmap p(":/res/boss_bullet0.png");
        p = p.scaled(QSize(20,80));
        size[0] = 20;
        size[1] = 80;
        this->setPixmap(p);
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
        break;
    }
    case BOSSBULLET_SECOND:{
        camp = ENEMY;
        QPixmap p(":/res/enemy_bullet0.png");
        p = p.scaled(QSize(50,50));
        size[0] = 50;
        size[1] = 50;
        this->setPixmap(p);
        bullet_speed = bul.bullet_speed;
        for(int i=0;i<3;i++){
            orb[i] = new Bullet(*bul.orb[i]);
        }
        angle = bul.angle;
        break;
    }
    case BOSSBULLET_SECOND_ORB:{
        camp = ENEMY;
        QPixmap p(":/res/enemy_bullet_2.png");
        p = p.scaled(QSize(30,30));
        size[0]=30;
        size[1]=30;
        this->setPixmap(p);
        break;
    }
    }
    this->setZValue(2);
    this->setShapeMode(QGraphicsPixmapItem::MaskShape);
}

void Bullet::move(const int screen_x,const int screen_y){
    if(state){//存活移动
        double nowX;
        double nowY;
        if(type==SLFBULLET||type==SLFBULLETLEVELUP){
            nowX = this->pos().x();
            nowY = this->pos().y()-bullet_speed;
            this->setPos(nowX,nowY);
        }
        else if(type==BOSSBULLET_SECOND){
            nowX = this->pos().x();
            nowY = this->pos().y()+bullet_speed;
            this->setPos(nowX,nowY);
            double centerX = this->pos().x()+this->size[0]/2;
            double centerY = this->pos().y()+this->size[1]/2;
            angle += a;
            a += 0.01;
            for(int i = 0;i<3;i++){
                if(orb[i]){
                    nowX = centerX + (30*cos(qDegreesToRadians(angle))+70)*sin(qDegreesToRadians(angle+120*i)) - orb[i]->size[0]/2;
                    nowY = centerY + (30*cos(qDegreesToRadians(angle))+70)*cos(qDegreesToRadians(angle+120*i)) - orb[i]->size[1]/2;
                    orb[i]->setPos(nowX,nowY);
                }
            }
        }
        else {
            if(type==EMYBULLET_THIRD||type==BOSSBULLET_FIRST){
                bullet_speed+=a;
            }
            nowX = this->pos().x() + dir[0]*bullet_speed;
            nowY = this->pos().y() + dir[1]*bullet_speed;
            this->setPos(nowX,nowY);
        }
        if(this->type == BOSSBULLET_SECOND){
            if(nowX<-size[0]-100||nowX>screen_x+100||nowY<-size[1]-100||nowY>screen_y+100){
                state = 0;//出界，删去子弹
            }
        }
        else if(nowX<-size[0]||nowX>screen_x||nowY<-size[1]||nowY>screen_y){
        if(bounce_times&&(nowX<0||nowX>screen_x-size[0])&&type==EMYBULLET_SECOND){
                bounce_times--;
                dir[0]*=-1;
        }
        if(nowY<-size[1]||nowY>screen_y||nowX<-size[0]||nowX>screen_x){
            state = 0;//出界，删去子弹
        }
    }
};
