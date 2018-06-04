#include <iostream>
#include "AVLtree.h"

class isBigger {
public:
    int operator()(int* a, int* b) {
        if (*a < *b) {
            return -1;
        }
        if (*a > *b) {
            return 1;
        }
        return 0;
    }
};

int main() {
    AvlTree<int,isBigger> tree = AvlTree<int,isBigger>();
  // for (int i = 1; i <= 10; i++){
//        tree.insert(&i);
    //}
    int x = 1;
    int y = 2;
    tree.insert(&x);
    tree.insert(&y);

    return 0;
}