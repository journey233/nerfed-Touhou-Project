#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <mypushbutton.h>
#include <QKeyEvent>
#include <QWheelEvent>
#include "myplane.h"
#include "enemy.h"

#define life_senemy_1 8
#define life_senemy_2 8
#define life_enemy_1 12
#define life_enemy_3 50
#define life_boss1 500
#define enemy_speed_norm 3
#define senemy_speed_norm 2
#define Senemy_speed 1
#define enemy_move_angle_x0 0.17
#define enemy_move_angle_x1 0.5
#define enemy_move_angle_x2 0.26
#define enemy_move_angle_y0 0.98
#define enemy_move_angle_y1 0.86
#define enemy_move_angle_y2 0.96

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
    void gameover(bool win);
    void pause();
    void boom(QPointF pos,QSize size);
    void bossHp();
    void createBoss();

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

    QWidget *gameoverWidget;
    QLabel *Text;
    MyPushButton * backBtn;

    QGraphicsPixmapItem *barItem;
    QPixmap barPixmap;

    QString BoomImgPath[11] = {
        ":/res/blast/blasts1.png",
        ":/res/blast/blasts2.png",
        ":/res/blast/blasts3.png",
        ":/res/blast/blasts4.png",
        ":/res/blast/blasts5.png",
        ":/res/blast/blasts6.png",
        ":/res/blast/blasts7.png",
        ":/res/blast/blasts8.png",
        ":/res/blast/blasts9.png",
        ":/res/blast/blasts10.png",
        ":/res/blast/blasts11.png",
    };

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
    QTimer *enemy_move;

    QGraphicsRectItem *bossblood;
    QGraphicsPixmapItem *barbg;

    int gameStop = 1;
    bool bosstime=0;
    void a_wave_of_enemies(int n);

signals:
    void Back();
};

#endif // PLAYWINDOW_H
