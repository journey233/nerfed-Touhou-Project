#ifndef BULLET_H
#define BULLET_H


#define ENEMY false
#define SELF true
#define SLFBULLET 0
#define SLFBULLETLEVELUP 9
#define EMYBULLET_FIRST 1
#define EMYBULLET_SECOND 2
#define EMYBULLET_THIRD 3
#define EMYBULLET_FORTH 4
//TODO




#include <QGraphicsPixmapItem>

class Bullet : public QGraphicsPixmapItem
{
public:
    explicit Bullet(const int ty,const double dx,const double dy,QGraphicsPixmapItem *parent = nullptr);
    int type;//子弹类型，据此写子弹pixmap及其大小，switch type：//TODO
    int bullet_speed;//弹速
    bool state;//子弹是否仍然存活
    double dir[2];
    bool camp;//子弹的阵营，敌0自1
    int size[2];
    void move(const int screen_x,const int screen_y);

signals:
};

#endif // BULLET_H
