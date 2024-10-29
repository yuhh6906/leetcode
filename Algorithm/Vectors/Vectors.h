//
// Created by yuhuanghua on 2023/9/7.
//
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <sstream>

#ifndef TEST_C___VECTORS_H
#define TEST_C___VECTORS_H
using namespace std;

class Vectors {
/* 28. 找出字符串中第一个匹配项的下标
 * 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。*/
    int strStr(string haystack, string needle) {
//        return haystack.find(needle);
        int m = haystack.size(), n = needle.size();
        for (int i = 0; i + n <= m; ++i) {
            bool flag = true;
            for (int j = 0; j < n; ++j) {
                if(haystack[i + j] != needle[j]){
                    flag = false;
                    break;
                }
            }
            if(flag) return i;
        }
        return -1;
    }


/* 6. Z字型变换
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
 * P   A   H   N
   A P L S I I G
   Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。*/
    string convert(string s, int numRows) {
        if(numRows < 2) return s;
        vector<string> rows(numRows);
        int i = 0, flag = -1;
        for (char c : s) {
            rows[i].push_back(c);
            if(i == 0 || i == numRows -1){
                flag = -flag;
            }
            i = i + flag;
        }
        string res;
        for (int j = 0; j < numRows; ++j) {
            res += rows[j];
        }
        return res;
    }

    /*三数之和
     * 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
     * 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。*/
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }



/*合并有序数组*/
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = 0, p2 = 0;
        int sorted[m + n];
        int cur;
        while (p1 < m || p2 < n) {
            if (p1 == m) {
                cur = nums2[p2++];
            } else if (p2 == n) {
                cur = nums1[p1++];
            } else if (nums1[p1] < nums2[p2]) {
                cur = nums1[p1++];
            } else {
                cur = nums2[p2++];
            }
            sorted[p1 + p2 - 1] = cur;
        }
        for (int i = 0; i != m + n; ++i) {
            nums1[i] = sorted[i];
        }
    }


    /*给你一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，并返回移除后数组的新长度。
     * 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。元素的顺序可以改变。
     * 你不需要考虑数组中超出新长度后面的元素。
     * 思路：双指针：右指针 right指向当前将要处理的元素，左指针 left指向下一个将要赋值的位置。*/
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for(int right = 0; right < n; ++right){
            if(nums[right] != val){
                nums[left++] = nums[right];
            }
        }
        return left;
    }

/*删除有序数组中的重复项
 * 给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次
 * ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数*/
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n == 0){
            return 0;
        }
        int fast = 1, slow = 1;
        while (fast < n){
            if(nums[fast] != nums[fast-1]){
                nums[slow] = nums[fast];//相当于往前压缩 00112 --> 012
                slow++;
            }
            fast++;
        }
        return slow;
    }


    /*删除有序数组中的重复项（2）
     * 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
     * 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。*/

    int removeDuplicates_2(vector<int>& nums) {
        int n = nums.size();
        if(n == 0 || n == 1){
            return n;
        }
        int fast = 2, slow = 2;
        while (fast < n){
            //需要检查上上个应该被保留的元素 nums[slow−2]是否和当前待检查元素 nums[fast]相同
            if(nums[fast] != nums[slow-2]){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }

    /*多数元素
     * 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。你可以假设数组是非空的，并且给定的数组总是存在多数元素。*/
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> map;
        for(int i = 0; i< n ; ++i){
            map[nums[i]] ++;
            if(map[nums[i]] > n/2){
                return nums[i];
            }
        }
        return 0;
    }

    /*轮转数组
 * 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。*/
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 0 || n == 1){
            return;
        }
        k = k % n;
        vector<int> ans(n);
        //用一个新的数组
        for(int i = 0; i < n ;++i){
            //主要理解这一步
            ans[(i + k) % n] = nums[i];
        }
        nums.assign(ans.begin(), ans.end());//将ans向量中的所有元素复制到nums向量中
    }

    /* 买卖股票的最佳时机
     * 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格
     * 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
     * 设计一个算法来计算你所能获取的最大利润返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0*/
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for(int i = 0; i< prices.size()-1; ++i){
            for(int j = i+1; j < prices.size(); ++j){
                if(prices[j] - prices[i] > 0){
                    ans = max(ans, prices[j] - prices[i]);
                }
            }
        }
        return ans;
    }
    //暴力超时 用贪心算法
    // 更新前 i天的最低价格，即最低买入成本 cost；
    //更新前 i天的最高利润 profit ，即选择「前 i−1 天最高利润 profit 」和「第 i 天卖出的最高利润 price - cost 」中的最大值 ；
    int maxProfit_2(vector<int>& prices) {
        int cost = INT_MAX;
        int profig = 0;
        for(int price : prices){
            cost = min(cost, price);//前i天 最低的价格
            profig = max(profig , price - cost);//第i天的最高首页
        }
        return profig;
    }

    /*买卖股票的最佳实际II(相比较1 可以买卖多次)
     * 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
     * 在每一天，你可以决定是否购买和/或出售股票。你在任何时候最多只能持有一股股票。你也可以先购买，然后在同一天出售。返回能获得的最大利润 。*/
        int maxProfit_3(vector<int>& prices) {
            /*动态规划
             * 定义状态 dp[i][0] 表示第 i 天交易完后手里没有股票的最大利润，dp[i][1] 表示第 i 天交易完后手里持有一支股票的最大利润（i 从 0 开始）
             * dp[i][0]=max{dp[i−1][0],dp[i−1][1]+prices[i]}
             * dp[i][1]=max{dp[i−1][1],dp[i−1][0]−prices[i]}
    。*/
            int n = prices.size();
            vector<vector<int>> dp(n, vector<int>(2));

            //初始条件:
            dp[0][0] = 0;
            dp[0][1] = -prices[0];
            for (int i = 1; i < prices.size(); ++i) {
                dp[i][0] = max(dp[i-1][0], dp[i -1][1] + prices[i]);
                dp[i][1] = max(dp[i-1][1], dp[i -1][0] - prices[i]);
            }
            return dp[n-1][0];
        }

/* 跳跃游戏：给你一个非负整数数组nums，你最初位于数组的第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。判断你是否能够到达最后一个下标，如果可以，返回 true否则，返回 false
 * 思路： 贪心算法只要存在一个位置 xxx，它本身可以到达，并且x+nums[x]≥y，那么位置 yyy 也可以到达。
 * */
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int right_remote = 0;
        for (int i = 0; i < n; ++i) {
            if(i <= right_remote){
                right_remote = max(right_remote, i + nums[i]);
                if(right_remote >= n-1){
                    return true;
                }
            }
        }
        return false;
    }

/* 跳跃游戏2：每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:返回到达 nums[n - 1] 的最小跳跃次数。
 * 思路：可以考虑最后一步跳跃前所在的位置，该位置通过跳跃能够到达最后一个位置。我们可以「贪心」地选择距离最后一个位置最远的那个位置，也就是对应下标最小的那个位置。*/
    int jump(vector<int>& nums) {
        //直观上来看，我们可以「贪心」地选择距离最后一个位置最远的那个位置，也就是对应下标最小的那个位置。因此，我们可以从左到右遍历数组，选择第一个满足要求的位置。
        //找到最后一步跳跃前所在的位置之后，我们继续贪心地寻找倒数第二步跳跃前所在的位置，以此类推，直到找到数组的开始位置。
        int position = nums.size() - 1;
        int step = 0;
        while (position > 0){
            for (int i = 0; i < position; ++i) {
                if(nums[i] + i >= position){
                    position = i;
                    step++;
                    break;
                }
            }
        }
        return step;
    }

/* 274.H指数：给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。
 * 一名科研人员的h指数:至少发表了h篇论文，并且每篇论文至少被引用h次。如果h有多种可能的值，h指数是其中最大的那个。[3,0,6,1,5]:有 3 篇论文每篇 至少 被引用了 3 次*/
    int hIndex(vector<int>& citations) {
/*如果当前 H 指数为 h 并且在遍历过程中找到当前值 citations[i]>h，则说明我们找到了一篇被引用了至少 h+1 次的论文，所以将现有的 h 值加 1。继续遍历直到 h 无法继续增大。最后返回 h 作为最终答案。*/
        sort(citations.begin(), citations.end());
        int h = 0, i = citations.size() - 1;
        while (i >=0 && citations[i] > h){
            i--;
            h++;
        }
        return h;
    }

/* 除自身以外数组的乘积：给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
 * nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。请 不要使用除法，且在 O(n) 时间复杂度内完成此题。*/
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> L(nums.size(),0);
        vector<int> R(nums.size(),0);
        vector<int> res(nums.size());
        L[0] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            L[i] = L[i-1] * nums[i-1];
        }
        R[nums.size()-1] = 1;
        for (int i = nums.size()-2; i >= 0 ; --i) {
            R[i] = nums[i+1] * R[i+1];
        }
        for (int i = 0; i < nums.size(); ++i) {
            res[i] =  L[i] * R[i];
        }
        return res;
    }


/* 加油站：在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。
 * 你从其中的一个加油站出发，开始时油箱为空。如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号（解唯一），否则返回-1。*/
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int i = 0;//表示从第i个加油站出发
        while (i < n){
            int sumOfgas = 0;
            int sumOfcost = 0;
            int cnt = 0;//表示经过了几个加油站
            while (cnt < n){
                int j = (cnt + i)%n; //j应该是表示到了第j个加油站
                sumOfcost += cost[j];
                sumOfgas += gas[j];
                if(sumOfgas < sumOfcost){
                    break;
                }
                cnt++;
            }
            if(cnt == n){
                return i;
            } else{
                i = i+cnt+1;//i到i+cnt之间都不会存在答案
            }
        }
        return -1;
    }


/* 分发糖果（困难）：n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。你需要按照以下要求，给这些孩子分发糖果：
 * 每个孩子至少分配到 1 个糖果。
 * 相邻两个孩子评分更高的孩子会获得更多的糖果。
 * 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目
 * 思路:左规则：当 ratings[i−1]<ratings[i]时，i号学生的糖果数量将比 i−1号孩子的糖果数量多。
 * 右规则：当 ratings[i]>ratings[i+1]时，i号学生的糖果数量将比 i+1号孩子的糖果数量多。
 * 遍历该数组两次，处理出每一个学生分别满足左规则或右规则时，最少需要被分得的糖果数量。每个人最终分得的糖果数量即为这两个数量的最大值。*/
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> left(n);
        left[0] = 1;
        int res = 0;
        for (int i = 1; i < n; ++i) {
            if(ratings[i] > ratings[i-1]){
                left[i] = left[i-1] + 1;
            } else{
                left[i] = 1;
            }
        }
        vector<int> right(n);
        for (int i = n-1; i >=0 ; --i) {
            if(i== n-1 && ratings[i] > ratings[i+1]){
                right[i] = right[i+1]+1;
            } else{
                right[i] = 1;
            }
            res += max(left[i], right[i]);
        }
        return res;
    }


/* 接雨水（困难）：给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * 思路1：求高度为 i 的水，首先用一个变量 temp 保存当前累积的水，初始化为 0。从左到右遍历墙的高度，遇到高度大于等于 i 的时候，开始更新 temp。
 * 更新原则是遇到高度小于 i 的就把 temp 加 1，遇到高度大于等于 i 的，就把 temp 加到最终的答案 ans 里，并且 temp 置零，然后继续循环。
*/
    int trap(vector<int>& height) {
        int maxNum = 0;
        int n = height.size();
        int sum = 0;
        for (int i = 1; i < n; ++i) {
            maxNum = max(maxNum, height[i]);
        }

        for (int i = 1; i <= maxNum; ++i) {
            int temp = 0;
            bool flag = false;
            for (int j = 0; j < n; ++j) {
                if(flag && height[j] < i){
                    temp++;
                }
                if(height[j] >= i){
                    flag = true;
                    sum += temp;
                    temp = 0;
                }
            }
        }
        return sum;
    }
/* 思路2：按列求。考虑当前列、左边最高的墙，右边最高的墙就够了。装水的多少，
 * 当然根据木桶效应，我们只需要看左边最高的墙和右边最高的墙中较矮的一个就够了。*/
    int trap_2(vector<int>& height) {
        int n = height.size();
        vector<int> left(n,0);//left[i]表示第i列左边最高的墙
        vector<int> right(n,0);
        int res = 0;
        //最两端的列不用考虑，因为一定不会有水。所以下标从 1 到 length - 2
        //找出左边最高
        for (int i = 1; i < n-1; ++i) {
            left[i] = max(left[i-1], height[i-1]);
        }
        for (int i = n-2; i > 0 ; --i) {
            right[i] = max(right[i+1], height[i+1]);
        }
        for (int i = 1; i < n-1; ++i) {
            int tmp = min(left[i], right[i]);
            if(tmp > height[i]){
                res += tmp - height[i];
            }
        }
        return res;
    }

/* 罗马数字转整数 ：罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
 当小值在大值的左边，则减小值，如 IV=5-1=4；当小值在大值的右边，则加小值，如 VI=5+1=6；*/
    int romanToInt(string s) {
        unordered_map<char, int> map = { //记下这种用法
                {'I',1},
                {'V', 5},
                {'X', 10},
                {'L', 50},
                {'C', 100},
                {'D', 500},
                {'M', 1000}
        };
        int res = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if(i < n-1 && map[s[i]] < map[s[i+1]]){
                res -= map[s[i]];
            } else{
                res += map[s[i]];
            }
        }
        return res;
    }


/* 整数转罗马数字：给你一个整数，将其转为罗马数字。
 * 例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
*/
    string intToRoman(int num) {
        const pair<int, string> valueSymbols[] = {
                {1000, "M"},
                {900,  "CM"},
                {500,  "D"},
                {400,  "CD"},
                {100,  "C"},
                {90,   "XC"},
                {50,   "L"},
                {40,   "XL"},
                {10,   "X"},
                {9,    "IX"},
                {5,    "V"},
                {4,    "IV"},
                {1,    "I"},
        };
        string res;
        int tmp = num;
        for(const auto &[value,Roman] : valueSymbols){//遍历数组
            while (tmp >= value){
                tmp -= value;
                res = res + Roman;
            }
            if(tmp == 0){
                break;
            }
        }
        return res;
    }


/* 最后一个单词的长度：给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 最后一个 单词的长度。
 * 单词是指仅由字母组成、不包含任何空格字符的最大子字符串。*/
    int lengthOfLastWord(string s) {
        istringstream  iss(s);
        string word;
        vector<string> words;
        while (iss >> word){
            words.push_back(word);
        }
        return word.size();
//fangf
        int n = s.size();
        int res = 0;
        bool flag = false;
        for (int i = n-1; i >= 0; --i) {
            if(s[i] != ' '){
                res++;
                flag = true;
            }
            if(!flag && res == 0){
                continue;
            }
            if(flag && s[i] == ' '){
                return res;
            }
        }
        return res;
    }

/* 最长公共前缀：编写一个函数来查找字符串数组中的最长公共前缀。如果不存在公共前缀，返回空字符串 ""。*/
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = strs[0];
        int n = strs.size();
        for(int i = 1; i < n; ++i) {
            prefix = longestCommonPrefix(prefix, strs[i]);
            if(!prefix.size()){
                break;
            }
        }
        return prefix;

    }
    string longestCommonPrefix(string str1, string str2){
        int minLength = min(str1.size(), str2.size());
        int i = 0;
        while (i < minLength && str1[i] == str2[i]){
            i++;
        }
        return str1.substr(0,i);
    }

/* 反转字符串中的单词*/
    string reverseWords(string s) {
        istringstream iss(s);
        string word;
        stack<string> words;
        while (iss >> word){
            words.push(word);
        }
        int n = words.size();
        string ans;
        for (int i = 0; i < n-1; ++i) {
            ans = ans + words.top() + " ";
            words.pop();
        }
        ans = ans+ words.top();
        return ans;
    }

/* 99. 最小路径和
 * 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。说明：一个机器人每次只能向下或者向右移动一步。*/
    int minPathSum(vector<vector<int>>& grid) {

        /* 动态规划：dp[i][j] : 左上角到【i,j】的最短路径
         * 状态转移方程：
         * dp[i][j] = grid[i][j] + [min(dp[i-1][j], dp[i][j-1])
         * 左/右侧：dp[i][j] = grid[i][j] + dp[i-1][j]
         * 上/下侧：dp[i][j] = grid[i][j] + dp[i][j-1]*/
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i -1][0] + grid[i][0];

        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j-1] + grid[0][j];

        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = grid[i][j]+min(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m-1][n-1];
    }


/* 螺旋矩阵
 * 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
 * 思考：
需要按照螺旋的顺序来打印，即要依次打印：上边一行、右边一列、下边一行、左边一列
主要是考虑边界问题；打印了上边一行后，打印右边一列必须得从下一个行的元素开始，不然会有重复元素；打印了右边一列之后，同理，需要从左边一列的元素开始，依次同理；
另外要考虑重复问题：在 右到左 和 下到上 时必须加上判断 top!= bottom 、left!=right ，否则会多走
 方案：
 首先设定上下左右边界
其次向右移动到最右，此时第一行因为已经使用过了，可以将其从图中删去，体现在代码中就是重新定义上边界
判断若重新定义后，上下边界交错，表明螺旋矩阵遍历结束，跳出循环，返回答案
若上下边界不交错，则遍历还未结束，接着向下向左向上移动，操作过程与第一，二步同理
不断循环以上步骤，直到某两条边界交错，跳出循环，返回答案
*/
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int m = matrix.size();
        int n = matrix[0].size();
        int u = 0, d = m-1, l = 0, r = n-1;//设置边界
        while(true){
            for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
            if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同  //注意 这里没有等号
            for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if(-- r < l) break; //重新设定有边界
            for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
            if(-- d < u) break; //重新设定下边界
            for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
            if(++ l > r) break; //重新设定左边界

        }
        return ans;
    }


 /* 连续子数组的最大乘积
  * 以dp[i] 表示以a[i]结尾的子数组的最大乘积
    但是由于有负数的存在，会导致乘法结果反转，dp[i-1]*a[i]反而成了最小值
    如果a[i]为负数，那么dp[i-1]越大，dp[i]就越小；dp[i-1]越小，dp[i]就越大
    所以我们需要同时保存最大值和最小值 maxdp[i] 、mindp[i]
    a[i] > 0时：
    maxdp[i] = max(a[i], a[i]*maxdp[i-1])
    mindp[i] = min(a[i], a[i]*mindp[i-1])
    a[i] < 0时：
    maxdp[i] = max(a[i], a[i]*mindp[i-1])
    mindp[i] = min(a[i], a[i]*maxdp[i-1])
    a[i]=0时，max和min肯定是0。
  * */
 double maxProduct(std::vector<double>& arr) {
     if(arr.empty()) return 0;
     std::vector<double> maxdp(arr.size());  //以arr[i]结尾的最大乘积
     std::vector<double> mindp(arr.size());  //以arr[i]结尾的最小乘积
     maxdp[0] = mindp[0] = arr[0];
     double max_result = arr[0];
     for(size_t i=1; i<arr.size(); i++){
         if(arr[i]>0){
             maxdp[i] = std::max(arr[i], maxdp[i-1]*arr[i]);
             mindp[i] = std::min(arr[i], mindp[i-1]*arr[i]);
         }else{
             maxdp[i] = std::max(arr[i], mindp[i-1]*arr[i]);
             mindp[i] = std::min(arr[i], maxdp[i-1]*arr[i]);
         }
         max_result = std::max(max_result, maxdp[i]);
     }
     return max_result;
 }
};


/* O(1) 时间插入、删除、和获取随机数据
 * 实现RandomizedSet 类：时间复杂度为 O(1)
 * RandomizedSet() 初始化 RandomizedSet 对象
 * bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
 * bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
 * int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
 * 思路：数组中存储元素，哈希表中存储每个元素在变长数组中的下标
*/
class RandomizedSet {
public:
    RandomizedSet() {
        //用于设置随机数种子的常见代码片段。它基于当前时间来生成一个随机数种子，以确保每次程序运行时生成的随机数序列是不同的。
        //具体地说，代码的作用是将当前时间戳转换为一个 unsigned 类型的整数，并将其作为参数传递给 srand 函数，从而设置随机数生成器的种子值。
        //请注意，此代码片段需要包含 <cstdlib> 和 <ctime> 头文件：
        srand((unsigned)time(NULL));
    }

    bool insert(int val) {
        if(map.count(val)){ //已经存在
            return false;
        }
        map[val] = vec.size();
        vec.emplace_back(val);
        return true;
    }

    bool remove(int val) {//不存在
        if(!map.count(val)){
            return false;
        }
        //在数组中 ,删除最后一个 所以需要将val的位置上过放last
        int index = map[val];//val所在vec的位置
        int last = vec.back();//vec数组最后一个值
        vec[index] = last;
        map[last] = index;
        vec.pop_back();
        map.erase(val);
        return true;
    }

    int getRandom() {
        int randomIndex = rand()%map.size();
        return vec[randomIndex];
    }

private:
    unordered_map<int, int> map;//key存储值  value存储位置
    vector<int> vec;
};



#endif //TEST_C___VECTORS_H
