//
// Created by yuhuanghua on 2023/7/27.
//

#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

#ifndef TEST_C___LRU_H
#define TEST_C___LRU_H

struct DLinkedNode{
    int key;
    int value;
    DLinkedNode* pre;
    DLinkedNode* next;
    DLinkedNode():key(0), value(0), pre(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value):key(_key), value(_value), pre(nullptr), next(nullptr){}
};

class lruCache {
private:
    int capacity;
    int size;
    DLinkedNode* head;
    DLinkedNode* tail;
    unordered_map<int, DLinkedNode*> hashmap;

public:
    lruCache(int _capacity):capacity(_capacity), size(0) {
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


#endif //TEST_C___LRU_H
