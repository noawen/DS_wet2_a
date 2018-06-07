#include "clan.h"

//
// Created by Dell on 04/06/2018.
//

Clan::Clan() {
    this->id = 0;
    this->num_of_players = 0;
    this->Conquer = false;
    this->players_tree =  AvlTree<int , isBigger>();
}

Clan::Clan(int id){
    this->id = id;
    this->num_of_players = 0;
    this->Conquer = false;
    this->players_tree =  AvlTree<int , isBigger>();
}

int Clan::getId() {
    if (!this)
        return 0;
    return this->id;
}

void Clan::setPlayersTree(AvlTree<int, isBigger>& tree) {
    if (!this)
        return;
    this->players_tree = tree;
}

AvlTree<int,isBigger>& Clan ::getPalyersTree(){
   // if (!this)
       // return NULL;
    return this->players_tree;
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
    this->Conquer = clan.Conquer;
    return *this;
}


Clan::~Clan() {
    //if (this->players_tree.getRoot() != NULL) {
       // delete this->players_tree;
   // }
    //this->players_tree = nullptr;
}