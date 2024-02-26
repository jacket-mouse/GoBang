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

    // 初始化槽函数和信号,通过ui文件创建的按钮，也要通过ui获取
    connect(ui->Local_btn, &QPushButton::clicked, this, &Widget::hideMenu);                      // 本地对战模式
    connect(ui->Ai_btn, &QPushButton::clicked, this, &Widget::hideMenuAi);                       // Ai对战模式
    connect(&gamecontrol.chessboard, &Chessboard::ReturnToMenu, this, &Widget::hideChessBoard);  // 隐藏棋盘，返回菜单

}

void Widget::hideMenu(){
    gamecontrol.chessboard.aiModel = false;
    gamecontrol.chessboard.setWindowTitle("本地对战");
    update();
    this->hide();
    gamecontrol.chessboard.show();
}
void Widget::hideMenuAi(){
    gamecontrol.chessboard.aiModel = true;
    gamecontrol.chessboard.setWindowTitle("人机对战");
    update();
    this->hide();
    gamecontrol.chessboard.show();
    gamecontrol.chessboard.ShowChoice();
}
void Widget::hideChessBoard(){
    this->show();
    gamecontrol.chessboard.hide();
    gamecontrol.chessboard.StartNewGame();  //返回菜单后将棋盘初始化
}

Widget::~Widget()
{
    delete ui;
}

