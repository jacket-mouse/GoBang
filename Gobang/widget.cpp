/*
 * Class Menu
*/

#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋");  // 设置窗口标题
    QIcon icon(":/img/icon.ico");
    setWindowIcon(icon);            // 设置窗口图标
    // 初始化槽函数和信号
    // 本地对战
    connect(ui->Local_btn, &QPushButton::clicked, this, &Widget::hideMenu);  // 通过ui文件创建的按钮，也要通过ui获取
    connect(&gamecontrol.chessboard, &Chessboard::Signal, this, &Widget::hideChessBoard);  // 隐藏棋盘，返回菜单
    connect(&gamecontrol, &Game_control::ReturnToMenu, this, &Widget::hideChessBoard);     // 隐藏菜单，进入对战
    // Ai对战
    connect(ui->Ai_btn, &QPushButton::clicked, this, &Widget::hideMenuAi);  // Ai对战模式
    connect(&gamecontrol.chessboardai, &Chessboard_ai::Signal, this, &Widget::hideChessBoardAi);  // 隐藏棋盘，返回菜单
    connect(&gamecontrol, &Game_control::ReturnToMenu, this, &Widget::hideChessBoardAi);     // 隐藏菜单，进入对战


}

void Widget::on_Ai_btn_clicked()
{
    qDebug()<<"人机对战";
}
void Widget::on_Local_btn_clicked()
{
    qDebug()<<"本地对战";
}
void Widget::hideMenu(){
    this->hide();
    gamecontrol.chessboard.show();
}
void Widget::hideMenuAi(){
    this->hide();
    gamecontrol.chessboardai.show();
}
void Widget::hideChessBoard(){
    this->show();
    gamecontrol.chessboard.hide();
    gamecontrol.chessboard.StartNewGame();  //返回菜单后将棋盘初始化
}
void Widget::hideChessBoardAi(){
    this->show();
    gamecontrol.chessboardai.hide();
    gamecontrol.chessboardai.StartNewGame();
}

Widget::~Widget()
{
    delete ui;
}

