#include "chessboard_ai.h"
#include "ui_chessboard_ai.h"

const QPoint Chessboard_ai::START_POS(40,40);            // 棋盘中单元格起始位置
const QSize Chessboard_ai::PIECE_SIZE(25,25);            // 棋子大小
const QSize Chessboard_ai::BOARD_SIZE(530,530);          // 棋盘大小

Chessboard_ai::Chessboard_ai(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chessboard_ai)
{
    ui->setupUi(this);
    setMouseTracking(true);  // 没有这句话就需要按住鼠标移动，才能更新选框，如果把这句话放在检测函数里，就会要先按住点一下才能跟随移动
    // control = new Control();
    // ui->scrollArea->setWidget(control);
    this->setWindowTitle("人机对战");                                  // 设置窗口标题

    ui->back_btn->setStyleSheet("QPushButton {"
                                "background-color: #8B4513;" // 棕色
                                "border: 2px solid #8B4513;"
                                "color: white;"

                                "text-align: center;"
                                "text-decoration: none;"
                                "display: inline-block;"
                                "font-size: 16px;"

                                "cursor: pointer;"
                                "border-radius: 5px;"
                                "}"
                                // 鼠标悬停时的样式
                                "QPushButton:hover {"
                                "background-color: #A0522D;" // 较深的棕色
                                "border-color: #A0522D;"
                                "}"
                                // 鼠标按下时的样式
                                "QPushButton:pressed {"
                                "background-color: #D2691E;" // 橙色
                                "border-color: #D2691E;"
                                "}");

    // 创建按钮动画
    QPropertyAnimation animation_back(ui->back_btn, "geometry");
    animation_back.setDuration(100); // 动画持续时间（毫秒）
    animation_back.setStartValue(QRect(100, 100, 200, 50)); // 初始位置和大小
    animation_back.setEndValue(QRect(100, 100, 220, 60)); // 结束位置和大小
    animation_back.setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线
    ui->re_btn->setStyleSheet("QPushButton {"
                              "background-color: #8B4513;" // 棕色
                              "border: 2px solid #8B4513;"
                              "color: white;"

                              "text-align: center;"
                              "text-decoration: none;"
                              "display: inline-block;"
                              "font-size: 16px;"

                              "cursor: pointer;"
                              "border-radius: 5px;"
                              "}"
                              // 鼠标悬停时的样式
                              "QPushButton:hover {"
                              "background-color: #A0522D;" // 较深的棕色
                              "border-color: #A0522D;"
                              "}"
                              // 鼠标按下时的样式
                              "QPushButton:pressed {"
                              "background-color: #D2691E;" // 橙色
                              "border-color: #D2691E;"
                              "}");
    // 创建按钮动画
    QPropertyAnimation animation_re(ui->re_btn, "geometry");
    animation_re.setDuration(100); // 动画持续时间（毫秒）
    animation_re.setStartValue(QRect(100, 100, 200, 50)); // 初始位置和大小
    animation_re.setEndValue(QRect(100, 100, 220, 60)); // 结束位置和大小
    animation_re.setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线
    ui->hui_btn->setStyleSheet("QPushButton {"
                              "background-color: #8B4513;" // 棕色
                              "border: 2px solid #8B4513;"
                              "color: white;"

                              "text-align: center;"
                              "text-decoration: none;"
                              "display: inline-block;"
                              "font-size: 16px;"

                              "cursor: pointer;"
                              "border-radius: 5px;"
                              "}"
                              // 鼠标悬停时的样式
                              "QPushButton:hover {"
                              "background-color: #A0522D;" // 较深的棕色
                              "border-color: #A0522D;"
                              "}"
                              // 鼠标按下时的样式
                              "QPushButton:pressed {"
                              "background-color: #D2691E;" // 橙色
                              "border-color: #D2691E;"
                              "}");
    // 创建按钮动画
    QPropertyAnimation animation(ui->hui_btn, "geometry");
    animation.setDuration(100); // 动画持续时间（毫秒）
    animation.setStartValue(QRect(100, 100, 200, 50)); // 初始位置和大小
    animation.setEndValue(QRect(100, 100, 220, 60)); // 结束位置和大小
    animation.setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线



    // 设置液晶数字显示器的范围和显示位数
    ui->bai_num->setSegmentStyle(QLCDNumber::Flat); // 设置显示风格
    //ui->bai_num->setFixedSize(200, 100); // 设置尺寸
    ui->bai_num->setDigitCount(4); // 设置显示位数
    // 设置液晶数字显示器的范围和显示位数
    ui->hei_num->setSegmentStyle(QLCDNumber::Flat); // 设置显示风格
    //ui->hei_num->setFixedSize(200, 100); // 设置尺寸
    ui->hei_num->setDigitCount(4); // 设置显示位数

    ui->hei_num->setStyleSheet("QLCDNumber { background-color: #d2b48c; color: #8b4513; border: 2px solid #8b4513; }");
    ui->bai_num->setStyleSheet("QLCDNumber { background-color: #d2b48c; color: #8b4513; border: 2px solid #8b4513; }");


    connect(this, &Chessboard_ai::WhiteScore, [&]() {
        ui->bai_num->display(white_score);
    });
    connect(this, &Chessboard_ai::BlackScore, [&]() {
        ui->hei_num->display(black_score);
    });

    QFont font("SimSun", 16); // 选择宋体作为古风字体
    font.setWeight(QFont::Bold); // 设置字体加粗
    ui->bai_piece->setFont(font);
    ui->hei_piece->setFont(font);





    QIcon icon(":/img/icon.ico");
    setWindowIcon(icon);                                              // 设置窗口图标
    this->setFixedSize(BOARD_SIZE.height()+200, BOARD_SIZE.width());  // 设置棋盘大小
    boardReceivePlayer << WHITE_PLAYER << BLACK_PLAYER;               // 棋盘默认双人对战
    connect(ui->back_btn, &QPushButton::clicked, this, &Chessboard_ai::sendSignal);  // 返回菜单
    connect(ui->re_btn, &QPushButton::clicked, this, &Chessboard_ai::SendReStart);  // 重开游戏
    connect(ui->hui_btn, &QPushButton::clicked, this, &Chessboard_ai::SendUnDo);  // 悔棋
    StartNewGame();
}
void Chessboard_ai::ReStartNewGame(){
    for (int i = 0; i < BOARD_COL; i++){
        for (int j = 0; j < BOARD_ROW; j++){
            board[i][j] = NO_PIECE;
        }
    }
    winPiecePos.clear();
    dropedPieces.clear();
    nextPlayer = BLACK_PLAYER;  // 默认黑棋先手
    isGameOver = false;
    update();
    emit(TurnToNextPlayer(nextPlayer));
}
void Chessboard_ai::StartNewGame() // 开始新游戏
{
    for (int i = 0; i < BOARD_COL; i++){
        for (int j = 0; j < BOARD_ROW; j++){
            board[i][j] = NO_PIECE;
        }
    }
    winPiecePos.clear();
    dropedPieces.clear();
    nextPlayer = BLACK_PLAYER;   // 默认玩家先手，Ai后手
    isGameOver = false;


    black_score = 0;            // 返回主界面清除得分
    emit BlackScore();
    white_score = 0;
    emit WhiteScore();

    update();
    emit(TurnToNextPlayer(nextPlayer));
}
// 绘图事件
// 需要注意的是，虽然update()函数会请求部件进行重新绘制，但具体的重绘操作由Qt的绘图系统来处理。需要通过重写部件的paintEvent()方法来实现自定义的绘制操作，以满足特定的需求。
void Chessboard_ai::paintEvent(QPaintEvent *event){

    // 设置背景颜色
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#B1723C")); // 背景色：棕黄色
    this->setPalette((palette));

    // 绘制棋盘边界与棋盘内颜色
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true); // 抗锯齿

    QBrush  brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20,20,490,490);  // 棋盘外框，四个数分别代表矩阵的左上角顶点的 x 坐标和 y 坐标，以及矩形的宽度和高度。

    // 绘制棋盘格
    for (int i = 0; i < BOARD_COL - 1; i++)
    {
        for (int j = 0; j < BOARD_ROW - 1; j++)
        {
            /*
             * 这行代码中，drawRect 方法接受了一个 QRect 对象作为参数。QRect类是Qt框架中用来表示矩形的类。在这里，QRect的构造函数被调用，传入了两个参数：
             * 第一个参数是一个点的坐标，它使用了 START_POS 和 QPoint(i * PIECE_SIZE.width(), j * PIECE_SIZE.height()) 来计算出一个点的位置。
             * START_POS 可能是一个起始位置，而 QPoint(i * PIECE_SIZE.width(), j * PIECE_SIZE.height()) 可能是相对于起始位置的偏移量。这样可以确定矩形的左上角的位置。
             * 第二个参数是矩形的尺寸，即宽度和高度，这个尺寸是通过 PIECE_SIZE 对象提供的。
             * 因此，这行代码的作用是在绘图中绘制一个矩形，矩形的左上角位置通过计算得到，宽度和高度由 PIECE_SIZE 指定。
            */
            painter.drawRect(QRect(START_POS + QPoint(i * PIECE_SIZE.width(), j * PIECE_SIZE.height()),PIECE_SIZE));
        }
    }

    // 绘制九个小黑点
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(112,112,6,6);  // 左上(3,3)
    painter.drawRect(262,112,6,6);
    painter.drawRect(412,112,6,6);
    painter.drawRect(112,262,6,6);
    painter.drawRect(112,412,6,6);
    painter.drawRect(262,262,6,6);
    painter.drawRect(412,262,6,6);
    painter.drawRect(412,412,6,6);  // 右下(16,16)
    painter.drawRect(262,412,6,6);


    // 绘制落子前的红色选框
    painter.setPen(Qt::red);
    QPoint pos[12] = {
        mousePos + QPoint(0, 8),
        mousePos,
        mousePos + QPoint(8, 0),
        mousePos + QPoint(17, 0),
        mousePos + QPoint(25, 0),
        mousePos + QPoint(25, 8),
        mousePos + QPoint(25, 17),
        mousePos + QPoint(25, 25),
        mousePos + QPoint(17, 25),
        mousePos + QPoint(8, 25),
        mousePos + QPoint(0, 25),
        mousePos + QPoint(0, 17)
    };
    painter.drawPolyline(pos, 3);   // 绘制四次平行线
    painter.drawPolyline(pos + 3, 3);
    painter.drawPolyline(pos + 6, 3);
    painter.drawPolyline(pos + 9, 3);

    // 绘制棋子
    painter.setPen(Qt::NoPen);
    for (int i = 0; i < BOARD_COL; i++)
    {
        for (int j = 0; j < BOARD_ROW; j++)
        {
            if (board[i][j] != NO_PIECE)
            {
                QColor color = (board[i][j] == WHITE_PIECE) ? Qt::white : Qt::black;
                painter.setBrush(QBrush(color));
                painter.drawEllipse(START_POS.x() - PIECE_SIZE.width()/2 + i*PIECE_SIZE.width(),
                                    START_POS.y() - PIECE_SIZE.height()/2 + j*PIECE_SIZE.height(),
                                    PIECE_SIZE.width(), PIECE_SIZE.height());
            }
        }
    }
    // 绘制最后一次落子的标志
    painter.setPen(Qt::red);
    if (!dropedPieces.isEmpty())
    {
        QPoint lastPos = dropedPieces.top();
        QPoint drawPos = START_POS + QPoint(lastPos.x() * PIECE_SIZE.width(), lastPos.y() * PIECE_SIZE.height());
        painter.drawLine(drawPos + QPoint(0, 5), drawPos + QPoint(0, -5));
        painter.drawLine(drawPos + QPoint(5, 0), drawPos + QPoint(-5, 0));
    }

    // 绘制五子连珠的标志
    for (QPoint pos : winPiecePos)
    {
        QPoint drawPos = START_POS + QPoint(pos.x() * PIECE_SIZE.width(), pos.y() * PIECE_SIZE.height());
        painter.drawLine(drawPos + QPoint(0, 5), drawPos + QPoint(0, -5));
        painter.drawLine(drawPos + QPoint(5, 0), drawPos + QPoint(-5, 0));
    }
}

void Chessboard_ai::SetMousePos(const QPoint &pos) // 将鼠标在棋盘中的位置保存于 mousePos 中
{
    mousePos = pos;
    /*
     * 在Qt中，update()是一个用于重新绘制部件（widget）的函数。
     * 当你调用update()函数时，它会触发部件的重新绘制，从而使得部件在屏幕上更新其外观。
     * 这通常在需要更新部件的内容或外观时使用，比如在响应用户交互或在程序逻辑中进行动态变化时。
     * update()函数会安排一个重绘事件，但不会立即执行，而是在Qt的事件循环中执行，以保持UI的响应性能。
     */
    update();

}
void Chessboard_ai::mouseMoveEvent(QMouseEvent *event) // 鼠标移动事件
{

    // 获取相对坐标
    QPoint pos = event->pos() - START_POS + QPoint(PIECE_SIZE.width()/2,PIECE_SIZE.height()/2);
    int x = pos.x();
    int y = pos.y();

    // 判断鼠标是否在棋盘内
    if(x < 0 || x >= PIECE_SIZE.width() * BOARD_COL || y < 0 || y >= PIECE_SIZE.height() * BOARD_ROW)
        return;

    // 设置偏移量
    int offsetX = x % PIECE_SIZE.width();
    int offsetY = y % PIECE_SIZE.height();

    // 更新已保存的的鼠标位置，自定义函数
    SetMousePos(QPoint(x - offsetX,y - offsetY) + START_POS - QPoint(PIECE_SIZE.width()/2, PIECE_SIZE.height()/2));
}

void Chessboard_ai::sendSignal(){
    emit Signal();
}

void Chessboard_ai::SetPiece(int x,int y)  // 落子
{
    if (x >= 0 && x < BOARD_COL && y >= 0 && y < BOARD_ROW && board[x][y] == NO_PIECE)  // 边界判断 && 无子判断
    {
        // qDebug()<<"x1"<<x<<"y1"<<y;
        dropedPieces.push(QPoint(x, y));
        if(nextPlayer == BLACK_PLAYER) board[x][y] = BLACK_PIECE;
        if(nextPlayer == WHITE_PLAYER) board[x][y] = WHITE_PIECE;
        repaint();      // 相较于update可实现立刻刷新效果
        CheckWinner();  // 胜负判断
        if (!isGameOver)
        {
            SwitchNextPlayer();
        }

    }
}
void Chessboard_ai::SwitchNextPlayer() // 切换选手
{
    if(nextPlayer == BLACK_PLAYER){
        nextPlayer = WHITE_PLAYER;
    }else if(nextPlayer == WHITE_PLAYER){
        nextPlayer = BLACK_PLAYER;
    }

    //emit TurnToNextPlayer(nextPlayer);  // 切换倒计时等
}
void Chessboard_ai::mouseReleaseEvent(QMouseEvent *event) // 鼠标点击事件
{
    // 获取相对坐标
    QPoint pos = event->pos() - START_POS + QPoint(PIECE_SIZE.width()/2,PIECE_SIZE.height()/2);
    int x = pos.x();
    int y = pos.y();

    // 判断鼠标是否在棋盘内
    if(x < 0 || x >= PIECE_SIZE.width() * BOARD_COL || y < 0 || y >= PIECE_SIZE.height() * BOARD_ROW){
        qDebug()<<"在棋盘外点击";
        return;
    }else{
        if(boardReceivePlayer.contains((nextPlayer) && !isGameOver)){    // 选手判断 && 游戏结束判断
            QPoint pos  = event->pos() - START_POS; // 获取点击的相对位置
            int x = pos.x();
            int y = pos.y();

            // 定位点击的格子位置
            int pieceX = x / PIECE_SIZE.width();
            int pieceY = y / PIECE_SIZE.height();
            int offsetX = x % PIECE_SIZE.width();
            int offsetY = y % PIECE_SIZE.height();

            // 判断格子点击时的左右偏移量
            if (offsetX > PIECE_SIZE.width() / 2)
                pieceX++;
            if(offsetY > PIECE_SIZE.height() / 2)
                pieceY++;
            if(nextPlayer == BLACK_PLAYER && !isGameOver){  // 只有当黑棋(玩家)回合时才允许落子
                SetPiece(pieceX,pieceY);
                emit setpiece(x, y);  // 发出落子信号，向Ai更新棋盘信息
            }

        }
    }
}
bool Chessboard_ai::IsFivePiece(int x, int y){
    return IsVerFivePiece(x, y) || IsHorFivePiece(x, y) || IsNorthEastFivePiece(x, y) || IsNorthWestFivePiece(x, y);
}
bool Chessboard_ai::IsVerFivePiece(int x, int y){  // 依次遍历棋盘，向下垂直查找
    int piece = board[x][y];  // 获取当前落子颜色
    for (int i = 1; i < 5; i++)
    {
        if(y + i >= BOARD_ROW || board[x][y+i] != piece)
            return false;
    }
    winPiecePos.clear();
    for(int i = 0; i < 5; i++)
        winPiecePos.append(QPoint(x,y+i));
    return true;
}
bool Chessboard_ai::IsHorFivePiece(int x, int y){  // 依次遍历棋盘，向右垂直查找
    int piece = board[x][y];
    for(int i = 1; i < 5; i++){
        if(x + i >= BOARD_COL || board[x+i][y] != piece){
            return false;
        }
    }
    winPiecePos.clear();
    for(int i = 0; i < 5; i++){
        winPiecePos.append(QPoint(x+i, y));
    }
    return true;

}
bool Chessboard_ai::IsNorthWestFivePiece(int x, int y){  // 坐标原点左上
    int piece = board[x][y];
    for(int i = 0; i < 5; i++){
        if(x + i >= BOARD_COL || y + i >= BOARD_ROW || board[x+i][y+i] != piece){
            return false;
        }
    }
    winPiecePos.clear();
    for(int i = 0; i < 5; i++){
        winPiecePos.append(QPoint(x+i, y+i));
    }
    return true;
}
bool Chessboard_ai::IsNorthEastFivePiece(int x, int y){
    int piece = board[x][y];
    for(int i = 0; i < 5; i++){
        if(x + i >= BOARD_COL || y - i < 0 || board[x+i][y-i] != piece){
            return false;
        }
    }
    winPiecePos.clear();
    for(int i = 0; i < 5; i++){
        winPiecePos.append(QPoint(x+i, y-i));
    }
    return true;
}
void Chessboard_ai::CheckWinner(){
    bool fullPieces = true;
    // 遍历棋盘
    for(int i = 0; i < BOARD_COL; i++)
    {
        for(int j = 0; j < BOARD_ROW; j++)
        {
            if(board[i][j] == NO_PIECE) // 判满
            {
                fullPieces = false;
            }
            if(board[i][j] != NO_PIECE && IsFivePiece(i,j)){ // 若有一方达成五子
                bool winner = (board[i][j] == WHITE_PIECE) ? WHITE_PLAYER : BLACK_PLAYER;
                isGameOver = true;
                emit GameOver(winner);

                // 记分板
                if(winner == WHITE_PLAYER){
                    white_score++;
                    emit WhiteScore();
                }else if(winner == BLACK_PLAYER){
                    black_score++;
                    emit BlackScore();
                }
                return;  // 防止重复判定五子，如六子连在一起
            }
        }
    }
    if (fullPieces)
    {
        isGameOver = true;
        emit GameOver(DRAW);    // 和棋
    }
}
void Chessboard_ai::SendReStart(){
    emit ReStart();
}
void Chessboard_ai::SendUnDo(){
    if(!isGameOver && !dropedPieces.empty()){  //当游戏没有结束且有落子的情况下才能悔棋
        QPoint point = dropedPieces.top();
        board[point.x()][point.y()] = 0;
        dropedPieces.pop();
        point = dropedPieces.top();
        board[point.x()][point.y()] = 0;
        dropedPieces.pop();
        repaint();
    }
}
Chessboard_ai::~Chessboard_ai()
{
    delete ui;
}
