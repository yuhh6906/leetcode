//
// Created by yuhuanghua on 2023/9/18.
//
#include <vector>
#include <string.h>
#ifndef C__MATRIX_H
#define C__MATRIX_H
using namespace std;

class Matrix {
/* 有效的数独
 * 请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。
    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
    rows[i][index]、columns[j][index] 和 subboxes[i/3⌋][j/3⌋][index]分别表示数独的第 i 行第 j列的单元格所在的行、列和小九宫格中，数字index+1出现的次数
    */
public:
    bool isValidSudoku(vector<vector<char>>& board) {
/*
       vector<vector<int>> rows(9, vector<int>(9));
        vector<vector<int>> columns(9, vector<int>(9));
        vector<vector<vector<int>>> subbox(3,vector<vector<int>>(3,vector<int>(9)));*/
        int rows[9][9];
        int columns[9][9];
        int subboxes[3][3][9];

        memset(rows,0,sizeof(rows));
        memset(columns,0,sizeof(columns));
        memset(subboxes,0,sizeof(subboxes));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c != '.') {
                    int index = c - '0' - 1;
                    rows[i][index]++;
                    columns[j][index]++;
                    subboxes[i / 3][j / 3][index]++;
                    if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / 3][j / 3][index] > 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    /*螺旋矩阵
     * 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。*/
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if(matrix.empty()) return ans; //若数组为空，直接返回答案
        int u = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;
        while(true)
        {
            for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
            if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if(-- r < l) break; //重新设定有边界
            for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
            if(-- d < u) break; //重新设定下边界
            for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
            if(++ l > r) break; //重新设定左边界
        }
        return ans;
    }
    /*旋转图像
     * 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
     * 你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
     * 解析：
     * matrix_new[col][n−row−1]=matrix[row][col]*/
    void rotate(vector<vector<int>>& matrix) {
        auto matrix_new = matrix;
        int n = matrix.size();
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                matrix_new[j][n-i-1] = matrix[i][j];
            }
        }
        matrix = matrix_new;
    }
    /* 矩阵置零
     * 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。*/
    void setZeroes(vector<vector<int>>& matrix) {
        bool row0_flag = false;
        bool col0_flag = false;
        int m = matrix.size();
        int n = matrix[0].size();
        //先用flag标记第一行第一列是否有0
        for(int i = 0; i < n; ++i){
            if(matrix[0][i] == 0){
                row0_flag = true;
            }
        }
        for (int i = 0; i < m; ++i) {
            if(matrix[i][0] == 0){
                col0_flag = true;
            }
        }
        //从第二行第二列开始遍历
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if(matrix[i][j] == 0){
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if(matrix[0][j] == 0 || matrix[i][0] == 0){
                    matrix[i][j] = 0;
                }
            }
        }
        if(row0_flag){
            for (int i = 0; i < n; ++i) {
                matrix[0][i] = 0;
            }
        }
        if (col0_flag){
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
    /*生命游戏
     * 给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态： 1 即为 活细胞 （live），或 0 即为 死细胞 （dead）。
     * 每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
    如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
    如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
    如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
    如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
     下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。给你 m x n 网格面板 board 的当前状态，返回下一个状态。*/
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int neighbors[3] = {-1 , 0 , 1};
        auto copy_board = board;
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                int lived = 0;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        //排除[0,0]这种情况
                        if(!(neighbors[i] == 0 && neighbors[j] == 0)){
                            int r = row + neighbors[i];
                            int c = col + neighbors[j];
                            //注意这里是copy_board
                            if((r < m && r >= 0) && (c < n && c >=0) && (copy_board[r][c] == 1)){
                                lived++;
                            }
                        }
                    }
                }
                //规则1 规则3
                // 注意这里是copy_board
                if((copy_board[row][col] == 1) && (lived < 2 || lived > 3)){
                    board[row][col] = 0;
                }
                if((copy_board[row][col] == 0) && lived == 3){
                    board[row][col] = 1;
                }
            }
        }
    }
};

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int neighbors[3] = {0, 1, -1};

        int rows = board.size();
        int cols = board[0].size();

        // 创建复制数组 copyBoard
        vector<vector<int> >copyBoard(rows, vector<int>(cols, 0));

        // 从原数组复制一份到 copyBoard 中
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                copyBoard[row][col] = board[row][col];
            }
        }

        // 遍历面板每一个格子里的细胞
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {

                // 对于每一个细胞统计其八个相邻位置里的活细胞数量
                int liveNeighbors = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {

                        if (!(neighbors[i] == 0 && neighbors[j] == 0)) {
                            int r = (row + neighbors[i]);
                            int c = (col + neighbors[j]);

                            // 查看相邻的细胞是否是活细胞
                            if ((r < rows && r >= 0) && (c < cols && c >= 0) && (copyBoard[r][c] == 1)) {
                                liveNeighbors += 1;
                            }
                        }
                    }
                }

                // 规则 1 或规则 3
                if ((copyBoard[row][col] == 1) && (liveNeighbors < 2 || liveNeighbors > 3)) {
                    board[row][col] = 0;
                }
                // 规则 4
                if (copyBoard[row][col] == 0 && liveNeighbors == 3) {
                    board[row][col] = 1;
                }
            }
        }
    }
};

#endif //C__MATRIX_H
