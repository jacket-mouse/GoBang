#include "gameai.h"

GameAi::GameAi() {
    chessStatus_init();
    Zobrist zobrist;
    for(int i = 0; i < BOARD_ROW; i++){
        for(int j = 0; j < BOARD_COL; j++){
            uint64_t randomNum = zobrist.getRandom();
            zobrist_black[i][j] = randomNum;
            // qDebug()<<zobrist_black[i][j];
        }
    }
    for(int i = 0; i < BOARD_ROW; i++){
        for(int j = 0; j < BOARD_COL; j++){
            uint64_t randomNum = zobrist.getRandom();
            zobrist_white[i][j] = randomNum;
        }
    }
}
GameAi::~GameAi() {}
void GameAi::reverseBoard(int board[BOARD_ROW][BOARD_COL], int rboard[BOARD_ROW][BOARD_COL]){
    for(int i = 0; i < BOARD_ROW; i++){
        for(int j = 0; j < BOARD_COL; j++){
            if(board[i][j] == WHITE_PIECE){
                rboard[i][j] = BLACK_PIECE;
            }else if(board[i][j] == BLACK_PIECE){
                rboard[i][j] = WHITE_PIECE;
            }
        }
    }
}
Points GameAi::localSearch(int board[BOARD_ROW][BOARD_COL]) {
    Points bestPoint{};
    bool localBoard[BOARD_ROW][BOARD_COL]  = {{false}};
    int weight[BOARD_ROW][BOARD_COL] = {{0}};

    //  局部搜索。找出棋盘上局部搜索匹配的位置，匹配规则为已下棋子周围八个方向的三格
    for (int i = 0; i < BOARD_ROW; i++) {
        for (int j = 0; j < BOARD_COL; j++) {
            if (board[i][j] != 0) {
                for (int k = -3; k <= 3; k++) {
                    //  横向
                    if (board[i][j + k] == 0 && (j + k < 19) && (j + k >= 0))
                        localBoard[i][j + k] = true;
                    //  纵向
                    if (board[i + k][j] == 0 && (i + k < 19) && (i + k) >= 0)
                        localBoard[i + k][j] = true;
                    //  斜向（左上到右下）
                    if (board[i + k][j + k] == 0 && (i + k < 19) && (i + k) >= 0 && (j + k < 19) && (j + k >= 0))
                        localBoard[i + k][j + k] = true;
                    //  斜向（左下到右上）
                    if (board[i - k][j + k] == 0 && (i - k < 19) && (i - k) >= 0 && (j + k < 19) && (j + k >= 0))
                        localBoard[i - k][j + k] = true;
                }
            }
        }
    }

    //  启发式评估，在局部搜索结果后模拟落子并对落子后结果打分。
    for (int i = 0; i < BOARD_ROW; i++) {
        for (int j = 0; j < BOARD_COL; j++) {
            weight[i][j] = INT_MIN;  // 最小int整数
            if (localBoard[i][j]) {
                board[i][j] = WHITE_PIECE;
                weight[i][j] = evaluate(board);
                board[i][j] = 0;
            }
        }
    }
    // 找到能使棋盘权重
    int w;
    Pos p = Pos();
    for (int k = 0; k < AN; k++) {
        w = INT_MIN;
        for (int i = 0; i < BOARD_ROW; i++) {
            for (int j = 0; j < BOARD_COL; j++) {
                if (weight[i][j] > w) {
                    w = weight[i][j];
                    p.x = i, p.y = j;
                }
            }
        }
        bestPoint.pos[k] = p, bestPoint.score[k] = w;
        weight[p.x][p.y] = INT_MIN; //将最大值去掉，寻找第二大的点。
    }
    return bestPoint; // 存了10个权重最大的点的集合
}

int GameAi::MaxMinSearch(int board[BOARD_ROW][BOARD_COL], int depth, int alpha, int beta){  // 极大极小值搜索
    //    if (debugMode && depth == DEPTH) cout << depth << endl;
    //    迭代深度为0，直接返回分析结果
    if (depth == 0) {
        Points p = this->localSearch(board);
        return p.score[0];
    }
    else if (depth % 2 == 0) { //max层
        int sameBoard[BOARD_ROW][BOARD_COL] = {{0}};
        // 将board复制给sameboard
        for(int i = 0; i < BOARD_ROW; i++){
            for(int j = 0; j < BOARD_COL; j++){
                sameBoard[i][j] = board[i][j];
            }
        }
        Points p = this->localSearch(board);
        for (int i = 0; i < AN; i ++) {
            sameBoard[p.pos[i].x][p.pos[i].y] = WHITE_PIECE; //模拟落子
            int a = this->MaxMinSearch(sameBoard, depth - 1, alpha, beta);
            sameBoard[p.pos[i].x][p.pos[i].y] = 0;
            if (a > alpha) {
                alpha = a;
                /*
                 * 下面的if忘了打大括号，导致本来只能在depth == DEPTH的条件下修改bestPos.x = p.pos[i].x，而y是任意修改的
                 * 所以下面一开始加了for循环，抵消掉if，使得x和y同时变，没问题
                 * 后面把for注释掉，又加了，qDebug，也抵消掉if，没问题
                 * 所以不是玄学
                 */
                if (depth == DEPTH) { // 顶层情况，  一旦找到最大的alpha，做出决策
                    // for (int j = 0; j < BOARD_ROW; j++) {
                    //     qDebug()<<board[j][0]<<" "<<board[j][1]<<" "<<board[j][2]<<" "<<board[j][3]<<" "<<board[j][4]<<" "<<board[j][5]<<" "<<board[j][6]<<" "<<board[j][7]<<" "<<board[j][8]<<" "<<board[j][9]<<" "<<board[j][10]<<" "<<board[j][11]<<" "<<board[j][12]<<" "<<board[j][13]<<" "<<board[j][14]<<" "<<board[j][15]<<" "<<board[j][16]<<" "<<board[j][17]<<" "<<board[j][18];
                    // }
                    qDebug()<<"i"<<i;
                    bestPos.x = p.pos[i].x;
                    bestPos.y = p.pos[i].y;
                    qDebug()<<"x0"<<bestPos.x<<"y0"<<bestPos.y;
                    //this->decision.score = p.score[i];
                }
            }
            if (beta <= alpha) break; //剪枝
        }
        return alpha;
    }
    else if (depth % 2 == 1) { //min层

        int rboard[BOARD_ROW][BOARD_COL] = {{0}};
        //  反转棋盘
        reverseBoard(board, rboard);
        int sameBoard[BOARD_ROW][BOARD_COL] = {{0}};
        for(int i = 0; i < BOARD_ROW; i++){
            for(int j = 0; j < BOARD_COL; j++){
                sameBoard[i][j] = board[i][j];
            }
        }
        Points p = this->localSearch(rboard); //寻找对于敌方的最佳落子点
        for (int i = 0; i < AN; i ++) {
            sameBoard[p.pos[i].x][p.pos[i].y] = BLACK_PIECE;
            int a = MaxMinSearch(sameBoard, depth - 1, alpha, beta);
            sameBoard[p.pos[i].x][p.pos[i].y] = 0;
            if (a < beta) beta = a;
            if (beta <= alpha) break; //剪枝
        }
        return beta;
    }
}

void GameAi::chessStatus_init() {
    //黑连5,ai输
    this->chessStatus[2][2][2][2][2][2]=LOSE;  // 六黑
    this->chessStatus[2][2][2][2][2][0]=LOSE;  // 五黑+无子
    this->chessStatus[0][2][2][2][2][2]=LOSE;
    this->chessStatus[2][2][2][2][2][1]=LOSE;  // 五黑+白子
    this->chessStatus[1][2][2][2][2][2]=LOSE;
    this->chessStatus[3][2][2][2][2][2]=LOSE;  // 五黑+边界
    this->chessStatus[2][2][2][2][2][3]=LOSE;
    //白连5,ai赢
    this->chessStatus[1][1][1][1][1][1]=WIN;  // 同上
    this->chessStatus[1][1][1][1][1][0]=WIN;
    this->chessStatus[0][1][1][1][1][1]=WIN;
    this->chessStatus[1][1][1][1][1][2]=WIN;
    this->chessStatus[2][1][1][1][1][1]=WIN;
    this->chessStatus[3][1][1][1][1][1]=WIN;
    this->chessStatus[1][1][1][1][1][3]=WIN;
    //黑活4
    this->chessStatus[0][2][2][2][2][0]=FLEX4;
    //白活4
    this->chessStatus[0][1][1][1][1][0]=flex4;
    //黑活3
    this->chessStatus[0][2][2][2][0][0]=FLEX3;
    this->chessStatus[0][0][2][2][2][0]=FLEX3;
    this->chessStatus[0][2][0][2][2][0]=FLEX3;
    this->chessStatus[0][2][2][0][2][0]=FLEX3;
    //白活3
    this->chessStatus[0][1][1][1][0][0]=flex3;
    this->chessStatus[0][0][1][1][1][0]=flex3;
    this->chessStatus[0][1][0][1][1][0]=flex3;
    this->chessStatus[0][1][1][0][1][0]=flex3;
    //黑活2
    this->chessStatus[0][2][2][0][0][0]=FLEX2;
    this->chessStatus[0][2][0][2][0][0]=FLEX2;
    this->chessStatus[0][2][0][0][2][0]=FLEX2;
    this->chessStatus[0][0][2][2][0][0]=FLEX2;
    this->chessStatus[0][0][2][0][2][0]=FLEX2;
    this->chessStatus[0][0][0][2][2][0]=FLEX2;
    //白活2
    this->chessStatus[0][1][1][0][0][0]=flex2;
    this->chessStatus[0][1][0][1][0][0]=flex2;
    this->chessStatus[0][1][0][0][1][0]=flex2;
    this->chessStatus[0][0][1][1][0][0]=flex2;
    this->chessStatus[0][0][1][0][1][0]=flex2;
    this->chessStatus[0][0][0][1][1][0]=flex2;
    //黑活1
    this->chessStatus[0][2][0][0][0][0]=FLEX1;
    this->chessStatus[0][0][2][0][0][0]=FLEX1;
    this->chessStatus[0][0][0][2][0][0]=FLEX1;
    this->chessStatus[0][0][0][0][2][0]=FLEX1;
    //白活1
    this->chessStatus[0][1][0][0][0][0]=flex1;
    this->chessStatus[0][0][1][0][0][0]=flex1;
    this->chessStatus[0][0][0][1][0][0]=flex1;
    this->chessStatus[0][0][0][0][1][0]=flex1;

    // 冲、眠
    int p1,p2,p3,p4,p5,p6,x,y,ix,iy;//x:左5中白个数,y:左5中黑个数,ix:右5中白个数,iy:右5中黑个数
    // 遍历六子的全部情况，选出冲、眠状况
    for(p1=0;p1<4;++p1){  // 边界只会出现在两侧
        for(p2=0;p2<3;++p2){
            for(p3=0;p3<3;++p3){
                for(p4=0;p4<3;++p4){
                    for(p5=0;p5<3;++p5){
                        for(p6=0;p6<4;++p6){  // 边界只会出现在两侧
                            x=y=ix=iy=0;
                            if(p1==1)x++;
                            else if(p1==2)y++;

                            if(p2==1){x++;ix++;}
                            else if(p2==2){y++;iy++;}

                            if(p3==1){x++;ix++;}
                            else if(p3==2){y++;iy++;}

                            if(p4==1){x++;ix++;}
                            else if(p4==2){y++;iy++;}

                            if(p5==1){x++;ix++;}
                            else if(p5==2){y++;iy++;}

                            if(p6==1)ix++;
                            else if(p6==2)iy++;

                            if(p1==3||p6==3){//有边界
                                if(p1==3&&p6!=3){//左边界
                                    //黑冲4
                                    if(ix==0&&iy==4){//若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            // 可能是活四
                                            // 3 0 2 2 2 2
                                            // 必然是冲四
                                            // 3 2 0 2 2 2
                                            // 3 2 2 0 2 2
                                            // 3 2 2 2 0 2
                                            // 3 2 2 2 2 0
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                    }
                                    //白冲4
                                    if(ix==4&&iy==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block4;
                                    }
                                    //黑眠3
                                    if(ix==0&&iy==3){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                    }
                                    //白眠3
                                    if(ix==3&&iy==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block3;
                                    }
                                    //黑眠2
                                    if(ix==0&&iy==2){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                    }
                                    //白眠2
                                    if(ix==2&&iy==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block2;
                                    }
                                }else if(p6==3&&p1!=3){//右边界
                                    //黑冲4
                                    if(x==0&&y==4){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                    }
                                    //白冲4
                                    if(x==4&&y==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block4;
                                    }
                                    //黑眠3
                                    if(x==0&&y==3){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                    }
                                    //白眠3
                                    if(x==3&&y==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block3;
                                    }
                                    //黑眠2
                                    if(x==0&&y==2){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                    }
                                    //白眠2
                                    if(x==2&&y==0){
                                        if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                            this->chessStatus[p1][p2][p3][p4][p5][p6]=block2;
                                    }
                                }
                            }else{//无边界
                                //黑冲4
                                if((x==0&&y==4)||(ix==0&&iy==4)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                }
                                //白冲4
                                if((x==4&&y==0)||(ix==4&&iy==0)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=block4;
                                }
                                //黑眠3
                                if((x==0&&y==3)||(ix==0&&iy==3)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                }
                                //白眠3
                                if((x==3&&y==0)||(ix==3&&iy==0)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=block3;
                                }
                                //黑眠2
                                if((x==0&&y==2)||(ix==0&&iy==2)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                }
                                //白眠2
                                if((x==2&&y==0)||(ix==2&&iy==0)){
                                    if(this->chessStatus[p1][p2][p3][p4][p5][p6]==OTHER)
                                        this->chessStatus[p1][p2][p3][p4][p5][p6]=block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

int GameAi::evaluate(int board[BOARD_ROW][BOARD_COL]){  // 评估函数
    //  权值
    int weight[17]={0, 1100000, -10000000, -1000000, 50000, -1000000, 400, -8000, 400, -50, 20, -50, 20, -3, 1, -3, 1};
    //  四个方向的棋形记录，每个位置对应一个权重值，如果包含一个该权重棋形则+1
    int shapeRecord[4][17] = {{0}};
    //  大棋盘边界初始化
    int bigBoard[BOARD_ROW+2][BOARD_COL+2] = {{ NO_PIECE }};
    for (int i = 0; i < BOARD_ROW + 2; i++) {
        bigBoard[0][i] = BORDER;
        bigBoard[i][0] = BORDER;
        bigBoard[BOARD_ROW+1][i] = BORDER;
        bigBoard[i][BOARD_COL+1] = BORDER;
    }

    //  棋盘复制
    for (int i = 0; i < BOARD_ROW; i ++) {
        for (int j = 0; j < BOARD_COL; j++)
            bigBoard[i + 1][j + 1] = board[i][j];
    }

    //  横向棋形统计
    for (int i = 1; i <= BOARD_ROW; i ++) {
        for (int j = 1; j < BOARD_COL - 3; j++) {
            int type = this->chessStatus[bigBoard[i][j]][bigBoard[i][j+1]][bigBoard[i][j+2]][bigBoard[i][j+3]][bigBoard[i][j+4]][bigBoard[i][j+5]];
            shapeRecord[0][type] ++;
        }
    }
    //  竖向棋形统计
    for (int i = 0; i < BOARD_ROW - 3; i ++) {
        for (int j = 1; j <= BOARD_COL; j ++) {
            int type = this->chessStatus[bigBoard[i][j]][bigBoard[i+1][j]][bigBoard[i+2][j]][bigBoard[i+3][j]][bigBoard[i+4][j]][bigBoard[i+5][j]];
            shapeRecord[1][type] ++;
        }
    }
    //  沿着左下→右上棋形统计
    for (int i = BOARD_ROW - 1; i > 4; i --) {
        for (int j = 0; j < BOARD_COL - 3; j ++) {
            int type = this->chessStatus[bigBoard[i][j]][bigBoard[i-1][j+1]][bigBoard[i-2][j+2]][bigBoard[i-3][j+3]][bigBoard[i-4][j+4]][bigBoard[i-5][j+5]];
            shapeRecord[2][type] ++;
        }
    }
    //  沿着左上→右下棋形统计
    for (int i = 0; i < BOARD_ROW - 3; i ++) {
        for (int j = 0; j < BOARD_COL - 3; j ++) {
            int type = this->chessStatus[bigBoard[i][j]][bigBoard[i+1][j+1]][bigBoard[i+2][j+2]][bigBoard[i+3][j+3]][bigBoard[i+4][j+4]][bigBoard[i+5][j+5]];
            shapeRecord[3][type] ++;
        }
    }
    //  分数统计
    int score = 0;
    int count = 0;
    for (int i = 0; i < 17; i ++) {
        score += weight[i] * shapeRecord[0][i] + weight[i] * shapeRecord[1][i] + weight[i] * shapeRecord[2][i] +
                 weight[i] * shapeRecord[3][i];
        count = shapeRecord[0][i] + shapeRecord[1][i] + shapeRecord[2][i] + shapeRecord[3][i];
    }
    //qDebug()<<"score:"<<score;
    return score;
}


