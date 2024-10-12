#include "mypushbutton.h"
#include <QDebug>
#include <QEvent>
#include <QPropertyAnimation>
#include <QMouseEvent>

MyPushButton::MyPushButton(QString normalImg,QPoint size)
{
    this->normalImgPath = normalImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }


    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    if(size == QPoint(0,0)){
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    else {
        //设置图片固定大小
        this->setFixedSize(size.x(),size.y());
        this->setIconSize(QSize(size.x(),size.y()));
    }
}

void MyPushButton::zoom_down()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //时间间隔
    animation->setDuration(100);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()+3,this->y()+3,this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutCurve);

    //执行动画
    animation->start();

}

void MyPushButton::zoom_up()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //时间间隔
    animation->setDuration(100);

    //起始位置
    animation->setStartValue(QRect(this->x()+3,this->y()+3,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutCurve);

    //执行动画
    animation->start();
}
