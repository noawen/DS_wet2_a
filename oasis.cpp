//
// Created by Dell on 10/06/2018.
//

#include "oasis.h"
#include "hash.h"
using std::cout;
using std::endl;

Oasis::Oasis(int n, int* clanIDs) :
        min_heap(n){
    if(n < 2){
        throw INVALID_INPUT_OASIS();
    }
    this->clans_hash = Hash<Clan>(n);
    Clan* clans_ptr[n];
    Clan clan_to_insert;
    for(int i = 0; i < n; i++){
        if(clanIDs[i] < 0){
            throw INVALID_INPUT_OASIS();
        }
        clan_to_insert = Clan(clanIDs[i]);
        clans_hash.insert(clan_to_insert);
        clans_ptr[i] = this->clans_hash.find_ptr(clan_to_insert);
    }
    this->min_heap.Heap_create(n,clanIDs,clans_ptr);
    this->all_players_by_id = AvlTree<Player,is_bigger_by_id_player>();
    this->tot_num_of_players = 0;
}


void Oasis::addClan(int clanID) {
    try{
        if (clanID < 0){
            throw INVALID_INPUT_OASIS();
        }
        Clan clan_to_insert(clanID);
        this->clans_hash.insert(clan_to_insert);
        Clan *clan_ptr = this->clans_hash.find_ptr(clanID);
        this->min_heap.insert(clanID,clan_ptr);
    }
    catch(ELEMENT_ALREADY_EXIST_HASH&){
        throw (FAILURE_OASIS());
    }
    catch(ELEMENT_NOT_FOUND_HASH&){
        throw (FAILURE_OASIS());
    }
    catch(FAILURE_MIN_HEAP&){
        throw (FAILURE_OASIS());
    }
}

void Oasis::addPlayer(int playerID, int score, int clan) {
    if ((score < 0) || (playerID < 0) ){
        throw INVALID_INPUT_OASIS();
    }
    try{
        Player new_player = Player(playerID);
        this->all_players_by_id.insert(&new_player);
        Clan clan_to_find  = Clan (clan);
        this->clans_hash.find(clan_to_find).operator*().getPlayersTree().insert(&new_player,score);
    }
    catch(FAILURE_TREE&){
        throw (FAILURE_OASIS());
    }
    catch(FAILURE_TREE&){
        throw (FAILURE_OASIS());
    }
}
/*
void Oasis::clanFight(int clan1, int clan2, int k1, int k2) {
    try{

    }
    catch(&){
        throw ();
    }
}

void Oasis::getMinClan( int* clan) {
    try{

    }
    catch(&){
        throw ();
    }
}
*/
Oasis::~Oasis() {
}



