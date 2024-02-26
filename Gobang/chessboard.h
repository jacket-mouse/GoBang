#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QStack>
#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QMessageBox>
#include "command.h"
#include <QPropertyAnimation>

namespace Ui {
class Chessboard;
}

class Chessboard : public QWidget
{
    Q_OBJECT

public:

    explicit Chessboard(QWidget *parent = nullptr);
    ~Chessboard();
    void sendReturnSignal();                          // 发送返回菜单界面信号
    void paintEvent(QPaintEvent *event);        // 重写绘图事件
    void SetMousePos(const QPoint &pos);        // 更新当前鼠标位置
    void mouseMoveEvent(QMouseEvent *event);    // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标点击事件
    void ReStartNewGame();                      // 再来一局
    void SwitchNextPlayer();                    // 切换棋手
    void CheckWinner();                         // 判断赢家
    void ShowChoice();                          // 人机对战选择先后手

    static const QPoint START_POS;              // 棋盘中单元格起始位置
    int board[BOARD_COL][BOARD_ROW];            // 棋盘中棋子的位置信息
    static const QSize BOARD_SIZE;              // 棋盘大小
    static const QSize PIECE_SIZE;              // 棋子大小
    QPoint mousePos;                            // 保存鼠标当前位置
    bool isGameOver;                            // 游戏的结束标志
    int nextPlayer;                             // 标志下一位棋手
    QVector<QPoint> winPiecePos;                // 保存获胜方五个棋子的位置
    QSet<int> boardReceivePlayer;               // 保存棋盘可接受的下棋方
    QStack<QPoint> dropedPieces;                // 保存落子的顺序信息
    int black_score;                            // 黑棋得分
    int white_score;                            // 白棋得分
    bool aiModel;                               // ai模式标志
    bool isHumFir;                              // ai模式下，人是否先手标志
    Ui::Chessboard *ui;
    //Ui::Chessboard *ui;                         // game_control通过ui获取按钮等(该方案有问题，也可以将按下按钮绑定一个发射信号，就像widget中的按钮一样，而把ui放入private

signals:
    void ReturnToMenu();                        // 返回菜单界面的信号
    void TurnToNextPlayer(int player);          // 切换棋手的信号
    void GameOver(int winner);                  // 游戏结束的信号
    void ReStart();                             // 重开游戏的信号
    void WhiteScore();                          // 白方得分的信号
    void BlackScore();                          // 黑方得分的信号
    // Ai棋盘特有
    void setpiece();                            // 发出落子信号，提醒Ai下棋
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
};

#endif // CHESSBOARD_H
