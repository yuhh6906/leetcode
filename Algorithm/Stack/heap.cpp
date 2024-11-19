//
// Created by yuhuanghua on 2024/10/29.
//
class Heap{
/* 215. 数组中的第K 个最大元素
 * 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 * 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        return nums[n - k ];
    }



/* 373. ERROR:查找和最小的K对数字： 给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。
 * 定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。*/
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<vector<int>> ans;
        for (int i = 0, j = 0; i < m && j < n; ) {
            vector<int> vec = {nums1[i], nums2[j]};
            ans.push_back(vec);
            if(--k <= 0) return ans;
            if(i+1 < m && j+1 < n && nums1[i+1] < nums2[j+1]) i++;
            if(i+1 < m && j+1 < n && nums1[i+1] > nums2[j+1]) j++;
        }
        return ans;
    }
};