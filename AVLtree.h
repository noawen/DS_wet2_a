//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_AVLTREE_H
#define DS_WET2_A_AVLTREE_H

#define nullptr 0
#include <iostream>
using std::cout;
using std::endl;

class TreeExceptions {
};
class FAILURE_TREE: public TreeExceptions {
};
class ALLOCATION_ERROR_TREE: public TreeExceptions {
};


template<class T>
class Node {
    T* data;
    int height;
    int balanceFactor;
    Node* father;
    Node* left, *right;

public:
    Node ( T* data){
        this->data = data;
        this->height = 0;
        this->balanceFactor = 0;
        this->father = nullptr;
        this->right = nullptr;
        this->left = nullptr;
    }

    void setData ( T* data){
        if (this == nullptr){
            return;
        }
        this->data = data;
    }

    void setHeight (const int height){
        if (this == nullptr){
            return;
        }
        this->height = height;
    }

    void setBalanceFactor (const int balanceFactor){
        if (this == nullptr){
            return;
        }
        this->balanceFactor = balanceFactor;
    }

    void setFather (Node<T>* father){
        if (this == nullptr){
            return;
        }
        this->father = father;
    }

    void setRight (Node<T>* right){
        if (this == nullptr){
            return;
        }
        this->right = right;
    }

    void setLeft (Node<T>* left){
        if (this == nullptr){
            return;
        }
        this->left = left;
    }


    T* getData (){
        return this->data;
    }

    int getBalanceFactor (){
        return this->balanceFactor;
    }

    int getHeight (){
        if(!this)
            return 0;
        return this->height;
    }


    Node<T>* getFather() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->father;
    }

    Node<T>* getRight() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->right;
    }

    Node<T>* getLeft() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->left;
    }

};

template <class T, class compKey>
class AvlTree {
    Node<T> *root;

    Node<T> *insert(T *data, Node<T> *current) {
        compKey compare;
        if (current == nullptr) {
            try {
                current = new Node<T>(data);
            } catch (std::bad_alloc &) {
                throw ALLOCATION_ERROR_TREE();
            }
        } else if (compare(data, current->getData()) < 0) {
            current->setLeft(insert(data, current->getLeft()));
            if (balanceFactor(current) == 2) {
                if (balanceFactor(current->getLeft()) >= 0) {
                    current = LL(current);
                } else if (balanceFactor(current->getLeft()) == -1) {
                    current = LR(current);
                }
            }
        } else if (compare(data, current->getData()) > 0) {
            current->setRight(insert(data, current->getRight()));
            if (balanceFactor(current) == -2) {
                if (balanceFactor(current->getRight()) <= 0) {
                    current = RR(current);
                } else if (balanceFactor(current->getRight()) == 1) {
                    current = RL(current);
                }
            }
        } else {
            throw FAILURE_TREE();
        }
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        return current;
    }

public:
    AvlTree() {
        this->root = nullptr;
    }

    Node<T> *getRoot() {
        if (!this){
            return NULL;
        }
        return this->root;
    }

    void setRoot(Node<T> *new_root) {
        if (new_root == nullptr)
            return;
        this->root = new_root;
    }


    T *find(T* data, Node<T> *current) {
        if (!current) {
            //   throw FAILURE_TREE();
            return nullptr;
        } else {
            compKey compare;
            if (compare(data, current->getData()) == 0) {
                return current->getData();
            } else {
                if (compare(data, current->getData()) > 0) {
                    return find(data, current->getRight());
                } else {
                    if (compare(data, current->getData()) < 0) {
                        return find(data, current->getLeft());
                    }
                    else {
                        //   throw FAILURE_TREE();
                        return nullptr;
                    }
                }
            }
        }
    }

    bool contain(T* data) {
        if (!find(data, this->getRoot())) {
            return false;

        }

        return true;
    }


    int max(Node<T> *left, Node<T> *right) {
        if (left == nullptr && right == nullptr) {
            return -1;
        } else if (left == nullptr) {
            return right->getHeight();
        } else if (right == nullptr) {
            return left->getHeight();
        }
        return left->getHeight() > right->getHeight() ? left->getHeight() : right->getHeight();
    }


    int balanceFactor(Node<T> *current) {
        if (current->getRight() == nullptr && current->getLeft() == nullptr) {
            current->setBalanceFactor(0);
            return 0;
        } else {
            if (current->getRight() == nullptr) {
                current->setBalanceFactor(current->getLeft()->getHeight() + 1);
                return (current->getLeft()->getHeight() + 1);
            } else {
                if (current->getLeft() == nullptr) {
                    current->setBalanceFactor(-(current->getRight()->getHeight()) - 1);
                    return (-(current->getRight()->getHeight()) - 1);
                }
            }
        }
        current->setBalanceFactor(current->getLeft()->getHeight() - current->getRight()->getHeight());
        return (current->getLeft()->getHeight() - current->getRight()->getHeight());
    }


    Node<T> *LL(Node<T> *current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node<T> *left = current->getLeft();
        Node<T> *leftR = left->getRight();
        if (leftR != nullptr) {
            current->setLeft(leftR);
        } else {
            current->setLeft(nullptr);
        }
        left->setRight(current);
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        left->setHeight(max(left->getLeft(), left->getRight()) + 1);
        return left;
    }


    Node<T> *RR(Node<T> *current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node<T> *right = current->getRight();
        Node<T> *rightL = right->getLeft();
        if (rightL != nullptr) {
            current->setRight(rightL);
        } else {
            current->setRight(nullptr);
        }
        right->setLeft(current);
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        right->setHeight(max(right->getLeft(), right->getRight()) + 1);
        return right;
    }

    Node<T> *LR(Node<T> *current) {
        current->setLeft(RR(current->getLeft()));
        return LL(current);
    }

    Node<T> *RL(Node<T> *current) {
        current->setRight(LL(current->getRight()));
        return RR(current);
    }


    void insert(T *data) {
        root = insert(data, root);
    }


    void remove(T *data) {
        if (!this)
            return;
        root = remove(data, root);
    }


    Node<T> *remove(T* data, Node<T> *current) {
        compKey compare;
        // Node<T> *temp;
        if (current == nullptr) {
            return current;
        }
        if (compare(data, current->getData()) < 0) {
            current->setLeft(remove(data, current->getLeft()));
        } else if (compare(data, current->getData()) > 0) {
            current->setRight(remove(data, current->getRight()));
        } else {                                                       //if we find and doesn't have 2 children
            Node<T> *left = current->getLeft();
            Node<T> *right = current->getRight();
            if (right == nullptr || left == nullptr) {
                Node<T> *tmp = (left != nullptr) ? left : right;     //tmp to be the only child
                if (tmp == nullptr) {                                // has no child
                    tmp = current;
                    current = nullptr;
                } else {                                     // has one child
                    current->setData(tmp->getData());
                    if (left == nullptr){
                        current->setRight(nullptr);
                    }
                    else{
                        current->setLeft(nullptr);
                    }
                }
                delete (tmp);
            } else {                                         // has two children
                Node<T> *min = findMin(current->getRight());
                current->setData(min->getData());
                current->setRight(remove(min->getData(), current->getRight()));
            }
        }
        if (current == nullptr){
            return current;
        }
        current->setHeight(max(current->getLeft(), current->getRight())+1);
        if (balanceFactor(current) == 2 && balanceFactor(current->getLeft()) >= 0){
            return LL(current);
        }
        if (balanceFactor(current) == 2 && balanceFactor(current->getLeft()) == -1){
            return LR(current);
        }
        if (balanceFactor(current) == -2 && balanceFactor(current->getRight()) <= 0){
            return RR(current);
        }
        if (balanceFactor(current) == -2 && balanceFactor(current->getRight()) == 1){
            return RL(current);
        }
        return current;
    }


    Node<T>* findMin(Node<T>* current)
    {
        if(current == NULL)
            return NULL;
        else if(current->getLeft() == NULL)
            return current;
        else
            return findMin(current->getLeft());
    }

    int returnBackInOrder(Node<T> *node, T** arr, int i) {
        if (node == NULL) {
            return i;
        }
        if (node->getRight() != NULL) {
            i = returnBackInOrder(node->getRight(), arr, i);
        }
        arr[i] = node->getData();
        //    cout<<arr[i]<<" , ";
        i++;
        if (node->getLeft() != NULL) {
            i = returnBackInOrder(node->getLeft(), arr, i);
        }
        return i;
    }

    void printInOrder(Node<T> *node) {
        if (node != NULL) {
            if (node->getLeft() != NULL) {
                printInOrder(node->getLeft());
            }
            cout << node->getData() << " ";
            if (node->getRight() != NULL) {
                printInOrder(node->getRight());
            }
        }
    }

    void printBackInOrder(Node<T> *node) {
        if (node != NULL) {
            if (node->getRight() != NULL) {
                printBackInOrder(node->getRight());
            }
            cout << node->getData() << " ";
            if (node->getLeft() != NULL) {
                printBackInOrder(node->getLeft());
            }
        }
    }

    int size(Node<T> *node) {
        if (node == NULL)
            return 0;
        else return 1 + size(node->getLeft()) + size(node->getRight());
    }


    void merge(T* a, int na, T* b, int nb, T* c) {
        compKey max;
        int ia, ib, ic;
        for (ia = ib = ic = 0; (ia < na) && (ib < nb); ic++) {
            if (a[ia] != NULL && b[ib] != NULL && max(a[ia], b[ib]) < 0) {
                c[ic] = a[ia];
                ia++;
            } else {
                c[ic] = b[ib];
                ib++;
            }
        }
        for (; ia < na; ia++, ic++)
            c[ic] = a[ia];
        for (; ib < nb; ib++, ic++)
            c[ic] = b[ib];
    }

    void printTreeToArray (Node<T>* current, T** arr, int *i){
        if (current != NULL) {
            if (current->getLeft() != NULL) {
                printTreeToArray(current->getLeft(), arr, i);
            }
            arr[*i] = (current->getData());
            ++(*i);
            if (current->getRight() != NULL) {
                printTreeToArray(current->getRight(), arr, i);
            }
        }
    }

    Node<T>* destroyTree (Node<T>* current){
        if (current == nullptr){
            return nullptr;
        }
        if (current->getLeft() != nullptr){
            current->setLeft(destroyTree(current->getLeft()));

        }
        if (current->getLeft() != nullptr){
            current->setRight(destroyTree(current->getRight()));
        }
        delete (current);
        return nullptr;
    }

    ~AvlTree(){
        destroyTree(this->getRoot());
        root = NULL;
    }
};



#endif //DS_WET2_A_AVLTREE_H
