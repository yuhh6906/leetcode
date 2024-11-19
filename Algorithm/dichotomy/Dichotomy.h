//
// Created by yuhuanghua on 2024/7/8.
//
#include <vector>

#ifndef LEEDCODE_C_DICHOTOMY_H
#define LEEDCODE_C_DICHOTOMY_H

/* 二分法最重要的两个点:
 * while循环中 left 和 right 的关系，到底是 left <= right 还是 left < right
 * 迭代过程中 middle 和 right 的关系，到底是 right = middle - 1 还是 right = middle
 * while(left <= right) 左闭又闭 while(left < right) 左开右闭 return left
 * */


class Template{

public:
    //朴素二分查找
    int binary_search(vector<int>& nums, int target) {
        int left = 0, right = nums.length - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else if(nums[mid] == target) {
                // 直接返回
                return mid;
            }
        }
        // 直接返回
        return -1;
    }

    //左端点查找
    int left_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.length - 1;
        //right = nums.length - 1 --> left <= right
        //right = nums.length     --> left < right
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target) {
                // 别返回，锁定左侧边界
                right = mid - 1;
            }
        }
        // 最后要检查 left 越界的情况
        if (left >= nums.length || nums[left] != target)
            return -1;
        return left;
    }


    int right_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target) {
                // 别返回，锁定右侧边界
                left = mid + 1;
            }
        }
        // 最后要检查 right 越界的情况
        if (right < 0 || nums[right] != target)
            return -1;
        return right;
    }

};

class Dichotomy {
public:
/* 35. 搜索插入位置
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。请必须使用时间复杂度为 O(log n) 的算法。*/
    int searchInsert(vector<int>& nums, int target) {
//        int n = nums.size();
////        if(n < 1) return n;
//        int left = 0;
//        int right = n - 1;
//        int ans = n;
//        //nums[pos-1] < target <= nums[pos];返回pos
//        while (left <= right){
//            int mid = ((right - left) >> 1) + left;
//            if(target <= nums[mid]){
//                ans = mid;
//                right = mid - 1;
//            } else{
//                left = mid + 1;
//            }
//        }
//        return ans;

        //解法2
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while(left <= right){
            int mid = left + ((right - left) >> 1);
            if(nums[mid] > target){
                right = mid - 1;
            }else if(nums[mid] < target){
                left = mid + 1;
            }else{
                //收敛右边界
                right = mid - 1;
            }
        }
        //因为目标值不存在于数组中，返回它将会被按顺序插入的位置，不用考虑越界的事情
        return left;
    }



/* 74. 搜素二维矩阵
 * 给你一个满足下述两条属性的 m x n 整数矩阵：每行中的整数从左到右按非严格递增顺序排列。每行的第一个整数大于前一行的最后一个整数。
 * 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。*/
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int length = m*n;
        vector<int> nums;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                nums.push_back(matrix[i][j]);
            }
        }

        int left = 0, right = length - 1;
        while (left <= right){
            int mid = ((right - left) >> 1) + left;
            if(nums[mid] > target){
                right = mid - 1;
            } else if(nums[mid] < target){
                left = mid + 1;
            } else{
                return true;
            }
        }
        return false;
    }

/* 162. 寻找峰值
 * 峰值元素是指其值严格大于左右相邻值的元素。给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
 * 你可以假设 nums[-1] = nums[n] = -∞ 。 你必须实现时间复杂度为 O(log n) 的算法来解决此问题。*/
    int findPeakElement(vector<int>& nums) {
        /* 因为nums[-1] = nums[n] = -∞，所以只要数组中存在一个元素比相邻元素大，那么沿着它一定可以找到一个峰值
         * 如果 m 较大，则左侧存在峰值，r = m，如果 m + 1 较大，则右侧存在峰值，l = m + 1*/
        int left = 0, right = nums.size() - 1;
        while (left < right){
            int mid = ((right - left) >> 1) + left;
            if(nums[mid] > nums[mid + 1]){
                right = mid;
            } else{
                left = mid + 1;
            }
        }
        return left;
    }

/* 33. 搜索旋转排序数组
 * 整数数组 nums 按升序排列，数组中的值互不相同 。在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了旋转，
 * 使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
 * 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。 O(log n)*/
    int search(vector<int>& nums, int target) {
     /* 1：只有在顺序区间内才可以通过区间两端的数值判断target是否在其中。
      * 2：判断顺序区间还是乱序区间，只需要对比 left 和 right 是否是顺序对即可，left <= right，顺序区间，否则乱序区间
      * 3：每次二分都会至少存在一个顺序区间。*/
         int n = nums.size();
         if(n == 0) return  -1;
         if(n == 1){
             return nums[0] == target ?  0 : -1;
         }
         int left = 0, right = n -1;
        while (left <= right) {
            int mid = (right + left) >> 1; //注意
            if(nums[mid] == target) return mid;
            if (nums[mid] >= nums[left]) {
                //left 到mid是顺序区间
                if (target < nums[mid] && target >= nums[left]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else{
                //mid到right 是顺序区间
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }

/* 34. 在排序数组中查找元素的第一个和最后一个位置
 * 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。如果数组中不存在目标值 target，返回 [-1, -1]。
 * 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。*/
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0,right = nums.size() - 1;
        vector<int> ans = {-1, -1};
        while (left <= right){
            int mid = ((right - left) >> 1) + left;
            if(nums[mid] >= target){
                right = mid - 1;
            }else if(nums[mid] < target){
                left = mid + 1;
            }
        }
        if(left >= nums.size() || nums[left] != target) {
            return ans;
        }else{
            ans[0] = left;
        }
        left = 0;
        right = nums.size() - 1;
        while (left <= right){
            int mid = ((right - left) >> 1) + left;
            if(nums[mid] > target){
                right = mid - 1;
            }else if(nums[mid] <= target){
                left = mid + 1;
            }
        }
        if(right < 0 || nums[right] != target){
            return vector<int>{-1, -1};
        }else{
            ans[1] = right;
        }
        return ans;

    }


/* 4.寻找两个正序数组中的中位数
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


/* 153. 寻找旋转排序数组中的最小值
 * 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
 * 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
 * 给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。*/
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left < right){
            int mid = ((right - left) >> 1) + left;
            if(nums[mid] < nums[right]){
                //说明右半部分是升序 最小值不在右半部分 丢弃右半部分
                right = mid;
            }else{//不存在相等的情况
                //说明左半部分是升序 最小值不在左半部分 丢弃左半部分
                left = mid + 1; //注意是+1 不是直接等于
            }
        }
        return nums[left];
    }
};


#endif //LEEDCODE_C_DICHOTOMY_H
