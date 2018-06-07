//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_MINHEAP_H
#define DS_WET2_A_MINHEAP_H

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

class MinHeapExceptions {
};

class FAILURE_MIN_HEAP : public MinHeapExceptions {
};

template <class T>
class Heap {
    int size;
    int used;
    T *data;

public:
    Heap(): size(0), used(0), data(){};

    Heap(int size){
        if(size > 0){
            this->size = size;
            this->used = 0;
            this->data = new T[size*2];
        }
    }

    Heap(int size, T* data){
        if(size > 0){
            this->size = size;
            this->used = 0;
            this->data = new T[size];
            for (int i = 0; i < this->size; i++){
                this->data[i] = data[i];
                this->used++;
            }
            for (int i = this->size/2; i >= 0; i--){
                this->siftDown(i);
            }
        }
    }

    void changeHeap(int size){
        T* arr = new T[size];
        for (int i = 0; i < this->used; i++){
            arr[i] = this->data[i];
        }
        delete[] this->data;
        this->data = arr;
        this->size = size;
    }

    void swap(T& a, T& b){
        if (a != b) {
            T temp;
            temp = a;
            a = b;
            b = temp;
        }
    }

    T& max(T& a, T& b){
        if(a > b){
            return a;
        }
        return b;
    }

    void siftDown(int index) {
        bool swapped = true;
        int son1, son2;
        son1 = index * 2;
        son2 = index * 2 + 1;
        while (son1 < this->used && swapped) {
            swapped = false;
            if (son2 < this->used) {
                if (this->data[index] > this->data[son1]) {
                    if (this->data[index] > this->data[son2]) {
                        if (this->data[son1] < this->data[son2]) {
                            swap(this->data[index], this->data[son1]);
                            index = son1;
                            swapped = true;
                        } else {
                            swap(this->data[index], this->data[son2]);
                            index = son2;
                            swapped = true;
                        }
                    } else {
                        swap(this->data[index], this->data[son1]);
                        index = son1;
                        swapped = true;
                    }
                } else if (this->data[index] > this->data[son2]) {
                    swap(this->data[index], this->data[son2]);
                    index = son2;
                    swapped = true;
                }
            } else if (this->data[index] > this->data[son1]) {
                swap(this->data[index], this->data[son1]);
                index = son1;
                swapped = true;
            }
            son1 = index * 2;
            son2 = index * 2 + 1;
        }
    }

    void siftUp(int index) {
        int father = index/2;
        bool end = false;
        while (father >= 0 && !end) {
            if(this->data[index] < this->data[father]){
                swap(this->data[index], this->data[father]);
            }
            if(father == 0){
                end = true;
            }
            index = father;
            father = father/2;
        }
    }

    void insert(T data){
        if (this->used < this->size-1){
            if(this->used < this->size/4){
                changeHeap(size/2);
            }
        } else {
            changeHeap(size*2);
        }
        this->data[this->used] = data;
        siftUp(this->used);
        this->used++;
    }
/*
    void decKey(int index, T value){
        if(this->data[index] > value){
            this->data[index] = value;
            siftUp(index);
        }
    }
    */

    void decKey(int* ptr, T value){
        if(*ptr > value){
            *ptr = value;
            siftUp(*ptr);
        }
    }

    void delMin(){
        swap(this->data[0], this->data[this->used-1]);
        this->used--;
        siftDown(0);
    }

    T& findMin(){
        if (this->used > 0) {
            return this->data[0];
        }
        else{
            throw FAILURE_MIN_HEAP(); //the heap is empty
        }
    }
    ~Heap(){
        delete[] this->data;
    }

    //printing functions//
    void printHeap(){
        for(int i = 0; i < this->used; i++){
            cout << this->data[i] << ",";
        }
        cout << endl;
    }

    void printSorted(){
        int end = this->used;
        for(int i = 0; i < end; i++){
            delMin();
        }
        cout << endl;
        for(int i = 0; i < end; i++){
            cout << this->data[i] << ",";
        }
        this->used = end;
        cout << endl;
    }
};


#endif //DS_WET2_A_MINHEAP_H
