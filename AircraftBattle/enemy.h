#ifndef ENEMY_H
#define ENEMY_H

#include "base_plane_class.h"
#include <QTimer>
#include <cmath>
class Enemy : public base_plane_class
{
protected:

public:
    double dir[2];
    QTimer *move_timer;
    int move_transfer=0;
    Enemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent = nullptr);
signals:
};

class ShootEnemy : public Enemy
{
protected:
public:
    bool attack_at_death = false;
    QTimer *timer;

    ShootEnemy(const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y, QGraphicsPixmapItem *parent = nullptr);

    int attack(int type,double dx, double dy);
signals:
};

#endif // ENEMY_H
