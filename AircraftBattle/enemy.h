#ifndef ENEMY_H
#define ENEMY_H

#include "base_plane_class.h"

class Enemy : public base_plane_class
{
private:
    double dir[2];
public:
    Enemy(const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent = nullptr);

signals:
};

#endif // ENEMY_H
