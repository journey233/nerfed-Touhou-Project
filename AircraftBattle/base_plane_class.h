#ifndef BASE_PLANE_CLASS_H
#define BASE_PLANE_CLASS_H

#include <QGraphicsPixmapItem>
#include <QList>
#include "bullet.h"

#define SELF true
#define ENEMY false

class base_plane_class : public QGraphicsPixmapItem
{
public:
    QList<Bullet*> bullet_list; // 每个机体发射的子弹的链表
private:
    int _life; // 血量
    int _speed; // 移动速度
    // 自机可能还需要添加是否处于无敌状态的变量
    bool _camp; // 机体的阵营 自机->SELF，敌机->ENEMY
    bool _state;//是否活着
public:
    base_plane_class(const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale, QGraphicsPixmapItem *parent = nullptr)
        :_life(l), _speed(s), _camp(c), _state(true)
    {
        QPixmap np = p.scaled(scale);
        this->setPixmap(np);
        this->setPos(pos);
        this->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }

    void move(double dx, double dy) // 机体向（dx, dy）方向移动一次
    {
        double x0 = this->x();
        double y0 = this->y();
        this->setPos(x0 + _speed * dx, y0 + _speed * dy);
    }
    void attack(int type, int dx, int dy) // 机体向（dx, dy）方向发射一颗子弹
    {
        Bullet *b= new Bullet(type, dx, dy);
        bullet_list.append(b);
    }
    void be_attacked() // 机体受击
    {
        if(this->_state==0){
            _state = false;
            return;
        }
        --(this->_life);
    }
    int life() const
    {
        return _life;
    }
    int speed() const
    {
        return _speed;
    }
    bool camp()
    {
        return _camp;
    }
    bool is_alive(){
        return _state;
    }

signals:
};

#endif // BASE_PLANE_CLASS_H
