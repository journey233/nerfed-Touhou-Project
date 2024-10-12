#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
public:
    MyPushButton();

    MyPushButton(QString normalImg,QPoint size = QPoint(0,0));

    //成员属性 保存图片路径
    QString normalImgPath;

    //弹跳特效
    void zoom_up();
    void zoom_down();
};

#endif // MYPUSHBUTTON_H
