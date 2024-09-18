//
// Created by yuhuanghua on 2023/8/30.
//

#ifndef TEST_C___LIST_H
#define TEST_C___LIST_H
#include <cstring>
#include <unordered_set>
#include <unordered_map>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class List {
private:
    void reverseLinkedList(ListNode *head) {
        // 也可以使用递归反转一个链表
        ListNode *pre = nullptr;
        ListNode *cur = head;

        while (cur != nullptr) {
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
    }

    ListNode *reverseList(ListNode *head) {
        ListNode *pre = new ListNode(-1);
        ListNode *cur = head;
        pre->next = head;
        while (cur != nullptr) {
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

public:
/* 随机列表的复制：复制带随机指针的链表：给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点
 * 回溯+哈希表
 * 用哈希表记录每一个节点对应新节点的创建情况。遍历该链表的过程中，我们检查next和random节点的创建情况。
 * 如果这两个节点中的任何一个节点的新节点没有被创建，我们都立刻递归地进行创建。
*/
    unordered_map<Node*, Node*> nodemap;
    Node* copyRandomList(Node* head) {
        if(head == nullptr){
            return nullptr;
        }
        if(nodemap.count(head)==0){
            Node* headNew = new Node(head->val);
            nodemap[head] = headNew;
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        return nodemap[head];

    }
/* k个一组反转列表
 * 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。*/
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *pre = dummy;
        ListNode *end = dummy;
        while (end->next){
            // 将end向后移动k个节点
            for (int i = 0; i < k && end != nullptr; ++i) {
                end = end->next;
            }
            // 如果end为空，说明剩余的节点不足k个，退出循环
            if(end == nullptr) break;
            ListNode *next = end->next;
            ListNode *start = pre->next;
            end->next = nullptr;//好像可有可无
            pre->next = reverseList(start);
            start->next = next;//现在的start是在反转之后的最后一个
            pre = start;
            end = pre;
        }
        return dummy->next;
    }

/* 分隔列表
 * 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
 * 你应当保留两个分区中每个节点的初始相对位置。*/
    ListNode *partition(ListNode *head, int x) {
        while (!head) {
            return head;
        }
        //分别通过两个链表记录大小列表，然后再拼接上
        ListNode *small = new ListNode(0);
        ListNode *large = new ListNode(0);
        ListNode *small_head = small;
        ListNode *large_head = large;
        ListNode *cur = head;
        while (cur) {
            if (cur->val < x) {
                small->next = cur;
                small = small->next;
            } else if (cur->val >= x) {
                large->next = cur;
                large = large->next;
            }
            cur = cur->next;
        }
        small->next = large_head->next;
        large->next = nullptr;
        return small_head->next;
    }

/* 旋转链表
 * 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
 * 我们首先计算出链表的长度 n，并找到该链表的末尾节点，将其与头节点相连。这样就得到了闭合为环的链表。
 * 然后我们找到新链表的最后一个节点（即原链表的第n个节点），将当前闭合为环的链表断开，即可得到我们所需要的结果。
*/
    ListNode *rotateRight(ListNode *head, int k) {
        if (!head) {
            return head;
        }
        int n = 1;
        ListNode *tail = head;
        ListNode *node = head;
        while (tail->next) {
            ++n;
            tail = tail->next;
        }
        //组成环
        tail->next = head;
        //比如n=7 k=2，lastnode=5 最后一个节点是原来第五个节点
        int last_node = n - k % n;
        last_node--;
        //现在node指向的是第一个节点1，所以需要将node节点往右移动4（5-1）次
        while (last_node != 0) {
            node = node->next;
            last_node--;
        }
        //node节点指向最后一个节点
        ListNode *res = node->next;
        node->next = nullptr;
        return res;

    }


/* 82.删除排序链表中的重复元素II：给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回已排序的链表 。
 * 思路：
 * 我们从指针 cur 指向链表的哑节点，随后开始对链表进行遍历。
 * 如果当前 cur.next与 cur.next.next对应的元素相同，那么我们就需要将 cur.next以及所有后面拥有相同元素值的链表节点全部删除。我们记下这个元素值 xxx，
 * 随后不断将 cur.next从链表中移除，直到 cur.next为空节点或者其元素值不等于 xxx 为止。
 * 此时，我们将链表中所有元素值为 xxx 的节点全部删除。
*/
    ListNode *deleteDuplicates(ListNode *head) {
        if (!head) {
            return head;
        }

        ListNode *dummy = new ListNode(0, head);

        ListNode *cur = dummy;
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x) {
                    cur->next = cur->next->next;
                }
            } else {
                cur = cur->next;
            }
        }

        return dummy->next;
    }

/* 92.反转链表II
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。*/
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *pre = dummyNode;
        // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }
        // 第 2 步：从 pre 再走 right - left + 1 步，来到 right 节点
        ListNode *rightNode = pre;
        for (int i = 0; i < right - left + 1; i++) {
            rightNode = rightNode->next;
        }

        // 第 3 步：切断出一个子链表（截取链表）
        ListNode *leftNode = pre->next;
        ListNode *curr = rightNode->next;

        // 注意：切断链接
        pre->next = nullptr;
        rightNode->next = nullptr;

        // 第 4 步：同第 206 题，反转链表的子区间
        reverseLinkedList(leftNode);

        // 第 5 步：接回到原来的链表中
        pre->next = rightNode;
        leftNode->next = curr;
        return dummyNode->next;
    }


/* 21.合并两个有序链表
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。*/
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode *pre = new ListNode(-1);
        ListNode *preHead = pre;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                pre->next = list1;
                list1 = list1->next;
            } else {
                pre->next = list2;
                list2 = list2->next;
            }
            pre = pre->next;
        }
        pre->next = list1 == nullptr ? list2 : list1;
        return preHead->next;
    }

/*方法二： 递归
 *如果 l1 或者 l2 一开始就是空链表 ，那么没有任何操作需要合并，所以我们只需要返回非空链表。
 * 否则，我们要判断 l1 和 l2 哪一个链表的头节点的值更小，然后递归地决定下一个添加到结果里的节点。
 * 如果两个链表有一个为空，递归结束
 */
    ListNode *mergeTwoLists_2(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }
        if (list1->val < list2->val) {
            mergeTwoLists(list1, list2->next);
            return list1;
        } else {
            mergeTwoLists(list1->next, list2);
            return list2;
        }
    }

/* 2.两数相加
 * 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储1位数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。你可以假设除了数字 0 之外，这两个数都不会以 0 开头。*/
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head = nullptr;
        ListNode *tail = nullptr;
        int carry = 0;
        while (l1 || l2) {
            int a = l1 ? l1->val : 0;
            int b = l2 ? l2->val : 0;
            int sum = a + b + carry;
            carry = sum / 10;
            if (!head) {//如果是空指针 也就是第一个
                head = tail = new ListNode(sum % 10);
            } else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            tail->next = new ListNode(carry);
        }
        return head;
    }

/* 141.环形链表
 * 给你一个链表的头节点 head ，判断链表中是否有环。
 * 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
 * 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
 * 注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。*/
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode *> list_set;
        while (head != nullptr) {
            if (list_set.count(head)) {
                return true;
            }
            list_set.insert(head);
            head = head->next;
        }
        return false;
    }

/*方法二： 快慢指针
 * 假想「乌龟」和「兔子」在链表上移动，「兔子」跑得快，「乌龟」跑得慢。
 * 当「乌龟」和「兔子」从链表上的同一个节点开始移动时，如果该链表中没有环，那么「兔子」将一直处于「乌龟」的前方；
 * 如果该链表中有环，那么「兔子」会先于「乌龟」进入环，并且一直在环内移动。等到「乌龟」进入环时，由于「兔子」的速度快，它一定会在某个时刻与乌龟相遇，即套了「乌龟」若干圈。
*/
    bool hasCycle_2(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }

/* 倒数第k个元素 :实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。
 * 设有两个指针 p 和 q，初始时均指向头结点。首先，先让 p 沿着 next 移动 k 次。此时，p 指向第 k+1个结点，q 指向头节点，两个指针的距离为 k 。
 * 然后，同时移动 p 和 q，直到 p 指向空，此时 q 即指向倒数第 k 个结点
 * */
    ListNode *getKthFromEnd(ListNode *head, int k) {
        ListNode *p = head;
        ListNode *q = head;
        while (k--) {
            p = p->next;
        }
        while (p != nullptr) {
            p = p->next;
            q = q->next;
        }
        return q;
    }
};

#endif //TEST_C___LIST_H
