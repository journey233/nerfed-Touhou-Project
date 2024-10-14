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
