#ifndef ENEMY_H
#define ENEMY_H

#include "base_plane_class.h"
#include <QTimer>
#include <cmath>
class Enemy : public base_plane_class
{
protected:
    double dir[2];
public:
    Enemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent = nullptr);
signals:
};

class ShootEnemy : public Enemy
{
protected:

public:
    QTimer *timer;

    ShootEnemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent = nullptr);

    int attack(int type,double dx, double dy);
signals:
};

#endif // ENEMY_H
