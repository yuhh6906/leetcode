//
// Created by yuhuanghua on 2023/10/20.
//

#ifndef C__GRAGH_H
#define C__GRAGH_H
#include <string>
#include <vector>
#include <queue>
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
    void dfs_numIslands(vector<vector<char>>& grid, int r, int c) {
        int nr = grid.size();
        int nc = grid[0].size();

        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r-1][c] == '1') dfs_numIslands(grid, r - 1, c);
        if (r + 1 < nr && grid[r+1][c] == '1') dfs_numIslands(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c-1] == '1') dfs_numIslands(grid, r, c - 1);
        if (c + 1 < nc && grid[r][c+1] == '1') dfs_numIslands(grid, r, c + 1);
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



/* 207. 课程表
 * 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。在选修某些课程之前需要一些先修课程。
 * 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
    请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false */
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
/*给定的先修课程关系可以看作是一个有向图，其中每个节点代表一门课程，每条边表示一门课程是另一门课程的先修课程。如果这个图中存在环，则意味着某门课程间接地是自己的先修课程，因此无法完成所有课程的学习。
 * 我们可以使用深度优先搜索（DFS）来检测图中的环。具体来说，我们维护一个颜色标记数组 visited 来跟踪每个节点的状态：
 * 0 表示节点尚未被访问；
 * 1 表示节点正在被访问（即在当前递归调用栈中）；
 * 2 表示节点已被完全访问过（即没有环包含此节点）。
    */
        unordered_map<int, vector<int>> graph;
        for(auto& p : prerequisites){
            graph[p[1]].push_back(p[0]);  //[i,j[]] 维护的是第i门课程后续可以学j[]门课程
        }

        vector<int> visted(numCourses,0);
        for (int i = 0; i < numCourses; ++i) {
            if(!dfs_canFinish(visted, graph, i)){
                return false;
            }
        }
        return true;
    }
    bool dfs_canFinish(vector<int>& visted, unordered_map<int, vector<int>>& graph, int Course){
        if(visted[Course] == 2){
            return true;
        }
        if(visted[Course] == 1){
            return false;
        }
        
        visted[Course] = 1;
        for(int next : graph[Course]){
            if(!dfs_canFinish(visted, graph, next)){
                return false;
            }
        }
        visted[Course] = 2;
        return true;
    }


/*  210课程表2:
 * 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。
 * 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组   */
/*拓扑排序步骤如下：
（1）定义一个队列Q，并把所有入度为0的结点加入队列
（2）取队首结点，访问输出，然后删除所有从它出发的边，并令这些边到达的顶点的入度减1，如果某个顶点的入度减为0，则将其加入队列。
（3）重复进行（2）操作，直到队列为空。如果队列为空时入过队的结点数恰好为N，说明拓扑排序成功，图G为有向无环图；否则，拓扑排序失败，图G有环。*/
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        queue<int> queue;
        vector<int> indegress(numCourses, 0);
        // 遍历所有的依赖关系，填充图和入度向量
        vector<vector<int>> graph(numCourses);
        for(auto& p : prerequisites){
            graph[p[1]].push_back(p[0]);
            indegress[p[0]]++;
        }
        for (int i = 0; i < numCourses; ++i) {
            if(indegress[i] == 0) queue.push(i);
        }
        vector<int> ans;
        while(!queue.empty()){
            int course = queue.front();
            queue.pop();
            ans.push_back(course);
            for(auto next: graph[course]){
                indegress[next]--;
                if(indegrees[next] == 0){
                    queue.push(next);
                }
            }
        }
        if(ans.size() == numCourses){
            return ans;
        }else{
            return vector<int>();
        }
    }

/* 433. 最小基因变化
 * 基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一。
 * 假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。
 * 例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化。
 * 另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。（变化后的基因必须位于基因库 bank 中）
 * 给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1 。
 * 注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中。*/
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        /* 排除边界条件：start 或 end 空或 bank 为空或 end 不在 bank 中。
         * bfs 的初始化工作：初始化步长，初始化 queue，将 start 入队列，用 visit 来标记已经访问过的点。
         * 进行 bfs：先将步长+1，然后确定每次 bfs 的长度 size，寻找目标基因，然后入队出队等操作。
         */
        // 1：判断极端情况
        if(start.empty()||end.empty()||bank.empty())return -1;
        if(find(bank.begin(),bank.end(),end)==bank.end())return -1;// 目标基因不在基因库中

        // 2：bfs的初始化工作
        vector<int> visit(bank.size(),0);
        int step=0;
        queue<string> q;
        q.push(start);

        // 3：进行bfs
        while(!q.empty()){
            step++;
            int n=q.size();// 确定每次bfs的宽度
            for(int i=0;i<n;++i){
                string temp=q.front();q.pop();// 这里获得队头元素不要用引用，至于具体原因可以参考评论区链接
                for(int j=0;j<bank.size();++j){// 遍历整个基因库，访问未标记的基因；找到某个字符变异的基因添加标记，并进入队列即可
                    if(visit[j]==0){
                        int diff=0;
                        for(int k=0;k<temp.size();++k){
                            if(temp[k]!=bank[j][k])diff++;
                        }
                        if(diff==1){// 找到某个字符编译的基因
                            if(bank[j]==end)return step;// 若该下标j代表的基因为目标基因，则直接返回步长
                            visit[j]=1;// 标记下标为j的基因已访问
                            q.push(bank[j]);
                        }
                    }
                }
            }
        }
        return -1;
    }



/* 399. 除法求值
 * 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
 * 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
 * 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
 * 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
 * 注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。*/
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        //1. 构建有向图 2. 广度优先搜索
        int n = equations.size();
        // 第 1 步：预处理，将变量的值与 id 进行映射[string,string]-->value
        unordered_map<string, unordered_map<string, double>> graph;  //类似与二维数组 不过坐标是string
        for (int i = 0; i < n; ++i) {
            string u = equations[i][0];
            string v = equations[i][1];
            double value = values[i];
            graph[u][v] = value;
            graph[v][u] = 1.0/value;
        }
        int m = queries.size();
        vector<double> ans(m, -1.0);
        for (int i = 0; i < m; ++i) {  //逐个找答案
            string start = queries[i][0];
            string target = queries[i][1];
            if(!graph.count(start) || !graph.count[target]){
                continue;//变量不存在 返回-1
            }
            if(start == target) {
                ans[i] = 1.0;
                continue;
            }

            //广度优先搜索
            queue<unordered_map<string, double>> q;
            q.push({start, -1.0});
            while(!q.empty()){
                auto pair = q.pop();
                string curr = pair.first;
                double currVal = pair.second;
                if(curr == start){
                    ans[i] = currVal;
                    break;
                }

                for(auto& )
            }
        }
    }
};


class Gragh_2{
public:
/* 909. 蛇梯棋 给你一个大小为 n x n 的整数矩阵 board ，方格按从 1 到 n2 编号，编号遵循 转行交替方式 ，从左下角开始 （即，从 board[n - 1][0] 开始）的每一行改变方向。
 *
   你一开始位于棋盘上的方格  1。每一回合，玩家需要从当前方格 curr 开始出发，按下述要求前进：
   选定目标方格 next ，目标方格的编号在范围 [curr + 1, min(curr + 6, n2)] 。
   传送玩家：如果目标方格 next 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 next 。
   当玩家到达编号 n2 的方格时，游戏结束。
   如果 board[r][c] != -1 ，位于 r 行 c 列的棋盘格中可能存在 “蛇” 或 “梯子”。那个蛇或梯子的目的地将会是 board[r][c]。编号为 1 和 n2 的方格不是任何蛇或梯子的起点。
   注意，玩家在每回合的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，玩家也 不能 继续移动。
*/
    int snakesAndLadders(vector<vector<int>>& board) {
        /* 广度优先搜索
         * 用一个队列来存储搜索状态，初始时将起点状态 (1,0) 加入队列，表示当前位于起点 1，移动次数为 0。
         * 然后不断取出队首，每次取出队首元素时扩展新状态，即遍历该节点的出边，若出边对应节点未被访问，则将该节点和移动次数加一的结果作为新状态，加入队列。如此循环直至到达终点或队列为空。*/
        queue<pair<int, int>> q;
        int n = board.size();
        vector<bool> vis(n*n+1);
        q.push(make_pair(1, 0));
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            for (int i = 0; i < 6; ++i) {
                int nxtd = p.first + i;
                if(nxtd > n * n){
                    break;
                }
                auto rc = index2rc(nxtd, n);
                if(board[rc.first][rc.second] != -1){// 存在蛇或梯子
                    nxtd = board[rc.first][rc.second];
                }
                if (nxtd == n * n) { // 到达终点
                    return p.second + 1;
                }
                if(!vis[nxtd]){
                    vis[nxtd] = true;
                    q.push(make_pair(nxtd, p.second+1));
                }
            }
        }
        return -1;
    }

    pair<int, int> index2rc(int index, int n){
        int r = (index - 1) / n;
        int c = (index - 1) % n;
        if(r % 2 == 1){
            c = n - c - 1;
        }
        return {n - 1 - r, c};
    }
};

#endif //C__GRAGH_H
