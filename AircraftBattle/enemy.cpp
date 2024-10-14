#include "enemy.h"

Enemy::Enemy(const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent)
    :base_plane_class(p, l, s, c, pos, scale, parent)
{
    dir[0] = x; dir[1] = y;
}
