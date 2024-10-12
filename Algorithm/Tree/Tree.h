//
// Created by yuhuanghua on 2023/9/13.
//
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_map>
#ifndef C_TREE_H
#define C_TREE_H
using namespace std;

struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode() : val(0), left(nullptr), right(nullptr) {}
         TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
         TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

class Tree {
public:
/* 104.二叉树的最大深度:
 * 给定一个二叉树 root ，返回其最大深度。二叉树的最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
 * 深度优先搜索*/
    int maxDepth(TreeNode* root) {
        if(root == nullptr){
            return 0;
        }
        return max(maxDepth(root->right), maxDepth(root->left)) + 1;
    }
    /* 广度优先搜索*/
    int maxDepth_2(TreeNode* root) {
        queue<TreeNode*> Q;
        Q.push(root);
        int ans = 0;
        while (!Q.empty()){ //Q不为空的时候
            int size = Q.size();
            while (size > 0){
                TreeNode* node = Q.front();
                if(node->left){
                    Q.push(node->left);
                }
                if(node->right){
                    Q.push(node->right);
                }
                --size;
            }
            ++ans;
        }
        return ans;
    }

/* 100.相同的树: 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。*/
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //深度优先搜索
        if(p == nullptr && q == nullptr){
            return true;
        } else if(p == nullptr || q == nullptr){
            return false;
        } else if(p->val != q->val){
            return false;
        } else{
            return isSameTree(p->left, q ->left) && isSameTree(p->right, q->right);
        }
    }

/* 226.翻转二叉树：
 * 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。*/
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr){
            return root;
        }
        TreeNode* node = root->right;
        root->right = root->left;
        root->left = node;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }

/* 101. ERROR:对称二叉树: 给你一个二叉树的根节点 root ， 检查它是否轴对称*/
    bool isSymmetric(TreeNode* root) {
        /*我们可以实现这样一个递归函数，通过「同步移动」两个指针的方法来遍历这棵树，p 指针和 q 指针一开始都指向这棵树的根，随后 p 右移时，q 左移，p 左移时，q 右移。
         * 每次检查当前 p 和 q 节点的值是否相等，如果相等再判断左右子树是否对称*/

        return check(root, root);
    }

    bool check(TreeNode* p, TreeNode* q){
        if(!p && !q) return true;
        if(!p || !q) return false;
        bool ret = (p->val == q->val) && check(p->left, q->right) && check(p->right, q->left);
        return ret;
    }

/* 114.二叉树展开为链表
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 * 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同*/
    void flatten(TreeNode* root) {
        vector<TreeNode*> vec;
        preorder(root, vec);
        int n = vec.size();
        for (int i = 1; i < n; ++i) {
            TreeNode* pre = vec.at(i-1);//跟vec[i-1]效果类似
            TreeNode* cur = vec.at(i);
            pre->left = nullptr;
            pre->right = cur;
        }
    }
    void preorder(TreeNode* root, vector<TreeNode*> &vec){
        if(root != nullptr){
            vec.push_back(root);
            preorder(root->left,vec);
            preorder(root->right, vec);
        }
    }

/* 112.路径总和
 * 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。
 * 如果存在，返回 true ；否则，返回 false 。叶子节点 是指没有子节点的节点。*/
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr){
            return false;
        }
        if(root->left== nullptr && root->right == nullptr){
            return targetSum == root->val;
        }
        return hasPathSum(root->left, targetSum-root->val) || hasPathSum(root->right, targetSum-root->val);
    }

/* 129. 求根节点到叶子节点路径之和
 * 给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。每条从根节点到叶节点的路径都代表一个数字
 * 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123*/
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
    int dfs(TreeNode* root, int num){
        if(root == nullptr){
            return 0;
        }
        num = num*10 + root->val;
        if(root->left == nullptr && root->right == nullptr){
            return num;
        }
        return dfs(root->left, num) + dfs(root->right, num);
    }

/* 二叉树中的最大路径和
 * 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中至多出现一次 。该路径至少包含一个节点，且不一定经过根节点。
 * 路径和是路径中各节点值的总和。给你一个二叉树的根节点 root ，返回其 最大路径和 。*/
    int maxPathSum(TreeNode* root) {
        int val = INT_MIN;
        maxSum(root, val);
        return val;
    }
    int maxSum(TreeNode* node, int &val){
        if(node == nullptr) return 0;
        int left = maxSum(node->left, val);
        int right = maxSum(node->right, val);
        int lmr = node->val + max(left, 0) + max(right, 0);  //左节点+右节点+跟节点 （注意如果左右节点小于零就舍弃）
        int ret = node->val + max(0, max(left, right));      //根节点+max（左节点，右节点）
        val = max(val, max(lmr, ret));
        return ret;
    }

/* 完全二叉树的节点个数：
 * 给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。
 * 完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
 * 根节点在第0层，若最底层为第 h 层，则该层包含 1~ 2h 个节点*/
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int level = 0;
        TreeNode* node = root;
        while (node->left != nullptr) {
            level++;
            node = node->left;
        }
        int low = 1 << level, high = (1 << (level + 1)) - 1;  //相当于2的n次方
        while (low < high) {
            int mid = (high - low + 1) / 2 + low;
            if (exists(root, level, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }

    bool exists(TreeNode* root, int level, int k) {
        int bits = 1 << (level - 1);
        TreeNode* node = root;
        while (node != nullptr && bits > 0) {
            if (!(bits & k)) {  //不甚了解
                node = node->left;
            } else {
                node = node->right;
            }
            bits >>= 1;
        }
        return node != nullptr;
    }


/* 二叉树的最近公共祖先
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先
 * 思路：符合条件的最近公共节点需要满足：
 * 1、左右子树分别包含p q;
 * 2、p、q正好是另一个的祖先节点，即p、q正好是最近公共节点*/
    TreeNode* ans;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p ,q);
        return ans;
    }

    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root == nullptr) return false;
        bool lflag = dfs(root->left, p , q);//判断该节点和它的左右子树是否包含了q和p
        bool rflag = dfs(root->right, p, q);//判断该节点和它的左右子树是否包含了q和p
        if((lflag && rflag) || ((p->val == root->val || q->val == root->val) && (lflag || rflag))){
            ans = root;
        }
        return (p->val == root->val || q->val == root->val) || lflag || rflag;  //判断该节点和它的左右子树是否包含了q和p
    }

/* 117. 填充每个节点的下一个右侧节点指针
 * struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。初始状态下，所有 next 指针都被设置为 NULL 。
 */
    Node* connect(Node* root) {
        /* 层次遍历*/
        if(! root) return nullptr;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()){
            int n = q.size();
            Node* last = nullptr;
            for (int i = 0; i < n; ++i) {
                Node* f = q.front();
                q.pop();
                if(f->left) q.push(f->left);
                if(f->right) q.push(f->right);
                if (i != 0){
                    last->next = f;
                }
                last = f;
            }
        }

        return root;
    }

/* 199.二叉树的右视图
 * 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值*/
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;  // 处理 root 为 nullptr 的情况
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()){
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                if( i == n - 1){
                    ans.push_back(node->val);
                }
            }
        }
        return ans;
    }

/* 637. 二叉树的层平均值
 * 给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。*/
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;

        if(!root) return ans;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()){
            int n = q.size();
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front();
                sum += node->val;
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            int ave = (float)(sum / n );
            ans.push_back(ave);
        }
        return ans;
    }


/* 103. 二叉树的锯齿形层序遍历
 * 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。 */
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (! root) return ans;
        int dep = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (! q.empty()){
            int n = q.size();
            ans.push_back(vector<int>());//每进入一层，初始化容器
            for (int i = 0; i < n; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if(dep % 2 == 1){
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                } else{
                    if (node->right) q.push(node->right);
                    if (node->left) q.push(node->left);
                }
                ans[dep].push_back(node->val);
            }
            dep++;
        }
        return ans;
    }


/* 530. 二叉搜索树的最小绝对差
 * 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。差值是一个正数，其数值等于两值之差的绝对值*/
    int getMinimumDifference(TreeNode* root) {
        //二叉搜索树中序遍历得到的值序列是递增有序的
        int ans = INT_MAX, pre = -1;

    }
    void dfs(TreeNode* root, int pre, int ans){
        if (root == nullptr) return;
        dfs(root->left, pre, ans);
        if(pre == -1 ){
            pre =
        }
    }
};



class treebuild {
private:
    unordered_map<int, int> index;//哈希映射中的每个键值对，键表示一个元素（节点的值），值表示其在中序遍历中的出现位置
    unordered_map<int, int> index2;
    int post_idx;
public:
/* 前序和中序遍历构造二叉树
* 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。*/
    TreeNode *
    myBuildTree(vector<int> &preorder, vector<int> &inorder, int preorder_left, int preorder_right, int inorder_left,
                int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        //前序遍历第一个节点就是根节点
        int preorder_root = preorder_left;
        //在中序遍历中定位根节点  都是在遍历中的位置
        int inorder_root = index[preorder[preorder_root]];
        //建立起根节点
        TreeNode *root = new TreeNode(preorder[preorder_root]);
        //得到左子树中的根节点数目
        int size_left = inorder_root - inorder_left;
        //递归构造左子树
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left, inorder_left,
                                 inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + 1 + size_left, preorder_right, inorder_root + 1,
                                  inorder_right);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int n = preorder.size();
        //哈希映射中的每个键值对，键表示一个元素（节点的值），值表示其在中序遍历中的出现位置
        for (int i = 0; i < n; i++) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
}

/* 从中序和后续遍历序列构造二叉树
 * 给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。*/

class treebuild2 {
    int post_idx;
    unordered_map<int, int> idx_map;
public:
    TreeNode* helper(int in_left, int in_right, vector<int>& inorder, vector<int>& postorder){
        // 如果这里没有节点构造二叉树了，就结束
        if (in_left > in_right) {
            return nullptr;
        }

        // 选择 post_idx 位置的元素作为当前子树根节点
        int root_val = postorder[post_idx];
        TreeNode* root = new TreeNode(root_val);

        // 根据 root 所在位置分成左右两棵子树
        int index = idx_map[root_val];

        // 下标减一
        post_idx--;
        // 构造右子树
        root->right = helper(index + 1, in_right, inorder, postorder);
        // 构造左子树
        root->left = helper(in_left, index - 1, inorder, postorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // 从后序遍历的最后一个元素开始
        post_idx = (int)postorder.size() - 1;

        // 建立（元素，下标）键值对的哈希表
        int idx = 0;
        for (auto& val : inorder) {
            idx_map[val] = idx++;
        }
        return helper(0, (int)inorder.size() - 1, inorder, postorder);
    }

/* 530. 二叉搜索树的最小绝对值*/

    void inorder(TreeNode* root, vector<int>& res){
        if (!root){
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
    int getMinimumDifference(TreeNode* root) {
        int x = INT_MAX;
        vector<int> arr;
        inorder(root, arr);
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] - arr[i-1] < x){
                x = arr[i] - arr[i-1];
            }
        }
        return x;
    }



/* 230.二叉搜索树中第k小的树*/

    int kthSmallest(TreeNode* root, int k) {
        vector<int> arr;
        inorder(root, arr);
        return arr[k-1];
    }

/* 98. 验证二叉搜索树*/
    bool isValidBST(TreeNode* root) {
        vector<int> arr;
        inorder(root, arr);
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i-1] >= arr[i]) return false;
        }
        return true;
    }
};



/* 173.二叉搜索树迭代器
 * 实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。*/
class BSTIterator {

private:
    int idx = 0;
    vector<int> arr;
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> res;
        inorder(root, res);
        return res;
    }
public:
    BSTIterator(TreeNode* root) {
        arr = inorderTraversal(root);
        idx = 0;
    }

    int next() {
        return arr[idx++];
    }

    bool hasNext() {
        return (idx < arr.size());
    }
};

#endif //C_TREE_H
