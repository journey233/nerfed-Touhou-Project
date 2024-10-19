#include "enemy.h"

Enemy::Enemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent)
    :base_plane_class(p, l, s, ENEMY, pos, scale, parent)
{
    move_timer= new QTimer();
    move_timer->start(1000/Fps);
    dir[0] = x; dir[1] = y;
    if(dir[1]){
        this->setTransformOriginPoint(40,40);
        this->setRotation(-(atan(dir[0]/dir[1])*(180.0/M_PI)));
    }
}

ShootEnemy::ShootEnemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent)
    :Enemy(p, l, s, pos, scale, x, y, parent)
{
    move_timer= new QTimer();
    move_timer->start(1000/Fps);
    dir[0]=x;dir[1]=y;
    if(dir[1]){
        this->setTransformOriginPoint(40,40);
        this->setRotation(-(atan(dir[0]/dir[1])*(180.0/M_PI)));
    }
    timer = new QTimer();
    timer->start(1500);
}

int ShootEnemy::attack(int type,double dx,double dy){
    if(type==EMYBULLET_FIRST){
    for (int i = 0; i < 6; ++i) {
            Bullet *b = new Bullet(type,-sin(qDegreesToRadians(45-18*i)),cos(qDegreesToRadians(45-18*i)));
        b->setPos(this->x() + this->pix.width() / 2 - b->size[0] / 2,this->y() + this->pix.height());
        bullet_list.append(b);
    }
    return 6;
    } else if(type==EMYBULLET_SECOND){

    } else if(type==EMYBULLET_THIRD){
        Bullet *b = new Bullet(type,dx,dy);
        b->setPos(this->x() + this->pix.width() / 2 - b->size[0] / 2,this->y() + this->pix.height());
        bullet_list.append(b);
        return 1;
    }
}
