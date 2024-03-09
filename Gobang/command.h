#ifndef COMMAND_H
#define COMMAND_H


// 棋盘数据
#define BOARD_COL  19        // 棋盘列数
#define BOARD_ROW  19        // 棋盘行数
#define NO_PIECE  0          // 棋子标志：无子
#define WHITE_PIECE  1       // 棋子标志：白子
#define BLACK_PIECE  2       // 棋子标志：黑子
#define BORDER 3             // 边界标志
#define BLACK_PLAYER  0      // 棋手标志：黑方
#define WHITE_PLAYER  1      // 棋手标志：白方
#define DRAW 2               // 和棋标志
#define HUMUN_MODE 1         // 悔棋步数：人类 1 步
#define AI_MODE 2            // 悔棋步数：AI 2 步

// 评估函数
// 大写代表黑子、小写代表白子
#define OTHER 0//0
#define WIN 1//1000000
#define LOSE 2//-10000000
#define FLEX4 3//-1000000
#define flex4 4//50000
#define BLOCK4 5//-100000
#define block4 6//400
#define FLEX3 7//-8000
#define flex3 8//400
#define BLOCK3 9//-50
#define block3 10//20
#define FLEX2 11//-50
#define flex2 12//20
#define BLOCK2 13//-3
#define block2 14//1
#define FLEX1 15//-3
#define flex1 16//1

#endif // COMMAND_H
