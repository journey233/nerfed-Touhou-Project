#include "playwindow.h"
#include <QApplication>
#include <QScreen>
PlayWindow::PlayWindow(QMainWindow *parent) : QMainWindow(parent) {
    //游戏界面大小
    this->setFixedSize(740,860);

    //移动到屏幕中央
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2-40;
    this->move(x, y);

}
