#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QWheelEvent>
#include "myplane.h"
#include "enemy.h"

class PlayWindow :public QMainWindow
{
    Q_OBJECT
public:
    PlayWindow(QMainWindow *parent = nullptr);

    void initScene();
    void updateBackground();
    void backButton();

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
    bool upgrade = true;//自机升级

    bool moving[4] = {0}; // 0左1上2右3下
    int di[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

signals:
    void Back();
};

#endif // PLAYWINDOW_H
