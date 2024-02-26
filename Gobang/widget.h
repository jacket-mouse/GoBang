#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QMainWindow>
#include <QDebug>
#include "game_control.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void hideMenu();        // 隐藏菜单界面，显示棋盘，默认为本地对战模式
    void hideMenuAi();      // 隐藏菜单界面，显示棋盘，为Ai对战模式
    void hideChessBoard();  // 隐藏棋盘界面

private:
    Game_control gamecontrol;  // 游戏控制对象
    Ui::Widget *ui;
    // 没有下面的对象，相当于这些类被隔离了，与主程序脱离了！！！


};
#endif // WIDGET_H
