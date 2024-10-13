#include "myplane.h"

Myplane::Myplane(const QPixmap &hitpoint,const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale,QGraphicsPixmapItem *parent):base_plane_class(p,l,s,c,pos,scale,parent){
    scale/=4;
    QPixmap nh = hitpoint.scaled(scale);
    hitPoint = new QGraphicsPixmapItem();
    hitPoint->setZValue(2);
    hitPoint->setPixmap(nh);
    hitPoint->setPos(pos.x()+30,pos.y()+25);
    hitPoint->setShapeMode(QGraphicsPixmapItem::MaskShape);
};

