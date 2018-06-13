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

    if (!clanIDs){
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
    if ((score < 0) || (playerID < 0) || (clan < 0) ){
        throw INVALID_INPUT_OASIS();
    }
    Clan clan_to_find  = Clan (clan);
    if(! (this->clans_hash.contain(clan_to_find))) {
        throw FAILURE_OASIS();
    }
    try{
        Player new_player = Player(playerID,score);
        this->all_players_by_id.insert(&new_player);
        this->clans_hash.find(clan_to_find).operator*().setNumOfPlayers();
        this->clans_hash.find(clan_to_find).operator*().getPlayersTree().insert(&new_player,score);
        //Clan clan_tst = this->clans_hash.find(clan_to_find).operator*();
    }
    catch(FAILURE_TREE&){
        throw (FAILURE_OASIS());
    }
    catch(ELEMENT_NOT_FOUND_HASH&){
        throw (FAILURE_OASIS());
    }
}

void Oasis::clanFight(int clan1, int clan2, int k1, int k2) {
    if (clan1 < 0 || clan2 < 0 || k1 <= 0 || k2 <= 0) {
        throw INVALID_INPUT_OASIS();
    }
    Clan clan_to_find1 = Clan(clan1);
    Clan clan_to_find2 = Clan(clan2);
    if ((!(this->clans_hash.contain(clan_to_find1))|| !(this->clans_hash.contain(clan_to_find2)))){
        throw FAILURE_OASIS();
    }
    try {

        Clan found_clan1 = this->clans_hash.find(clan_to_find1).operator*();
        Clan found_clan2 = this->clans_hash.find(clan_to_find2).operator*();
        if (found_clan1.getNumOfPlayers() < k1 || found_clan2.getNumOfPlayers() < k2 || clan1 == clan2 || found_clan1.isConquered() ||found_clan2.isConquered() ) {
            throw FAILURE_OASIS();
        }
        int ptr1=0;
        int ptr2=0;
        found_clan1.getPlayersTree().select(found_clan1.getNumOfPlayers() - (k1 -1), &ptr1);
        found_clan2.getPlayersTree().select(found_clan2.getNumOfPlayers() - (k2-1), &ptr2);
        if (ptr1 > ptr2 || (ptr1 == ptr2 && clan2 > clan1)) {
            this->clans_hash.find(found_clan2).operator*().setConquered();
            this->min_heap.decKey(found_clan2.getClanInHeap(), -1);
            this->min_heap.delMin();
        } else {
            if (ptr2 > ptr1 || (ptr1 == ptr2 && clan1 > clan2)) {
                this->clans_hash.find(found_clan1).operator*().setConquered();
                this->min_heap.decKey(found_clan1.getClanInHeap(), -1);
                this->min_heap.delMin();
            }
        }
    }
    catch (ELEMENT_NOT_FOUND_HASH &) {
        throw (FAILURE_OASIS());
    }
    catch (FAILURE_RANK_TREE &) {
        throw (FAILURE_OASIS());
    }
    catch (FAILURE_MIN_HEAP &) {
        throw (FAILURE_OASIS());
    }
}

void Oasis::getMinClan(int *clan) {
    if (clan == NULL){
        throw INVALID_INPUT_OASIS();
    }
    try{
        *clan = this->min_heap.min();
    }
    catch(FAILURE_MIN_HEAP&){
        throw (FAILURE_OASIS());
    }
}

Oasis::~Oasis() {
}



