#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
#include "chessboard_ai.h"
#include "gameai.h"

namespace Ui {
class Game_control;
}

class Game_control : public QWidget
{
    Q_OBJECT

public:
    explicit Game_control(QWidget *parent = nullptr);
    ~Game_control();
    bool isHumenGame = true;            // 模式标志：人人对战
    bool isAiGame = false;              // 模式标志：人机对战
    Chessboard chessboard;              // 本地对战棋盘对象，在widget中调用所以在puclic下
    Chessboard_ai chessboardai;         // 人机对战棋盘对象
    GameAi gameai;                      // 人机对战Ai
signals:
    void ReturnToMenu();                // 返回主菜单信号
public slots:
    void GameIsOver(int winner);        // 游戏结束槽函数
    void GameReStart();                 // 游戏重开槽函数
    void UpdateInfo(int x, int y);      // 更新棋盘信息

private:
    Ui::Game_control *ui;
};

#endif // GAME_CONTROL_H
