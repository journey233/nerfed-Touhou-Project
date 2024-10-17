#ifndef MYPLANE_H
#define MYPLANE_H

#include "base_plane_class.h"
#include <QStack>

class Myplane : public base_plane_class
{
public:
    Myplane(const QPixmap &hitpoint,const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale,QGraphicsPixmapItem *parent = nullptr);
    int nondead_time = 5 * Fps;
    int time_after_death = 0;
    bool nondead = false;
    bool low_speed = false;
    void move(double dx, double dy);
    int attack(int type, double dxx, double dyy);
    void be_attacked();
    QGraphicsPixmapItem *hitPoint;//自机命中点

    QStack<QGraphicsPixmapItem*> hp;
    QStack<QGraphicsPixmapItem*> lost_hp;
    QPixmap bloodPixmap;
    QPixmap lostbloodPixmap;

signals:
};

#endif // MYPLANE_H
