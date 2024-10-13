#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


class PlayWindow :public QMainWindow
{
    Q_OBJECT
public:
    PlayWindow(QMainWindow *parent = nullptr);

    void initScene();
    void updateBackground();
    void backButton();

    QTimer *timer;
    int scene_width = 740;//窗口宽度
    int scene_height = 860;//窗口高度
    int Fps = 60 ;//帧率

    QGraphicsScene *scene;
    QGraphicsPixmapItem *backgroundItem;
    int backgroundheight;
    QPixmap backgroundPixmap;
    int offset = 0;

signals:
    void Back();
};

#endif // PLAYWINDOW_H
