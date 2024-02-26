#ifndef GAMEAI_H
#define GAMEAI_H
#define AN 10
#define DEPTH 4 // 迭代深度
#include "command.h"
#include <QPoint>
#include <QDebug>
#include <iostream>
#include <random>
#include <cstdint>
struct Pos {
    int x;
    int y;
};


struct Points {
    Pos pos[AN];
    int score[AN];
};

class GameAi
{
public:
    GameAi();
    ~GameAi();
    int evaluate(int board[BOARD_ROW][BOARD_COL]);                        // 进行评估整个棋局的得分
    void chessStatus_init();                                              // 评估函数初始化
    Points localSearch(int board[BOARD_ROW][BOARD_COL]);                  // 局部搜索
    void reverseBoard(int board[BOARD_ROW][BOARD_COL], int rboard[BOARD_ROW][BOARD_COL]);       // 反转棋盘
    // QVector<QPoint> GetAllDropPiecePos();       // 返回棋盘上所有NO_PIECE位置
    // int GetPieceScore(int x,int y,int player);  // 返回该位置相对于player的分数
    // int GetPosValue(int x,int y);               // 返回该位置的分数，越靠近中间分数越高
    // int GetChessType(int x,int y,int direction,int pieceColor);     // 返回该位置direction方向上的棋形
    // int GetLinePieceNum(int x,int y,int direction,int pieceColor,int &pieceEnd);    //获取该位置该方向上pieceColor颜色的连续棋子数，pieceEnd为结束位置棋子
    // bool IsBeyond(int x,int y);
    int MaxMinSearch(int board[BOARD_ROW][BOARD_COL], int deep, int alpha, int beta);  // 极大极小值搜索

public:
    int chessStatus[4][4][4][4][4][4] = {{{{{{0}}}}}};
    Pos bestPos;
    uint64_t zobrist_black[BOARD_ROW][BOARD_COL];
    uint64_t zobrist_white[BOARD_ROW][BOARD_COL];
};

// 定义 Zobrist 类
class Zobrist {
private:
    std::mt19937_64 engine; // 64位随机数引擎

public:
    // 构造函数
    Zobrist() : engine(std::random_device()()) {} // 使用随机设备作为种子初始化随机数引擎

    // 生成随机数
    uint64_t getRandom() {
        std::uniform_int_distribution<uint64_t> dist(0, std::numeric_limits<uint64_t>::max());
        return dist(engine);
    }
};

#endif // GAMEAI_H
