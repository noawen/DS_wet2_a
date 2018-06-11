#include "clan.h"

//
// Created by Dell on 04/06/2018.
//

Clan::Clan() {
    this->id = 0;
    this->num_of_players = 0;
    this->conquer = false;
    this->players_tree =  rankTree<Player , is_bigger_by_score_player>();
    this->clanInHeap = NULL;
}

Clan::Clan(int id){
    this->id = id;
    this->num_of_players = 0;
    this->conquer = false;
    this->players_tree =  rankTree<Player , is_bigger_by_score_player>();
    this->clanInHeap = NULL;
}

int Clan::getId() {
    if (!this)
        return 0;
    return this->id;
}

void Clan::setPlayersTree(rankTree<Player , is_bigger_by_score_player>& tree) {
    if (!this)
        return;
    this->players_tree = tree;
}

heapNode* Clan::getClanInHeap() {
    if (!this)
        return nullptr;
    return clanInHeap;
}

rankTree<Player , is_bigger_by_score_player>& Clan ::getPlayersTree(){
    // if (!this)
    // return NULL;
    return this->players_tree;
}

void Clan::setClanInHeap(heapNode* clanInHeap) {//MAYBE NEW IS NEEDED
    if (!this)
        return;
    this->clanInHeap = clanInHeap;
}

int Clan::operator%(int n){
    return this->id % n;
}

bool Clan::operator== (Clan& clan){
    return (this->id == clan.id);
}

Clan& Clan::operator=(const Clan& clan){
    this->id = clan.id;
    this->num_of_players = clan.num_of_players;
    this->players_tree = clan.players_tree;
    this->conquer = clan.conquer;
    this->clanInHeap = clan.clanInHeap;
    return *this;
}


std::ostream& operator<<(std::ostream& os,  Clan& cl) {
    os << "id:" << cl.getId();
    return os;
}

Clan::~Clan() {
}

