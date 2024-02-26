#ifndef CHESSBOARD_AI_H
#define CHESSBOARD_AI_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QStack>
#include "command.h"
#include <QPropertyAnimation>
namespace Ui {
class Chessboard_ai;
}
class Chessboard_ai : public QWidget
{
    Q_OBJECT

public:
    explicit Chessboard_ai(QWidget *parent = nullptr);
    ~Chessboard_ai();
    int board[BOARD_COL][BOARD_ROW];            // 棋盘中棋子的位置信息
    static const QSize BOARD_SIZE;              // 棋盘大小
    static const QSize PIECE_SIZE;              // 棋子大小
    bool isGameOver;                            // 游戏的结束标志

    void sendSignal();                          // 发送返回菜单界面信号
    void paintEvent(QPaintEvent *event);        // 重写绘图事件
    void SetMousePos(const QPoint &pos);        // 更新当前鼠标位置
    static const QPoint START_POS;              // 棋盘中单元格起始位置
    void mouseMoveEvent(QMouseEvent *event);    // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标点击事件
    void SwitchNextPlayer();                    // 切换棋手
    void CheckWinner();                         // 判断赢家
    void ReStartNewGame();                      // 再来一局

    QStack<QPoint> dropedPieces;                // 保存落子的顺序信息
    QPoint mousePos;                            // 保存鼠标当前位置
    int nextPlayer;                             // 标志下一位棋手
    QVector<QPoint> winPiecePos;                // 保存获胜方五个棋子的位置
    QSet<int> boardReceivePlayer;               // 保存棋盘可接受的下棋方



signals:
    void Signal();                              // 返回菜单界面的信号
    void TurnToNextPlayer(int player);          // 切换棋手的信号
    void GameOver(int winner);                  // 游戏结束的信号
    void ReStart();                             // 重开游戏的信号
    void setpiece(int x, int y);                // 发出落子信号，向Ai更新棋盘信息
    void WhiteScore();                          // 白方得分的信号
    void BlackScore();                          // 黑方得分的信号

public slots:
    void StartNewGame();                        // 清除棋盘信息，开始新游戏
    void SetPiece(int x,int y);                 // 落子
    void SendReStart();                         // 向控制类发送重开游戏信号
    void SendUnDo();                            // 悔棋

private:

    bool IsFivePiece(int x,int y);              // 判断是否五子连珠
    bool IsVerFivePiece(int x,int y);           // 判断垂直方向五子连珠
    bool IsHorFivePiece(int x,int y);           // 判断水平方向五子连珠
    bool IsNorthWestFivePiece(int x,int y);     // 判断45°方向上五子连珠
    bool IsNorthEastFivePiece(int x,int y);     // 判断135°方向上五子连珠
    int black_score;                            // 黑棋得分
    int white_score;                            // 白棋得分
    Ui::Chessboard_ai *ui;
    // Control *control;
};

#endif // CHESSBOARD_AI_H
