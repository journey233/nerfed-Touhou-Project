#ifndef BULLET_H
#define BULLET_H


#define ENEMY false
#define SELF true
#define SLFBULLET 1
#define SLFBULLETLEVELUP 9
#define EMYBULLET_FIRST 2
#define EMYBULLET_SECOND 3
#define EMYBULLET_THIRD 4
#define BOSSBULLET_FIRST 5
//TODO




#include <QGraphicsPixmapItem>

class Bullet : public QGraphicsPixmapItem
{
public:
    Bullet(const int ty,const double dx,const double dy,QGraphicsPixmapItem *parent = nullptr);
    int type;//子弹类型，据此写子弹pixmap及其大小，switch type：//TODO
    int bullet_speed;//弹速
    bool state;//子弹是否仍然存活
    double dir[2];
    bool camp;//子弹的阵营，敌0自1
    int size[2];
    double a = 0;//子弹加速度
    void move(const int screen_x,const int screen_y);

signals:
};

#endif // BULLET_H
