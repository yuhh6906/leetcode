//
// Created by yuhuanghua on 2024/10/18.
//

#ifndef LEETCODE_LOOKBACK_H
#define LEETCODE_LOOKBACK_H


class Lookback {

};
class Solution {
/*
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 * 输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]*/
    vector<string>  letterCombinations(string digits) {
        unorder_map<char, string> hash_map = {
                {'2', "abc"},
                {'3', "def"},
                {'4', "ghi"},
                {'5', "jkl"},
                {'6', "mno"},
                {'7', "pqrs"},
                {'8', "tuv"},
                {'9', "wxyz"}
        };
        vector<string> ans;
        if(digits.empty()) return ans;

        string combination;
        backtrack(ans, hash_map, digits, 0, )
        return ans;
    }
    void backtrack(vector<string>& ans, unordered_map<char, string>& hash_map, const string digits, int index, string& combination){
        if(index == digits.length()) ans.push_back(combination);
        char ch = digits[index];
        string letters = hashmap.at(ch);
        for(char& c : letter){
            combination.push_back(c);
            backtrack(ans, hash_map, digits, index+1, combination);
            combination.pop();

        }
    }


/*77. 组合 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。你可以按 任何顺序 返回答案*/
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> vec;
        backtrack_2(ans, 1, k, n, vec);
        return ans;
    }
    void backtrack_2(vector<vector<int>>& ans, int cur, int k, int n, vector<int>& vec){  //cur是在[1,n]的指针  vec是ans的每一行(123 234 124 这样)
        // 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
        if (vec.size() + (n - cur + 1) < k) {
            return;
        }
        if(vec.size() == k) {
            ans.push_back(vec);
            return;
        }

        //选择当前的位置
        vec.push_back(cur);
        backtrack_2(ans, cur+1, k, n, vec);
        //不选择当前的位置
        vec.pop_back();
        backtrack_2(ans, cur+1, k, n, vec);
    }


/* 46.   给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 * [1,2,3]    输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]*/
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        dfs(nums, ans, 0, nums.size());
        return ans;
    }
    /*填到第 first 个位置，那么 nums 数组中 [0,first−1] 是已填过的数的集合，[first,n−1] 是待填的数的集合。
     * 我们肯定是尝试用 [first,n−1] 里的数去填第 first 个数，假设待填的数的下标为 i，那么填完以后我们将第 i 个数和第 first 个数交换，
     * 即能使得在填第 first+1 个数的时候 nums 数组的 [0,first] 部分为已填过的数，[first+1,n−1] 为待填的数，回溯的时候交换回来即能完成撤销操作。
*/
    void dfs(vector<int>& nums, vector<vector<int>>& ans, int index, int length){//index表示需要填第index个数
        //感觉只能死记硬背
        if(index == length){
            ans.push_back(nums);
            return;
        }

        for (int i = index; i < length; ++i) {//注意是从index-length
            // 动态维护数组
            swap(nums[i], nums[index]);
            // 继续递归填下一个数
            dfs(nums, ans, index+1, length);
            // 撤销操作
            swap(nums[i], nums[index]);
        }
    }

/* 39. 组合总和
 * 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
 * candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 * 对于给定的输入，保证和为 target 的不同组合数少于 150 个。*/
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> vec;
        dfs_combinationSum(candidates, target, ans, vec, 0);
        return ans;
    }
    void dfs_combinationSum(vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& vec, int index){
        /*dfs(target,combine,idx) 表示当前在 candidates 数组的第 idx 位，还剩 target 要组合，已经组合的列表为 combine。
         * 递归的终止条件为 target≤0 或者 candidates 数组被全部用完。
         * 那么在当前的函数中，每次我们可以选择跳过不用第 idx 个数，即执行 dfs(target,combine,idx+1)。
         * 也可以选择使用第 idx 个数，即执行 dfs(target−candidates[idx],combine,idx)，注意到每个数字可以被无限制重复选取，因此搜索的下标仍为 idx。
        */

        if(target == 0){
            ans.push_back(vec);
            return;
        }
        if (index == candidates.size()) {
            return;
        }

        //1. 不选择当前index值
        dfs_combinationSum(candidates, target, ans, vec, index+1);

        //2. 选择当前index值
        if(target - candidates[index] >= 0){
            vec.push_back(candidates[index]);
            dfs_combinationSum(candidates, target - candidates[index] , ans, vec, index);
            vec.pop_back();//返回到原有的状态继续执行
        }
    }



 /* 22. 括号生成：
  * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。*/
    vector<string> generateParenthesis(int n) {
        //思路1: 暴力 遍历所有可能，再判断有效性
        //思路2: 动态规划  如果左括号数量不大于 n，我们可以放一个左括号。如果右括号数量小于左括号的数量，我们可以放一个右括号。
        vector<string> ans;
        string cur;
//        generate_all(ans, n * 2, cur);
        backtrack_generateParenthesis(ans, cur, 0, 0, n);
        return ans;
    }
    void backtrack_generateParenthesis(vector<string>& ans, string& cur, int open, int close, int n) {
        //open 左括号个数 close 右括号个数 n: 括号的个数
        if(cur.size() == n*2){
            ans.push_back(cur);
            return;
        }
        if(open < n){
            cur.push_back('(');
            backtrack_generateParenthesis(ans, cur, open+1, close, n);
            cur.pop_back();
        }
        if(close < open){
            cur.push_back(')');
            backtrack_generateParenthesis(ans, cur, open, close+1, n);
            cur.pop_back();
        }

    }
    bool valid(string str){
        int balance = 0;
        for(char ch : str){
            if(ch == '('){
                balance++;
            }
            if(ch == ')'){
                balance--;
            }
            if(balance < 0){
                return false;
            }
        }
        return balance==0;
    }
    void generate_all(vector<string>& ans, int n, string& cur){
        //n:左右括号的个数 cur:可能的情况
        if(cur.size() == n){
            if(valid(cur)){
                ans.push_back(cur);
            }
        }

        cur += '(';
        generate_all(ans, n, cur);
        cur.pop_back();
        cur += ')';
        generate_all(ans, n, cur);
        cur.pop_back();
    }



/* 79. 单词搜索
 * 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。*/
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(backtrack_exist(i, j, 0, board, word)){
                    return true;
                }
            }
        }
        return false;
    }

    bool backtrack_exist(int x, int y, int k, vector<vector<char>>& board, string word){
        //x y 是board的坐标 k是指word的第k个字符
        int m = board.size();
        int n = board[0].size();
        if(x >= m || x < 0 || y >= n || y < 0) return false;
        if(board[x][y] != word[k]) return false;
        if(k == word.size() -1) return true;
        board[x][y] = '\0';//表示已经访问过
        int res = (backtrack_exist(x+1,y,k+1, board, word) || backtrack_exist(x-1,y,k+1, board, word) || backtrack_exist(x,y+1,k+1, board, word) || backtrack_exist(x,y-1,k+1, board, word));
        board[x][y] = word[k];
        return res;
    }


};

#endif //LEETCODE_LOOKBACK_H
