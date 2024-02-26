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
    void hideMenu();        // 隐藏菜单界面，显示本地对战棋盘
    void hideMenuAi();      // 隐藏菜单界面，显示人机对战棋盘
    void hideChessBoard();  // 隐藏本地对战棋盘界面
    void hideChessBoardAi();// 隐藏人机对战棋盘界面

private:
    Ui::Widget *ui;
    // 没有下面的对象，相当于这些类被隔离了，与主程序脱离了！！！
    Game_control gamecontrol;  // 游戏控制对象

private slots:
    void on_Local_btn_clicked();   // 人机对战槽函数
    void on_Ai_btn_clicked();   // 人机对战槽函数
};
#endif // WIDGET_H
