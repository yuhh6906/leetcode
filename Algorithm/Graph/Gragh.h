//
// Created by yuhuanghua on 2023/10/20.
//

#ifndef C__GRAGH_H
#define C__GRAGH_H
#include <string>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;


class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Gragh {

public:
/* 419. 棋盘上的战舰
 * 给你一个大小为 m x n 的矩阵 board 表示棋盘，其中，每个单元格可以是一艘战舰 'X' 或者是一个空位 '.' ，返回在棋盘 board 上放置的 舰队 的数量。
   舰队只能水平或者垂直放置在 board 上。换句话说，舰队只能按 1 x k（1 行，k 列）或 k x 1（k 行，1 列）的形状放置，其中 k 可以是任意大小。
 两个舰队之间至少有一个水平或垂直的空格分隔 （即没有相邻的舰队）。*/
    int countBattleships(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        int ans = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X'){
                    board[i][j] = '.';
                    for (int k = j + 1; k < n && board[i][k] == 'X'; ++k) {
                        board[i][k] = '.';
                    }
                    for (int k = i + 1; k < m && board[k][j] == 'X'; ++k) {
                        board[k][j] = '.';
                    }
                    ans++;
                }
            }
        }
        return ans;
    }


    void dfs_numIslands(vector<vector<char>>& grid, int r, int c) {
        int nr = grid.size();
        int nc = grid[0].size();

        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r-1][c] == '1') dfs_numIslands(grid, r - 1, c);
        if (r + 1 < nr && grid[r+1][c] == '1') dfs_numIslands(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c-1] == '1') dfs_numIslands(grid, r, c - 1);
        if (c + 1 < nc && grid[r][c+1] == '1') dfs_numIslands(grid, r, c + 1);
    }
/* 200.岛屿数量
 * 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。此外，你可以假设该网格的四条边均被水包围。*/
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    dfs_numIslands(grid, r, c);
                }
            }
        }
        return num_islands;
    }

/* 130.被围绕的区域
 * 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
 * 思路：对于每一个边界上的 O，我们以它为起点，标记所有与它直接或间接相连的字母O*/
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; ++i) {
            dfs_solve(board, i, 0);
            dfs_solve(board, i, n-1);
        }
        for (int j = 1; j < n-1; ++j) {
            dfs_solve(board, 0, j);
            dfs_solve(board, m-1, j);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(board[i][j] == 'A'){
                    board[i][j] == '0';
                } else if(board[i][j] == 'O'){
                    board[i][j] == 'X';
                }
            }
        }
    }

    void dfs_solve(vector<vector<char>>& board, int x, int y){
        int m = board.size();
        int n = board[0].size();
        if(x < 0 || x >= m || y < 0 || y >= n){
            return;
        }
        if(board[x][y] == 'O'){
            board[x][y] = 'A';//把这些不被包括的置为‘A’
            dfs_solve(board, x-1, y);
            dfs_solve(board, x+1, y);
            dfs_solve(board, x, y+1);
            dfs_solve(board, x, y-1);
        }
    }

/* 133.克隆图
 * 给你无向连通图中一个节点的引用，请你返回该图的 深拷贝（克隆）。图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。
 * 思路：
 * 1、使用一个哈希表存储所有已被访问和克隆的节点。哈希表中的 key 是原始图中的节点，value 是克隆图中的对应节点。
 * 2、从给定节点开始遍历图。如果某个节点已经被访问过，则返回其克隆图中的对应节点。
 * 3、如果当前访问的节点不在哈希表中，则创建它的克隆节点并存储在哈希表中。
 * 4、递归调用每个节点的邻接点。每个节点递归调用的次数等于邻接点的数量，每一次调用返回其对应邻接点的克隆节点，最终返回这些克隆邻接点的列表，将其放入对应克隆节点的邻接表中。这样就可以克隆给定的节点和其邻接点。
*/
    unordered_map<Node*, Node*> visited;
    Node* cloneGraph(Node* node) {
        if(node == nullptr){
            return node;
        }
        //如果该节点已经被访问过了
        if(visited.find(node) != visited.end()){
            return visited[node];
        }
        //克隆节点
        Node* cloneNode = new Node(node->val);
        visited[node] = cloneNode;
        //克隆node 的邻居
        for(auto& neigh : node->neighbors){
            cloneNode->neighbors.emplace_back(cloneGraph(neigh));
        }
        return cloneNode;
    }


/* */
};


#endif //C__GRAGH_H
