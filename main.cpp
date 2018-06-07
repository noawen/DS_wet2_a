#include <iostream>
#include "AVLtree.h"
#include "minHeap.h"
#include "hash.h"
#include "clan.h"



void testMinHeap(){
    int a[5] = {20,18,32,9,0};
    Heap<int> h = Heap<int>(5,a);
    h.printHeap();
    h.delMin();
    h.printHeap();
    h.delMin();
    h.delMin();
    h.delMin();
    h.printHeap();
    h.delMin();
    h.printHeap();
   // h.findMin();
    h.insert(6);
    h.printHeap();
    h.insert(1);
    h.insert(7);
    int* ptr;
    int x;
     x = 10;
    ptr = &x;
    h.insert(x);
    h.printHeap();
    cout<<"min elemnt is:" <<h.findMin()<<endl;
    //h.decKey(ptr,-1);
    h.printHeap();
    //h.delMin();

}

void testTree(){

    AvlTree<int,isBigger> tree = AvlTree<int,isBigger>();
    int x = 1;
    int y = 2;
    tree.insert(&x);
    tree.insert(&y);
}


/*
void testMemory(){
    AvlTree<Clan,isBigger_byId_clan> tree = AvlTree<Clan,isBigger_byId_clan>();
    Clan clan1 = Clan (11);
    Clan clan2 = Clan (22);
    tree.insert(&clan1);
    tree.insert(&clan2);

    AvlTree<int,isBigger> players_tree = AvlTree<int,isBigger>();
    int x = 312;
    players_tree.insert(&x);
    Clan clan3 = Clan (33);
    //clan3.setPlayersTree(players_tree);
    Clan clan4 = Clan (44);
}
 */

void testHash(){
    int a[5] = {1,2,3,4,5};
    Hash<int> h = Hash<int>(5,a);

    for (int i = 0; i < 5; i++){
        int x = 12+i;
        h.insert(x);
    }
    h.printHash();

    for (int i = 0; i < 5; i++){
        int y = 24+i;
        h.insert(y);
    }
    for (int i = 0; i < 5; i++){
        int z = 19+i;
        h.insert(z);
    }
    h.printHash();
     h.find(27);

    /****Clan's hash***/
    Clan clan1 (1);
    Clan clan2 (2);
    Clan clan3 (3);
    Clan b [3]={clan1,clan2,clan3};
    Hash<Clan> clans = Hash<Clan>(3,b);
    Clan clan4 (4);
    clans.insert(clan4);
    int x=4;
    clan1.getPalyersTree().insert(&x);
}

int main() {
  // testMinHeap();
  //  testTree();
   // testMemory();
    testHash();


    return 0;
}