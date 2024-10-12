#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>

class PlayWindow :public QMainWindow
{
public:
    PlayWindow(QMainWindow *parent = nullptr);
signals:
    void Back();
};

#endif // PLAYWINDOW_H
