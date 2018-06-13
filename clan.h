//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_CLAN_H
#define DS_WET2_A_CLAN_H

#include "AVLtree.h"
#include "player.h"
#include "rankTree.h"
class heapNode;
class isBigger_byId_clan;
class is_bigger_by_score_player;
class isBigger;
class Player;

class Clan{

    int id;
    int num_of_players;
    bool conquer;
    rankTree<Player,is_bigger_by_score_player> players_tree;
    heapNode* clanInHeap;

public:
    Clan();

    Clan(int id);

    int getId();

    int getNumOfPlayers();

    void setNumOfPlayers();

    heapNode* getClanInHeap();

    void setConquered();

    bool isConquered();

    void setNumOfPlayers(int num);

    int getHeapIndex();

    //void setHeapIndex(int new_index);

    void setClanInHeap(heapNode* clanInHeap);

    /////
    void setPlayersTree (rankTree<Player,is_bigger_by_score_player>& tree);

    friend std::ostream& operator<<(std::ostream& output,  Clan& clan);



    rankTree<Player,is_bigger_by_score_player>& getPlayersTree();
/////

    Clan&operator=(const Clan& clan);

    bool operator== (Clan& clan);

    int operator%(int n);

    ~Clan() ;

};


/*
class isBigger_byId_clan {
public:
    int operator()(Clan* a, Clan* b) {
        if ((*a).getId() < (*b).getId()) {
            return -1;
        }
        if ((*a).getId() > (*b).getId()) {
            return 1;
        }
        return 0;
    }
};

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
*/


#endif //DS_WET2_A_CLAN_H


