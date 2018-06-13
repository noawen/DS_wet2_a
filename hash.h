//
// Created by Dell on 06/06/2018.
//

#ifndef DS_WET2_A_HASH_H
#define DS_WET2_A_HASH_H
#include "List.h"
#include "clan.h"

using namespace List_t;
using std::cout;
using std::endl;

class HashExceptions{};
class ELEMENT_ALREADY_EXIST_HASH : HashExceptions{};
class ELEMENT_NOT_FOUND_HASH : HashExceptions{};


template <class T>
class Hash {
    int size;
    int used;
    List<T>* table;

public:
    Hash(): size(0), used(0), table(){};

    Hash(int size){
        if(size > 0){
            this->size = size*2;
            this->used = 0;
            this->table = new List<T>[size*2];
        }
    }

    Hash(int size, T* data){
        if(size > 0){
            this->size = size*2;
            this->used = 0;
            this->table = new List<T>[size*2];
        }
        for (int i = 0; i < size; i++){
            this->insert(data[i]);
        }
    }

    Hash(const Hash& toCopy): size(toCopy.size), used(toCopy.used), table(NULL) {
        table = new List<T>[toCopy.size];
        try {
            for (int i = 0; i < toCopy.size; i++) {
                table[i] = toCopy.table[i];
            }
        } catch (std::bad_alloc& e) {
            delete[] table;
            throw e;
        }
    }

    Hash&operator= (const Hash& toCopy){
        List<T>* temp_list = new List<T>[toCopy.size];
    //    try {
            for (int i = 0; i < toCopy.size; i++) {
                temp_list[i] = toCopy.table[i];
           }
     //   } catch (std::bad_alloc& e) {
      //      delete[] temp_copy;
     //       throw e;
     //   }
        delete[] this->table;
        this->table = temp_list;
        this->size = toCopy.size;
        this->used = toCopy.used;
        return *this;
    }

    void rehash(int size){
        List<T>* new_hash = new List<T>[size];
        for (int i = 0; i < this->size; i++){
            for(typename List<T>::Iterator it = this->table[i].begin(); it != this->table[i].end(); it++){
                new_hash[it.operator*() % size].insert(it.operator*());
            }
        }
        delete []this->table;
        this->table = new_hash;
        this->size = size;
    }

    void insert(T& data){
        if (this->used >= this->size){
            rehash(this->size*2);
        }
        for(typename List<T>::Iterator it = this->table[data % size].begin(); it != this->table[data % size].end(); it++){
            if (it.operator*() == data){
                throw ELEMENT_ALREADY_EXIST_HASH();
            }
        }
        this->table[data % size].insert(data);
        this->used++;
    }


    typename List<T>::Iterator find(T data){
        for(typename List<T>::Iterator it = this->table[data % size].begin(); it != this->table[data % size].end(); it++){
            if (it.operator*() == data){
                return it;
            }
        }
        throw ELEMENT_NOT_FOUND_HASH();
    }

    bool contain (T data) {
        for(typename List<T>::Iterator it = this->table[data % size].begin(); it != this->table[data % size].end(); it++){
            if (it.operator*() == data){
                return true;
            }
        }
        return false;
    }

    T* find_ptr(T data){
        for(typename List<T>::Iterator it = this->table[data % size].begin(); it != this->table[data % size].end(); it++){
            if (it.operator*() == data){
                return &it.operator*();
            }
        }
        throw ELEMENT_NOT_FOUND_HASH();
    }



    void printHash(){
        for (int i = 0; i < this->size; i++){
            cout << i << " : ";
            for(typename List<T>::Iterator it = this->table[i].begin(); it != this->table[i].end(); it++){
                cout << it.operator*() << ",";
            }
            cout << endl;
        }
    }

    ~Hash(){
        delete [] this->table;
    }
};

#endif //DS_WET2_A_HASH_H
