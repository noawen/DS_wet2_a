//
// Created by Dell on 09/06/2018.
//

#ifndef DS_WET2_A_RANKTREE_H
#define DS_WET2_A_RANKTREE_H

#define nullptr 0
#include <iostream>
using std::cout;
using std::endl;

class RankTreeExceptions {
};
class FAILURE_RANK_TREE: public RankTreeExceptions {
};
class ALLOCATION_ERROR_RANK_TREE: public RankTreeExceptions {
};


template<class T>
class Node_r {
    T* data;
    int height;
    int contain;
    int score;
    int scoreInTree;
    int balanceFactor;
    Node_r* father;
    Node_r* left, *right;

public:
    Node_r (T* data, int score){
        try {
            T* new_data = new T(*data);
            this->data = new_data;
        }
        catch (std::bad_alloc&){
            throw ALLOCATION_ERROR_RANK_TREE();
        }
        this->height = 0;
        this->contain = 1;
        this->score = score;
        this->scoreInTree = score;
        this->balanceFactor = 0;
        this->father = nullptr;
        this->right = nullptr;
        this->left = nullptr;
    }

    void setData (T* data){
        if (this == nullptr){
            return;
        }
        delete this->data;
        try {
            T* new_data = new T(*data);
            this->data = new_data;
        }
        catch (std::bad_alloc&){
            throw ALLOCATION_ERROR_RANK_TREE();
        }
    }

    void setHeight (const int height){
        if (this == nullptr){
            return;
        }
        this->height = height;
    }

    void setContain (const int contain){
        if (this == nullptr){
            return;
        }
        this->contain = contain;
    }
    void setScore (const int score){
        if (this == nullptr){
            return;
        }
        this->score = score;
    }

    void setScoreInTree (const int scoreInTree){
        if (this == nullptr){
            return;
        }
        this->scoreInTree = scoreInTree;
    }

    void setBalanceFactor (const int balanceFactor){
        if (this == nullptr){
            return;
        }
        this->balanceFactor = balanceFactor;
    }

    void setFather (Node_r<T>* father){
        if (this == nullptr){
            return;
        }
        this->father = father;
    }

    void setRight (Node_r<T>* right){
        if (this == nullptr){
            return;
        }
        this->right = right;
    }

    void setLeft (Node_r<T>* left){
        if (this == nullptr){
            return;
        }
        this->left = left;
    }


    T* getData (){
        if (!this){
            return nullptr;
        }
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

    int getContain (){
        if(!this)
            return 0;
        return this->contain;
    }

    int getScore (){
        if(!this)
            return 0;
        return this->score;
    }

    int getScoreInTree (){
        if(!this)
            return 0;
        return this->scoreInTree;
    }


    Node_r<T>* getFather() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->father;
    }

    Node_r<T>* getRight() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->right;
    }

    Node_r<T>* getLeft() {
        if (this == nullptr) {
            return nullptr;
        }
        return this->left;
    }


};

template <class T, class compKey>
class rankTree {
    Node_r<T> *root;

    Node_r<T> *insert(T *data, int score, Node_r<T> *current) {
        compKey compare;
        if (current == nullptr) {
            try {
                current = new Node_r<T>(data, score);
            } catch (std::bad_alloc &) {
                throw ALLOCATION_ERROR_RANK_TREE();
            }
        } else if (compare(data, current->getData()) < 0) {
            current->setLeft(insert(data, score, current->getLeft()));
            current->setContain(calcContain(current));                //rank update
            current->setScoreInTree(calcScore(current));
            if (balanceFactor(current) == 2) {
                if (balanceFactor(current->getLeft()) >= 0) {
                    current = LL(current);
                } else if (balanceFactor(current->getLeft()) == -1) {
                    current = LR(current);
                }
            }
        } else if (compare(data, current->getData()) > 0) {
            current->setRight(insert(data, score, current->getRight()));
            current->setContain(calcContain(current));                //rank update
            current->setScoreInTree(calcScore(current));
            if (balanceFactor(current) == -2) {
                if (balanceFactor(current->getRight()) <= 0) {
                    current = RR(current);
                } else if (balanceFactor(current->getRight()) == 1) {
                    current = RL(current);
                }
            }
        } else {
            throw FAILURE_RANK_TREE();
        }
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        return current;
    }

public:
    rankTree() {
        this->root = nullptr;
    }

    Node_r<T> *getRoot() {
        if (!this){
            return NULL;
        }
        return this->root;
    }

    void setRoot(Node_r<T> *new_root) {
        if (new_root == nullptr)
            return;
        this->root = new_root;
    }
    Node_r<T>* copyRec(Node_r<T>* dst, Node_r<T>* src){
        if (src == nullptr){
            return nullptr;
        }
        Node_r<T>* newNode_r;
        try {
            newNode_r = new Node_r<T>(src->getData(), 0);
            newNode_r->setHeight(src->getHeight());
            newNode_r->setContain(src->getContain());
            newNode_r->setScore(src->getScore());
            newNode_r->setScoreInTree(src->getScoreInTree());
            newNode_r->setBalanceFactor(src->getBalanceFactor());
        }
        catch (std::bad_alloc&){
            throw ALLOCATION_ERROR_RANK_TREE();
        }
        newNode_r->setLeft(copyRec(newNode_r->getLeft(), src->getLeft()));
        newNode_r->setRight(copyRec(newNode_r->getRight(), src->getRight()));
        return newNode_r;
    }


    //copyC'tor
    rankTree<T, compKey>(const rankTree<T, compKey>& tree){
        this->root = copyRec(nullptr, tree.root);
    }
    //oprator=
    rankTree<T, compKey>& operator=(const rankTree<T, compKey>& tree){
        //DELETE deleteRec
        deleteRec(this->root);
        this->root = copyRec(nullptr, tree.root);
        return *this;
    }

    //delete rec
    void deleteRec (Node_r<T>* current){
        if (current == nullptr){
            return;
        }
        deleteRec(current->getLeft());
        deleteRec(current->getRight());
        delete (current->getData());
        delete (current);
    }


    T find(T data, Node_r<T> *current) {
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


    int max(Node_r<T> *left, Node_r<T> *right) {
        if (left == nullptr && right == nullptr) {
            return -1;
        } else if (left == nullptr) {
            return right->getHeight();
        } else if (right == nullptr) {
            return left->getHeight();
        }
        return left->getHeight() > right->getHeight() ? left->getHeight() : right->getHeight();
    }


    int balanceFactor(Node_r<T> *current) {
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

    int calcContain (Node_r<T>* current){
        if (!current){
            return 0;
        }
        if (!current->getLeft()){       //no left son
            if (!current->getRight()){      //no right son
                return 1;
            } else{                       //has right son
                return  current->getRight()->getContain() + 1;
            }
        } else {                        //has left son
            if (!current->getRight()){   //no right son
                return  current->getLeft()->getContain() + 1;
            } else {
                return current->getLeft()->getContain() + current->getRight()->getContain() + 1;
            }
        }
    }

    int calcScore (Node_r<T>* current){
        if (!current){
            return 0;
        }
        if (!current->getLeft()){       //no left son
            if (!current->getRight()){      //no right son
                return current->getScore();
            } else{                       //has right son
                return  current->getScore() + current->getRight()->getScoreInTree();
            }
        } else {                        //has left son
            if (!current->getRight()){   //no right son
                return  current->getScore() + current->getLeft()->getScoreInTree();
            } else {
                return current->getScore() + current->getLeft()->getScoreInTree() + current->getRight()->getScoreInTree();
            }
        }
    }

    Node_r<T> *LL(Node_r<T> *current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node_r<T> *left = current->getLeft();
        Node_r<T> *leftR = left->getRight();
        if (leftR != nullptr) {
            current->setLeft(leftR);
        } else {
            current->setLeft(nullptr);
        }
        left->setRight(current);
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        left->setHeight(max(left->getLeft(), left->getRight()) + 1);
        current->setContain(calcContain(current));
        left->setContain(calcContain(left));
        current->setScoreInTree(calcScore(current));
        left->setScoreInTree(calcScore(left));
        return left;
    }


    Node_r<T> *RR(Node_r<T> *current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node_r<T> *right = current->getRight();
        Node_r<T> *rightL = right->getLeft();
        if (rightL != nullptr) {
            current->setRight(rightL);
        } else {
            current->setRight(nullptr);
        }
        right->setLeft(current);
        current->setHeight(max(current->getLeft(), current->getRight()) + 1);
        right->setHeight(max(right->getLeft(), right->getRight()) + 1);
        current->setContain(calcContain(current));
        right->setContain(calcContain(right));
        current->setScoreInTree(calcScore(current));
        right->setScoreInTree(calcScore(right));
        return right;
    }

    Node_r<T> *LR(Node_r<T> *current) {
        current->setLeft(RR(current->getLeft()));
        return LL(current);
    }

    Node_r<T> *RL(Node_r<T> *current) {
        current->setRight(LL(current->getRight()));
        return RR(current);
    }


    void insert(T *data, int score) {
        root = insert(data, score, root);
    }


    void remove(T *data) {
        if (!this)
            return;
        root = remove(data, root);
    }


    Node_r<T>* remove(T data, Node_r<T> *current) {
        compKey compare;
        // Node_r<T> *temp;
        if (current == nullptr) {
            return current;
        }
        if (compare(data, current->getData()) < 0) {
            current->setLeft(remove(data, current->getLeft()));
            current->setContain(calcContain(current));
            current->setScoreInTree(calcScore(current));
        } else if (compare(data, current->getData()) > 0) {
            current->setRight(remove(data, current->getRight()));
            current->setContain(calcContain(current));
            current->setScoreInTree(calcScore(current));
        } else {                                                       //if we find and doesn't have 2 children
            Node_r<T> *left = current->getLeft();
            Node_r<T> *right = current->getRight();
            if (right == nullptr || left == nullptr) {
                Node_r<T> *tmp = (left != nullptr) ? left : right;     //tmp to be the only child
                if (tmp == nullptr) {                                // has no child
                    tmp = current;
                    current = nullptr;
                } else {                                     // has one child
                    current->setData(tmp->getData());
                    current->setScore(tmp->getScore());
                    if (left == nullptr){
                        current->setRight(nullptr);
                    }
                    else{
                        current->setLeft(nullptr);
                    }
                }
                delete (tmp->getData());
                delete (tmp);
            } else {                                         // has two children
                Node_r<T> *min = findMin(current->getRight());
                current->setData(min->getData());
                current->setScore(min->getScore());
                current->setRight(remove(min->getData(), current->getRight()));
                current->setContain(calcContain(current));
                current->setScoreInTree(calcScore(current));
            }
        }
        if (current == nullptr){
            return current;
        }
        current->setHeight(max(current->getLeft(), current->getRight())+1);
        current->setContain(calcContain(current));
        current->setScoreInTree(calcScore(current));
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


    Node_r<T>* findMin(Node_r<T>* current)
    {
        if(current == NULL)
            return NULL;
        else if(current->getLeft() == NULL)
            return current;
        else
            return findMin(current->getLeft());
    }

    int returnBackInOrder(Node_r<T>* node, T* arr, int i) {
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

    void printInOrder(Node_r<T> *node) {
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

    void printBackInOrder(Node_r<T> *node) {
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

    int size(Node_r<T> *node) {
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

    void printTreeToArray (Node_r<T>* current, T** arr, int *i){
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

    Node_r<T>* select(int k, int* bigger){
        return selectRec(this->getRoot(), k, bigger);
    }

    Node_r<T>* selectRec(Node_r<T>* current ,int k, int* bigger){
        if (current->getLeft()->getContain() == k-1){
            (*bigger) += current->getScore() + current->getRight()->getScoreInTree();
            return current;
        } else{
            if (current->getLeft()->getContain() > k-1){
                (*bigger) += current->getScore() + current->getRight()->getScoreInTree();
                return selectRec(current->getLeft(), k, bigger);
            }else {
                return selectRec(current->getRight(), k-current->getLeft()->getContain()-1, bigger);
            }
        }
    }

    Node_r<T>* destroyTree (Node_r<T>* current){
        if (current == nullptr){
            return nullptr;
        }
        if (current->getLeft() != nullptr){
            current->setLeft(destroyTree(current->getLeft()));

        }
        if (current->getRight() != nullptr){
            current->setRight(destroyTree(current->getRight()));
        }
        delete (current->getData());
        delete (current);
        return nullptr;
    }

    ~rankTree(){
        destroyTree(this->getRoot());
        root = NULL;
    }
};



#endif //DS_WET2_A_RANKTREE_H
