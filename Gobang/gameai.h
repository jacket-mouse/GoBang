#ifndef GAMEAI_H
#define GAMEAI_H
#define AN 10
#define DEPTH 4 // 迭代深度
#include "command.h"
#include <QPoint>
#include <QDebug>
#include "zobrist.h"
struct Pos {
    int x;
    int y;
};

struct Points {
    Pos pos[AN];
    int score[AN];
};
enum gameResult{R_BLACK,R_WHITE,R_DRAW};//黑棋赢，白棋赢，和棋
struct EVALUATION{
    int score;
    gameResult result;
    int STAT[8];//储存部分棋形的个数,下标WIN=1为黑连5,LOSE=2为白连5,FLEX4=3为黑活4,BLOCK4=5为黑冲4,FLEX3=7为黑活3
};

class GameAi
{
public:
    GameAi();
    ~GameAi();
    Points seekPoints(int board[BOARD_ROW][BOARD_COL],int flag,int depth);
    void copyBoard(int board[BOARD_ROW][BOARD_COL], int sameboard[BOARD_ROW][BOARD_COL]);       // 复制棋盘
    EVALUATION evaluate(int board[BOARD_ROW][BOARD_COL]);                                       // 进行评估整个棋局的得分
    void chessStatus_init();                                                                    // 评估函数初始化
    Points localSearch(int board[BOARD_ROW][BOARD_COL]);                                        // 局部搜索
    void reverseBoard(int board[BOARD_ROW][BOARD_COL], int rboard[BOARD_ROW][BOARD_COL]);       // 反转棋盘
    int MaxMinSearch(int board[BOARD_ROW][BOARD_COL], int deep, int alpha, int beta);           // 极大极小值搜索

public:
    int chessStatus[4][4][4][4][4][4] = {{{{{{0}}}}}};
    Pos bestPos;
    zobrist zobb=zobrist((unsigned long long)100000);

};

#endif // GAMEAI_H
