#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QWheelEvent>
#include "myplane.h"
#include "enemy.h"

#define life_enemy_1 12

enum EnemyType{
    enemy1,
    enemy2,
    shootenemy1,
    shootenemy2,
    shootenemy3,
    boss1,
    boss2
};

class PlayWindow :public QMainWindow
{
    Q_OBJECT
public:
    PlayWindow(QMainWindow *parent = nullptr);

    void initScene();
    void updateBackground();
    void backButton();

    void createEnemy(EnemyType type,const QPixmap &p, int l, int s, QPointF pos, QSize scale, double x, double y);


    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QTimer *timer;
    int scene_width = 740;//窗口宽度
    int scene_height = 860;//窗口高度

    QGraphicsScene *scene;
    QGraphicsPixmapItem *backgroundItem;
    int backgroundheight;
    QPixmap backgroundPixmap;
    int offset = 0;


    QGraphicsPixmapItem *barItem;
    QPixmap barPixmap;


    Myplane *myplane = nullptr;
    int selfattacktimer = 0;
    bool upgrade = false;//自机升级

    Enemy * bullet_supporter;
    QList<Enemy*> enemies;
    QList<ShootEnemy*> shootenemies;

    bool moving[4] = {0}; // 0左1上2右3下
    int di[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
    int enemy_phase=1;
    int enemy_clock=0;
    QTimer *enemy_generate;

    void a_wave_of_enemies(int n);

signals:
    void Back();
};

#endif // PLAYWINDOW_H
