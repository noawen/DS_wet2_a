//
// Created by Dell on 04/06/2018.
//

#ifndef DS_WET2_A_CLAN_H
#define DS_WET2_A_CLAN_H

#include "AVLtree.h"
class isBigger_byId_clan;
class isBigger;
class Player;

class Clan {
    int id;
    int num_of_players;
    bool Conquer;
    AvlTree<int,isBigger> players_tree;

public:
    Clan();

    Clan(int id);

    int getId();

    int getNumOfPlayers();

    void setNumOfPlayers();

    bool isConquered();

    void setNumOfPlayers(int num);

    /////
    void setPlayersTree (AvlTree <int,isBigger>& tree);

    AvlTree <int,isBigger>& getPalyersTree();
/////

    Clan&operator=(const Clan& clan);

    bool operator== (Clan& clan);

    int operator%(int n);

    ~Clan() ;

};


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



#endif //DS_WET2_A_CLAN_H
