#include "game_control.h"
#include "ui_game_control.h"

Game_control::Game_control(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game_control)
{
    ui->setupUi(this);
    // 初始化信号与槽
    // 本地对战
    connect(&chessboard, SIGNAL(GameOver(int)), this, SLOT(GameIsOver(int)));  // 游戏结束
    //connect(&chessboard.ui->re_btn, &QPushButton::clicked, this, &Game_control::GameReStart);  //Invalid use of incomplete type 'class Ui::Chessboard (QT error)
    connect(&chessboard, &Chessboard::ReStart, this, &Game_control::GameReStart);  // 再来一局，重新开始
    // Ai对战
    connect(&chessboardai, SIGNAL(GameOver(int)), this, SLOT(GameIsOver(int)));  // 游戏结束
    connect(&chessboardai, &Chessboard_ai::ReStart, this, &Game_control::GameReStart);  // 再来一局，重新开始
    connect(&chessboardai, SIGNAL(setpiece(int, int)), this, SLOT(UpdateInfo(int, int)));
}

void Game_control::GameIsOver(int winner){
    if(winner != DRAW)  // 若接收到非和棋信号
    {
        QString playerName = (winner == BLACK_PLAYER) ? "黑方" : "白方";
        //QMessageBox::information(this, "游戏结束", tr("恭喜%1获胜！！").arg(playerName), QMessageBox::Ok);
        QMessageBox msgBox;
        QFont font("SimSun", 16); // 选择宋体作为古风字体
        font.setBold(true);
        msgBox.setFont(font);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("游戏结束");

        msgBox.setInformativeText(tr("恭喜%1获胜！！").arg(playerName));
        msgBox.addButton(QMessageBox::Ok);


        // 设置样式表
        QString styleSheet = "QMessageBox {"
                             "background-color: #f0f0f0;"
                             "color: #333333;"
                             "border-radius: 10px;"
                             "}"
                             "QMessageBox QPushButton {"
                             "background-color: #4CAF50;"
                             "border: none;"
                             "color: white;"
                             "padding: 10px 20px;"
                             "text-align: center;"
                             "text-decoration: none;"
                             "display: inline-block;"
                             "font-size: 16px;"
                             "margin: 4px 2px;"
                             "cursor: pointer;"
                             "border-radius: 5px;"
                             "}"
                             "QMessageBox QPushButton:hover {"
                             "background-color: #45a049;"
                             "}"
                             "QMessageBox QPushButton:pressed {"
                             "background-color: #398438;"
                             "}"
                             "QMessageBox QLabel {"
                             "padding: 10px;"
                             "}"
                             "QMessageBox QPushButton:focus {"
                             "outline: none;"
                             "}"
                             "QMessageBox {"
                             "background-color: #f0f0f0;"
                             "color: #333333;"
                             "font-size: 14px;"
                             "}"
                             "QMessageBox QPushButton {"
                             "background-color: #4CAF50;"
                             "border: none;"
                             "color: white;"
                             "padding: 10px 20px;"
                             "text-align: center;"
                             "text-decoration: none;"
                             "display: inline-block;"
                             "font-size: 16px;"
                             "margin: 4px 2px;"
                             "cursor: pointer;"
                             "border-radius: 5px;"
                             "}"
                             "QMessageBox QPushButton:hover {"
                             "background-color: #45a049;"
                             "}";
        msgBox.setWindowFlags(Qt::FramelessWindowHint);
        msgBox.setStyleSheet(styleSheet);
        msgBox.exec();
        //emit(ReturnToMenu());
    }
    else
    {
        QMessageBox msgBox;
        QFont font("SimSun", 16); // 选择宋体作为古风字体
        font.setBold(true);
        msgBox.setFont(font);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("游戏结束");
        msgBox.setInformativeText("和棋");
        msgBox.addButton(QMessageBox::Ok);

        // 设置样式表
        QString styleSheet = "QMessageBox {"
                             "background-color: #f0f0f0;"
                             "color: #333333;"
                             "border-radius: 10px;"
                             "}"
                             "QMessageBox QPushButton {"
                             "background-color: #4CAF50;"
                             "border: none;"
                             "color: white;"
                             "padding: 10px 20px;"
                             "text-align: center;"
                             "text-decoration: none;"
                             "display: inline-block;"
                             "font-size: 16px;"
                             "margin: 4px 2px;"
                             "cursor: pointer;"
                             "border-radius: 5px;"
                             "}"
                             "QMessageBox QPushButton:hover {"
                             "background-color: #45a049;"
                             "}"
                             "QMessageBox QPushButton:pressed {"
                             "background-color: #398438;"
                             "}"
                             "QMessageBox QLabel {"
                             "padding: 10px;"
                             "}"
                             "QMessageBox QPushButton:focus {"
                             "outline: none;"
                             "}"
                             "QMessageBox {"
                             "background-color: #f0f0f0;"
                             "color: #333333;"
                             "font-size: 14px;"
                             "}"
                             "QMessageBox QPushButton {"
                             "background-color: #4CAF50;"
                             "border: none;"
                             "color: white;"
                             "padding: 10px 20px;"
                             "text-align: center;"
                             "text-decoration: none;"
                             "display: inline-block;"
                             "font-size: 16px;"
                             "margin: 4px 2px;"
                             "cursor: pointer;"
                             "border-radius: 5px;"
                             "}"
                             "QMessageBox QPushButton:hover {"
                             "background-color: #45a049;"
                             "}";
        msgBox.setWindowFlags(Qt::FramelessWindowHint);
        msgBox.setStyleSheet(styleSheet);
        msgBox.exec();
    }
}
void Game_control::GameReStart(){
    chessboard.ReStartNewGame();
    chessboardai.ReStartNewGame();
}
void Game_control::UpdateInfo(int x, int y){

    // qDebug()<<"x2"<<x<<"y2"<<y;
    int score = gameai.MaxMinSearch(chessboardai.board, DEPTH, INT_MIN, INT_MAX);
    int X = gameai.bestPos.x;
    int Y = gameai.bestPos.y;
    // for(int i = 0; i < 19; i++){
    //     for(int j = 0; j < 19; j++){
    //         qDebug()<<"i"<<chessboardai.board[i][j];
    //     }
    //     qDebug()<<"\n";
    // }
    chessboardai.SetPiece(X, Y);
    // qDebug()<<"X"<<X<<"Y"<<Y;

}
Game_control::~Game_control()
{
    delete ui;
}


