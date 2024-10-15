#include "enemy.h"

Enemy::Enemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent)
    :base_plane_class(p, l, s, ENEMY, pos, scale, parent)
{
    dir[0] = x; dir[1] = y;
}

ShootEnemy::ShootEnemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent)
    :Enemy(p, l, s, pos, scale, x, y, parent)
{
    timer = new QTimer();
    timer->start(750);
}

int ShootEnemy::attack(int type,double dx,double dy){
    if(type==EMYBULLET_FIRST){
    for (int i = 0; i < 11; ++i) {
            Bullet *b = new Bullet(type,-sin(qDegreesToRadians(45-9*i)),cos(qDegreesToRadians(45-9*i)));
        b->setPos(this->x() + this->pix.width() / 2 - b->size[0] / 2,this->y() + this->pix.height());
        bullet_list.append(b);
    }
    return 11;
    }
}
