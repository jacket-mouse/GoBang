#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
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
    Chessboard chessboard;              // 棋盘对象，在widget中调用所以在puclic下
    GameAi gameai;                      // 人机对战Ai

public slots:
    void GameIsOver(int winner);        // 游戏结束槽函数
    void GameReStart();                 // 游戏重开槽函数
    void UpdateInfo();                  // Ai下棋

private:
    Ui::Game_control *ui;
};

#endif // GAME_CONTROL_H
