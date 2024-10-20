/**
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             永无BUG
 */
#ifndef BASE_PLANE_CLASS_H
#define BASE_PLANE_CLASS_H

#include <QGraphicsPixmapItem>
#include <QList>
#include "bullet.h"

#define SELF true
#define ENEMY false
#define Fps 60 // 帧率
#define screenWid  680
#define screenHei  860

class base_plane_class : public QGraphicsPixmapItem
{
public:
    QList<Bullet*> bullet_list; // 每个机体发射的子弹的链表，需要从playwindow获取
protected:
    int _life; // 血量
    double _speed; // 移动速度
    // 自机可能还需要添加是否处于无敌状态的变量
    bool _camp; // 机体的阵营 自机->SELF，敌机->ENEMY
    bool _state; // 是否活着
    QPixmap pix; // 贴图
public:
    base_plane_class(const QPixmap &p, int l, int s, bool c, QPointF pos, QSize scale, QGraphicsPixmapItem *parent = nullptr)
        :_life(l), _speed(s), _camp(c), _state(true)
    {
        pix = p.scaled(scale);
        this->setPixmap(pix);
        this->setPos(pos);
        this->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }

    virtual void move(double dx, double dy) // 机体向（dx, dy）方向移动一次
    {
        if(_state)
        {
            double x0 = this->x();
            double y0 = this->y();
            double nowX = x0 + this->speed() * dx;
            double nowY = y0 + this->speed() * dy;
            if(nowX <= -pix.width() || nowX >= 760 || nowY >= 860)
            {
                _state = false;
            }
            this->setPos(nowX, nowY);
        }
    }
    virtual int attack(int type, double dx, double dy) // 机体向（dx, dy）方向发射一颗子弹
    {
        Bullet *b= new Bullet(type, dx, dy);
        b->setPos(this->x() + this->pix.width() / 2 - b->size[0] / 2,this->y() + this->pix.height());
        bullet_list.append(b);
        return 1;
    }
    void bullet_move(){ // 子弹移动
        int len = bullet_list.size();
        for (int i = 0; i < len; ++i) {
            bullet_list[i]->move(680,860);
        }
    }
    void bullet_dead(){ // 子弹删除
        for(auto it = bullet_list.begin();it != bullet_list.end();){
            if(!(*it)->state){
                for(int i=0;i<3;i++){
                    if((*it)->orb[i]){
                        delete (*it)->orb[i];
                    }
                }
                delete (*it);
                it = bullet_list.erase(it);
            } else {
                for(int i=0;i<3;i++){
                    if((*it)->orb[i]){
                        if(!(*it)->orb[i]->state){
                            delete (*it)->orb[i];
                            (*it)->orb[i] = nullptr;
                        }
                    }
                }
                it++;
            }
        }
    }
    virtual void be_attacked() // 机体受击
    {
        if(this->_life == 1){
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
    void setSpeed(int s)
    {
        _speed = s;
    }

signals:
};

#endif // BASE_PLANE_CLASS_H
