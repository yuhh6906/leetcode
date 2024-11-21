//
// Created by yuhuanghua on 2024/11/4.
//
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution{

public:
/* 108. 将有序数组转换为二叉搜索树
 * 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵平衡二叉搜索树*/
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root;
        root = helper(nums, 0, nums.size() - 1);
        return root;
    }
    TreeNode* helper(vector<int>& nums, int left, int right){
        //终止条件
        if(left > right) return nullptr;
        int mid = (left + right) >> 1;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = helper(nums, left, mid - 1);
        node->right = helper(nums, mid + 1, right);
        return node;
    }


/* 148 排序列表:给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表*/
    ListNode* sortList(ListNode* head) {
        ListNode* tail = head;
        int n = 1;
        while(true){
            if(tail->next){
                n++;
            }
            tail = tail->next;
        }
//        ListNode* pivot =
    }

};


int main(){

    return 0;
}