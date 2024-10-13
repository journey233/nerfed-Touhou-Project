#ifndef MYPLANE_H
#define MYPLANE_H

#include "base_plane_class.h"

class Myplane : public base_plane_class
{
public:
    Myplane(const QPixmap &hitpoint,const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale,QGraphicsPixmapItem *parent = nullptr);
    QGraphicsPixmapItem *hitPoint;//自机命中点
signals:
};

#endif // MYPLANE_H
