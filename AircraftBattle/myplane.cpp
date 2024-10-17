#include "myplane.h"

Myplane::Myplane(const QPixmap &hitpoint,const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale,QGraphicsPixmapItem *parent):base_plane_class(p,l,s,c,pos,scale,parent){
    scale/=4;
    QPixmap nh = hitpoint.scaled(scale);
    hitPoint = new QGraphicsPixmapItem();
    hitPoint->setZValue(2);
    hitPoint->setPixmap(nh);
    hitPoint->setPos(pos.x()+30,pos.y()+25);
    hitPoint->setShapeMode(QGraphicsPixmapItem::MaskShape);

    bloodPixmap = QPixmap(":/res/hp.png").scaled(40, 40, Qt::KeepAspectRatio);
    lostbloodPixmap = QPixmap("");
    for(int i=0;i<l;i++){
        QGraphicsPixmapItem* blood = new QGraphicsPixmapItem();
        blood->setPixmap(bloodPixmap);
        blood->setPos(690,100+80*i);
        blood->setZValue(4);
        hp.push_back(blood);
    }
};

void Myplane::move(double dx, double dy){
    double x0 = this->x();
    double y0 = this->y();
    double nowX = x0 + this->speed() * dx;
    double nowY = y0 + this->speed() * dy;
    if(nowX>=630) nowX=630;
    if(nowX<=-30) nowX=-30;
    if(nowY>=815) nowY=815;
    if(nowY<=-25) nowY=-25;
    this->setPos(nowX, nowY);
    hitPoint->setPos(nowX+30,nowY+25);
};

int Myplane::attack(int type, double dxx, double dyy) // 机体向（dx, dy）方向发射一颗子弹
{
    double dx = 0;
    double dy = -1;
    if(type==SLFBULLET){
        Bullet *b= new Bullet(type, dx, dy);
        b->setPos(this->x()+25,this->y()-30);
        bullet_list.append(b);
        return 1;
    } else if(type==SLFBULLETLEVELUP){
        int op = 0;
        Bullet *b = new Bullet(type, dx, dy);
        double thisX = this->x();
        double thisY = this->y();
        if(thisX-10>-30){
            Bullet *a = new Bullet(type, dx, dy);
            a->setPos(thisX-10,thisY-30);
            bullet_list.append(a);
            op++;
        }
        b->setPos(thisX+25,thisY-40);
        bullet_list.append(b);
        op++;
        if(thisX+60<680){
            Bullet *c = new Bullet(type, dx, dy);
            c->setPos(thisX+60,thisY-30);
            bullet_list.append(c);
            op++;
        }
        return op;
    }
}

void Myplane::be_attacked()
{
    if(!nondead)
    {
        if(this->_life == 0){
            // 结束游戏
        }
        else{
            --(this->_life);
            hp.top()->setPixmap(lostbloodPixmap);
            lost_hp.push_back(hp.top());
            hp.pop_back();
            nondead = true;
        }
    }
}
