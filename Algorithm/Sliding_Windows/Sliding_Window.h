//
// Created by yuhuanghua on 2023/8/29.
//
#include <vector>
#include <climits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#ifndef TEST_C___SLIDING_WINDOW_H
#define TEST_C___SLIDING_WINDOW_H
using namespace std;



class Section {
public:

/* 用最少数量的箭引爆气球
 * 有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。
 * 你不知道气球的确切 y 坐标。一支弓箭可以沿着 x 轴从不同点完全垂直地射出。
 * 在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆.
 * 给你一个数组 points ，返回引爆所有气球所必须射出的 最小弓箭数
 *输入：points = [[10,16],[2,8],[1,6],[7,12]]     输出：2
    解释：气球可以用2支箭来爆破:
    -在x = 6处射出箭，击破气球[2,8]和[1,6]。
    -在x = 11处发射箭，击破气球[10,16]和[7,12]
*/
    int findMinArrowShots(vector <vector<int>> &points) {
        //排序加贪心
        if (points.empty()) {
            return 0;
        }
        sort(points.begin(), points.end(), [](const vector<int> &u, const vector<int> &v) {
            return u[1] < v[1];
        });
        int ans = 1;
        int pos = points[0][1];
        for (int i = 0; i < points.size(); ++i) {
            if (points[i][0] > pos) {
                ++ans;
                pos = points[i][1];
            }
        }
        return ans;
    }

    /*插入区间
     * 给你一个 无重叠的 ，按照区间起始端点排序的区间列表。在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间
     * 输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
       输出：[[1,2],[3,10],[12,16]]）*/
    vector <vector<int>> insert(vector <vector<int>> &intervals, vector<int> &newInterval) {
        vector <vector<int>> intervals_t = intervals;
        intervals_t.push_back(newInterval);
        sort(intervals_t.begin(), intervals_t.end());
        vector <vector<int>> ans;
        for (int i = 0; i < intervals_t.size(); ++i) {
            int L = intervals_t[i][0];
            int R = intervals_t[i][1];
            if (ans.size() == 0 || ans.back()[1] < L) {
                ans.push_back({L, R});
            } else {
                ans.back()[1] = max(ans.back()[1], R);
            }
        }
        return ans;
    }

    /* 合并区间
     * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
     * 请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
     *
     * 思路：
     * 将第一个区间加入 merged 数组中
     * 如果当前区间的左端点在数组 merged 中最后一个区间的右端点之后，那么它们不会重合，我们可以直接将这个区间加入数组 merged 的末尾；
     * 否则，它们重合，我们需要用当前区间的右端点更新数组 merged 中最后一个区间的右端点，将其置为二者的较大值

     * */
    vector <vector<int>> merge(vector <vector<int>> &intervals) {
        if (intervals.size() == 0) {
            return {};
        }
        sort(intervals.begin(), intervals.end());
        vector <vector<int>> merged;
        for (int i = 0; i < intervals.size(); ++i) {
            int L = intervals[i][0], R = intervals[i][1];
            //merged的末尾 < L ,直接加上
            if (!merged.size() || merged.back()[1] < L) {
                merged.push_back({L, R});
            } else {
                //否则的话，merged的最后一个的右边参数为 两个中更大的一个
                merged.back()[1] = max(merged.back()[1], R);
            }
        }
        return merged;
    }

    /* 汇总区间
     * 给定一个  无重复元素 的 有序 整数数组 nums 。返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。
     * 也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。
        列表中的每个区间范围 [a,b] 应该按如下格式输出：
        "a->b" ，如果 a != b
        "a" ，如果 a == b
     * */
    vector <string> summaryRanges(vector<int> &nums) {
        vector <string> ans;
        int n = nums.size();
        int i = 0;
        while (i < n) {
            int low = i;
            i++;

            while (i < n && (nums[i] == nums[i - 1] + 1)) {
                i++;
            }
            int high = i - 1;
            if (low == high) {
                string s = to_string(nums[low]);
                ans.push_back(s);
            } else {
                string s = to_string(nums[low]) + "->" + to_string(nums[high]);
                ans.push_back(s);
            }
        }
        return ans;
    }
}

class Sliding_Window {
public:
    /*最小覆盖子串
     * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。*/
    string minWindow(string s, string t) {
        int l =0, r=0;
        unordered_map<char ,int> smap, tmap;
        int correct = 0;
        string res = s + "******";
        for (const auto &ch : t){
            tmap[ch]++;
        }
        while (r<s.size()){
            smap[s[r]]++;
            // 当前right对应s的字符是在t中出现的，并且数量上还没有达到冗余，是一次有效添加
            if(tmap[s[r]] >= smap[s[r]]){
                ++correct;
            }
            //如果left对应的字符是冗余，那么进行右移删除
            while(l < r && smap[s[l]]  > tmap[s[l]]){
                smap[s[l]]--;
                l++;
            }
            if(correct == t.size()){
                //窗口内已经满足t串的所有字符
                if(r - l + 1 < res.size()){
                    res = s.substr(l, r -l +1 );
                }
            }
            r++;
        }
        return res == s + "******"? "" : res;
    }

    /*串联所有单词的字串
     * 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串长度相同。s 中的串联子串是指一个包含words中所有字符串以任意顺序排列连接起来的子串。
     * 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。*/
    vector<int> findSubstring(string s, vector<string>& words) {
        int l = s.size();
        int m = words.size();
        int n = words[0].size();
        vector<int> ans;
        for (int i = 0; i< n && i + m*n <= l ; ++i) {
            unordered_map<string,int> map;
            for (int j = 0; j < m; ++j) {
                string string1 = s.substr(i + n*j, n);
                map[string1] ++;
            }
            for(auto word : words){
                if(--map[word] == 0){
                    map.erase(word);
                }
            }
            //滑动窗口
            for (int start = i; start + m*n <= l ; start += n) {
                if(start != i){
                    //这部分没看懂
                    string word = s.substr(start + (m - 1) * n, n);
                    if (++map[word] == 0) {
                        map.erase(word);
                    }
                    word = s.substr(start - n, n);
                    if (--map[word] == 0) {
                        map.erase(word);
                    }
                }
                if(map.empty()){
                    ans.push_back(start);
                }
            }
        }
        return ans;
    }   
    /* 找出字符串中所有字母异位词
     * 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
     * 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。*/
    vector<int> findAnagrams(string s, string p) {
/*      自己写的 超出时间限制 但是私认为没错
 *      int lenS = s.size();
        int lenP = p.size();
        vector<int> pCount(26);
        vector<int> sCount(26);
        vector<int> ans;
        for (int i = 0; i < lenP; ++i) {
            ++pCount[p[i] - 'a'];
        }
        for (int i = 0; i + lenP  <= lenS; ++i) {
            for (int j = 0; i < lenP; ++i) {
                ++sCount[p[j] - 'a'];
            }
            if(sCount == pCount){
                ans.push_back(i);
            }
        }*/
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
    /* 无重复字符的最长子串
     * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。*/
    int lengthOfLongestSubstring(string s) {
        int i = 0, j =0;
        int res = 0;
        unordered_set<char> set;
        while (j < s.size()){
            while (set.find(s[j])  != set.end()){
                set.erase(s[i]);
                i++;
            }
            res = max(res , j-i+1);
            set.insert(s[j]);
            j++;
        }
        return res;
    }
};

/*  长度最小的子数组
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 * 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。*/
    int minSubArrayLen(int target, vector<int>& nums) {
        int i = 0;
        int j = 0;
        int sum = 0;
        int res = INT_MAX;
        while (i< nums.size() && j < nums.size()){
            sum += nums[j];
            while(sum >= target){
                res = min(res , j - i +1);
                sum -= nums[i];
                i++;
            }
            j++;
        }
        return res == INT_MAX ? 0 : res;
    }







#endif //TEST_C___SLIDING_WINDOW_H
