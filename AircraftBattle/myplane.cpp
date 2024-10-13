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

void Myplane::move(double dx, double dy){
    double x0 = this->x();
    double y0 = this->y();
    double nowX = x0 + this->speed() * dx;
    double nowY = y0 + this->speed() * dy;
    if(nowX>=630)nowX=630;
    if(nowX<=-30)nowX=-30;
    if(nowY>=815)nowY=815;
    if(nowY<=-25)nowY=-25;
    this->setPos(nowX, nowY);
    hitPoint->setPos(nowX+30,nowY+25);
};
