//
// Created by yuhuanghua on 2023/8/29.
//
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

#ifndef TEST_C___HASHMAP_H
#define TEST_C___HASHMAP_H
using namespace std;



class Hashmap {
public:
/* 383. 赎金信
 * 给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。如果可以，返回 true ；否则返回 false 。
 * magazine 中的每个字符只能在 ransomNote 中使用一次。*/
    bool canConstruct(string ransomNote, string magazine) {
        //只需要满足字符串 magazine 中的每个英文字母 (’a’-’z’) 的统计次数都大于等于 ransomNote 中相同字母的统计次数即可。
        unordered_map<char, int> map;
        for(char ch : magazine){
            map[ch] ++;
        }

        for (char ch : ransomNote) {
            map[ch] --;
            if(map[ch] < 0) return false;
        }
        return true;
    }



    /* 128.最长连续序列
     * 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度 。要求：时间复杂度为 O(n)*/
    int longestConsecutive(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        if (nums.size() == 0 || nums.size() == 1) {
            return nums.size();
        }
        int length = 1;
        int maxL = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1 || nums[i] == nums[i - 1]) {
                length++;
                maxL = max(length, maxL);
            } else if (nums[i] - nums[i - 1] > 1) {
                length = 1;
            }
        }
    }

    /* 219.存在重复元素II
     * 给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个不同的索引 i 和 j ，满足 nums[i] == nums[j] 且 abs(i - j) <= k 。
     * 如果存在，返回 true ；否则，返回 false 。*/
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            int n = nums[i];
            if (map.count(n) && i - map[n] <= k) {
                return true;
            }
            map[n] = i;
        }

        return false;
    }
/* 202.快乐数
 * 编写一个算法来判断一个数 n 是不是快乐数。
 * 快乐数」 定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。然后重复这个过程直到这个数变为 1，
 * 也可能是 无限循环 但始终变不到 1。如果这个过程 结果为 1，那么这个数就是快乐数。*/
    int get_res(int n) {
        int num = 0;
        int res = 0;
        while (n > 0) {
            num = n % 10;
            n = n / 10;
            res += num * num;
        }
        return res;
    }

    bool isHappy(int n) {
        /*两种情况：1、最终会得到1    2、最终会进入循环。*/
        unordered_set<int> set;
        while (n != 1 && set.find(n) != set.end()) {
            set.emplace(n);
            n = get_res(n);
        }
        return n == 1;
/*      方法二：快慢指针
        int low=get_res(n);
        int fast=get_res(get_res(n));
        while(fast!=1&&fast!=low){
            low=get_res(low);
            fast=get_res(get_res(fast));
        }
        return fast==1;*/
    }
    /* 49. 字母异味词分组：给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。字母异位词 是由重新排列源单词的所有字母得到的一个新单词。*/
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for(auto & str : strs){
            string key = str;
            sort(key.begin(), key.end());
            map[key].emplace_back(str);
        }
        vector<vector<string>> res;
        for(auto it = map.begin(); it != map.end(); it++){
            res.emplace_back(it->second);
        }
        return res;
    }


/* 392. 有效的字母异味词
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。*/
    bool isAnagram(string s, string t) {
        int m = s.size();
        if(m != t.size()){
            return false;
        }

        unordered_map<char, int> map;
        for(char ch : s){
            map[ch]++;
        }
        for(char ch : t){
            map[ch]--;
            if(map[ch] < 0){
                return false;
            }
        }
        return true;
    }
/* 290.单词规律 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。这里的遵循指完全匹配，
* 例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。*/
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> char2str;
        unordered_map<string, char> str2char;
        int m = s.size();
        int i = 0;
        string tmp;
        for(char ch : pattern){
            if (i >= m) {
                return false;
            }
            int j = i;
            while(j < m && s[j] != ' '){
                j++;
            }
            tmp = s.substr(i, j-i);
            if(char2str.count(ch)>0 && char2str[ch]!= tmp){
                return false;
            }
            if(str2char.count(tmp)>0 && str2char[tmp]!= ch){
                return false;
            }
            str2char[tmp] = ch;
            char2str[ch] = tmp;
            i = j+1;
        }
        return i >= m;
    }
};

class Double_pointer{
/* 392. 判断子序列
 * 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。*/
    bool isSubsequence(string s, string t) {
        int m = s.size(), n = t.size();
        int i = 0, j = 0;
        while (i < m && j < n){
            if(s[i] == t[j]){
                i++;
            }
            j++;
        }
        return i == m;
    }

/* 125. 验证回文串
 * 如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。
 * 字母和数字都属于字母数字字符。给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。*/
    bool isPalindrome(string s) {
        //#include<cctype>
        string str;
        for(char c : s){
            if(isalnum(c)) {
                str += tolower(c);//error: str.push_back(tolower(c));
            }
        }

        int n = str.size();
        int i = 0, j = n -1;
        while (i < j){
            if(str[i] != str[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;
    }


/* 167.两数之和 II - 输入有序数组
* 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
* 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
* 你可以按任意顺序返回答案。*/
    //双指针
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right){
            int sum = nums[left] + nums[right];
            if(sum == target){
                return {left+1 , right+1};
            } else if(sum < target){
                left++;
            } else{
                right--;
            }
        }
        return {-1 , -1};
    }

    /* 11.盛最多水的容器
     * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
     * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
     *  返回容器可以储存的最大水量*/
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int ans = 0;
        while (l < r) {
            int area = min(height[l], height[r]) * (r - l);
            ans = max(ans, area);
            if (height[l] <= height[r]) {
                ++l;
            }
            else {
                --r;
            }
        }
        return ans;
    }

    /*三数之和
     * 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
     * 请你返回所有和为 0 且不重复的三元组。*/
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        for (int first = 0; first < nums.size(); ++first) {
            if(first > 0 && nums[first] == nums[first - 1]) continue;
            int target = -nums[first];
            int third = n - 1;
            for (int second = first + 1; second < n; ++second) {
                if(second > first + 1 && nums[second] ==  nums[second - 1]) continue;
                while (second < third && nums[second] + nums[third] > target){
                    third --;
                }
                if(second == third) break;
                if(nums[second] + nums[third] == target){
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }


};







#endif //TEST_C___HASHMAP_H
