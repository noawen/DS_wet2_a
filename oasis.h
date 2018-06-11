//
// Created by Dell on 10/06/2018.
//

#ifndef DS_WET2_A_OASIS_H
#define DS_WET2_A_OASIS_H

#include "clan.h"
#include "player.h"
#include "AVLtree.h"
#include "minHeap.h"
#include "rankTree.h"
#include "hash.h"

class OasisExceptions{};
class FAILURE_OASIS:             public OasisExceptions{};
class ALLOCATION_ERROR_OASIS:    public OasisExceptions{};
class INVALID_INPUT_OASIS:       public OasisExceptions{};

class Oasis {
    int tot_num_of_players;
    AvlTree<Player, is_bigger_by_id_player> all_players_by_id;
    Hash<Clan> clans_hash;
    Heap min_heap;

public:

    Oasis(int n, int* clanIDs);

    void addClan(int clanID);

    void addPlayer(int playerID, int score, int clan);

    void clanFight(int clan1, int clan2, int k1, int k2);

    void getMinClan(int* clan);

    ~Oasis();

};


#endif //DS_WET2_A_OASIS_H
