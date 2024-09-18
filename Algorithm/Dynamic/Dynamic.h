//
// Created by yuhuanghua on 2023/11/13.
//
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#ifndef C__DYNAMIC_H
#define C__DYNAMIC_H
using namespace std;

class Dynamic {

};
/*一维动态规划*/
class Onedimensiona_Dynamic{
/* 70.爬楼梯。 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢
 *  f(x)=f(x-1)+f(x-2)
 */
    int climbStairs(int n) {
        vector<int> ans(n+1);
        ans[0] = 1;
        ans[1] = 1;
        if(n <= 1){
            return ans[n];
        }
        if(n > 1){
            for (int i = 2; i <= n; ++i) {
                ans[i] = ans[i-1]+ans[i-2];
            }
        }
        return ans[n];
    }


/* 198.打家劫舍
 * 一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
 *
 * 思路：1、偷窃第k间房屋，那么就不能偷窃第k−1间房屋，偷窃总金额为前k−2间房屋的最高总金额与第k间房屋的金额之和。2、不偷窃第k间房屋，偷窃总金额为前 k−1间房屋的最高总金额。
*/
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size == 1){
            return nums[0];
        }
        vector<int> dp = vector<int>(size,0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < size; ++i) {
            dp[i] = max(nums[i] + dp[i-2],dp[i-1]);
        }
        return dp[size-1];
    }

/* 139.单词拆分：
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
 * 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。*/
    bool wordBreak(string s, vector<string>& wordDict) {
/* dp[i] 表示字符串 s 前 i 个字符组成的字符串 s[0..i−1] 是否能被空格拆分成若干个字典中出现的单词
 * 思路：dp[i]=dp[j] && check(s[j..i−1])  其中 check(s[j..i−1]) 表示子串 s[j..i−1] 是否出现在字典中。*/

        auto word_set = unordered_set <string> ();
        for(auto word : wordDict){
            word_set.insert(word);
        }
        auto dp = vector<bool> (s.size() +1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if(dp[j] && word_set.find(s.substr(j,i-j)) != word_set.end()){// dp[j]为true并(j,i-1)出现在字典中
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
/* 322.零钱兑换
 * 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 * 你可以认为每种硬币的数量是无限的。 */
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;//dp[x] = y : 凑成x的最小硬币数量为y
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) { //硬币面值要小于凑成的数i
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);//F(3)=min(F(3−1),F(3−2),F(3−5))+1=2
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
/* 寻找两个正序数组中的中位数
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 * 算法的时间复杂度应该为 O(log (m+n)) 。*/
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
/* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
         * 这里的 "/" 表示整除
         * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
         * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
         * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
         * 这样 pivot 本身最大也只能是第 k-1 小的元素
         * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
         * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
         * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
         */
        int total = nums2.size() + nums1.size();
        int ans = 0;
        if(total % 2 == 1){
            ans = getKthElement(nums1, nums2, (total/2+1));
        } else{
            ans = (getKthElement(nums1, nums2, total/2)+getKthElement(nums1, nums2, (total/2+1)))/2;
        }
        return ans;
    }
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;//起始位置z
        while (true){
            // 边界
            if(index1 == m){
                return nums2[index2 + k -1];
            }
            if(index2 == n){
                return nums1[index1 + k -1];
            }
            if(k == 1){
                return min(nums1[index1], nums2[index2]);
            }
            int newIndex1 = min(index1 + k/2 -1, m-1);//中位数下标，需要加上偏移量
            int newIndex2 = min(index2 + k/2 -1, n-1);
            int pivot1 = nums1[newIndex1];//中位数
            int pivot2 = nums2[newIndex2];

            if(pivot1 <= pivot2){
                k = k - newIndex1 + 1 +index1;
                index1 = newIndex1 + 1;
            } else{
                k = k - newIndex2 +1 + index2;
                index2 = newIndex2 + 1;
            }
        }
    }


/* 300. 最长递增子序列
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列
 */
    int lengthOfLIS(vector<int>& nums) {
        /* dp[i] 以第i个数字结尾的最长上升子序列的长度
         * dp[i]=max(dp[j])+1,其中0≤j<i且num[j]<num[i] */
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> dp = vector<int>(n ,0);

        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if(nums[i] > nums[j]) {
                    dp[i] = max(dp[j]+1, dp[i]);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
class Multidimensional {
/* 64.最小路径和：
 * 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。*/
    int minPathSum(vector <vector<int>> &grid) {
        /*f(m,n) = min(f(m-1,n),f(m,n-1))+grid[m][n]*/
        int m = grid.size();
        int n = grid[0].size();
        if (m == 0 || n == 0) {
            return 0;
        }
        auto dp = vector < vector < int >> (m, vector<int>(n));//vector<vector<int>> arr(m, vector<int>(n,0);
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        int ans = dp[m - 1][n - 1];
        return ans;
    }


/* 120、三角形最小路径和
 * 给定一个三角形 triangle ，找出自顶向下的最小路径和。
 * 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
 * 也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。*/
    int minimumTotal(vector <vector<int>> &triangle) {
        //状态转移方程： f(i,j) = min(f(i-1,j-1), f(i-1,j)) + triangle(i,j)
        //边界第一列和最后一列
        int m = triangle.size();
        vector <vector<int>> f(m, vector<int>(m));//auto f = vector<vector<int>> (n,vector<int>(n))
        f[0][0] = triangle[0][0];
        for (int i = 1; i < m; ++i) {
            f[i][0] = f[i - 1][0] + triangle[i][0];
            for (int j = 1; j < i; ++j) {
                f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
            }
            f[i][i] = f[i - 1][i - 1] + triangle[i][i];
        }
        int minnum = INT_MAX;
        for (int i = 0; i < m; ++i) {
            minnum = min(minnum, f[m - 1][i]);
        }
        return minnum;

        //return *min_element(f[n - 1].begin(), f[n - 1].end());

    }

/* 97. 交错字符串
 * 给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干非空子字符串*/
    bool isInterleave(string s1, string s2, string s3) {
        //定义 f(i,j) 表示 s的前 i 个元素和 s的前 j 个元素是否能交错组成 s的前 i+j 个元素
        //f(i,j)=[f(i−1,j)ands(i−1)=s(p)] or [f(i,j−1)ands(j−1)=s(p)]
        int m = s1.size();
        int n = s2.size();
        int t = s3.size();
        auto f = vector < vector < int >> (m + 1, vector<int>(n + 1));
        f[0][0] = true;
        if (m + n != t) {
            return false;
        }

        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                int p = i + j - 1;
                if (i > 0) {
                    f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
                }
                if (j > 0) {
                    f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
                }
            }
        }
        return f[m][n];
    }

/* 63.不同路径||
 *  一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
 *  现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？网格中的障碍物和空位置分别用 1 和 0 来表示。*/

    int uniquePathsWithObstacles(vector <vector<int>> &obstacleGrid) {
        //dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        //i = 0; dp[i][j] = dp[0][j - 1]
        //j = 0; dp[i][j] = dp[i - 1][j]
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        auto dp = vector < vector < int >> (m, vector<int>(n, 0));
        dp[0][0] = 1;
        if (obstacleGrid[0][0] == 1) return 0;
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] != 1) {
                dp[i][0] = dp[i - 1][0];
            } else {
                break;
            }
        }
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] != 1) {
                dp[0][j] = dp[0][j - 1];
            } else {
                break;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] != 1) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }

/* 221 最大正方形;
 * 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。*/
    int maximalSquare(vector<vector<char>>& matrix) {
        /*用 dp(i,j) 表示以 (i,j) 为右下角，且只包含 1 的正方形的边长最大值
            * dp(i,j)=min(dp(i−1,j),dp(i−1,j−1),dp(i,j−1))+1*/
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return 0;
        }
        int maxSide = 0;
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(columns));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        int maxSquare = maxSide * maxSide;
        return maxSquare;
    }

/* 5.最长回文子串
 * 给你一个字符串 s，找到 s 中最长的回文子串
。*/
    string longestPalindrome(string s) {
        /* 用 P(i,j) 表示字符串 s 的第 i 到 j 个字母组成的串（下文表示成 s[i:j]）是否为回文串：
         * 状态转移方程   P(i,j)=P(i+1,j−1)∧(Si==Sj) */
        int n = s.size();
        if(n < 2){
            return s;
        }
        int max = 1;//之所以不等0 是因为单个字符也算作回文串
        auto dp = vector<vector<int>> (n, vector<int>(n));//用dp[i][j] 表示第 i 到 j 个字母组成是否是回文串
        int begin = 0;

        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        for (int L = 2; L <= n ; ++L) {
            //枚举左边界
            for (int i = 0; i < n; ++i) {
                int j = i + L - 1;
                //边界值
                if(j >= n){
                    break;
                }
                if(s[i] != s[j]){
                    dp[i][j] = false;
                } else{
                    //间隔为1 ：0 1 间隔为2：0 1 2  间隔为3：0 1 2 3
                    if(j - i < 3){
                        dp[i][j] = true;
                    } else{
                        dp[i][j] = dp[i+1][j-1];
                    }
                }
                if(dp[i][j] && j - i +1 > max){
                    max = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, max);
    }
/* 72. 编辑距离
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数 你可以对一个单词进行如下三种操作：
 * 插入一个字符、删除一个字符、替换一个字符*/
    int minDistance(string word1, string word2) {

    }

/* 188. 买卖股票的最佳时机 4
 * 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。*/
    int maxProfit(int k, vector<int>& prices) {
        /* 用 buy[i][j] 表示对于数组 prices[0..i] 中的价格而言，进行恰好 j 笔交易，并且当前手上持有一支股票，这种情况下的最大利润；
         * 用 sell[i][j] 表示恰好进行 j 笔交易，并且当前手上不持有股票，这种情况下的最大利润。
         * 状态转移方程”
         * buy[i][j]=max{buy[i−1][j],sell[i−1][j]−price[i]}
         * 当前手上持有的股票是否是在第 i 天买入的。如果是第 i 天买入的，那么在第 i−1 天时，我们手上不持有股票，对应状态 sell[i−1][j]，并且需要扣除 prices[i] 的买入花费；如果不是第 i 天买入的，那么在第 i−1 天时，我们手上持有股票，对应状态 buy[i−1][j]
         * sell[i][j]=max{sell[i−1][j],buy[i−1][j−1]+price[i]}
        */
        if(prices.empty()) return 0;
        int n = prices.size();
        k = min(k, n/2);
        auto buy = vector<vector<int>>(n, vector<int>(k+1));
        auto sell = vector<vector<int>>(n, vector<int>(k+1));
        buy[0][0] = -prices[0];
        sell[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {

            }
        }
    }
}





#endif //C__DYNAMIC_H
