//
// Created by yuhuanghua on 2023/7/27.
//

#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

#ifndef TEST_C___LRU_H
#define TEST_C___LRU_H

/* 146. LRU缓存
 * 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。实现 LRUCache 类：
 * LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 * int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
 * void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。*/

struct DLinkedNode{
    int key;
    int value;
    DLinkedNode* pre;
    DLinkedNode* next;
    DLinkedNode():key(0), value(0), pre(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value):key(_key), value(_value), pre(nullptr), next(nullptr){}
};

class LRUCache {
private:
    int capacity;
    int size;
    DLinkedNode* head;
    DLinkedNode* tail;
    unordered_map<int, DLinkedNode*> hashmap;

public:
    LRUCache(int _capacity):capacity(_capacity), size(0) {
        DLinkedNode* head;
        DLinkedNode* tail;
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        if(!hashmap.count(key)){
            return -1;
        }
        DLinkedNode* node = hashmap[key];
        moveTohead(node);
        return node->value;
    }

    void put(int key, int value) {
        if(!hashmap.count(key)){
            //没有这个key 增加
            DLinkedNode* node = new DLinkedNode(key,value);
            addTohead(node);
            ++size;
            if(size > capacity){
                DLinkedNode* last = removeLast();
                hashmap.erase(last->key);
                delete last;
                --size;
            }
        } else{
            //更新
            DLinkedNode* node = hashmap[key];
            hashmap[key]->value  = value;
            moveTohead(node);
        }
    }

    void addTohead(DLinkedNode* node){
        node->next = head->next;
        head->next->pre = node;
        node->pre = head;
        head->next = node;
    }

    void removeNode(DLinkedNode* node){
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void moveTohead(DLinkedNode* node){
        removeNode(node);
        addTohead(node);
    }

    DLinkedNode* removeLast(){
        DLinkedNode* last = tail->pre;
        removeNode(tail->pre);
        return last;
    }
};



class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

#endif //TEST_C___LRU_H
