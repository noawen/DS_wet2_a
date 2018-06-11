//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_MINHEAP_H
#define DS_WET2_A_MINHEAP_H

#include <iostream>
#include <cstdlib>
#include "clan.h"


using std::cout;
using std::endl;

class MinHeapExceptions {
};

class FAILURE_MIN_HEAP : public MinHeapExceptions {
};


class heapNode {
    int data;
    heapNode* father;
    heapNode* left, *right;
    Clan* clan;


public:
    heapNode (int data, Clan* clan){
        this->data = data;
        this->father = nullptr;
        this->right = nullptr;
        this->left = nullptr;
        this->clan = clan;
    }

    void setData (int data){
        if (!this){
            return;
        }
        this->data = data;
    }

    void setFather (heapNode* father){
        if (this == nullptr){
            return;
        }
        this->father = father;
    }

    void setRight (heapNode* right){
        if (this == nullptr){
            return;
        }
        this->right = right;
    }

    void setLeft (heapNode* left){
        if (this == nullptr){
            return;
        }
        this->left = left;
    }

    void setClan(Clan* clan){
        if (this == nullptr){
            return;
        }
        this->clan = clan;
    }

    int getData (){
        return this->data;
    }

    heapNode* getFather() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->father;
    }

    heapNode* getRight() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->right;
    }

    heapNode* getLeft() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->left;
    }

    Clan* getClan(){
        if (this == nullptr){
            return nullptr;
        }
        return this->clan;
    }
};

class Heap {
    int size;
    heapNode* root;

public:

    Heap(int size){ //ALL INPUT CHECKS SHOULD BE DONE
        this->size = size;
        root = nullptr;
    }


   void Heap_create(int size, int* arr, Clan** clans){ //ALL INPUT CHECKS SHOULD BE DONE BEFORE
       root = buildHeap(root, nullptr, 1, arr, clans);
       makeHeap(root);
   }


    heapNode* getRoot(){
        return this->root;
    }

    heapNode* buildHeap (heapNode* current, heapNode* current_father,int index, int* arr, Clan** clans){
        if (index-1 >= size){
            return nullptr;
        }
        if (current == nullptr) {
            try {
                current = new heapNode(arr[index-1], clans[index-1]);
                current->setFather(current_father);
                Clan* clan = clans[index-1];
                clan->setClanInHeap(current);
            } catch (std::bad_alloc &) {
                throw FAILURE_MIN_HEAP();
            }
        }
        current->setLeft(buildHeap(current->getLeft(), current, 2*index, arr, clans));
        current->setRight(buildHeap(current->getRight(), current, 2*index + 1, arr, clans));
        return current;
    }

    void makeHeap(heapNode* current){
        if (!current){
            return;
        }
        makeHeap(current->getLeft());
        makeHeap(current->getRight());
        siftDown(current);
    }

    void siftDown (heapNode* current){
        if (!(current->getLeft()) && !(current->getRight())){       //has no sons
            return;
        }
        heapNode* left = current->getLeft();
        heapNode* right = current->getRight();
        if (!(left) || !(right)){                                   //has one son
            heapNode* son = (left) ? left : right;
            if (current->getData() < son->getData()){
                return;
            } else{
                int swap = current->getData();
                Clan* clanSwap = current->getClan();
                current->setData(son->getData());
                current->setClan(son->getClan());
                son->setData(swap);
                son->setClan(clanSwap);
                current->getClan()->setClanInHeap(current);
                son->getClan()->setClanInHeap(son);
                siftDown(son);
                return;
            }
        }else {                                                     //has two sons
            if (current->getData() < left->getData() && current->getData() < right->getData()){
                return;
            } else{
                int swap = current->getData();
                Clan* clanSwap = current->getClan();
                if(left->getData() < right->getData()){
                    current->setData(left->getData());
                    current->setClan(left->getClan());
                    left->setData(swap);
                    left->setClan(clanSwap);
                    current->getClan()->setClanInHeap(current);
                    left->getClan()->setClanInHeap(left);
                    siftDown(left);
                    return;
                }else {
                    current->setData(right->getData());
                    current->setClan(right->getClan());
                    right->setData(swap);
                    right->setClan(clanSwap);
                    current->getClan()->setClanInHeap(current);
                    right->getClan()->setClanInHeap(right);
                    siftDown(right);
                    return;
                }
            }
        }
    }

    void insert(int data, Clan* clan){
        root = insert(root, nullptr, data, clan, size+1, (size+1)%2);
    }

    heapNode* insert(heapNode* current, heapNode* father, int data, Clan* clan, int size, int r){
        if (size/2 == 0){                   //in case of root
            try {
                current = new heapNode(data, clan);
                current->setFather(father);
                clan->setClanInHeap(current);
            } catch (std::bad_alloc &){
                throw FAILURE_MIN_HEAP();
            }
            this->size++;
            return current;
        }
        size = size/2;
        if (size == 1){
            if (r == 0){
                current->setLeft(insert(current->getLeft(), current, data, clan, size, r));
            }else {
                current->setRight(insert(current->getRight(), current, data, clan, size, r));
            }
            siftDown(current);
            return current;
        } else {
            if (size % 2 == 0) {
                current->setLeft(insert(current->getLeft(), current, data, clan, size, r));
            } else {
                current->setRight(insert(current->getRight(), current, data, clan, size, r));
            }
            siftDown(current);
            return current;
        }
    }

    void delMin(){
        if (size == 0){
            throw FAILURE_MIN_HEAP();
        }
        root = delMin(root, size, size%2);
    }

    heapNode* delMin(heapNode* current, int size, int r){
        if (size == 1){
            this->root->getClan()->setClanInHeap(nullptr);      //this clan is not in the heap anymore
            this->root->setData(current->getData());
            this->root->setClan(current->getClan());
            this->root->getClan()->setClanInHeap(root);
            delete current;
            this->size--;
            return nullptr;
        }
        size = size/2;
        if (size == 1){
            if (r == 0){
                current->setLeft(delMin(current->getLeft(), size, r));
            }else {
                current->setRight(delMin(current->getRight(), size, r));
            }
            siftDown(current);
            return current;
        } else {
            if (size % 2 == 0) {
                current->setLeft(delMin(current->getLeft(), size, r));
            } else {
                current->setRight(delMin(current->getRight(), size, r));
            }
            siftDown(current);
            return current;
        }
    }

    int min(){
        return this->root->getData();
    }

    void decKey(heapNode* current, int data){
        current->setData(data);
        siftUp(current);
    }

    void siftUp(heapNode* current){
        if (current->getFather()){
            if (current->getData() < current->getFather()->getData()){
                int swap = current->getData();
                Clan* clanSwap = current->getClan();
                current->setData(current->getFather()->getData());
                current->setClan(current->getFather()->getClan());
                current->getFather()->setData(swap);
                current->getFather()->setClan(clanSwap);
                current->getClan()->setClanInHeap(current);
                current->getFather()->getClan()->setClanInHeap(current->getFather());
                siftUp(current->getFather());
            }else {
                return;
            }
        } else{
            return;
        }
    }

    void deleteRec (heapNode* current){
        if (current == nullptr){
            return;
        }
        deleteRec(current->getLeft());
        deleteRec(current->getRight());
        delete (current);
    }

    ~Heap(){
        deleteRec(this->root);
    }
};


#endif //DS_WET2_A_MINHEAP_H